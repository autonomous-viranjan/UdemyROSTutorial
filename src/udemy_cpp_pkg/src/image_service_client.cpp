#include "ros/ros.h"
#include "udemy_cpp_pkg/ImageService.h"
#include <stdio.h>

#include <opencv2/core.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
#include <sensor_msgs/image_encodings.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_service_client_node");
  
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<udemy_cpp_pkg::ImageService>("image_return"); // "name" same as server
  udemy_cpp_pkg::ImageService image_srv;
  
  int angle;

  cv_bridge::CvImagePtr cv_ptr;

  while (ros::ok())
  {
    std::cout << "Input Cam Angle (-30, -15, 0, 15, or 30):";
    std::cin >> angle;

    image_srv.request.angle = angle;

    if (client.call(image_srv))
    {
      cv_ptr = cv_bridge::toCvCopy(image_srv.response.output, sensor_msgs::image_encodings::BGR8);
      cv::imshow("Robot Camera Image", cv_ptr->image);
      cv::waitKey(1000);
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