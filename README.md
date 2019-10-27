# Elrond Runtime Application for Arduino

Runtime for Elrond Modules for Arduino IDE based platforms. The runtime application is the engine of projects based on Elrond Modules. The application runtime is responsible for load and initialize the modules instances and control to everything runs fine.

## Compatibility
 - Arduino Uno;
 - Arduino Nano (ATmega 328p);
 - Arduino Mega (ATmega 2560);
 - ESP32;

## Build and run
First of all, you will need of build-essentials package for you distro linux. The requirements are:
 - **GNU Make**;
 - **Git**;
 - **Arduino IDE**

After the repository clone, will need initialize the git submodule:
```
$ git submodule init
$ git submodule update
```

To install to Arduino IDE (Linux only):
```
$ make arduino-install
```

## Example sketch
Copy and paste the code in bellow in a new Arduino Sketch and upload to your board.

```c++
#include <elrond-ino.hpp>

elrond::modules::Example test;

SETUP(
    MODULES(
        INSTANCE(test, CONFIG(100,
            KEY_CFG("allowLoop", true)
            KEY_CFG("timeLoop", 1000)
        ))
    ),
    OPTIONS(
        DEBUG(Serial, 115200)
    )
)
```

In the `Serial Monitor` with speed defined to `115200 baud`, the output will be some like:
```
Elrond Runtime for Arduino v0.0-alpha
Initializing instance "gpio-ino"...
Initializing instance "test"...
Example::onInit
Example::onStart
Example::loop (sync)
Example::loop (sync)
Example::loop (sync)
```
