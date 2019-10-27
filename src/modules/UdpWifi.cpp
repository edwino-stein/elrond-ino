#include "modules/UdpWifi.hpp"

using elrond::runtime::modules::UdpWifi;
using elrond::config::ConfigMap;

void UdpWifi::onInit(elrond::config::ConfigMap &cfg){

    this->getLoopControl().allow = true;
    this->getLoopControl().async = false;
    this->getLoopControl().time = 5;

    if(!cfg.isInt("port")) elrond::error(STR("Invalid or missing key \"port\"."));
    unsigned int port = cfg.asInt("port");

    if(port >= 65535) elrond::error(STR("Invalid or missing key \"port\"."));

    #if defined ESP_PLATFORM
        if(this->udp.begin(port) != 1)  elrond::error(STR("Failed to start the UDP server."));
    #endif
}

void UdpWifi::loop(){
    if(this->cm == nullptr) return;

    #if defined ESP_PLATFORM

        if(this->udp.parsePacket() == 0) return;

        const elrond::sizeT length = this->cm->getRxBufferSize();
        elrond::byte buffer[length];

        if(this->udp.read(buffer, length) != -1){
            this->cm->onReceive(buffer, length);
        }

    #endif
}

void UdpWifi::send(elrond::byte data[], const elrond::sizeT length){
    #if defined ESP_PLATFORM
        this->udp.beginPacket(this->udp.remoteIP(), this->udp.remotePort());
        this->udp.write(data, length);
        this->udp.endPacket();
    #endif
}

void UdpWifi::setChannelManager(elrond::channel::BaseChannelManager *cm){
    if(this->cm == nullptr) this->cm = cm;
}
