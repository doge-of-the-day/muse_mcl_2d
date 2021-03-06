#ifndef MUSE_MCL_2D_UPDATE_MODEL_2D_HPP
#define MUSE_MCL_2D_UPDATE_MODEL_2D_HPP

#include <ros/node_handle.h>

#include <cslibs_math_ros/tf/tf_provider.hpp>
#include <cslibs_plugins/common/plugin.hpp>
#include <cslibs_plugins_data/data.hpp>
#include <muse_mcl_2d/instance/sample_2d.hpp>
#include <muse_smc/smc/traits/update_model.hpp>

namespace muse_mcl_2d {
class UpdateModel2D : public muse_smc::traits::UpdateModel<Hypothesis2D>::type,
                      public cslibs_plugins::Plugin<UpdateModel2D> {
 public:
  using Ptr = std::shared_ptr<UpdateModel2D>;
  using base_t = cslibs_plugins::Plugin<UpdateModel2D>;
  using data_t = muse_smc::traits::Data<Hypothesis2D>::type;
  using transform_t = muse_smc::traits::Transform<Hypothesis2D>::type;
  using state_t = muse_smc::traits::State<Hypothesis2D>::type;
  using point_t = muse_smc::traits::StateSpaceBoundary<Hypothesis2D>::type;
  using state_space_t = muse_smc::traits::StateSpace<Hypothesis2D>::type;
  using sample_set_t = muse_smc::traits::SampleSet<Hypothesis2D>::type;

  static std::string Type() { return "muse_mcl_2d::UpdateModel2D"; }

  inline std::size_t getModelId() const override {
    return base_t::getId();
  }

  inline std::string const &getName() const override {
    return base_t::getName();
  }

  inline void setup(const cslibs_math_ros::tf::TFProvider::Ptr &tf,
                    ros::NodeHandle &nh) {
    auto param_name = [this](const std::string &name) {
      return name_ + "/" + name;
    };
    tf_ = tf;

    world_frame_ = nh.param<std::string>("world_frame", "world");
    robot_base_frame_ = nh.param<std::string>("base_frame", "base_link");
    tf_timeout_ =
        ros::Duration(nh.param<double>(param_name("tf_timeout"), 0.1));
    doSetup(nh);
  }

 protected:
  cslibs_math_ros::tf::TFProvider::Ptr tf_{nullptr};
  ros::Duration tf_timeout_{0.1};
  std::string world_frame_;
  std::string robot_base_frame_;

  virtual void doSetup(ros::NodeHandle &nh) = 0;
};
}  // namespace muse_mcl_2d

#endif  // MUSE_MCL_2D_UPDATE_MODEL_2D_HPP
