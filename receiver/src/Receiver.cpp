//
// Created by pi on 06.11.2022.
//

#include "../include/Receiver.h"
#include <functional>

template <typename L>
void receiverROS<L>::connect() {
//    std::function<void(receiverROS<L>, L)> f = &receiverROS<L>::msgCallback;
    sub = n->subscribe( topic, queue_size, &receiverROS<L>::msgCallback, this);
    std::cout << "subscriber is set to topic: " << topic << std::endl;
}

template <typename T>
T receiverROS<T>::receive() {
    if (!q.empty()){
        auto msg = q.front();
        q.pop();
        return msg;
    }
    else{
        return nullptr;
    }
}

template <typename T>
void receiverROS<T>::msgCallback(const T & msg){
//    std::cout << "message received! saving..." << std::endl;
    q.push(msg);
}

//template<>
//void receiverROS<std_msgs::StringPtr>::msgCallback(const std_msgs::StringPtr &msg){
////    std::cout << "message received! saving..." << std::endl;
//    q.push(msg);
//}

//template void receiverROS<robotcorp::commandPtr>::msgCallback(const robotcorp::commandPtr &msg);