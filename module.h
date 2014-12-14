#ifndef MODULE_H_
#define MODULE_H_

#include "include/object_saver.h"

namespace gm {
class ModuleManager;

class Module {
  public:
    virtual ~Module() {
    }

    uint32 id() const {
      return id_;
    }
    uint32 key() const {
      return id();
    }

    const std::string& name() const {
      return name_;
    }

    virtual bool init() = 0;
    virtual void destroy() = 0;

    virtual void process(void* pkg) = 0;

  protected:
    Module(const std::string& mod_name, uint32 mod_id, ModuleManager* mgr)
        : id_(mod_id), name_(mod_name), mgr_(mgr) {
      DCHECK(!mod_name.empty());

      DCHECK_NOTNULL(mgr);
    }

    const uint32 id_;
    const std::string name_;

    ModuleManager* mgr_;

  private:
    DISALLOW_COPY_AND_ASSIGN(Module);
};

class ModuleManager : public ObjectVectorSaver<uint32, Module> {
  public:
    ModuleManager()
        : ObjectVectorSaver<uint32, Module>(new DefaultObjectSavePolicy<Module>) {
    }
    virtual ~ModuleManager();

    bool init(const std::string& mod_dir);

    Module* findById(uint32 id);
    Module* findByName(const std::string& name);

  private:

    DISALLOW_COPY_AND_ASSIGN(ModuleManager);
};
}
#endif /* MODULE_H_ */
