#include "actionlib/client/simple_action_client.h"
#include "udemy_cpp_pkg/Nav2DAction.h"

typedef actionlib::SimpleActionClient<udemy_cpp_pkg::Nav2DAction> NavClient;

bool feedback_cb_ready_flag = false;

void activeCallback()
{
    std::cout << "\n Goal Activated" << std::endl;
    feedback_cb_ready_flag = true;
}

void feedbackCallback(const udemy_cpp_pkg::Nav2DFeedback::ConstPtr& feedback)
{
    if (feedback_cb_ready_flag)
    {
        std::cout << "\33[2K\r";
        std::cout << "Distance to Goal: " << feedback->distance_to_point;
        std::cout.flush();
    }
    
}

void resultCallback(const actionlib::SimpleClientGoalState& state, 
                    const udemy_cpp_pkg::Nav2DResult::ConstPtr& result)
{
    std::cout << "\n Finished. Time Elapsed: " << result->elapsed_time << std::endl;
    feedback_cb_ready_flag = false;
}

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "action_client_node");
    ros::NodeHandle node_handle;

    NavClient client("navigate_2d", true);
    client.waitForServer();

    udemy_cpp_pkg::Nav2DGoal goal;
    goal.point.z = 0;

    while (ros::ok())
    {
        std::cout << "\n Enter Goal X: ";
        std::cin >> goal.point.x;

        std::cout << "\n Enter Goal Y: ";
        std::cin >> goal.point.y;

        client.sendGoal(goal, &resultCallback, &activeCallback, &feedbackCallback);

        client.waitForResult();
    }
    

    return 0;
}