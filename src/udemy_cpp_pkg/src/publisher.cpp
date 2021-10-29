#include "ros/ros.h"
#include "std_msgs/String.h"
// Writing a publisher node for ros
int main(int argc, char **argv)
{
    ros::init(argc, argv, "hello_world_pub_node");

    ros::NodeHandle node_handle;

    ros::Publisher hello_world_pub = node_handle.advertise<std_msgs::String>("hello", 10);

    ros::Rate pub_rate(5);

    ROS_INFO("Publisher Node Started");

    int counter = 0;

    while(ros::ok())
    {
        std_msgs::String msg;

        msg.data = "Hello";

        hello_world_pub.publish(msg);

        counter++;

        pub_rate.sleep();
    }
}