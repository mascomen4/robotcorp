//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_ROBOTMANAGER_H
#define ROBOTCORP_ROBOTMANAGER_H

#include <utility>

#include "Command.h"
#include "Receiver.h"
#include "MsgToCommandConverter.h"

template <typename T>
class RobotManager {
    std::shared_ptr<Receiver<T>> recv;
public:
    explicit RobotManager(std::shared_ptr<Receiver<T>> receiver) : recv(std::move(receiver)){};
    void manage();
};

//template class RobotManager<std_msgs::String>;
template class RobotManager<robotcorp::commandPtr>;

#endif //ROBOTCORP_ROBOTMANAGER_H
