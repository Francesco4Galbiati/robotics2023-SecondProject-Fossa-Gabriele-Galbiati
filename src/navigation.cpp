#include "ros/ros.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "actionlib/client/simple_action_client.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <fstream>
#include <iostream>
#include <string>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){

	//initializes the navigation node
	ros::init(argc, argv, "navigation");
	ros::NodeHandle nh;

	//initializes the action client
	MoveBaseClient ac("move_base", true);

	//waits for the action server to start
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the action server...");
	}

	//file stream declaration for waypoints.csv
	std::ifstream file;
	std::string filename;
	nh.getParam("/waypoints_file", filename);
	file.open(filename);

	if(file.is_open()){

		move_base_msgs::MoveBaseGoal goal;
		std::string line, x_s, y_s, yaw_s;
		tf2::Quaternion quat;

		//reads the file line by line
		while(getline(file, line))
		{
			std::stringstream str(line);

			//separates the values in the read line
			getline(str, x_s, ',');
			getline(str, y_s, ',');
			getline(str, yaw_s);

			//sets the goal target pose
			try{
				quat.setRPY(0.0, 0.0, stof(yaw_s));
				goal.target_pose.pose.position.x = stof(x_s);
				goal.target_pose.pose.position.y = stof(y_s);
				tf2::convert(quat, goal.target_pose.pose.orientation);
			}catch (const std::invalid_argument& e){}

			goal.target_pose.header.frame_id = "map";
			goal.target_pose.header.stamp = ros::Time::now();

			ROS_INFO("Sending goal (x: %f, y: %f)",
				goal.target_pose.pose.position.x,
				goal.target_pose.pose.position.y);

			//sends the goal
			ac.sendGoal(goal);

			//waits for the goal result
			ac.waitForResult();

			if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
				ROS_INFO("Goal reached");
			}else{
				ROS_INFO("The navigation failed");
			}

			//gives time to the navigation to update (without this it may sometimes skip a goal)
			ros::Duration(1.0).sleep();
		}
	}else{
		std::cout << "Error";
	}

	return 0;
}
