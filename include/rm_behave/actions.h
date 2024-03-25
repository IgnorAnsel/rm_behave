#ifndef ACTIONS_H
#define ACTIONS_H
#include <behaviortree_cpp/action_node.h>
#include "sb.h"
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav2_msgs/action/navigate_to_pose.hpp>
#include "rclcpp_action/rclcpp_action.hpp" // 导入ROS 2的C++ Action客户端库
#include "rm_decision_interfaces/msg/hy_pub.hpp"
using NavigationAction = nav2_msgs::action::NavigateToPose; // 定义导航动作类型为NavigateToPose

class SendGoal : public BT::SyncActionNode
{
public:
    using NavigationActionClient = rclcpp_action::Client<NavigationAction>;               // 定义导航动作客户端类型
    using NavigationActionGoalHandle = rclcpp_action::ClientGoalHandle<NavigationAction>; // 定义导航动作目标句柄类型
    SendGoal(const std::string &name, const BT::NodeConfiguration &config) : BT::SyncActionNode(name, config)
    {
        action_client_ = rclcpp_action::create_client<NavigationAction>(node_, "navigate_to_pose");
        
    }
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("goal_pose")};
    }
    void sendGoal();

    NavigationActionClient::SharedPtr action_client_;
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("navigate_to_pose_node");

private:
    BT::NodeStatus tick() override;
};

class Rotate : public BT::SyncActionNode
{
public:
    Rotate(const std::string &name, const BT::NodeConfiguration &config) : BT::SyncActionNode(name, config)
    {
        cmd_rotate_pub_ = node_->create_publisher<rm_decision_interfaces::msg::HyPub>("/HyPub", 10);
    }
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<bool>("rotate")};
    }

private:
    BT::NodeStatus tick() override;
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("rotate_action_node");
    rclcpp::Publisher<rm_decision_interfaces::msg::HyPub>::SharedPtr cmd_rotate_pub_;
};
class Attack : public BT::SyncActionNode
{
public:
    Attack(const std::string &name, const BT::NodeConfiguration &config) : BT::SyncActionNode(name, config)
    {
        cmd_attack_pub_ = node_->create_publisher<rm_decision_interfaces::msg::HyPub>("/HyPub", 10);
    }
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<bool>("attack")};
    }

private:
    BT::NodeStatus tick() override;
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("attack_action_node");
    rclcpp::Publisher<rm_decision_interfaces::msg::HyPub>::SharedPtr cmd_attack_pub_;
};
class ScanEnermy : public BT::SyncActionNode
{
public:
    ScanEnermy(const std::string &name) : BT::SyncActionNode(name, {})
    {
        cmd_scan_pub_ = node_->create_publisher<rm_decision_interfaces::msg::HyPub>("/HyPub", 10);
    }

private:
    BT::NodeStatus tick() override;
    rclcpp::Node::SharedPtr node_ = rclcpp::Node::make_shared("scan_enermy_action_node");
    rclcpp::Publisher<rm_decision_interfaces::msg::HyPub>::SharedPtr cmd_scan_pub_;
};
#endif // ACTIONS_H