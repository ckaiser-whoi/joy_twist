#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>



ros::Publisher cmd_vel_publisher;


//ros::Publisher cmd_vel_publisher;

//int linear, angular;

int a_gain = 1;
int l_gain = -1;

geometry_msgs::Twist joy_twist;

void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  joy_twist.angular.z = a_gain*joy->axes[6];
  joy_twist.linear.x = l_gain*joy->axes[7];
}

void TimerCallback(const ros::TimerEvent&)
{
      
  cmd_vel_publisher.publish(joy_twist);
  
}


int main(int argc, char** argv)
{

  ros::init(argc, argv, "joy_twist");

  ros::NodeHandle node;
  
  ros::Subscriber sub = node.subscribe("joy", 10, joyCallback);
  //ros::Publisher cmd_vel_publisher = node.advertise<geometry_msgs::Twist>("edumip/cmd", 10);
  cmd_vel_publisher = node.advertise<geometry_msgs::Twist>("edumip/cmd", 10);

  

    
  ros::Timer timer = node.createTimer(ros::Duration(0.1), TimerCallback);

  ros::spin();
  
};
