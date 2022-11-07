//
// Created by pi on 06.11.2022.
//

#include "../include/Sender.h"

void senderROS::send(robotcorp::commandPtr & msg) {
    pub.publish(*msg);
}

void senderROS::connect() {
    pub = n->advertise<robotcorp::command>(topic, queue_size);
    std::cout << "publisher is set to topic: " << topic << std::endl;
}