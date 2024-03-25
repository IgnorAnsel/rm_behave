#include "../../include/rm_behave/sb.h"
#include "../../include/rm_behave/define_flag.h"
bool is_topic_ok = false;
bool is_nav2_ok = false;
int current_hp = 600;
int Remain_time;
bool is_game_over = false;
bool Is_Rotate = false;
bool Is_Onlyone_SB = false;
bool Is_Onlyone_without_SB = false;
bool is_game_start = false;
bool nothing = false;
bool Is_First_Begin_flag = true;
bool Is_Can_Shoot_flag = true;
bool Team_color = 0; // 默认红队
bool Is_Can_Attack_1 = true;
bool Is_Can_Attack_2 = true;
int Game_progress = 0;
void AutoFSM::robotHpCallback(const rm_decision_interfaces::msg::AllRobotHP::SharedPtr msg)
{
    // 处理接收到的消息
    // 全局血量
    topics_received_["/robot_hp"] = true; // 已成功接收消息
    int hp_values[] = {
        msg->red_1_robot_hp, msg->red_2_robot_hp, msg->red_3_robot_hp,
        msg->red_4_robot_hp, msg->red_5_robot_hp, msg->red_7_robot_hp,
        msg->red_outpost_hp, msg->red_base_hp,
        msg->blue_1_robot_hp, msg->blue_2_robot_hp, msg->blue_3_robot_hp,
        msg->blue_4_robot_hp, msg->blue_5_robot_hp, msg->blue_7_robot_hp,
        msg->blue_outpost_hp, msg->blue_base_hp};

    std::string names[] = {
        "red 1", "red 2", "red 3", "red 4", "red 5", "red 7",
        "red outpost", "red base",
        "blue 1", "blue 2", "blue 3", "blue 4", "blue 5", "blue 7",
        "blue outpost", "blue base"};

    int num_robots = sizeof(hp_values) / sizeof(hp_values[0]);
    int robot_live = 0; //存活机器人数
    bool sb_robot_live = false; //哨兵是否存活
    Is_Onlyone_SB = false;
    Is_Onlyone_without_SB =false;
        if(!Team_color)// 哨兵是红队的情况
        {
            for (int i = 0; i < num_robots / 2; ++i) // Assuming the second half of the array is the blue team
            {
                if (_SHOW_AllRobotHP_)
                    RCLCPP_INFO(this->get_logger(), "Red Team - %s HP: %d", names[i].c_str(), hp_values[i]);
                if (names[i]!=names[7] && hp_values[i] > 0)
                {
                    RCLCPP_INFO(this->get_logger(), "red robot %s is alive", names[i].c_str());
                    robot_live++;
                    if(names[i] == names[5])
                        sb_robot_live = true;
                    continue;
                }
            }
            RCLCPP_INFO(this->get_logger(), "robot_live: %d", robot_live);
            if (robot_live <= 1)
            {
                if (sb_robot_live)
                    {
                        Is_Onlyone_SB = true;
                        RCLCPP_INFO(this->get_logger(), "just 1 SB");
                    }
                else
                    {
                        Is_Onlyone_SB = false;
                        Is_Onlyone_without_SB = true;
                        RCLCPP_INFO(this->get_logger(), "just 1");
                    }
            }
        }
        else // 哨兵是蓝队的情况
        {
            for (int i = num_robots / 2; i < num_robots; ++i) // Assuming the second half of the array is the blue team
            {
                if (_SHOW_AllRobotHP_)
                    RCLCPP_INFO(this->get_logger(), "Blue Team - %s HP: %d", names[i].c_str(), hp_values[i]);
                if (names[i]!=names[15] && hp_values[i] > 0)
                {
                    RCLCPP_INFO(this->get_logger(), "blue robot %s is alive", names[i].c_str());
                    robot_live++;
                    if(names[i] == names[13])
                        sb_robot_live = true;
                    continue;
                }
            }
            RCLCPP_INFO(this->get_logger(), "robot_live: %d", robot_live);
            if (robot_live <= 1)
            {
                if (sb_robot_live)
                    {
                        Is_Onlyone_SB = true;
                        RCLCPP_INFO(this->get_logger(), "just 1 SB");
                    }
                else
                    {
                        Is_Onlyone_SB = false;
                        Is_Onlyone_without_SB = true;
                        RCLCPP_INFO(this->get_logger(), "just 1");
                    }
            }
        }

    check_all_topics_received();
}

