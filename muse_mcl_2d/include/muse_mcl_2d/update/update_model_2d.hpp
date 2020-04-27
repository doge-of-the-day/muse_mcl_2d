#ifndef UPDATE_MODEL2D_HPP
#define UPDATE_MODEL2D_HPP

#include <muse_mcl_2d/samples/sample_2d.hpp>

#include <muse_smc/smc/smc_types.hpp>

#include <cslibs_math_ros/tf/tf_provider.hpp>

#include <cslibs_plugins/plugin.hpp>
#include <cslibs_plugins_data/data.hpp>
#include <ros/node_handle.h>

namespace muse_mcl_2d {
class UpdateModel2D : public muse_smc::Types<Sample2D>::update_model_t,
                      public cslibs_plugins::Plugin
{
public:
    using Ptr           = std::shared_ptr<UpdateModel2D>;
    using data_t        = cslibs_plugins_data::Data;
    using sample_t      = Sample2D;
    using transform_t   = muse_smc::traits::Transform<sample_t>::type;
    using state_t       = muse_smc::traits::State<sample_t>::type;
    using point_t       = muse_smc::traits::StateSpaceBoundary<sample_t>::type;

    UpdateModel2D() = default;
    virtual ~UpdateModel2D() = default;

    inline const static std::string Type()
    {
        return "muse_mcl_2d::UpdateModel2D";
    }

    virtual inline std::size_t getModelId() const override
    {
        return cslibs_plugins::Plugin::getId();
    }

    virtual inline const std::string getName() const override
    {
        return cslibs_plugins::Plugin::getName();
    }

    inline void setup(const cslibs_math_ros::tf::TFProvider::Ptr &tf,
                      ros::NodeHandle &nh)
    {
        auto param_name = [this](const std::string &name){return name_ + "/" + name;};
        tf_ = tf;

        world_frame_      = nh.param<std::string>("world_frame", "world");
        robot_base_frame_ = nh.param<std::string>("base_frame",  "base_link");
        tf_timeout_       = ros::Duration(nh.param<double>(param_name("tf_timeout"), 0.1));
        doSetup(nh);
    }

protected:
    cslibs_math_ros::tf::TFProvider::Ptr tf_;
    ros::Duration tf_timeout_;
    std::string   world_frame_;
    std::string   robot_base_frame_;

    virtual void doSetup(ros::NodeHandle &nh) = 0;
};
}

#endif // UPDATE_MODEL2D_HPP
