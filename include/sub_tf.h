#ifndef _SUB_BASE_LINK_H_
#define _SUB_BASE_LINK_H_

#include "ros/ros.h"
#include "tf/transform_listener.h"
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>

#include <string>

class FrameTransform{
public:
	FrameTransform(std::string _tarf, std::string _sourf):target_frame_(_tarf), source_frame_(_sourf){}
	geometry_msgs::PoseStamped getTransform();
private:
	tf::TransformListener listener_;
	std::string target_frame_;
	std::string source_frame_;
};

#endif