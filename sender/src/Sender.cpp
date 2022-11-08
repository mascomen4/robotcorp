//
// Created by pi on 06.11.2022.
//

#include "../include/Sender.h"

template <typename T>
void senderROS<T>::send(T & msg) {
    pub.publish(msg);
}

template void senderROS<std_msgs::String>::send(std_msgs::String & msg);
template void senderROS<robotcorp::command>::send(robotcorp::command & msg);

template<typename T>
void senderROS<T>::connect() {
    pub = n->advertise<T>(topic, queue_size);
    std::cout << "publisher is set to topic: " << topic << std::endl;
}

template void senderROS<std_msgs::String>::connect();
template void senderROS<robotcorp::command>::connect();
//template void senderROS<robotcorp::command>::connect();