void AutoFSM::robotStatusCallback(const rm_decision_interfaces::msg::RobotStatus::SharedPtr msg)
{
    // 处理接收到的消息
    // 个人信息
    topics_received_["/robot_status"] = true; // 已成功接收消息
    if (_SHOW_RobotStatus_)
    {
        // 机器人ID  1~7->红，101~107->蓝
        RCLCPP_INFO(this->get_logger(), "Robot_id: %d", msg->robot_id);
        // 机器人当前血量
        RCLCPP_INFO(this->get_logger(), "Current_hp: %d", msg->current_hp);
        // 机器人底盘功率
        RCLCPP_INFO(this->get_logger(), "Chassis_power: %f", msg->chassis_power);
        // 机器人1号枪管热量
        RCLCPP_INFO(this->get_logger(), "Shooter_heat: %d", msg->shooter_17mm_1_barrel_heat);
        // 机器人2号枪管热量
        RCLCPP_INFO(this->get_logger(), "Shooter_heat: %d", msg->shooter_17mm_2_barrel_heat);
        // 枪口热量上限
        RCLCPP_INFO(this->get_logger(), "shooter_barrel_heat_limit: %d", msg->shooter_barrel_heat_limit);
        // 17mm弹丸量
        RCLCPP_INFO(this->get_logger(), "Bullet_17mm: %d", msg->projectile_allowance_17mm);
        // 机器人队伍 队伍颜色 0->红 1->蓝
        RCLCPP_INFO(this->get_logger(), "Team_color: %d", msg->team_color);
    }
    current_hp = msg->current_hp;
    Team_color = msg->team_color;
    //判断枪口1热量是否超上限
    if(msg->shooter_17mm_1_barrel_heat < msg->shooter_barrel_heat_limit)
        Is_Can_Attack_1 = true;
    else
        Is_Can_Attack_1 = false;
    //判断枪口2热量是否超上限
    if(msg->shooter_17mm_2_barrel_heat < msg->shooter_barrel_heat_limit)
        Is_Can_Attack_2 = true;
    else
        Is_Can_Attack_2 = false;
    //判断是否有充足弹丸
    if(msg->projectile_allowance_17mm > 0)
        Is_Can_Shoot_flag = true;
    else
        Is_Can_Shoot_flag = false;
    
    check_all_topics_received();
}

void AutoFSM::enemyLocateCallback(const rm_decision_interfaces::msg::FriendLocation::SharedPtr msg)
{
    // 处理接收到的消息
    // 位置信息
    // `hero`: 己方哨兵出生点
    // `engineer`: 能量机关（靠己方）
    // `standard_3`: 己方环形高地
    // `standard_4`: 敌方前哨站
    // `standard_5`: 敌方基地
    topics_received_["/friend_location"] = true; // 已成功接收消息
    if (_SHOW_EnemyLocate_)
    {
        // 哨兵位置
        RCLCPP_INFO(this->get_logger(), "SB location X: %f Y: %f", msg->hero_x, msg->hero_y);
        // 己方能量机关
        RCLCPP_INFO(this->get_logger(), "energy location X: %f Y: %f", msg->engineer_x, msg->engineer_y);
        // 己方环形高地
        RCLCPP_INFO(this->get_logger(), "standard_3 location X: %f Y: %f", msg->standard_3_x, msg->standard_3_y);
        // 敌方前哨站
        RCLCPP_INFO(this->get_logger(), "standard_4 location X: %f Y: %f", msg->standard_4_x, msg->standard_4_y);
        // 敌方基地
        RCLCPP_INFO(this->get_logger(), "standard_5 location X: %f Y: %f", msg->standard_5_x, msg->standard_5_y);
    }
    check_all_topics_received();
}
void AutoFSM::enermyCallback(const rm_decision_interfaces::msg::Enermy::SharedPtr msg)// 已经检查到的敌人回调
{
    // 处理接收到的消息
    // 敌人信息:ID
    std::vector<uint8_t> es1 = msg->enermies_1;
    std::vector<uint8_t> es2 = msg->enermies_2;
    if (_SHOW_enermy_)
    {

    }
}

