#include "path_subscriber.hpp"
#include <memory>

using Path = autoware_auto_planning_msgs::msg::Path;
using PathWithLaneId = autoware_auto_planning_msgs::msg::PathWithLaneId;
using std::placeholders::_1;

PathSubscriber::PathSubscriber() : Node("path_subscriber")
{
  
  sub_path_pub_ = create_publisher<Path>(
    "behavior_planning/path2", 1);

  sub_path_sub_ = create_subscription<PathWithLaneId>("behavior_planning/path_with_lane_id", 10, std::bind(&PathSubscriber::topicCallback, this, _1));
  sub_path_candidate_sub_ = create_subscription<Path>("/planning/scenario_planning/lane_driving/behavior_planning/path", 10, std::bind(&PathSubscriber::topicCandidateCallback, this, _1));

}

void PathSubscriber::topicCallback(const PathWithLaneId::ConstSharedPtr msg)
{
  path_sub_ = msg;

  Path path;
  
  /*
  if(!path_sub_candidate_){
    path.header = path_sub_candidate_->header;
    path.left_bound = path_sub_candidate_->left_bound;
    path.right_bound = path_sub_candidate_->right_bound;
    for (const auto & point : path_sub_candidate_->points) {
      path.points.push_back(point);
    }
    path_sub_candidate_ = NULL;
  } else {
    path.header = path_sub_->header;
    path.left_bound = path_sub_->left_bound;
    path.right_bound = path_sub_->right_bound;
    for (const auto & point : path_sub_->points) {
      path.points.push_back(point.point);
    }
  }
  */

  path.header = msg->header;
  path.left_bound = msg->left_bound;
  path.right_bound = msg->right_bound;
  for (const auto & point : msg->points) {
    path.points.push_back(point.point);
  }

  //RCLCPP_INFO(this->get_logger(), "I heard");

 sub_path_pub_->publish(path);

}

void PathSubscriber::topicCandidateCallback(const Path::ConstSharedPtr msg)
{
  //RCLCPP_INFO(this->get_logger(), "I heard2");
  path_sub_candidate_ = msg;
}

