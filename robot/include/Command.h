//
// Created by pi on 06.11.2022.
//

#ifndef ROBOTCORP_COMMAND_H
#define ROBOTCORP_COMMAND_H


class Command {
public:
    Command(int speed, int duration) : speed(speed), duration(duration){};
    Command() = default;
    virtual int execute() = 0;
    int speed{}, duration{};
};

class Left : public Command{
public:
    Left(int speed, int duration) : Command(speed, duration) {};
    int execute() override;
};

class Right : public Command{
public:
    Right(int speed, int duration) : Command(speed, duration) {};
    int execute() override;
};

class Stop : public Command{
public:
    Stop()= default;;
    int execute() override;
};

class Forward : public Command{
public:
    Forward(int speed, int duration) : Command(speed, duration){};
    int execute() override;
};

class Backward : public Command{
public:
    Backward(int speed, int duration) : Command(speed, duration){};
    int execute() override;
};


#endif //ROBOTCORP_COMMAND_H
