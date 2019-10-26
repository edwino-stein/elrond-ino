#include "modules/GpioIno.hpp"

//redef from Arduino.h
#define INPUT 0x0

using elrond::runtime::modules::GpioIno;
using elrond::modules::BaseGpioModule;
using elrond::config::ConfigMap;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;
using elrond::gpio::PwmPin;
using elrond::gpio::ServoPin;
using elrond::gpio::AinPin;

/*  ****************************************************************************
    *********** Implementation for elrond::runtime::modules::GpioIno ***********
    ****************************************************************************/

GpioIno::GpioIno(){
    this->getLoopControl().allow = false;
    this->getLoopControl().async = false;
    this->getLoopControl().time = 0;
}

void GpioIno::attach(elrond::gpio::BaseGpioPin &pin){

    bool error = false;
    switch (pin.getType()) {

        case elrond::GpioType::DOUT: error = !this->initDOutPin(pin); break;
        case elrond::GpioType::PWM: error = !this->initPwmPin(pin); break;
        case elrond::GpioType::SERVO: error = !this->initServoPin(pin); break;
        case elrond::GpioType::AIN: error = !this->initAInPin(pin); break;

        default:
            error = true;
    }

    if(error){
        elrond::dout().put(STR("pin #")).putLn(pin.getNumber());
        elrond::error(STR("GPIO mode error"));
    }
}

bool GpioIno::initDOutPin(BaseGpioPin &pin) const {
    if(!this->isValidDPin(pin.getNumber())) return false;

    #if defined INO_PLATFORM
        ::pinMode(pin.getNumber(), OUTPUT);
    #endif

    pin.setReadHandle(GpioIno::readDIO);
    pin.setWriteHandle(GpioIno::writeDIO);

    return true;
}

elrond::word GpioIno::readDIO(BaseGpioPin &pin){
    #if defined INO_PLATFORM
        elrond::word data = ::digitalRead(pin.getNumber());
        ((DOutPin &) pin).value = data;
        return data > 0 ? HIGH_VALUE : LOW_VALUE;
    #else
        return ((DOutPin &) pin).value;
    #endif
}

void GpioIno::writeDIO(BaseGpioPin &pin, elrond::word &data){
    #if defined INO_PLATFORM
        ::digitalWrite(pin.getNumber(), data > 0 ? HIGH : LOW);
        ((DOutPin &) pin).value = data > 0 ? HIGH : LOW;
    #else
        ((DOutPin &) pin).value = data > 0 ? HIGH_VALUE : LOW_VALUE;

        #if defined GENERIC_STD_PLATFORM
            std::cout << "#" << pin.getNumber() << " => " << ((DOutPin &) pin).value << std::endl;
        #endif

    #endif
}

bool GpioIno::initPwmPin(BaseGpioPin &pin) const {
    if(!this->isValidPwmPin(pin.getNumber())) return false;

    #if defined ARDUINO_ARCH_AVR
        ::pinMode(pin.getNumber(), OUTPUT);
    #endif

    pin.setReadHandle(GpioIno::readPwm);
    pin.setWriteHandle(GpioIno::writePwm);

    return true;
}

elrond::word GpioIno::readPwm(BaseGpioPin &pin){
    return ((PwmPin &) pin).value;
}

void GpioIno::writePwm(BaseGpioPin &pin, elrond::word &data){

    #if defined ARDUINO_ARCH_AVR

        elrond::word d = elrond::map(
                data,
                LOW_VALUE,
                HIGH_VALUE,
                MIN_D2A_VALUE,
                MAX_D2A_VALUE
        );

        ::analogWrite(pin.getNumber(), d);
        ((PwmPin &) pin).value = d;

    #else

        ((PwmPin &) pin).value = data;

        elrond::word d = elrond::map(
                data,
                LOW_VALUE,
                HIGH_VALUE,
                MIN_D2A_VALUE,
                MAX_D2A_VALUE
        );

        #if defined GENERIC_STD_PLATFORM
            std::cout << "#" << pin.getNumber() << " => " << d << std::endl;
        #endif

    #endif
}

bool GpioIno::initServoPin(BaseGpioPin &pin) const {

    if(!this->isValidPwmPin(pin.getNumber())) return false;

    #if defined ARDUINO_ARCH_AVR
        ((ServoPin &) pin).value.attach(pin.getNumber());
    #endif

    pin.setReadHandle(GpioIno::readServo);
    pin.setWriteHandle(GpioIno::writeServo);

    return true;
}

elrond::word GpioIno::readServo(BaseGpioPin &pin){
    #if defined ARDUINO_ARCH_AVR
        return elrond::map(
            ((ServoPin &) pin).value.read(),
            MIN_ANGLE_VALUE,
            MAX_ANGLE_VALUE,
            LOW_VALUE,
            HIGH_VALUE
        );
    #else
        return ((ServoPin &) pin).value;
    #endif
}

void GpioIno::writeServo(BaseGpioPin &pin, elrond::word &data){

    #if defined ARDUINO_ARCH_AVR

        ((ServoPin &) pin).value.write(elrond::map(
            data,
            LOW_VALUE,
            HIGH_VALUE,
            MIN_ANGLE_VALUE,
            MAX_ANGLE_VALUE
        ));

    #else
        ((ServoPin &) pin).value = data;

        elrond::word angle = elrond::map(
            data,
            LOW_VALUE,
            HIGH_VALUE,
            MIN_ANGLE_VALUE,
            MAX_ANGLE_VALUE
        );

        #if defined GENERIC_STD_PLATFORM
            std::cout << "#" << pin.getNumber() << " => " << angle << std::endl;
        #endif

    #endif
}

bool GpioIno::initAInPin(elrond::gpio::BaseGpioPin &pin) const {
    if(!this->isValidAPin(pin.getNumber())) return false;
    pin.setReadHandle(GpioIno::readAIn);
    return true;
}

elrond::word GpioIno::readAIn(elrond::gpio::BaseGpioPin &pin){

    #if defined INO_PLATFORM
        elrond::word data = ::analogRead(pin.getNumber());
        ((AinPin &) pin).value = data;
        return elrond::map(
            data,
            MIN_ANALOG_VALUE,
            MAX_ANALOG_VALUE,
            LOW_VALUE,
            HIGH_VALUE
        );
    #else
        return ((AinPin &) pin).value;
    #endif

}

bool GpioIno::isValidDPin(const int pin) const {
    #if defined ARDUINO_ARCH_AVR
        return (pin >= 0) && (pin < INO_TOTAL_DO_PIN);
    #else
        return true;
    #endif
}

bool GpioIno::isValidPwmPin(const int pin) const {

    #if defined ARDUINO_ARCH_AVR

        if(!this->isValidDPin(pin)) return false;

        #if defined ARDUINO_AVR_MEGA2560 || ARDUINO_AVR_MEGA2560
            if(pin > 13) return false;
        #endif

        return ((INO_ALLOW_PWM & (0x1 << pin)) >> pin) == 1;

    #else
        return true;
    #endif
}

bool GpioIno::isValidAPin(const int pin) const {
    #if defined ARDUINO_ARCH_AVR
        return (pin >= 0) && (pin < INO_TOTAL_AI_PIN);
    #else
        return true;
    #endif
}

