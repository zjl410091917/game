#ifndef GM_SERVER_H_
#define GM_SERVER_H_

#include "gm_thread.h"
#include "include/object_saver.h"

namespace gm {
class Monitor;
class GlobalQueue;
class ModuleManager;

class GmServer : public ObjectVectorSaver<uint32, GmThread> {
  public:
    explicit GmServer(uint32 worker)
        : worker_(worker) {
      DCHECK_GT(worker, 0);
    }
    virtual ~GmServer();

    bool init();
    bool start();

  private:
    const uint32 worker_;
    scoped_ptr<ModuleManager> module_mgr_;

    scoped_ptr<Monitor> monitor_;
    scoped_ptr<GmThread> io_thread_;
    scoped_ptr<GlobalQueue> global_queue_;

    DISALLOW_COPY_AND_ASSIGN(GmServer);
};
}

#endif /* GM_SERVER_H_ */
