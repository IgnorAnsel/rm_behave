#include <behaviortree_cpp/action_node.h>
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <behaviortree_cpp/bt_factory.h>
class RotateAction : public BT::SyncActionNode
{
public:
    RotateAction(const std::string& name) : BT::SyncActionNode(name, {})
    {
        cmd_vel_pub_ = node_->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

    BT::NodeStatus tick() override
    {
        // 发布旋转指令
        geometry_msgs::msg::Twist twist;
        twist.angular.z = 0.5;  // 角速度为0.5 rad/s，可以根据需要调整
        cmd_vel_pub_->publish(twist);

        // 模拟一段时间的旋转
        rclcpp::sleep_for(std::chrono::seconds(2));

        // 发布停止指令
        twist.angular.z = 0.0;
        cmd_vel_pub_->publish(twist);

        return BT::NodeStatus::SUCCESS;
    }

private:
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("rotate_action_node");
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};
class GoaheadlAction : public BT::SyncActionNode
{
public:
    GoaheadlAction(const std::string& name) : BT::SyncActionNode(name, {})
    {
        cmd_vel_pub_ = node_->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

    BT::NodeStatus tick() override
    {
        // 发布前进指令
        geometry_msgs::msg::Twist twist;
        twist.linear.x = 0.5;  // 线速度为0.5 m/s，可以根据需要调整
        cmd_vel_pub_->publish(twist);
        // 模拟一段时间的前进
        rclcpp::sleep_for(std::chrono::seconds(2));
        // 发布停止指令
        twist.linear.x = 0.0;
        cmd_vel_pub_->publish(twist);
        return BT::NodeStatus::SUCCESS;
    }

private:
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("goahead_action_node");
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<RotateAction>("RotateAction");
    factory.registerNodeType<GoaheadlAction>("GoaheadAction");
    auto tree = factory.createTreeFromFile("/home/ansel/pb_rmsimulation/src/rm_behaviortree/src/behaviortree/behaviortree_rotation_goahead.xml");

    // 运行行为树主循环
    while (rclcpp::ok())
    {
        tree.tickWhileRunning();        
        //rclcpp::spin_some(tree.node());  // 处理ROS回调
        // 可以添加适当的休眠时间或其他逻辑
    }

    rclcpp::shutdown();
    return 0;
}
