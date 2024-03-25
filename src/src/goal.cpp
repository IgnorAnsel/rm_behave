// #include "../../include/rm_behave/goal.h"
// #include "rclcpp/rclcpp.hpp"

// std::shared_ptr<BT::Blackboard> blackboard = std::make_shared<BT::Blackboard>();
// std::shared_ptr<geometry_msgs::msg::PoseStamped> aim_supply_pose = std::make_shared<geometry_msgs::msg::PoseStamped>();
// std::shared_ptr<geometry_msgs::msg::PoseStamped> my_supply_pose = std::make_shared<geometry_msgs::msg::PoseStamped>();
// std::shared_ptr<geometry_msgs::msg::PoseStamped> aim_pose = std::make_shared<geometry_msgs::msg::PoseStamped>();
// std::shared_ptr<geometry_msgs::msg::PoseStamped> base_pose = std::make_shared<geometry_msgs::msg::PoseStamped>();
// // 初始化和存储逻辑可以放在某个函数或者类的方法中
// void initializeAndStorePose()
// {
//     aim_supply_pose->header.frame_id = "map";
//     aim_supply_pose->header.stamp = rclcpp::Clock().now();
//     aim_supply_pose->pose.position.x = 3.82;
//     aim_supply_pose->pose.position.y = -1.72;
//     // aim_supply_pose->pose.position.z = 0.0;
//     // aim_supply_pose->pose.orientation.x = 0.0;
//     // aim_supply_pose->pose.orientation.y = 0.0;
//     // aim_supply_pose->pose.orientation.z = 0.0;
//     // aim_supply_pose->pose.orientation.w = 1.0;
//     my_supply_pose->header.frame_id = "map";
//     my_supply_pose->header.stamp = rclcpp::Clock().now();
//     my_supply_pose->pose.position.x = -2.48;
//     my_supply_pose->pose.position.y = 3.97;
//     // my_supply_pose->pose.position.z = 0.0;
//     // my_supply_pose->pose.orientation.x = 0.0;
//     // my_supply_pose->pose.orientation.y = 0.0;
//     // my_supply_pose->pose.orientation.z = 0.0;
//     // my_supply_pose->pose.orientation.w = 1.0;
//     aim_pose->header.frame_id = "map";
//     aim_pose->header.stamp = rclcpp::Clock().now();
//     aim_pose->pose.position.x = 4.01;
//     aim_pose->pose.position.y = 2.62;
//     // my_supply_pose->pose.position.z = 0.0;
//     // my_supply_pose->pose.orientation.x = 0.0;
//     // my_supply_pose->pose.orientation.y = 0.0;
//     // my_supply_pose->pose.orientation.z = 0.0;
//     // my_supply_pose->pose.orientation.w = 1.0;
//     base_pose->header.frame_id = "map";
//     base_pose->header.stamp = rclcpp::Clock().now();
//     base_pose->pose.position.x = 6.01;
//     base_pose->pose.position.y = 1.19;
//     // my_supply_pose->pose.position.z = 0.0;
//     // my_supply_pose->pose.orientation.x = 0.0;
//     // my_supply_pose->pose.orientation.y = 0.0;
//     // my_supply_pose->pose.orientation.z = 0.0;
//     // my_supply_pose->pose.orientation.w = 1.0;

//     blackboard->set("aim_supply_pose", aim_supply_pose);
//     blackboard->set("base_pose", base_pose);
//     blackboard->set("my_supply_pose", my_supply_pose);
//     blackboard->set("aim_pose", aim_pose);
// }