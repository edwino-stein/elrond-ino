#include "elrond-ino.hpp"
#include <csignal>

bool _loop = true;
elrond::runtime::VirtualSerial Serial(std::cout);
void stopLoop(int signum){ _loop = false; }

elrond::modules::Example test;

SETUP(
    MODULES(
        INSTANCE(test, CONFIG(100,
            KEY_CFG("allowLoop", true)
            KEY_CFG("timeLoop", 500)
        ))
    ),
    OPTIONS(
        DEBUG(Serial, 0)
    )
)

int main(int argc, char const *argv[]){
    std::signal(SIGINT, stopLoop);

    setup();
    while(_loop) loop();

    return 0;
}
