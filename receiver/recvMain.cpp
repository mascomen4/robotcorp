//
// Created by pi on 07.11.2022.
//

#include "Receiver.h"
#include "Sender.h"
#include <thread>
#include <chrono>

int main(int argc, char **argv){
    ros::init(argc, argv, "receiver");
    auto nh = std::make_shared<ros::NodeHandle>();
    std::string recvTopic = "/json";
    receiverROS receiver(nh, recvTopic, 10);
    receiver.connect();

//    std::cout << 1 << std::endl;
    std::string sendTopic = "mqtt";
//    std::cout << 2 << std::endl;
    senderROS sender(nh, sendTopic, 10);
//    std::cout << 3 << std::endl;
    sender.connect();
//    std::cout << 4 << std::endl;
    std::thread t1([&](){
        std::cout << "entering the thread" << std::endl;
        while (true){
            auto command = receiver.receive();
            if (!command) {
//                std::cout << "no commands, sleeping for 1 second..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                continue;
            }
            else if (command->direction == 0){
                break;
            }
            sender.send(command);
            std::cout << "message sent! sleeping for 1 second..." << std::endl;
        }
        std::cout << "exiting..." << std::endl;
    });
    ros::spin();
    t1.join();
}