#include "RuntimeApp.hpp"

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
    elrond::error(STR("Invalid input service."));
}

BaseChannelManager &RuntimeApp::getChannelManager(const elrond::sizeT id) const {
    elrond::error(STR("Invalid channel manager."));
}

const DebugOutInterface &RuntimeApp::dout() const {
    elrond::error(STR("Invalid Debug service."));
}

void RuntimeApp::onError(const char *error){
    RuntimeApp::fatalError();
}

#if defined INO_PLATFORM
    void RuntimeApp::onError(const __FlashStringHelper *error){
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

