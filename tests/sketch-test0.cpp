#include "elrond-ino.hpp"
#include <csignal>

bool _loop = true;
void stopLoop(int signum){ _loop = false; }

int main(int argc, char const *argv[]){
    std::signal(SIGINT, stopLoop);

    setup();
    while(_loop) loop();

    return 0;
}
