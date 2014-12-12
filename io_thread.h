#ifndef IO_THREAD_H_
#define IO_THREAD_H_

#include "gm_thread.h"

namespace gm {

class IoThread : public GmThread {
  public:
    IoThread(Monitor* monitor, GlobalQueue* global_queue)
        : GmThread("io thread", monitor, global_queue) {
    }
    virtual ~IoThread();

  private:
    virtual void loop();

    DISALLOW_COPY_AND_ASSIGN(IoThread);
};
}
#endif /* IO_THREAD_H_ */
