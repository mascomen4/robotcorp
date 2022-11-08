//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_ROBOTMANAGER_H
#define ROBOTCORP_ROBOTMANAGER_H

#include <utility>

#include "Command.h"
#include "Receiver.h"
#include "MsgToCommandConverter.h"

class RobotManager {
    std::shared_ptr<Receiver<robotcorp::commandPtr>> recv;
public:
    explicit RobotManager(std::shared_ptr<Receiver<robotcorp::commandPtr>> receiver) : recv(std::move(receiver)){};
    void manage();
};

#endif //ROBOTCORP_ROBOTMANAGER_H
