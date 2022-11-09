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
    virtual void connect() = 0;
    virtual T receive() = 0;
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
    void connect() override{
        sub = n->subscribe( topic, queue_size, &receiverROS<T>::msgCallback, this);
        ROS_INFO_STREAM("subscriber is set to topic: " << topic << std::endl);
    };

    T receive() override {
        if (!q.empty()){
            auto msg = q.front();
            q.pop();
            return msg;
        }
        else{
            return nullptr;
        }
    };

    void msgCallback(const T & msg){
        q.push(msg);
    };

};

template <typename T>
class receiverMQTT : public Receiver<T>{
public:
    receiverMQTT() = default;
    void connect() override {};
    T receive() override {return nullptr;};
};

#endif //ROBOTCORP_RECEIVER_H
