#include "ros/ros.h"
#include "udemy_cpp_pkg/OddEvenCheck.h"

bool OddEvenChecker(udemy_cpp_pkg::OddEvenCheck::Request  &req,
         udemy_cpp_pkg::OddEvenCheck::Response &res)
{
  int remainder = req.Number % 2;

  if (remainder == 0)
  {
      res.check = "Even";
  }
  else if (remainder == 1)
  {
      res.check = "Odd";
  }
  else
  {
      return false;
  }
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odd_even_service_server_node");
  ros::NodeHandle node_handle;

  ros::ServiceServer service = node_handle.advertiseService("odd_even_check", OddEvenChecker);
  ROS_INFO("Ready to Check Odd/Even");
  ros::spin();

  return 0;
}