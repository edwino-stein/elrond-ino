#if !defined  _ELROND_RUNTIME_SERIAL_TRANSPORT_MODULE_INO_HPP
    #define _ELROND_RUNTIME_SERIAL_TRANSPORT_MODULE_INO_HPP

    #include "rtTypes.hpp"

    namespace elrond {
        namespace runtime {
            namespace modules {

                class Serial : public elrond::modules::BaseTransportModule {

                    protected:
                        elrond::channel::BaseChannelManager *cm = nullptr;

                        #if defined INO_PLATFORM
                            HardwareSerial *serial = nullptr;
                            bool simplexMode = false;
                            static HardwareSerial *getSerialByIndex(const int index);
                        #endif

                    public:

                        void onInit(elrond::config::ConfigMap &cfg) override;
                        void loop() override;

                        void send(elrond::byte data[], const elrond::sizeT length) override;
                        void setChannelManager(elrond::channel::BaseChannelManager *cm) override;
                };
            }
        }
    }

#endif
