#ifndef SB_H
#define SB_H
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rm_decision_interfaces/msg/robot_status.hpp"
#include "rm_decision_interfaces/msg/friend_location.hpp"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"
// #include "rm_decision_interfaces/msg/armor.hpp"
#include "rm_decision_interfaces/msg/rfid.hpp"
#include "rm_decision_interfaces/msg/game_status.hpp"
#include "rm_decision_interfaces/msg/enermy.hpp"
#include <chrono>
#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <yaml-cpp/yaml.h>
#include <filesystem>
class AutoFSM : public rclcpp::Node
{
public:
    AutoFSM() : Node("sbauto"){
    // 订阅裁判系统信息
    robot_status_sub_ = this->create_subscription<rm_decision_interfaces::msg::RobotStatus>(
        "/robot_status", 1, std::bind(&AutoFSM::robotStatusCallback, this, std::placeholders::_1));
    // 也许取消下面这个能降低负担？
    // 联盟赛唯有根据血量来判断是否进攻对面基地时才使用
    robot_hp_sub_ = this->create_subscription<rm_decision_interfaces::msg::AllRobotHP>(
        "/robot_hp", 1, std::bind(&AutoFSM::robotHpCallback, this, std::placeholders::_1));
    // enemy_locate_sub_ = this->create_subscription<rm_decision_interfaces::msg::FriendLocation>(
    //     "/friend_location", 1, std::bind(&AutoFSM::enemyLocateCallback, this, std::placeholders::_1)); // 联盟赛不需要
    // armor_sub_ = this->create_subscription<rm_decision_interfaces::msg::Armor>(
    //     "/detector/armors", 1, std::bind(&AutoFSM::armorCallback, this, std::placeholders::_1)); // 暂时不需要
    // rfid_sub_ = this->create_subscription<rm_decision_interfaces::msg::RFID>(
    //     "/rfid", 1, std::bind(&AutoFSM::rfidCallback, this, std::placeholders::_1)); // 可要可不要
    game_status_sub_ = this->create_subscription<rm_decision_interfaces::msg::GameStatus>(
        "/game_status", 1, std::bind(&AutoFSM::gameStatusCallback, this, std::placeholders::_1));
    enemy_sub_ = this->create_subscription<rm_decision_interfaces::msg::Enermy>(
        "/enermy", 1, std::bind(&AutoFSM::enermyCallback, this, std::placeholders::_1));
    // 需要接收的话题  联盟赛：机器人血量 机器人状态 游戏状态 （场地交互信息）
    //               对抗赛：机器人血量 机器人状态 位置信息 游戏状态 场地交互信息
    //对抗赛再说： topics_received_ = {{"/robot_hp", false}, {"/robot_status", false}, {"/friend_location", false}, /*{"/detector/armors", false}*/{"/game_status", false}, {"/rfid", false}};// 定义的所有话题集，用于判断是否所有话题接入
    // 联盟赛：其实最主要就是一个信息 自身机器人状态 次主要是游戏状态 全局机器人血量不太有必要
    topics_received_ = {{"/robot_hp", false}, {"/robot_status", false}, {"/friend_location", true}, /*{"/detector/armors", false}*/{"/game_status", false}, {"/rfid", true}};// 定义的所有话题集，用于判断是否所有话题接入
    check_all_topics_received(); // 等待初始化消息
                };
    ~AutoFSM(){};
    // void readYaml();

private:
    void robotHpCallback(const rm_decision_interfaces::msg::AllRobotHP::SharedPtr msg); // 接收全部机器人血量回调
    void robotStatusCallback(const rm_decision_interfaces::msg::RobotStatus::SharedPtr msg); // 接收当前机器人信息回调
    void enemyLocateCallback(const rm_decision_interfaces::msg::FriendLocation::SharedPtr msg); // 接收部分位置信息回调
    // void armorCallback(const rm_decision_interfaces::msg::Armor::SharedPtr msg); // 自瞄启动
    void rfidCallback(const rm_decision_interfaces::msg::RFID::SharedPtr msg); // 
    void gameStatusCallback(const rm_decision_interfaces::msg::GameStatus::SharedPtr msg); // 游戏状态回调
    void enermyCallback(const rm_decision_interfaces::msg::Enermy::SharedPtr msg); // 敌人回调
    void check_all_topics_received();// 检查所有话题是否接收
    std::string join(const std::vector<std::string> &vec, const std::string &delim);//辅助添加
    
    rclcpp::Subscription<rm_decision_interfaces::msg::AllRobotHP>::SharedPtr robot_hp_sub_;
    rclcpp::Subscription<rm_decision_interfaces::msg::RobotStatus>::SharedPtr robot_status_sub_;
    rclcpp::Subscription<rm_decision_interfaces::msg::FriendLocation>::SharedPtr enemy_locate_sub_;\
    rclcpp::Subscription<rm_decision_interfaces::msg::GameStatus>::SharedPtr game_status_sub_;
    // rclcpp::Subscription<rm_decision_interfaces::msg::Armor>::SharedPtr armor_sub_;
    rclcpp::Subscription<rm_decision_interfaces::msg::RFID>::SharedPtr rfid_sub_; 
    rclcpp::Subscription<rm_decision_interfaces::msg::Enermy>::SharedPtr enemy_sub_;
    std::unordered_map<std::string, bool> topics_received_; // 定义的所有话题集，用于判断是否所有话题接入

    // 决定哨兵行为的信息
    int Robot_id;
    int Current_hp;
    int Shooter_heat;
    int RFID_id;
    int Armor_id;
    int Follow_robot_id;
    int Robot_status;
};
#endif // SB_H
