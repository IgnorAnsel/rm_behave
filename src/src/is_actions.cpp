#include "../../include/rm_behave/is_actions.h"
#include "../../include/rm_behave/define_flag.h"
BT::NodeStatus IsMsgOk::tick()
{
    if(is_topic_ok)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus IsGameStart::tick()
{
    if(Remain_time <= 0)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus IsGameOver::tick()
{
    if(is_game_over)
        return BT::NodeStatus::FAILURE;
    else
        return BT::NodeStatus::SUCCESS;
}
BT::NodeStatus Is_Hp_Low::tick()
{
    if(current_hp<=300)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus Is_Hp_Full::tick()
{
    if(current_hp>=550)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus IsRotate::tick()
{
    if(Is_Rotate)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus Is_onlyone_sb::tick()
{
    if(Is_Onlyone_SB)
        return BT::NodeStatus::SUCCESS;
    else    
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus Is_onlyone_without_sb::tick()
{
    if(Is_Onlyone_without_SB)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus Is_First_Begin::tick()
{
    if(Is_First_Begin_flag)
    {
        Is_First_Begin_flag = false;
        return BT::NodeStatus::SUCCESS;
    }
    else
        return BT::NodeStatus::FAILURE;
}
BT::NodeStatus Is_Can_Shoot::tick()
{
    if(Is_Can_Shoot_flag)
        return BT::NodeStatus::SUCCESS;
    else
        return BT::NodeStatus::FAILURE;
}