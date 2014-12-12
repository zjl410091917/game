#ifndef GM_QUEUE_H_
#define GM_QUEUE_H_

#include "base/base.h"

namespace gm {

class GmQueue {
  public:
    virtual ~GmQueue() {
    }

    Module* module() const {
      return module_;
    }

    bool pop(void** pkg);

  protected:
    GmQueue(Module* module)
        : module_(module) {
      DCHECK_NOTNULL(module);
    }

    Module* module_;

  private:
    DISALLOW_COPY_AND_ASSIGN(GmQueue);
};

class GlobalQueue {
  public:
    GlobalQueue();
    ~GlobalQueue();

    GmQueue* pop();
    void push(GmQueue* q);

  private:
    DISALLOW_COPY_AND_ASSIGN(GlobalQueue);
};
}
#endif /* GM_QUEUE_H_ */
