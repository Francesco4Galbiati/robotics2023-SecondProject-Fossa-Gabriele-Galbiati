#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "nav_msgs/Odometry.h"
#include <time.h>

#define ODOM_TOPIC "/t265/odom"

class tf_publisher{
	private:

		//node handle
		ros::NodeHandle nh;

		//subscribes to the odometry message
		ros::Subscriber tf_sub;

		//broadcasts the tf
		tf::TransformBroadcaster tfbr;

	public:

		//class constructor
		tf_publisher(){
			tf_sub = nh.subscribe(ODOM_TOPIC, 1, &tf_publisher::tf_callback, this);
		}

		//callback function that converts the odom_message to a tf and publishes it
		void tf_callback(const nav_msgs::Odometry::ConstPtr &odom){

			//sets the position
			tf::Transform transform;
			transform.setOrigin(tf::Vector3(odom->pose.pose.position.x, odom->pose.pose.position.y, odom->pose.pose.position.z));

			//sets the orientation
			tf::Quaternion quaternion;
			tf::quaternionMsgToTF(odom->pose.pose.orientation, quaternion);
			transform.setRotation(quaternion);

			//broadcasts the tf
			tfbr.sendTransform(tf::StampedTransform(transform, odom->header.stamp, "odom", "t265"));
		}
};


int main(int argc, char** argv){

	//initializes the node
	ros::init(argc, argv, "tf_publisher");

	//creates the node object
	tf_publisher tf_publisher;

	ros::spin();

	return 0;
}
