#include "modules/WifiManager.hpp"

using elrond::runtime::modules::WifiManager;
using elrond::config::ConfigMap;


void WifiManager::onInit(ConfigMap &cfg){

    this->getLoopControl().allow = true;
    this->getLoopControl().async = false;
    this->getLoopControl().time = 100;

    #if defined ARDUINO_ARCH_AVR
        if(WifiManager::status() == WifiManager::WifiStatus::NO_SHIELD){
            elrond::error(STR("No Wi-Fi shield detected."));
        }
    #endif

    if(!cfg.isString("ssid")) elrond::error(STR("Invalid or missing key \"ssid\"."));
    const char *ssid = cfg.asString("ssid");

    if(!cfg.isString("password")) elrond::error(STR("Invalid or missing key \"password\"."));
    const char *password = cfg.asString("password");

    #if defined ARDUINO_ARCH_AVR
        WiFi.begin((char *) ssid, (char *) password);
        this->_status = WifiManager::status();
        this->onStatusChanged();
    #endif
}

void WifiManager::loop(){
    #if defined ARDUINO_ARCH_AVR

        WifiManager::WifiStatus s = WifiManager::status();
        if(s == this->_status) return;

        this->_status = s;
        this->onStatusChanged();

    #endif
}

#if defined ARDUINO_ARCH_AVR

    void WifiManager::onStatusChanged() const {

        switch (this->_status) {

            case WifiManager::WifiStatus::CONNECTED:
                elrond::dout().putLn(STR(" * Connected to Wi-Fi network"));

                elrond::dout().put(STR("\t- SSID = "))
                              .putLn(WiFi.SSID());

                elrond::dout().put(STR("\t- IP = "))
                              .putLn(WiFi.localIP());

            break;

            case WifiManager::WifiStatus::DISCONNECTED:
                elrond::dout().putLn(STR(" * Disconnected from Wi-Fi network"));
            break;

            case WifiManager::WifiStatus::IDLE:
                elrond::dout().putLn(STR(" * Trying connection with Wi-Fi network..."));
            break;

            case WifiManager::WifiStatus::NO_SSID_AVAIL:
                elrond::dout().putLn(STR(" * Wi-Fi network out of range..."));
            break;

            default: return;
        }
    }

    WifiManager::WifiStatus WifiManager::status(){
        return (WifiManager::WifiStatus) WiFi.status();
    }

#endif
