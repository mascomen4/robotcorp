//
// Created by pi on 06.11.2022.
//

#include "../include/RobotManager.h"
#include <chrono>
#include <thread>

template<typename T>
void RobotManager<T>::manage() {
    recv->connect();

    std::thread t1([&](){
        while (true){
            auto msg = recv->receive();
            if (!msg) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                continue;
            }
            else if (msg->direction == 0){
                break;
            }
            auto command = MsgToCommandConverter::convert(msg);
            auto status = command->execute();
            if (status == 1) break;

        }
    });
    ros::spin();
    t1.join();
}