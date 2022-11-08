//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_RECEIVER_H
#define ROBOTCORP_RECEIVER_H

#include "command.h"
#include <queue>
#include <utility>
#include <ros/node_handle.h>
#include "std_msgs/String.h"

template <typename T>
class Receiver{
public:
    Receiver() = default;
    virtual ~Receiver() = default;
    virtual void connect() {};
    virtual T receive() {return T{};};
};

template <typename T>
class receiverROS : public Receiver<T>{
    ros::Subscriber sub;
    std::shared_ptr<ros::NodeHandle> n;
    std::string topic = "chatter";
    int queue_size = 1000;

public:
    receiverROS<T>(std::shared_ptr<ros::NodeHandle> nh, std::string topic, int queue_size) : n(std::move(nh)), topic(std::move(topic)), queue_size(queue_size) {};
    receiverROS() = delete;
    ~receiverROS() override = default;

    std::queue<T> q;
    void connect() override;
    T receive() override;
//    void msgCallback(const robotcorp::commandPtr &msg);
    void msgCallback(const T &);
//    void msgCallback(const std_msgs::StringPtr &msg);

};

template <typename T>
class receiverMQTT : public Receiver<T>{
public:
    receiverMQTT() = default;
    void connect() override {};
    T receive() override {return nullptr;};
};

template class receiverROS<std_msgs::StringPtr>;
template class receiverROS<robotcorp::commandPtr>;

#endif //ROBOTCORP_RECEIVER_H
