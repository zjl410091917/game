#include "gm_server.h"

#include "module.h"
#include "monitor.h"
#include "gm_queue.h"
#include "io_thread.h"
#include "worker_thread.h"

DEFINE_string(mod_dir, "/etc/gm/", "directory used to store module file");

namespace gm {

GmServer::~GmServer() {
  io_thread_.reset();
}

bool GmServer::init() {
  monitor_.reset(new Monitor);
  global_queue_.reset(new GlobalQueue);

  module_mgr_.reset(new ModuleManager);
  if (!module_mgr_->init(FLAGS_mod_dir)) {
    module_mgr_.reset();
    return false;
  }

  return true;
}

bool GmServer::start() {
  for (uint32 i = 0; i < worker_; ++i) {
    std::string name("worker: " + std::to_string(i));

    GmThread* t = new GmWorker(name, monitor_.get(), global_queue_.get());
    if (!t->start() || !Add(t)) {
      LOG(WARNING)<<"start thread error, id: " << i;
      delete t;
      return false;
    }
  }

  io_thread_.reset(new IoThread(monitor_.get(), global_queue_.get()));
  if (!io_thread_->start()) {
    io_thread_.reset();
    return false;
  }

  return true;
}

}
