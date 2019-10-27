#if !defined  _ELROND_RUNTIME_WIFI_MANAGER_INO_HPP
    #define _ELROND_RUNTIME_WIFI_MANAGER_INO_HPP

    #include "rtTypes.hpp"

    #if defined INO_PLATFORM
        #include <WiFi.h>
    #endif

    namespace elrond {
        namespace runtime {
            namespace modules {
                class WifiManager : public elrond::modules::BaseModule {

                    public:
                        #if defined INO_PLATFORM

                            //Enums
                            enum class WifiStatus {
                                CONNECTED = WL_CONNECTED,               // Assigned when connected to a WiFi network;
                                NO_SHIELD = WL_NO_SHIELD,               // Assigned when no WiFi shield is present;
                                IDLE = WL_IDLE_STATUS,                  // It is a temporary status assigned when WiFi.begin() is called and remains active until the number of attempts expires (resulting in WL_CONNECT_FAILED) or a connection is established (resulting in WL_CONNECTED);
                                NO_SSID_AVAIL = WL_NO_SSID_AVAIL,       // Assigned when no SSID are available;
                                SCAN_COMPLETED = WL_SCAN_COMPLETED,     // Assigned when the scan networks is completed;
                                CONNECT_FAILED = WL_CONNECT_FAILED,     // Assigned when the connection fails for all the attempts;
                                CONNECTION_LOST = WL_CONNECTION_LOST,    // Assigned when the connection is lost;
                                DISCONNECTED = WL_DISCONNECTED          // Assigned when disconnected from a network;
                            };

                            static WifiStatus status();

                        #endif

                        void onInit(elrond::config::ConfigMap &cfg) override;
                        void loop() override;

                    protected:

                        #if defined INO_PLATFORM
                            WifiStatus _status = WifiStatus::IDLE;
                            void onStatusChanged() const;
                        #endif
                };
            }
        }
    }

#endif
