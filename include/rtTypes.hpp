#if !defined  _ELROND_RUNTIME_TYPES_INO_HPP
#define _ELROND_RUNTIME_TYPES_INO_HPP

    #include "elrond.hpp"


    namespace elrond {
        namespace runtime {

            class RuntimeApp;
            class DebugOut;
            template<elrond::sizeT C> class StaticConfigMemory;

            namespace modules {
                using cfgHandleT = void (*)(elrond::interfaces::ModuleInterface * const);
                class ModuleHandle;
            }
        }
    }

    //Arduino Scetch
    void setup(void);
    void loop(void);

#endif
