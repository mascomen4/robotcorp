//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_SENDER_H
#define ROBOTCORP_SENDER_H

#include "command.h"
#include <ros/publisher.h>
#include <ros/node_handle.h>
#include "std_msgs/String.h"

template <typename T>
class Sender{
public:
    Sender() = default;
    virtual ~Sender() = default;
    virtual void connect() = 0;
    virtual void send(T &) = 0;
};

template <typename T>
class senderROS : public Sender<T>{
    ros::Publisher pub;
    std::shared_ptr<ros::NodeHandle> n;
    std::string topic = "chatter";
    int queue_size = 1000;
public:
    senderROS(std::shared_ptr<ros::NodeHandle> nh, std::string topic, int queue_size) : n(std::move(nh)),
        topic(std::move(topic)), queue_size(queue_size) {};
    senderROS() = delete;

    void connect() override {
        pub = n->advertise<T>(topic, queue_size);
        ROS_INFO_STREAM("publisher is set to topic: " << topic << std::endl;);
    };

    void send(T & msg) override {
        pub.publish(msg);
    };
};

template <typename T>
class senderMQTT : public Sender<T>{
public:
    senderMQTT() = default;
    void connect() override{};
    void send (robotcorp::command &){};
    void send(std_msgs::String &) override {};
};

#endif //ROBOTCORP_SENDER_H
