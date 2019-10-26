#include "modules/ModuleHandle.hpp"
#include "StaticConfigMemory.hpp"

using namespace elrond::runtime::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ModuleInterface;
using elrond::runtime::StaticConfigMemory;

/*  ****************************************************************************
    ******** Implementation for elrond::runtime::modules::ModuleHandle *********
    ****************************************************************************/

ModuleHandle::ModuleHandle(ModuleInterface *module, cfgHandleT initModule, const char *name):
module(module), initModule(initModule), name(name), _nextNode(nullptr), timout(0){}

void ModuleHandle::doInit() const {

    elrond::dout().put(STR("Initializing instance \""))
                  .put(this->name)
                  .putLn(STR("\"..."));

    if(this->initModule != nullptr) this->initModule(this->module);
    else ModuleHandle::nullInit(this->module);
}

void ModuleHandle::nullInit(elrond::interfaces::ModuleInterface * const mod){
    StaticConfigMemory<0> scm;
    elrond::config::ConfigMapAllocator c(scm);
    mod->onInit(c);
}
