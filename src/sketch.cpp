#include "rtTypes.hpp"
#include "RuntimeApp.hpp"
#include "modules/ModuleHandle.hpp"

using elrond::channel::BaseChannelManager;
using elrond::runtime::RuntimeApp;
using elrond::runtime::modules::ModuleHandle;

ModuleHandle *elrond::runtime::modules::__looped__ = nullptr;

void setup(void){

    elrond::__rtInstance__ = &elrond::runtime::__app_inst__;

    //Init serial for debug
    if(elrond::runtime::__app_inst__.dbo.wrapper != nullptr){
        elrond::runtime::__app_inst__.dbo.wrapper->initSerial();
    }

    elrond::dout().put(STR("Elrond Runtime for Arduino v"))
                  .put(ELROND_API_VERSION).put('.').put(ELROND_API_REVISION)
                  .putLn(STR("-alpha"));

    // Init the channel managers
    BaseChannelManager *c = elrond::runtime::__app_inst__.chm;
    while(c != nullptr){
        c->init();
        c = c->_nextNode;
    }

    //Init all module instances
    for(elrond::sizeT i = 0; i < elrond::runtime::modules::__total__; ++i)
        elrond::runtime::modules::__instances__[i].doInit();

    //Start the instances
    ModuleHandle **l = &elrond::runtime::modules::__looped__;
    for(elrond::sizeT i = 0; i < elrond::runtime::modules::__total__; ++i){
        ModuleHandle &m = elrond::runtime::modules::__instances__[i];
        if(m.module->getLoopControl().allow){
            *l = &m;
            l = &(m._nextNode);
        }
        m.module->onStart();
    }
}

void loop(void){
    ModuleHandle *l = elrond::runtime::modules::__looped__;
    while (l != nullptr){
        l->doLoop();
        l = l->_nextNode;
    }
}
