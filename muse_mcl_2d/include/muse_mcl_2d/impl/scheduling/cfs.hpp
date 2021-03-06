#pragma once

#include <cslibs_plugins/common/plugin.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <muse_mcl_2d/scheduling/scheduler_2d.hpp>
#include <muse_smc/smc/traits/update.hpp>
#include <unordered_map>

namespace muse_mcl_2d {
class CFS : public muse_mcl_2d::Scheduler2D {
 public:
  struct Entry {
    int64_t vtime;
    std::size_t id;

    inline explicit Entry(const std::size_t id) : vtime(0), id(id) {}

    inline explicit Entry(const int64_t vtime, const std::size_t id)
        : vtime(vtime), id(id) {}

    inline Entry(const Entry &other)
        : vtime(other.vtime),
          id(other.id)

    {}

    inline Entry &operator=(const Entry &other) {
      vtime = other.vtime;
      id = other.id;
      return *this;
    }

    struct Greater {
      inline bool operator()(const Entry &lhs, const Entry &rhs) const {
        return (lhs.vtime == rhs.vtime) ? (lhs.id > rhs.id)
                                        : (lhs.vtime > rhs.vtime);
      }
    };
  };

  using Ptr = std::shared_ptr<CFS>;
  using rate_t = cslibs_time::Rate;
  using update_t = muse_smc::traits::Update<Hypothesis2D>::type;
  using queue_t = __gnu_pbds::priority_queue<Entry, typename Entry::Greater,
                                             __gnu_pbds::rc_binomial_heap_tag>;
  using time_priority_map_t = std::unordered_map<id_t, double>;
  using resampling_t = muse_smc::traits::Resampling<Hypothesis2D>::type;
  using sample_set_t = muse_smc::traits::SampleSet<Hypothesis2D>::type;
  using nice_map_t = std::unordered_map<id_t, double>;
  using time_t = cslibs_time::Time;
  using duration_t = cslibs_time::Duration;
  using update_model_map_t = std::map<std::string, std::shared_ptr<UpdateModel2D>>;

  CFS();

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
  nice_map_t nice_values_;
  queue_t q_;
  bool may_resample_;
};
}  // namespace muse_mcl_2d
