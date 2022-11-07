//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_RECEIVER_H
#define ROBOTCORP_RECEIVER_H

#include "command.h"
#include <queue>
#include <utility>
#include <ros/node_handle.h>

class Receiver{
public:
    Receiver() = default;
    virtual ~Receiver() = default;
    virtual void connect() = 0;
    virtual robotcorp::commandPtr receive() {return nullptr;};
};

class receiverROS : public Receiver{
    ros::Subscriber sub;
    std::shared_ptr<ros::NodeHandle> n;
    std::string topic = "chatter";
    int queue_size = 1000;

public:
    receiverROS(std::shared_ptr<ros::NodeHandle> nh, std::string topic, int queue_size) : n(std::move(nh)), topic(std::move(topic)), queue_size(queue_size) {};
    receiverROS() = delete;
    ~receiverROS() override = default;

    std::queue<robotcorp::commandPtr> q;
    void connect() override;
    robotcorp::commandPtr receive() override;
    void msgCallback(const robotcorp::commandPtr &msg);

};

class receiverMQTT : public Receiver{
public:
    receiverMQTT() = default;
    void connect() override {};
    robotcorp::commandPtr receive() override {return nullptr;};
};


#endif //ROBOTCORP_RECEIVER_H
