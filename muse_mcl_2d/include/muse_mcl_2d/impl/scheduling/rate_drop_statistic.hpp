#pragma once

#include <cslibs_plugins/common/plugin.hpp>
#include <fstream>
#include <muse_mcl_2d/scheduling/scheduler_2d.hpp>
#include <unordered_map>

namespace muse_mcl_2d {
class RateDropStatistic : public muse_mcl_2d::Scheduler2D {
 public:
  using Ptr = std::shared_ptr<RateDropStatistic>;
  using rate_t = cslibs_time::Rate;
  using update_t = muse_smc::traits::Update<Hypothesis2D>::type;
  using time_priority_map_t = std::unordered_map<id_t, double>;
  using resampling_t = muse_smc::traits::Resampling<Hypothesis2D>::type;
  using sample_set_t = muse_smc::traits::SampleSet<Hypothesis2D>::type;
  using count_map_t = std::unordered_map<id_t, std::size_t>;
  using name_map_t = std::unordered_map<id_t, std::string>;
  using time_t = cslibs_time::Time;
  using duration_t = cslibs_time::Duration;
  using update_model_map_t = std::map<std::string, std::shared_ptr<UpdateModel2D>>;

  RateDropStatistic();
  virtual ~RateDropStatistic();

  inline void print();

  inline void setup(const update_model_map_t &update_models,
                    ros::NodeHandle &nh) override;
  virtual bool apply(std::shared_ptr<update_t> &u,
                     std::shared_ptr<sample_set_t> &s) override;
  virtual bool apply(std::shared_ptr<resampling_t> &r,
                     std::shared_ptr<sample_set_t> &s) override;

 protected:
  time_t next_update_time_;
  time_t resampling_time_;
  duration_t resampling_period_;
  bool may_resample_;

  /// drop statistic stuff
  std::string output_path_;
  count_map_t drops_;
  count_map_t processed_;
  name_map_t names_;
};
}  // namespace muse_mcl_2d
