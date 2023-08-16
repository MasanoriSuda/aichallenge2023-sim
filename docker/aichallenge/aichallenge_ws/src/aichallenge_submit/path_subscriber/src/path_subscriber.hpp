#ifndef PATH_SUBSCRIBER_HPP_
#define PATH_SUBSCRIBER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <autoware_auto_planning_msgs/msg/path.hpp>
#include <autoware_auto_planning_msgs/msg/path_with_lane_id.hpp>
#include <autoware_auto_planning_msgs/msg/path_point.hpp>

using PathWithLaneId = autoware_auto_planning_msgs::msg::PathWithLaneId;
using Path = autoware_auto_planning_msgs::msg::Path;

class PathSubscriber : public rclcpp::Node {
    public:
        PathSubscriber(void);
        void topicCallback(const PathWithLaneId::ConstSharedPtr msg);
        void topicCandidateCallback(const Path::ConstSharedPtr msg);
    private:
        rclcpp::Subscription<PathWithLaneId>::ConstSharedPtr sub_path_sub_;
        rclcpp::Subscription<Path>::ConstSharedPtr sub_path_candidate_sub_;
        PathWithLaneId::ConstSharedPtr path_sub_;
        Path::ConstSharedPtr path_sub_candidate_;
        rclcpp::Publisher<Path>::SharedPtr sub_path_pub_;
        Path::ConstSharedPtr path_pub_;
};


#endif  // PATH_SUBSCRIBER_HPP_
