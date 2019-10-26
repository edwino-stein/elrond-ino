#include "elrond-ino.hpp"
#include <csignal>

bool _loop = true;
elrond::runtime::VirtualSerial Serial(std::cout);
void stopLoop(int signum){ _loop = false; }

elrond::modules::Example test;
elrond::modules::Loopback transport;

SETUP(
    MODULES(
        INSTANCE(test, CONFIG(100,
            KEY_CFG("allowLoop", true)
            KEY_CFG("timeLoop", 500)
        )),
        INSTANCE(transport, NULL_CFG)
    ),
    OPTIONS(
        DEBUG(Serial, 0)
        CH_MGR(transport, 5, 5)
    )
)

int main(int argc, char const *argv[]){
    std::signal(SIGINT, stopLoop);

    setup();
    while(_loop) loop();

    return 0;
}
