#include "modules/Serial.hpp"
#include "DebugOut.hpp"

using elrond::runtime::modules::Serial;
using elrond::config::ConfigMap;
using elrond::runtime::DebugOut;

void Serial::onInit(elrond::config::ConfigMap &cfg){

    this->getLoopControl().allow = true;
    this->getLoopControl().async = false;
    this->getLoopControl().time = 100;

    #if defined INO_PLATFORM

        int index = 0;
        if(cfg.isInt("serial")) index = cfg.asInt("serial");

        this->serial = Serial::getSerialByIndex(index);
        if(this->serial == nullptr) elrond::error(STR("Invalid serial interface\"."));

        HardwareSerial *debugSerial = nullptr;
        if(((DebugOut &) elrond::app().dout()).wrapper != nullptr){
            debugSerial = &(((DebugOut &) elrond::app().dout()).wrapper->debugOut);
        }

        if(this->serial == debugSerial){
            this->simplexMode = true;
            elrond::dout().putLn(STR(" * WARNING: The serial selected is same of debug output"))
                          .putLn(STR(" * WARNING: The module will operate in RX mode only"));
        }
        else{
            #if defined ARDUINO_AVR_NANO || defined ARDUINO_AVR_UNO
                this->serial->begin(9600);
            #elif defined ARDUINO_AVR_MEGA2560 || defined ARDUINO_AVR_MEGA
                this->serial->begin(115200);
            #elif defined ESP_PLATFORM
                this->serial->begin(115200);
            #endif
        }
    #endif
}

void Serial::loop(){
    if(this->cm == nullptr) return;

    #if defined INO_PLATFORM

        if(!this->serial->available()) return;

        const elrond::sizeT length = this->cm->getRxBufferSize();
        elrond::byte buffer[length];

        const elrond::sizeT received = this->serial->readBytes(buffer, length);
        if(received == length) this->cm->onReceive(buffer, length);
        this->serial->flush();

    #endif
}

void Serial::send(elrond::byte data[], const elrond::sizeT length){
    #if defined INO_PLATFORM
        if(this->simplexMode) return;
        this->serial->write(data, length);
    #endif
}

void Serial::setChannelManager(elrond::channel::BaseChannelManager *cm){
    if(this->cm == nullptr) this->cm = cm;
}

#if defined INO_PLATFORM

    HardwareSerial *Serial::getSerialByIndex(const int index){

        #if defined ARDUINO_AVR_NANO || defined ARDUINO_AVR_UNO
            return index == 0 ? &::Serial : nullptr;
        #elif defined ARDUINO_AVR_MEGA2560 || defined ARDUINO_AVR_MEGA

            switch (index) {
                case 0: return &::Serial; break;
                case 1: return &::Serial1; break;
                case 2: return &::Serial2; break;
                case 3: return &::Serial3; break;
            }
            return nullptr;

        #elif defined ESP_PLATFORM
            return index == 0 ? &::Serial : nullptr;
        #else
            return nullptr;
        #endif
    }

#endif
