#if !defined  _ELROND_RUNTIME_UDP_WIFI_INO_HPP
    #define _ELROND_RUNTIME_WIFI_MANAGER_INO_HPP

    #include "rtTypes.hpp"

    namespace elrond {
        namespace runtime {
            namespace modules {
                class UdpWifi : public elrond::modules::BaseTransportModule {

                    protected:

                        elrond::channel::BaseChannelManager *cm = nullptr;

                        #if defined ESP_PLATFORM
                            WiFiUDP udp;
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