void AutoFSM::gameStatusCallback(const rm_decision_interfaces::msg::GameStatus::SharedPtr msg)// 游戏状态回调
{
    // 处理接收到的消息
    // 游戏状态
    topics_received_["/game_status"] = true; // 已成功接收消息
    if (_SHOW_GameStatus_)
    {
        // 游戏状态

        RCLCPP_INFO(this->get_logger(), "Game Status: %d", msg->game_progress);
        RCLCPP_INFO(this->get_logger(), "Game Remain Time: %d", msg->stage_remain_time);
    }
    Remain_time = msg->stage_remain_time;
    Game_progress = msg->game_progress;
    if (Game_progress == 4)
        is_game_start = true;
    else
        is_game_start = false;
    // if(Remain_time <= 0)
    //     is_game_start = true;
    check_all_topics_received();
}
// void AutoFSM::armorCallback(const rm_decision_interfaces::msg::Armor::SharedPtr msg)
// {
//     // 处理接收到到的信息
//     // 自瞄
//     topics_received_["/detector/armors"] = true; // 已成功接收消息
//     if (_SHOW_Armor_)
//     {
//         // 瞄准机器人编号
//         RCLCPP_INFO(this->get_logger(), "Armor_id: %s", msg->number.c_str());
//         // 瞄准机器人装甲板类型
//         RCLCPP_INFO(this->get_logger(), "Armor_type: %s", msg->type.c_str());
//         // 离装甲板距离
//         RCLCPP_INFO(this->get_logger(), "Armor_distance: %f", msg->distance_to_image_center);

//         // 姿态
//         // Pose:position
//         RCLCPP_INFO(this->get_logger(), "Armor_position: x:%f y:%f z:%f  ", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
//         // Pose:orientation
//         RCLCPP_INFO(this->get_logger(), "Armor_orientation: x:%f y:%f z:%f w:%f", msg->pose.orientation.x, msg->pose.orientation.y, msg->pose.orientation.z, msg->pose.orientation.w);
//     }
//     check_all_topics_received();
// }
void AutoFSM::rfidCallback(const rm_decision_interfaces::msg::RFID::SharedPtr msg)
{
    // 处理接收到的信息
    // 场地增强RFID
    topics_received_["/rfid"] = true; // 已成功接收消息
    if (_SHOW_RFID_)
    {
        // RFID场地
        RCLCPP_INFO(this->get_logger(), "RFID_id: %d", msg->rfid_patrol_status);
    }
}
std::string AutoFSM::join(const std::vector<std::string> &vec, const std::string &delim)
{
    std::string result;
    for (const auto &str : vec)
    {
        if (!result.empty())
        {
            result += delim;
        }
        result += str;
    }
    return result;
}
void AutoFSM::check_all_topics_received()
{
    if (!is_topic_ok)
    {
        std::vector<std::string> missing_topics;
        for (const auto &topic : topics_received_)
        {
            if (!topic.second)
            {
                missing_topics.push_back(topic.first);
            }
        }

        if (!missing_topics.empty())
        {
            std::string missing_list = join(missing_topics, ", ");
            RCLCPP_WARN(this->get_logger(), "Missing messages from: %s", missing_list.c_str());
        }
        else
        {
            is_topic_ok = true; // 标志所有的话题已经接收到了
            RCLCPP_INFO(this->get_logger(), "All topics have received messages.");
        }
    }
}