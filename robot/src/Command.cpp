//
// Created by pi on 06.11.2022.
//

#include "../include/Command.h"
#include <iostream>
#include <thread>
#include <chrono>

void print_move(const std::string & direction, int duration, int speed){
    std::cout << "[ROBOT]: " << "\033[1;32m" << "moving" << direction << "for " << duration << " seconds with speed "
        << speed << " ..." << "\033[0m\n" << std::endl;
}

void print_stop(){
    std::cout << "[ROBOT]: " << "\033[1;31m" << "STOP" << "\033[0m\n" << std::endl;
}


int Left::execute() {
    print_move("left", duration, speed);
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    return 0;
}

int Right::execute() {
    print_move("right", duration, speed);
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    return 0;
}

int Forward::execute() {
    print_move("forward", duration, speed);
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    return 0;
}

int Backward::execute() {
    print_move("backward", duration, speed);
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    return 0;
}

int Stop::execute() {
    print_stop();
    return 1;
}