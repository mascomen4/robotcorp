//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_ROBOTMANAGER_H
#define ROBOTCORP_ROBOTMANAGER_H

#include <utility>
#include <chrono>
#include <thread>

#include "Command.h"
#include "Receiver.h"
#include "MsgToCommandConverter.h"

/**
 * @brief Robot manager class. It can work only with the messages of type robotcorp::commandPtr
 */

class RobotManager {
    std::shared_ptr<Receiver<robotcorp::commandPtr>> recv;
public:
    explicit RobotManager(std::shared_ptr<Receiver<robotcorp::commandPtr>> receiver) : recv(std::move(receiver)){};
    void manage() {
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
    };
};

#endif //ROBOTCORP_ROBOTMANAGER_H
