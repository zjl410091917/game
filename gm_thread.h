#ifndef GM_THREAD_H_
#define GM_THREAD_H_

#include "base/base.h"

namespace gm {
class GlobalQueue;

class GmThread {
  public:
    virtual ~GmThread() {
    }

    const std::string& name() const {
      return name_;
    }

    bool start() {
      if (stop_) {
        loop_thread_.reset(
            new StoppableThread(
                NewPermanentCallback(this, &GmThread::threadMain, this)));
        if (loop_thread_->Start()) {
          stop_ = false;
          return true;
        }
      }
      return false;
    }

    void stop() {
      stop_ = true;
    }

  protected:
    GmThread(const std::string& name, Monitor* monitor,
             GlobalQueue* global_queue)
        : stop_(true), monitor_(monitor), global_queue_(global_queue), name_(
            name) {
      DCHECK(!name.empty());
      DCHECK_NOTNULL(monitor);
      DCHECK_NOTNULL(global_queue);
    }

    bool stop_;
    Monitor* monitor_;
    GlobalQueue* global_queue_;

    virtual void loop() = 0;

  private:
    const std::string name_;

    scoped_ptr<StoppableThread> loop_thread_;
    static void threadMain(GmThread* const t) {
      DCHECK_NOTNULL(t);
      t->loop();
    }

    DISALLOW_COPY_AND_ASSIGN(GmThread);
};
}
#endif /* GM_THREAD_H_ */
