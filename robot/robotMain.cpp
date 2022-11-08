//
// Created by pi on 07.11.2022.
//

#include "ros/node_handle.h"
#include "Receiver.h"
#include "RobotManager.h"
#include "MsgToCommandConverter.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "robot");
    auto nh = std::make_shared<ros::NodeHandle>();
    std::string topic = "/mqtt_recv";
    auto recvBase = std::make_shared<receiverROS<robotcorp::commandPtr>>(nh, topic, 10);
    RobotManager<robotcorp::commandPtr> manager(recvBase);
    manager.manage();
    ros::spin();
}