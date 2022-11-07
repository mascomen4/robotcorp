//
// Created by pi on 06.11.2022.
//

#include "../include/Command.h"
#include <iostream>
#include <thread>
#include <chrono>

int Left::execute() {
    std::cout << "moving left for " << duration << " seconds with speed " << speed << " ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(duration));
//    std::cout << "done! exiting command... " << std::endl;
    return 0;
}

int Right::execute() {
    std::cout << "moving right for " << duration << " seconds with speed " << speed << " ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(duration));
//    std::cout << "done! exiting command... " << std::endl;
    return 0;
}

int Forward::execute() {
    std::cout << "moving forward for " << duration << " seconds with speed " << speed << " ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(duration));
//    std::cout << "done! exiting command... " << std::endl;
    return 0;
}

int Backward::execute() {
    std::cout << "moving backwards for " << duration << " seconds with speed " << speed << " ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(duration));
//    std::cout << "done! exiting command... " << std::endl;
    return 0;
}

int Stop::execute() {
    return 1;
}