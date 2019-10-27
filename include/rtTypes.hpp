#if !defined  _ELROND_RUNTIME_TYPES_INO_HPP
#define _ELROND_RUNTIME_TYPES_INO_HPP

    #include "elrond.hpp"

    namespace elrond {
        namespace runtime {

            class RuntimeApp;
            class DebugOut;
            template<elrond::sizeT C> class StaticConfigMemory;
            template<elrond::sizeT TXS, elrond::sizeT RXS> class ChannelManager;

            namespace modules {
                using cfgHandleT = void (*)(elrond::interfaces::ModuleInterface * const);
                class ModuleHandle;
                class GpioIno;
                class SerialRxTransport;
                class WifiManager;
            }
        }
    }

    //Arduino Scetch
    void setup(void);
    void loop(void);

#endif
