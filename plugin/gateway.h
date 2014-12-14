#ifndef GATEWAY_H_
#define GATEWAY_H_

#include "module.h"

namespace gm {

class GatewayModule : public Module {
  public:
    explicit GatewayModule(ModuleManager* mgr);
    virtual ~GatewayModule();

  private:
    virtual bool init();
    virtual void destroy();

    virtual void process(void* pkg);

    DISALLOW_COPY_AND_ASSIGN(GatewayModule);
};
}

#endif /* GATEWAY_H_ */
