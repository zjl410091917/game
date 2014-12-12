#include "gm_queue.h"
#include "worker_thread.h"

DEFINE_int32(exec_count, 1, "");

namespace gm {

GmWorker::~GmWorker() {
}

void GmWorker::loop() {
  GmQueue* q = NULL;
  while (!stop_) {
    q = global_queue_->pop();
    if (q == NULL) {
      waitInternal();
      continue;
    }

    processInternal(q);
  }
}

void GmWorker::waitInternal() {
  monitor_->wait();
}

void GmWorker::processInternal(GmQueue* q) {
  void* pkg;
  bool need_relink;

  Module* module = q->module();
  for (int32 i = 0; i < FLAGS_exec_count; ++i) {
    need_relink = q->pop(&pkg);
    if (pkg == NULL) return;

    module->process(pkg);

    if (!need_relink) return;
  }

  if (need_relink) {
    global_queue_->push(q);
  }
}

}

