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
    senderROS<std_msgs::String> sender = senderROS<std_msgs::String>(nh, topic, 10);
    sender.connect();

    // Fill the commands from the json and send them as ROS string message. 
    std::string fn = "src/robotcorp/commands/commands.json";
    if (argc == 2) {
        fn = std::string(argv[1]);
    };
    std::ifstream f(fn);
    json data;
    if (f) data = json::parse(f);
    else {std::cout << "no file! exiting..." << std::endl; return 1;}
    std::vector<std_msgs::StringPtr> commands{};
    for (auto it = data.begin(); it != data.end(); ++it){
        std::cout << it->dump() << std::endl;
        std_msgs::StringPtr tmp = boost::make_shared<std_msgs::String>();
        tmp->data = it->dump();
        commands.push_back(tmp);
    }

    for (const auto& command : commands){
        sender.send(*command);
        std::cout << "command sent! sleeping for 1 second..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    ros::spin();
}
