#include "rtTypes.hpp"
#include "RuntimeApp.hpp"
#include "modules/ModuleHandle.hpp"

using elrond::runtime::RuntimeApp;
using elrond::runtime::modules::ModuleHandle;


void setup(void){

    elrond::__rtInstance__ = &elrond::runtime::__app_inst__;

    //Init serial for debug
    if(elrond::runtime::__app_inst__.dbo.wrapper != nullptr){
        elrond::runtime::__app_inst__.dbo.wrapper->initSerial();
    }

    elrond::dout().put(STR("Elrond Runtime for Arduino v"))
                  .put(ELROND_API_VERSION).put('.').put(ELROND_API_REVISION)
                  .putLn(STR("-alpha"));

    //Init all module instances
    for(elrond::sizeT i = 0; i < elrond::runtime::modules::__total__; ++i)
        elrond::runtime::modules::__instances__[i].doInit();

}

void loop(void){
}
