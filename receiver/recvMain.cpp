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

//    std::cout << 1 << std::endl;
    std::string sendTopic = "mqtt";
//    std::cout << 2 << std::endl;
    senderROS<robotcorp::command> sender(nh, sendTopic, 10);
//    std::cout << 3 << std::endl;
    sender.connect();
//    std::cout << 4 << std::endl;
    std::thread t1([&](){
        std::cout << "entering the thread" << std::endl;
        while (true){
            auto msg = receiver.receive();
            if (!msg) {
//                std::cout << "no commands, sleeping for 1 second..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                continue;
            }
            auto data = json::parse(msg->data);
            if (*data.begin() == 0){
                break;
            }
            robotcorp::commandPtr command = robotcorp::commandPtr();
            command->direction = std::stoi(data.begin()->dump());
            command->speed = std::stoi( (data.begin()+1)->dump());
            command->duration = std::stoi( (data.begin()+2)->dump());
            sender.send(*command);
            std::cout << "message sent! sleeping for 1 second..." << std::endl;
        }
        std::cout << "exiting..." << std::endl;
    });
    ros::spin();
    t1.join();
}