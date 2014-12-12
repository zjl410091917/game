#ifndef MONITOR_H_
#define MONITOR_H_

#include "base/base.h"

namespace gm {

class Monitor {
  public:
    Monitor()
        : sync_event_(false, false) {
    }
    ~Monitor() {
    }

    void notify() {
      sync_event_.Signal();
    }

    void wait() {
      sync_event_.Wait();
    }

    // return false iif timedout.
    bool wait(uint32 micro_secs) {
      return sync_event_.TimeWait(micro_secs);
    }

  private:
    SyncEvent sync_event_;

    DISALLOW_COPY_AND_ASSIGN(Monitor);
};

}

#endif /* MONITOR_H_ */
