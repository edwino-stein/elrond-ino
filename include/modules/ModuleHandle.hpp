#if !defined  _ELROND_RUNTIME_MODULE_HANDLE_HPP
    #define _ELROND_RUNTIME_MODULE_HANDLE_HPP

    #include "rtTypes.hpp"

    namespace elrond {
        namespace runtime {
            namespace modules {

                class ModuleHandle {

                    public:

                        elrond::interfaces::ModuleInterface * const module;
                        const cfgHandleT initModule;
                        const char *name;
                        ModuleHandle *_nextNode;

                        ModuleHandle(elrond::interfaces::ModuleInterface *module, cfgHandleT initModule, const char *name);

                        static void nullInit(elrond::interfaces::ModuleInterface * const mod);
                        void doInit() const;
                };

                extern elrond::runtime::modules::ModuleHandle __instances__[];
                extern const elrond::sizeT __total__;
            }
        }
    }

#endif
