#include "ros/ros.h"
#include "udemy_cpp_pkg/OddEvenCheck.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odd_even_service_client_node");
  
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<udemy_cpp_pkg::OddEvenCheck>("odd_even_check"); // "name" same as server
  udemy_cpp_pkg::OddEvenCheck odd_even_srv;
  
  int input_number;

  std::cout << "Press 0 to exit" << std::endl;

  while (ros::ok())
  {
    std::cout << "Input an Integer:";
    std::cin >> input_number;

    odd_even_srv.request.Number = input_number;

    if (input_number == 0)
    {
      ROS_INFO("Exiting...");
      return 0;
    }
    if (client.call(odd_even_srv))
    {
      std::string resp;
      resp = odd_even_srv.response.check;
      std::cout << "The number is " << resp << std::endl;
    }    
    else
    {
      ROS_ERROR("Service Call Failed");
      return 1;
    }  
  }

  std::cin.clear();  

  return 0;
}