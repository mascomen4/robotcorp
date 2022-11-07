//
// Created by pi on 06.11.2022.
//

#include "../include/Receiver.h"
#include <functional>


void receiverROS::connect() {
    sub = n->subscribe( topic, queue_size, &receiverROS::msgCallback, this);
    std::cout << "subscriber is set to topic: " << topic << std::endl;
}

robotcorp::commandPtr receiverROS::receive() {
    if (!q.empty()){
        auto msg = q.front();
        q.pop();
        return msg;
    }
    else{
        return nullptr;
    }
}

void receiverROS::msgCallback(const robotcorp::commandPtr &msg){
//    std::cout << "message received! saving..." << std::endl;
    q.push(msg);
}