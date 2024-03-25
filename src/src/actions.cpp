#include "../../include/rm_behave/actions.h"
#include "../../include/rm_behave/define_flag.h"
#include <vector>
void SendGoal::sendGoal()
{
  // 发送目标点
  // 等待导航动作服务器上线，等待时间为5秒

  while (!action_client_->wait_for_action_server(std::chrono::seconds(5)))
  {
    RCLCPP_INFO(node_->get_logger(), "等待Action服务上线。");
  }
  // 设置导航目标点
  is_nav2_ok = true;
  auto goal_msg = NavigationAction::Goal();
  float goal_x = 2, goal_y = 2, goal_z = 0;
  auto res = getInput<std::string>("goal_pose");
  RCLCPP_INFO(node_->get_logger(), "goal_pose: %s", res.value().c_str());
  if (res)
  {
    std::string goal_pose = res.value();
    RCLCPP_INFO(node_->get_logger(), "goal_pose: %s", goal_pose.c_str());
    std::vector<std::string> tokens; // 用于存储分割后的字符串
    std::stringstream ss(goal_pose);
    std::string item;
    // 使用分号作为分隔符分割字符串
    while (std::getline(ss, item, ';'))
    {
      tokens.push_back(item);
    }
    // 转换字符串为相应的数值类型并分配给目标变量
    if (tokens.size() >= 3)
    { // 确保有足够的分割后的数据
      goal_x = std::stod(tokens[0]);
      goal_y = std::stod(tokens[1]);
      goal_z = std::stod(tokens[2]);
      
    }
  }
  goal_msg.pose.header.stamp = node_->get_clock()->now();
  goal_msg.pose.header.frame_id = "map";
  goal_msg.pose.pose.position.x = goal_x;
  goal_msg.pose.pose.position.y = goal_y;
  goal_msg.pose.pose.position.z = goal_z;
  RCLCPP_INFO(node_->get_logger(), "发送目标点：%f, %f, %f", goal_x, goal_y, goal_z);
  auto send_goal_options =
      rclcpp_action::Client<NavigationAction>::SendGoalOptions();
  // 设置请求目标结果回调函数
  send_goal_options.goal_response_callback =
      [this](NavigationActionGoalHandle::SharedPtr goal_handle)
  {
    if (goal_handle)
    {
      is_nav2_ok = true;
      RCLCPP_INFO(node_->get_logger(), "目标点已被服务器接收");
    }
  };
  // 设置移动过程反馈回调函数
  send_goal_options.feedback_callback =
      [this](
          NavigationActionGoalHandle::SharedPtr goal_handle,
          const std::shared_ptr<const NavigationAction::Feedback> feedback)
  {
    (void)goal_handle; // 假装调用，避免 warning: unused
    RCLCPP_INFO(node_->get_logger(), "反馈剩余距离:%f",
                feedback->distance_remaining);
  };
  // 设置执行结果回调函数
  send_goal_options.result_callback =
      [this](const NavigationActionGoalHandle::WrappedResult &result)
  {
    if (result.code == rclcpp_action::ResultCode::SUCCEEDED)
    {
      RCLCPP_INFO(node_->get_logger(), "处理成功！");
    }
  };
  // 发送导航目标点
  action_client_->async_send_goal(goal_msg, send_goal_options);
  rclcpp::spin_some(node_); // 处理ROS回调
}

BT::NodeStatus SendGoal::tick()
{
  sendGoal();
  if (is_nav2_ok)
  {
    RCLCPP_INFO(node_->get_logger(), "ok");
    return BT::NodeStatus::SUCCESS;
  }
  else
    return BT::NodeStatus::FAILURE;
}
BT::NodeStatus Rotate::tick()
{
  auto res = getInput<bool>("rotate");
  rm_decision_interfaces::msg::HyPub msg;
  if (res)
    msg.is_rotate = res.value();
  else
    msg.is_rotate = res.value();
  cmd_rotate_pub_->publish(msg);
  return BT::NodeStatus::SUCCESS;
}
BT::NodeStatus Attack::tick()
{
  auto res = getInput<bool>("attack");
  rm_decision_interfaces::msg::HyPub msg;
  if (res)
    {
      if(res.value())
      {
        if(Is_Can_Attack_1)
          msg.is_attack1 = true;
        if(Is_Can_Attack_2)
          msg.is_attack2 = true;
      }
      else
      {
        msg.is_attack1 = false;
        msg.is_attack2 = false;
      }
    }
  cmd_attack_pub_->publish(msg);
  return BT::NodeStatus::SUCCESS;
}
BT::NodeStatus ScanEnermy::tick()
{
  return BT::NodeStatus::SUCCESS;
}