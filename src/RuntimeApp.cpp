#include "RuntimeApp.hpp"
#include "modules/ModuleHandle.hpp"

using namespace elrond::runtime;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ModuleInterface;
using elrond::modules::BaseGpioModule;
using elrond::modules::BaseInputDriverModule;
using elrond::channel::BaseChannelManager;
using elrond::interfaces::DebugOutInterface;

/*  ****************************************************************************
    ************** Implementation for elrond::runtime::RuntimeApp **************
    ****************************************************************************/

BaseGpioModule &RuntimeApp::getGpioService() const {
    elrond::error(STR("Invalid GPIO driver."));
}

BaseInputDriverModule &RuntimeApp::getInputService(const elrond::sizeT id) const {

    BaseInputDriverModule *m = nullptr;
    elrond::sizeT j = 0;

    for(elrond::sizeT i = 0; i < elrond::runtime::modules::__total__; ++i){
        if(elrond::runtime::modules::__instances__[i].module->getType() != elrond::ModuleType::INPUT) continue;
        if(j++ != id) continue;
        m = (BaseInputDriverModule *) elrond::runtime::modules::__instances__[i].module;
        break;
    }

    if(m == nullptr) elrond::error(STR("Invalid input service."));
    return *((BaseInputDriverModule *) m);
}

BaseChannelManager &RuntimeApp::getChannelManager(const elrond::sizeT id) const {

    BaseChannelManager *c = this->chm;
    elrond::sizeT i = 0;

    while(c != nullptr){
        if(i++ == id) break;
        c = c->_nextNode;
    }

    if(c == nullptr) elrond::error(STR("Invalid channel manager."));
    return *c;
}

const DebugOutInterface &RuntimeApp::dout() const { return this->dbo; }

void RuntimeApp::onError(const char *error){
    this->dbo.put(STR("ERROR: ")).putLn(error);
    RuntimeApp::fatalError();
}

#if defined INO_PLATFORM
    void RuntimeApp::onError(const __FlashStringHelper *error){
        this->dbo.put(STR("ERROR: ")).putLn(error);
        RuntimeApp::fatalError();
    }
#endif

void RuntimeApp::fatalError(){
    #if defined INO_PLATFORM
        ::pinMode(LED_BUILTIN, OUTPUT);
        while(true){
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            elrond::delay(100);
        }
    #else
        std::exit(1);
    #endif
}

void RuntimeApp::pushChannelManager(BaseChannelManager *chm){
    BaseChannelManager **c = &(this->chm);
    while(*c != nullptr) c = &((*c)->_nextNode);
    *c = chm;
}
