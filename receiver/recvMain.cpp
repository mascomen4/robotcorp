//
// Created by pi on 07.11.2022.
//

#include "Receiver.h"
#include "Sender.h"
#include <thread>
#include <chrono>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char **argv){
    ros::init(argc, argv, "receiver");
    auto nh = std::make_shared<ros::NodeHandle>();
    std::string recvTopic = "/json";
    receiverROS<std_msgs::StringPtr> receiver(nh, recvTopic, 10);
    receiver.connect();

    std::string sendTopic = "mqtt";
    senderROS<robotcorp::command> sender(nh, sendTopic, 10);
    sender.connect();
    std::thread t1([&](){
        while (true){
            auto msg = receiver.receive();
            if (!msg) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                continue;
            }
            json data = json::parse(msg->data);
            if (*data.begin() == 0){
                break;
            }
            robotcorp::commandPtr command = boost::make_shared<robotcorp::command>();
            auto it = data.begin();
            command->direction = std::stoi(it->dump());
            command->speed = std::stoi((++it)->dump());
            command->duration = std::stoi((++it)->dump());
            sender.send(*command);
            ROS_INFO_STREAM("message sent! sleeping for 1 second...");
        }
        std::cout << "exiting..." << std::endl;
    });
    ros::spin();
    t1.join();
}