#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
MoveBaseClient* ac;
move_base_msgs::MoveBaseGoal goal;
string ns;

void followWaypoint(float x, float y){

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  ROS_INFO_STREAM("x: "<< x<<", y: "<<y);
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = 1;

  ROS_INFO("Sending goal");
  ac->sendGoal(goal);

  ac->waitForResult();

  if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Goal completed.");
  else
    ROS_INFO("Goal failed");
}

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  ns = ros::this_node::getNamespace();

  //tell the action client that we want to spin a thread by default
  ac = new MoveBaseClient(ns + "/move_base", true);

  //wait for the action server to come up
  while(!ac->waitForServer(ros::Duration(5.0))){
  ROS_INFO_STREAM(ns + "/move_base");
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  int id = ns.back() - '0'; 
  int widthDiv2 = 3;
  int center = id*widthDiv2*3;


  followWaypoint(center, center);
  followWaypoint(center + 3, center);
  while(true){
    followWaypoint(center + 3, center + 3);
    followWaypoint(center + -3, center + 3);
    followWaypoint(center + -3, center + -3);
    followWaypoint(center + 3, center + -3);
  }

  free(ac);
  return 0;
}
