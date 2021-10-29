#include "actionlib/server/simple_action_server.h"
#include "udemy_cpp_pkg/Nav2DAction.h"
#include <cmath>

float DISTANCE_THRESHOLD = 0.1;
typedef actionlib::SimpleActionServer<udemy_cpp_pkg::Nav2DAction> NavServer;

geometry_msgs::Point robot_current_position;

void navCallback(const udemy_cpp_pkg::Nav2DGoal::ConstPtr& goal_point, NavServer* nav_server)
{
    udemy_cpp_pkg::Nav2DFeedback feedback_msg;
    udemy_cpp_pkg::Nav2DResult result_msg;

    ros::Rate feedback_rate(2);

    double goal_received_time = ros::Time::now().toSec();
    ROS_INFO("Goal Received");

    float dis = std::sqrt((std::pow((robot_current_position.x - goal_point->point.x), 2)) + std::pow((robot_current_position.y - goal_point->point.y), 2));

    while (dis > DISTANCE_THRESHOLD)
    {
        dis = std::sqrt((std::pow((robot_current_position.x - goal_point->point.x), 2)) + std::pow((robot_current_position.y - goal_point->point.y), 2));

        feedback_msg.distance_to_point = dis;

        nav_server->publishFeedback(feedback_msg);

        feedback_rate.sleep();
    }

    double goal_reached_time = ros::Time::now().toSec();
    ROS_INFO("Goal Reached");

    double time_elapsed = goal_reached_time - goal_received_time;

    result_msg.elapsed_time = time_elapsed;

    nav_server->setSucceeded(result_msg);    
}

void subscriberCallback(const geometry_msgs::Point::ConstPtr& msg)
{
    robot_current_position = *msg;
}

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "action_server_node");
    ros::NodeHandle node_handle;

    ros::Subscriber robot_position = node_handle.subscribe("robot_position", 10, subscriberCallback);
    
    NavServer server(node_handle, "navigate_2d", boost::bind(&navCallback, _1, &server), false);
    server.start();

    ros::spin();

    return 0;
}
