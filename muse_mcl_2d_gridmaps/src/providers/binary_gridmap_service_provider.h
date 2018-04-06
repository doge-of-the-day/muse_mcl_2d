#ifndef MAP_PROVIDER_BINARY_GRIDMAP_SERVICE_H
#define MAP_PROVIDER_BINARY_GRIDMAP_SERVICE_H

#include <nav_msgs/OccupancyGrid.h>

#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

#include <muse_mcl_2d/map/map_provider_2d.hpp>
#include <muse_mcl_2d_gridmaps/maps/binary_gridmap.h>

namespace muse_mcl_2d_gridmaps {
class BinaryGridmapServiceProvider : public muse_mcl_2d::MapProvider2D
{
public:
    BinaryGridmapServiceProvider();

    state_space_t::ConstPtr getStateSpace() const override;
    void setup(ros::NodeHandle &nh) override;

protected:
    mutable ros::ServiceClient          source_;
    std::string                         service_name_;
    double                              binarization_threshold_;
    bool                                blocking_;

    mutable std::mutex                                  map_mutex_;
    mutable muse_mcl_2d_gridmaps::BinaryGridmap::Ptr    map_;
    mutable std::mutex                                  map_load_mutex_;
    mutable std::thread                                 worker_;
    mutable std::condition_variable                     notify_;

};
}


#endif // MAP_PROVIDER_BINARY_GRIDMAP_SERVICE_H
