# A 3 part system:

- A Robot component: receives directions in MQTT, translates them into commands and executes them by printing to the console. (forward, backward, left, right, jump, stop)
Commands have a duration and a speed

- A Receiver component: receives instructions in JSON via a sub/pub event system and sends them over to the robot using  the MQTT protocol.
Instructions comprise a list of 10 commands.

- A Manager component: sends out instructions (for the sake of the assignment, have it send out instructions at the start)

1. install [mqtt_client](https://github.com/ika-rwth-aachen/mqtt_client) to your ros directory
2. copy file from `launch/params.yaml` to `launch/params.yaml` of the mqtt_client repository.
3. run docker mqtt: ```docker run --rm --network host --name mosquitto eclipse-mosquitto``` and then ``` roslaunch mqtt_client standalone.launch ```
2. `rosrun robotcorp robotMain`
3. `rosrun robotcorp receiverMain`
4. `rosrun robotcorp senderMain`
