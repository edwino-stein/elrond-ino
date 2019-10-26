#include "rtTypes.hpp"
#include "RuntimeApp.hpp"

using elrond::interfaces::RuntimeInterface;
using elrond::runtime::RuntimeApp;

RuntimeApp elrond::runtime::__app_inst__;
RuntimeInterface *elrond::__rtInstance__ = nullptr;

void setup(void){

    elrond::__rtInstance__ = &elrond::runtime::__app_inst__;

    //Init serial for debug
    if(elrond::runtime::__app_inst__.dbo.wrapper != nullptr){
        elrond::runtime::__app_inst__.dbo.wrapper->initSerial();
    }

    elrond::dout().put(STR("Elrond Runtime for Arduino v"))
                  .put(ELROND_API_VERSION).put('.').put(ELROND_API_REVISION)
                  .putLn(STR("-alpha"));

}

void loop(void){
}
