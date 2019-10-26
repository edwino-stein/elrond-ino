#if !defined  _ELROND_RUNTIME_TYPES_INO_HPP
#define _ELROND_RUNTIME_TYPES_INO_HPP

    #include "elrond.hpp"


    namespace elrond {
        namespace runtime {

            class RuntimeApp;
            class DebugOut;
            template<elrond::sizeT C> class StaticConfigMemory;

        }
    }

    //Arduino Scetch
    void setup(void);
    void loop(void);

#endif
