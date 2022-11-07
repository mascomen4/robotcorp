//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_SENDER_H
#define ROBOTCORP_SENDER_H

#include "command.h"
#include <ros/publisher.h>
#include <ros/node_handle.h>

class Sender{
public:
    Sender() = default;
    virtual ~Sender() = default;
    virtual void connect() {};
    virtual void send(robotcorp::commandPtr &) {};
};

class senderROS : public Sender{
    ros::Publisher pub;
    std::shared_ptr<ros::NodeHandle> n;
    std::string topic = "chatter";
    int queue_size = 1000;
public:
    senderROS(std::shared_ptr<ros::NodeHandle> nh, std::string topic, int queue_size) : n(std::move(nh)),
                            topic(std::move(topic)), queue_size(queue_size) {};
    senderROS() = delete;
    void connect() override;
    void send(robotcorp::commandPtr &) override;
};

class senderMQTT : public Sender{
public:
    senderMQTT() = default;
    void connect() override{};
    void send (const robotcorp::commandPtr &){};
};


#endif //ROBOTCORP_SENDER_H
