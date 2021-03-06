#ifndef MUSE_MCL_2D_MAP_PROVIDER_2D_HPP
#define MUSE_MCL_2D_MAP_PROVIDER_2D_HPP

#include <ros/ros.h>
#include <cslibs_plugins/common/plugin.hpp>

#include <muse_mcl_2d/instance/sample_2d.hpp>
#include <muse_smc/smc/traits/state_space_provider.hpp>

namespace muse_mcl_2d {
class MapProvider2D
    : public muse_smc::traits::StateSpaceProvider<Hypothesis2D>::type,
      public cslibs_plugins::Plugin<MapProvider2D> {
 public:
  using Ptr = std::shared_ptr<MapProvider2D>;
  using ConstPtr = std::shared_ptr<MapProvider2D const>;
  using state_space_t = muse_smc::traits::StateSpace<Hypothesis2D>::type;
  using base_t = cslibs_plugins::Plugin<MapProvider2D>;

  static std::string Type() { return "muse_mcl_2d::MapProvider2D"; }

  std::string const& getName() const override {
    return base_t::getName();
  }

  virtual void setup(ros::NodeHandle& nh) = 0;
};
}  // namespace muse_mcl_2d

#endif  // MUSE_MCL_2D_MAP_PROVIDER_2D_HPP
