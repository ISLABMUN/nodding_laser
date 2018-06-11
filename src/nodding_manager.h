/*
*Author: Matthew King
*Date: June 8th, 2018
*
*This class is responsible for driving the Dynamixel position controller and for updating the corresponding TF frames.
*/
#include "ros/ros.h"
#include<tf/transform_broadcaster.h>
#include<dynamixel_workbench_msgs/DynamixelStateList.h>
#include<dynamixel_workbench_msgs/DynamixelState.h>



class nodding_manager
{
public:
nodding_manager(ros::NodeHandle n, int stepsize = 2); //to try - 4, 11.
//~nodding_manager();

//recieve data corresponding to the current state of the Dynamixel as self-reported. Insufficient frequency for TF data to be soley based upon.
void recieveDynamixelState(dynamixel_workbench_msgs::DynamixelStateList &msg);

/*
*Loop calls the other private functions. Returns true unless something has gone wrong.
*/
bool loop();

private:
//Functions

//Publishes the transform corresponding to the latest update.
void updateTF();

//Calls the service of the position controller in order to move the servo.
void updatePosition();

//sends to command to the position controller
bool sendJointCommand();

//Variables
ros::NodeHandle myNodeHandler;
tf::TransformBroadcaster myBroadcaster;
ros::ServiceClient myClient;

int error; //difference between current position and goal position.

const int minPosition = 378; //40 degrees from vertical = 378
const int maxPosition = 649; //-40 degrees from vertical = 649

int position = 512;	//We want to intialize to a horizontal position.
int stepSize;

bool cw_CCWb=true; //clockwise or (not) counterclockwise. Clockwise herein defined to be increasing numerical value.
};