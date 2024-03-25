#include <behaviortree_cpp/action_node.h>
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include <sensor_msgs/msg/laser_scan.hpp>
// #include "rm_decision_interfaces/msg/robot_status.h"
class ObstacleDetected : public BT::SyncActionNode
{
public:
    ObstacleDetected(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config),
          node_(rclcpp::Node::make_shared("obstacle_detected_node"))
    {
        subscriber_ = node_->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&ObstacleDetected::scanCallback, this, std::placeholders::_1));
        self_subscriber_ = node_->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&ObstacleDetected::scanCallback, this, std::placeholders::_1));
    }

    BT::NodeStatus tick() override
    {
        if (obstacle_detected_)
        {
            RCLCPP_INFO(node_->get_logger(), "Obstacle detected!");
            return BT::NodeStatus::SUCCESS; 
        }
        else
        {
            return BT::NodeStatus::FAILURE;
        }
    }

    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        RCLCPP_INFO(node_->get_logger(), "Range: %zu", msg->ranges.size());
        for (auto range : msg->ranges)
        {
            if (range < safety_distance_)
            {
                obstacle_detected_ = true;
                return;
            }
        }
        obstacle_detected_ = false;
    }

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<double>("safety_distance") };
    }

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr self_subscriber_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscriber_;
    bool obstacle_detected_ = false;
    double safety_distance_ = 5; 
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
        // RCLCPP_INFO(node_->get_logger(), "SUCCESS!");
        return BT::NodeStatus::SUCCESS;
    }

private:
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("goahead_action_node");
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("bt_runner_node");
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<GoaheadlAction>("GoaheadAction");
    factory.registerNodeType<ObstacleDetected>("ObstacleDetection");
    auto tree = factory.createTreeFromFile("/home/ansel/pb_rmsimulation/src/rm_behaviortree/src/behaviortree/auto.xml");

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
