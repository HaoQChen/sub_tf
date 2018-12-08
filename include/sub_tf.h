#ifndef _SUB_BASE_LINK_H_
#define _SUB_BASE_LINK_H_

#include "ros/ros.h"
#include "tf/transform_listener.h"
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>
#include <fstream>

#include <string>

class FrameTransform{
public:
	FrameTransform(std::string _tarf, std::string _sourf, const char* filename):target_frame_(_tarf), source_frame_(_sourf){
		save_file_.open(filename, std::ios::out);
		if(!save_file_){
			ROS_ERROR("Can not create the file!");
		}
	}
	~FrameTransform(){
		save_file_.close();
	}
	bool getTransform(geometry_msgs::PoseStamped& ps);
private:
	tf::TransformListener listener_;
	std::string target_frame_;
	std::string source_frame_;
	std::ofstream save_file_;
};

#endif