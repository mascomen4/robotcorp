//
// Created by pi on 07.11.2022.
//

#include "../sender/include/Sender.h"
#include <thread>
#include <chrono>
#include "nlohmann/json.hpp"
#include <fstream>
#include <algorithm>

using json = nlohmann::json;

//enum Directions {stop = 0, right = 1, forward = 2, left = 3, backward = 4};

int main(int argc, char **argv){
//    std::cout << 0 << std::endl;
    ros::init(argc, argv, "sender");
    auto nh = std::make_shared<ros::NodeHandle>();
    std::string topic = "json";
    senderROS sender = senderROS(nh, topic, 10);
    sender.connect();

    // Fill the commands from the json and send them as ROS string message. 
    std::string file = "/home/pi/workspace/opensource_ov/src/robotcorp/commands/commands.json";
    if (argc == 2) {
        file = std::string(argv[1]);
        std::ifstream f(file);
        json data = json::parse(f);
        std::for_each(data.begin(), data.end(), [](auto item){std::cout << item.dump() << " ";});
    };

    std::array<robotcorp::commandPtr, 10> commands;
//    for (int i = 0; i < 10; ++i){
////        std::cout << 1 << std::endl;
//        robotcorp::commandPtr command(boost::make_shared<robotcorp::command>());
////        std::cout << 2 << std::endl;
//        command->direction = (i % 4 + 1);
//        command->speed = (i % 3 + 1);
//        command->duration = (i % 5 + 1);
//        commands[i] = command;
////        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    }

    for (int i = 0; i < 10; ++i){
        auto command = commands[i];
        sender.send(command);
        std::cout << "command sent! sleeping for 1 second..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    ros::spin();
}
