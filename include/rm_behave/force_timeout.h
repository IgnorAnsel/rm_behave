#ifndef FORCE_TIMEOUT_H
#define FORCE_TIMEOUT_H
#include "behaviortree_cpp/decorator_node.h"
#include "define_flag.h"

class ForceSuccessOnTimeout : public BT::DecoratorNode
{
public:
    ForceSuccessOnTimeout(const std::string& name, const BT::NodeConfiguration& config)
        : BT::DecoratorNode(name, config),
          _timeout_ms(0)
    {
        setRegistrationID("ForceSuccessOnTimeout"); // 注册ID用于Groot
        initialized_ = false;
    }

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<int>("timeout_ms"),
                  BT::InputPort<std::string>("w_true")};
    }
    virtual BT::NodeStatus tick() override
    {
        if (!initialized_)
        {
            getInput("timeout_ms", _timeout_ms);
            getInput("w_true", w_true_);
            initialized_ = true;
            _start_time = std::chrono::steady_clock::now();
        }

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
        if (elapsed.count() >= _timeout_ms)
        {
            if(w_true_ == "nothing");
            if(w_true_ == "is_topic_ok")
            {
                is_topic_ok = true;
            }
            if(w_true_ == "is_game_start")
            {
                is_game_start = true;
            }
            return BT::NodeStatus::SUCCESS; // 超时则返回成功
        }
        else 
        {
            // std::cout << "ForceSuccessOnTimeout elapsed: " << elapsed.count() << std::endl;
            // std::cout << "ForceSuccessOnTimeout w_true: " << w_true_ << std::endl;
            // std::cout << "ForceSuccessOnTimeout timeout_ms: " << _timeout_ms << std::endl;
        }
        const BT::NodeStatus child_status = child_node_->executeTick();

        // 如果子节点还在运行或已经成功，则继续正常的返回状态
        return child_status;
    }

    virtual void halt() override
    {
        initialized_ = false;
        DecoratorNode::halt();
    }

private:
    std::chrono::steady_clock::time_point _start_time;
    bool initialized_ = false;
    int _timeout_ms;
    std::string w_true_;
};

class ForceSuccessOnTimeout_topic : public BT::DecoratorNode
{
public:
    ForceSuccessOnTimeout_topic(const std::string& name, const BT::NodeConfiguration& config)
        : BT::DecoratorNode(name, config),
          _timeout_ms(0)
    {
        setRegistrationID("ForceSuccessOnTimeout_topic"); // 注册ID用于Groot
        initialized_ = false;
    }

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<int>("timeout_ms"),
                  BT::InputPort<std::string>("w_true")};
    }
    virtual BT::NodeStatus tick() override
    {
        if (!initialized_)
        {
            getInput("timeout_ms", _timeout_ms);
            getInput("w_true", w_true_);
            initialized_ = true;
            _start_time = std::chrono::steady_clock::now();
        }

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
        if (elapsed.count() >= _timeout_ms)
        {
            if(w_true_ == "nothing");
            if(w_true_ == "is_topic_ok")
            {
                is_topic_ok = true;
            }
            if(w_true_ == "is_game_start")
            {
                is_game_start = true;
            }
            return BT::NodeStatus::SUCCESS; // 超时则返回成功
        }
        else 
        {
            // std::cout << "ForceSuccessOnTimeout elapsed: " << elapsed.count() << std::endl;
            // std::cout << "ForceSuccessOnTimeout w_true: " << w_true_ << std::endl;
            // std::cout << "ForceSuccessOnTimeout timeout_ms: " << _timeout_ms << std::endl;
        }
        const BT::NodeStatus child_status = child_node_->executeTick();

        // 如果子节点还在运行或已经成功，则继续正常的返回状态
        return child_status;
    }

    virtual void halt() override
    {
        initialized_ = false;
        DecoratorNode::halt();
    }

private:
    std::chrono::steady_clock::time_point _start_time;
    bool initialized_ = false;
    int _timeout_ms;
    std::string w_true_;
};

class ForceSuccessOnTimeout_game : public BT::DecoratorNode
{
public:
    ForceSuccessOnTimeout_game(const std::string& name, const BT::NodeConfiguration& config)
        : BT::DecoratorNode(name, config),
          _timeout_ms(0)
    {
        setRegistrationID("ForceSuccessOnTimeout_game"); // 注册ID用于Groot
        initialized_ = false;
    }

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<int>("timeout_ms"),
                  BT::InputPort<std::string>("w_true")};
    }
    virtual BT::NodeStatus tick() override
    {
        if (!initialized_)
        {
            getInput("timeout_ms", _timeout_ms);
            getInput("w_true", w_true_);
            initialized_ = true;
            _start_time = std::chrono::steady_clock::now();
        }

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
        if (elapsed.count() >= _timeout_ms)
        {
            if(w_true_ == "nothing");
            if(w_true_ == "is_topic_ok")
            {
                is_topic_ok = true;
            }
            if(w_true_ == "is_game_start")
            {
                is_game_start = true;
            }
            return BT::NodeStatus::SUCCESS; // 超时则返回成功
        }
        else 
        {
            // std::cout << "ForceSuccessOnTimeout elapsed: " << elapsed.count() << std::endl;
            // std::cout << "ForceSuccessOnTimeout w_true: " << w_true_ << std::endl;
            // std::cout << "ForceSuccessOnTimeout timeout_ms: " << _timeout_ms << std::endl;
        }
        const BT::NodeStatus child_status = child_node_->executeTick();

        // 如果子节点还在运行或已经成功，则继续正常的返回状态
        return child_status;
    }

    virtual void halt() override
    {
        initialized_ = false;
        DecoratorNode::halt();
    }

private:
    std::chrono::steady_clock::time_point _start_time;
    bool initialized_ = false;
    int _timeout_ms;
    std::string w_true_;
};
#endif