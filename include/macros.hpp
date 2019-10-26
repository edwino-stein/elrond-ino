#if !defined  _ELROND_MACROS_INO_HPP
#define _ELROND_MACROS_INO_HPP

    #define CONCAT_(x,y) x##y
    #define CONCAT(x,y) CONCAT_(x,y)
    #define UNIQUE_NAME(prefix) CONCAT(prefix, __COUNTER__)

    #define NULL_CFG elrond::runtime::modules::ModuleHandle::nullInit
    #define KEY_CFG(key, value) c.push(key, value);
    #define CONFIG(SIZE, ...) [](elrond::interfaces::ModuleInterface * const m){\
                                 elrond::runtime::StaticConfigMemory<SIZE> scm;\
                                 elrond::config::ConfigMapAllocator c(scm);\
                                 __VA_ARGS__\
                                 m->onInit(c);}

    #define _INSTANCE(inst, name, cfg) elrond::runtime::modules::ModuleHandle(inst, cfg, name)
    #define INSTANCE(name, cfg) _INSTANCE(&name, #name, cfg)
    #define MODULES(...) elrond::runtime::modules::ModuleHandle elrond::runtime::modules::__instances__[]={\
                         _INSTANCE(&elrond::runtime::__app_inst__.gpio, "gpio-ino", NULL_CFG), __VA_ARGS__ };\
                         const elrond::sizeT elrond::runtime::modules::__total__ = sizeof(\
                         elrond::runtime::modules::__instances__)/sizeof(elrond::runtime::modules::ModuleHandle);

    #define CH_MGR(TRANS, TXS, RXS) elrond::runtime::ChannelManager<TXS,RXS> UNIQUE_NAME(__chm_)(TRANS, elrond::runtime::__app_inst__);

    #define DEBUG(serial, speed) elrond::runtime::DebugOut::DOWrapper __dout_wrapper__(\
                                 serial, elrond::runtime::__app_inst__,[](){\
                                 serial.begin(speed); while(!serial);});

    #define OPTIONS(...) __VA_ARGS__

    #define SETUP(mods, opts) elrond::interfaces::RuntimeInterface *elrond::__rtInstance__ = nullptr;\
                              elrond::runtime::RuntimeApp elrond::runtime::__app_inst__;\
                              mods\
                              opts
#endif
