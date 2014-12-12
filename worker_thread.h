#ifndef WORKER_THREAD_H_
#define WORKER_THREAD_H_

#include "gm_thread.h"

namespace gm {
class GmQueue;

class GmWorker : public GmThread {
  public:
    GmWorker(const std::string& name, Monitor* monitor,
             GlobalQueue* global_queue)
        : GmThread(name, monitor, global_queue) {
    }
    virtual ~GmWorker();

  private:
    virtual void loop();

    void waitInternal();
    void processInternal(GmQueue* q);

    DISALLOW_COPY_AND_ASSIGN(GmWorker);
};
}
#endif /* WORKER_THREAD_H_ */
