#include "../../include/rm_behave/sb.h"
#include "../../include/rm_behave/actions.h"
#include "../../include/rm_behave/is_actions.h"
#include "../../include/rm_behave/force_timeout.h"
// #include "../../include/rm_behave/goal.h"
#include <iostream>
#include <memory>
#include <string>


#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/json_export.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_cpp/utils/shared_library.h"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AutoFSM>();
    // initializeAndStorePose();
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<IsMsgOk>("IsMsgOk");
    factory.registerNodeType<IsGameStart>("IsGameStart");
    factory.registerNodeType<IsGameOver>("IsGameOver");
    factory.registerNodeType<Is_Hp_Full>("Is_Hp_Full");
    factory.registerNodeType<Is_Hp_Low>("Is_Hp_Low");
    factory.registerNodeType<IsRotate>("IsRotate");
    factory.registerNodeType<Is_onlyone_sb>("Is_onlyone_sb");
    factory.registerNodeType<Is_onlyone_without_sb>("Is_onlyone_without_sb");
    factory.registerNodeType<Is_First_Begin>("Is_First_Begin");
    factory.registerNodeType<Is_Can_Shoot>("Is_Can_Shoot");
    factory.registerNodeType<SendGoal>("SendGoal");
    factory.registerNodeType<SendGoal>("Home");
    factory.registerNodeType<Rotate>("Rotate");
    factory.registerNodeType<Attack>("Attack");
    factory.registerNodeType<ScanEnermy>("ScanEnermy");
    //
    BT::NodeBuilder builder = [](const std::string& name, const BT::NodeConfiguration& config) {
    return std::make_unique<ForceSuccessOnTimeout>(name, config);};
    factory.registerBuilder<ForceSuccessOnTimeout>("ForceSuccessOnTimeout", builder);
    //
    BT::NodeBuilder builder_topic = [](const std::string& name, const BT::NodeConfiguration& config) {
    return std::make_unique<ForceSuccessOnTimeout_topic>(name, config);};
    factory.registerBuilder<ForceSuccessOnTimeout_topic>("ForceSuccessOnTimeout_topic", builder_topic);
    BT::NodeBuilder builder_game = [](const std::string& name, const BT::NodeConfiguration& config) {
    return std::make_unique<ForceSuccessOnTimeout_game>(name, config);};
    factory.registerBuilder<ForceSuccessOnTimeout_game>("ForceSuccessOnTimeout_game", builder_game);
    auto tree = factory.createTreeFromFile("/home/ansel/pb_rmsimulation-master/src/rm_behave/tree/6d6.xml");
    // 运行行为树主循环
    const unsigned port = 1667;
    BT::Groot2Publisher publisher(tree, port);
    while (rclcpp::ok())
    {
        tree.tickWhileRunning();        
        rclcpp::spin_some(node);  // 处理ROS回调
        // 可以添加适当的休眠时间或其他逻辑
    }
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}