//
// Created by pi on 07.11.2022.
//

#include "../sender/include/Sender.h"
#include <thread>
#include <chrono>
#include "nlohmann/json.hpp"
#include <fstream>
#include <algorithm>
#include <ios>

using json = nlohmann::json;
using commands_t = std::vector<std_msgs::StringPtr>;

commands_t parseJSONCommands(std::ifstream && f){
    json data;
    if (f) {
        ROS_INFO_STREAM("files reading success. Parsing..." << std::endl);
        data = json::parse(f);
    }
    else {
        ROS_ERROR("can't open file! exiting...");
        throw std::ios_base::failure("");
    }
    std::vector<std_msgs::StringPtr> commands{};
    for (auto & it : data){
        std_msgs::StringPtr tmp = boost::make_shared<std_msgs::String>();
        tmp->data = it.dump();
        commands.push_back(tmp);
    }
    return commands;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "sender");
    auto nh = std::make_shared<ros::NodeHandle>();
    std::string topic = "json";
    senderROS<std_msgs::String> sender = senderROS<std_msgs::String>(nh, topic, 10);
    sender.connect();

    std::string fn = "src/robotcorp/commands/commands.json";
    if (argc == 2) {
        fn = std::string(argv[1]);
    }
    std::ifstream f(fn);
    auto commands = parseJSONCommands(std::move(f));

    for (const auto& command : commands){
        sender.send(*command);
        ROS_INFO_STREAM("command sent! sleeping for 1 second...");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    ros::spin();
}
