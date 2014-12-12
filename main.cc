#include "module.h"
#include "gm_server.h"

DEFINE_int32(gm_worker, 4, "the number of worker");

int main(int argc, char*argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::google::ParseCommandLineFlags(&argc, &argv, true);

  scoped_ptr<gm::GmServer> serv;
  serv.reset(new gm::GmServer(static_cast<uint32>(FLAGS_gm_worker)));
  if (!serv->init() || !serv->start()) {
    LOG(WARNING)<< "start gm server error";
    return -1;
  }

  // todo: main thread.

  return 0;
}

