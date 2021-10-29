// Server to turn camera to client specified angle

#include "ros/ros.h"
#include "udemy_cpp_pkg/ImageService.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

std::string exe_dir, ws_dir, image_path;

int available_angles[5]{-30, -15, 0, 15, 30};

bool ImageReturn(udemy_cpp_pkg::ImageService::Request  &req,
         udemy_cpp_pkg::ImageService::Response &res)
{
  image_path = ws_dir + "src/udemy_cpp_pkg/images/" + std::to_string((int)req.angle) + ".png";
  std::cout << image_path << std::endl;

  cv::Mat image = cv::imread(image_path, 1);

  sensor_msgs::ImagePtr img_ptr = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  res.output = *img_ptr;

  return true;
}

int main(int argc, char **argv)
{
    exe_dir = argv[0];
    std::string::size_type substr_index = exe_dir.find("devel");
    ws_dir = exe_dir.substr(0, substr_index);
    // std::cout << ws_dir << std::endl;

    ros::init(argc, argv, "image_service_server_node");
    ros::NodeHandle node_handle;

    ros::ServiceServer service = node_handle.advertiseService("image_return", ImageReturn);
    ROS_INFO("Ready to Return Images...");
    ros::spin();

  return 0;
}