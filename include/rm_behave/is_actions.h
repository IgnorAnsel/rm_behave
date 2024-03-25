#ifndef IS_ACTIONS_H
#define IS_ACTIONS_H
#include <behaviortree_cpp/action_node.h>

class IsMsgOk : public BT::SyncActionNode
{
public:
    IsMsgOk(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class IsGameStart : public BT::SyncActionNode
{
public:
    IsGameStart(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class IsGameOver : public BT::SyncActionNode
{
public:
    IsGameOver(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class Is_Hp_Low : public BT::SyncActionNode
{
public:
    Is_Hp_Low(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class Is_Hp_Full : public BT::SyncActionNode
{
public:
    Is_Hp_Full(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class IsRotate : public BT::SyncActionNode
{
public:
    IsRotate(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};
class Is_onlyone_sb : public BT::SyncActionNode
{
public:
    Is_onlyone_sb(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class Is_onlyone_without_sb : public BT::SyncActionNode
{
public:
    Is_onlyone_without_sb(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

class Is_First_Begin : public BT::SyncActionNode
{
public:
    Is_First_Begin(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};
class Is_Can_Shoot : public BT::SyncActionNode
{
public:
    Is_Can_Shoot(const std::string &name) : BT::SyncActionNode(name, {}) {}

private:
    BT::NodeStatus tick() override;
};

#endif // IS_ACTIONS_H