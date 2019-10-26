#include "rtTypes.hpp"
#include "RuntimeApp.hpp"

using elrond::interfaces::RuntimeInterface;
using elrond::runtime::RuntimeApp;

RuntimeApp elrond::runtime::__app_inst__;
RuntimeInterface *elrond::__rtInstance__ = nullptr;

void setup(void){

    elrond::__rtInstance__ = &elrond::runtime::__app_inst__;

}

void loop(void){
}
