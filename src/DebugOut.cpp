#include "DebugOut.hpp"
#include "RuntimeApp.hpp"

using namespace elrond::runtime;
using elrond::interfaces::DebugOutInterface;


/*  ****************************************************************************
    *************** Implementation for elrond::runtime::DebugOut ***************
    ****************************************************************************/

DebugOut::DOWrapper::DOWrapper(SerialT &debugOut, elrond::runtime::RuntimeApp &app, void (*initSerial)(void)):
debugOut(debugOut), initSerial(initSerial){
    app.dbo.wrapper = this;
}

const DebugOutInterface& DebugOut::put(const char c[]) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(c);
    return *this;
}

const DebugOutInterface& DebugOut::put(char c) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(c);
    return *this;
}

const DebugOutInterface& DebugOut::put(unsigned char c) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(c);
    return *this;
}

const DebugOutInterface& DebugOut::put(int i) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(i);
    return *this;
}

const DebugOutInterface& DebugOut::put(unsigned int i) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(i);
    return *this;
}

const DebugOutInterface& DebugOut::put(long l) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(l);
    return *this;
}

const DebugOutInterface& DebugOut::put(unsigned long l) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(l);
    return *this;
}

const DebugOutInterface& DebugOut::put(double d) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.print(d);
    return *this;
}

#if defined INO_PLATFORM
    const DebugOutInterface& DebugOut::put(const __FlashStringHelper *fs) const {
        if(this->wrapper != nullptr) this->wrapper->debugOut.print(fs);
        return *this;
    }

    const DebugOutInterface& DebugOut::put(const Printable& p) const {
        if(this->wrapper != nullptr) this->wrapper->debugOut.print(p);
        return *this;
    }

    const DebugOutInterface& DebugOut::put(const String &s) const {
        if(this->wrapper != nullptr) this->wrapper->debugOut.print(s);
        return *this;
    }
#endif


const DebugOutInterface& DebugOut::putLn(const char c[]) const { return this->put(c).putLn(); }
const DebugOutInterface& DebugOut::putLn(char c) const { return this->put(c).putLn(); }
const DebugOutInterface& DebugOut::putLn(unsigned char c) const { return this->put(c).putLn(); }
const DebugOutInterface& DebugOut::putLn(int i) const { return this->put(i).putLn(); }
const DebugOutInterface& DebugOut::putLn(unsigned int i) const { return this->put(i).putLn(); }
const DebugOutInterface& DebugOut::putLn(long l) const { return this->put(l).putLn(); }
const DebugOutInterface& DebugOut::putLn(unsigned long l) const { return this->put(l).putLn(); }
const DebugOutInterface& DebugOut::putLn(double d) const { return this->put(d).putLn(); }

#if defined INO_PLATFORM
    const DebugOutInterface& DebugOut::putLn(const __FlashStringHelper *fs) const { return this->put(fs).putLn(); }
    const DebugOutInterface& DebugOut::putLn(const Printable& p) const { return this->put(p).putLn(); }
    const DebugOutInterface& DebugOut::putLn(const String &s) const { return this->put(s).putLn(); }
#endif

const DebugOutInterface& DebugOut::putLn(void) const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.println();
    return *this;
}

const DebugOutInterface& DebugOut::flush() const {
    if(this->wrapper != nullptr) this->wrapper->debugOut.flush();
    return *this;
}

#if defined GENERIC_STD_PLATFORM
    VirtualSerial::VirtualSerial(std::ostream &os) : os(os){}
    void VirtualSerial::begin(unsigned long baud){}
    VirtualSerial::operator bool(){ return true; }
    void VirtualSerial::print(const char c[]){ this->os << c; }
    void VirtualSerial::print(char c){ this->os << c; }
    void VirtualSerial::print(unsigned char c){ this->os << c; }
    void VirtualSerial::print(int i){ this->os << i; }
    void VirtualSerial::print(unsigned int i){ this->os << i; }
    void VirtualSerial::print(long l){ this->os << l; }
    void VirtualSerial::print(unsigned long l){ this->os << l; }
    void VirtualSerial::print(double d){ this->os << d; }
    void VirtualSerial::println(void){ this->os << std::endl; }
    void VirtualSerial::flush(){ this->os << std::flush; }
#endif
