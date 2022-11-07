//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_MSGTOCOMMANDCONVERTER_H
#define ROBOTCORP_MSGTOCOMMANDCONVERTER_H

#include "command.h"
#include "Command.h"

enum Directions {stop = 0, right = 1, forward = 2, left = 3, backward = 4};

class MsgToCommandConverter{
public:
     static std::shared_ptr<Command> convert(const robotcorp::commandPtr& msg){
         auto res = std::make_shared<Command>();
         switch (msg->direction) {
             case Directions::stop:
                 res = std::make_shared<Stop>();
                 break;
             case Directions::right:
                 res = std::make_shared<Right>(msg->speed, msg->duration);
                 break;
             case Directions::forward:
                 res = std::make_shared<Forward>(msg->speed, msg->duration);
                 break;
             case Directions::left:
                 res = std::make_shared<Left>(msg->speed, msg->duration);
                 break;
             case Directions::backward:
                 res = std::make_shared<Backward>(msg->speed, msg->duration);
                 break;
         }
         return res;
     };
};

#endif //ROBOTCORP_MSGTOCOMMANDCONVERTER_H
