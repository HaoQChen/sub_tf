#include "ros/ros.h"
#include "tf/transform_listener.h"
//#include <tf/message_filter.h>
//#include <message_filters/subscriber.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>

#include "sub_tf.h"

geometry_msgs::PoseStamped FrameTransform::getTransform()
{   
    tf::StampedTransform transform;
    geometry_msgs::PoseStamped ps;

    listener_.waitForTransform(target_frame_, source_frame_, ros::Time(0), ros::Duration(0.2));
    try{
        listener_.lookupTransform(target_frame_, source_frame_, ros::Time(0), transform);
    }catch(tf::TransformException e){
        ROS_ERROR("%s", e.what());
    }

    ps.header.stamp = transform.stamp_;
    ps.pose.position.x = transform.getOrigin().x();
    ps.pose.position.y = transform.getOrigin().y();
    ps.pose.position.z = transform.getOrigin().z();
    ps.pose.orientation.x = transform.getRotation().x();
    ps.pose.orientation.y = transform.getRotation().y();
    ps.pose.orientation.z = transform.getRotation().z();
    ps.pose.orientation.w = transform.getRotation().w();

    ROS_INFO("Time: %f", ps.header.stamp.toSec());
    ROS_INFO("XYZ: (%f, %f, %f)", ps.pose.position.x, ps.pose.position.y, ps.pose.position.z);
    double yaw, pitch, roll;
    transform.getBasis().getEulerYPR(yaw, pitch, roll);
    ROS_INFO("YPR: (%f, %f, %f)", yaw, pitch, roll);

    return ps;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "sub_tf");
    ros::NodeHandle nh;
    ros::Rate loop(20);
    FrameTransform base2map("/map", "base_link");
    ros::Publisher pub_tf_b2m = nh.advertise<geometry_msgs::PoseStamped>("tf_b2m", 1, true);
    
    while(ros::ok()){
        geometry_msgs::PoseStamped ps_base2map = base2map.getTransform();
        pub_tf_b2m.publish(ps_base2map);
        loop.sleep();
    }
    return 0;
}

