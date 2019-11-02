# Elrond Runtime Application for Arduino

Runtime for Elrond Modules for Arduino IDE based platforms. The runtime application is the engine of projects based on Elrond Modules. The application runtime is responsible for load and initialize the modules instances and control to everything runs fine.

## Compatibility
 - **Arduino Uno**;
 - **Arduino Nano** `*`;
 - **Arduino Mega**;
 - **ESP32**;

> `*` The Arduino with **ATmega168** is not recommended because low memory.
## Build and run
Currently the library build process is based in makefile on linux. The requirements are:
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

elrond::Example test;

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
> **To more details, see [Sketch configuration structure](#sketch-configuration-structure)**

In the `Serial Monitor` with speed defined to `115200 baud`, the output will be some like:
```
Elrond Runtime for Arduino v0.0-alpha
Initializing instance "gpio-ino"...
Initializing instance "test"...
Example::onInit
Starting modules...
Example::onStart
Application running...
Example::loop (sync)
Example::loop (sync)
Example::loop (sync)
```
## Sketch configuration structure
The sketch structure used to configure an Elrond Application on Arduino IDE must have inicialized by `#include` macros of modules that will be used. After comes the instances definitions, in variable declaration C++ style, like `module_type instance_name;`. Bellow of the instances definitions, must have the `SETUP(MODULES(...), OPTIONS(...))` macro function call.

##### The `MODULES(...)` paramter:
Macro function with list of instances used by application. To define an instance, must be called the macro function `INSTANCE(inst, CONFIG(...))`, where:
 - `inst`: Module instance name;
 - `CONFIG(...)`: Module configuration. The module configuration must be made using the macro function `CONFIG(buffer_s, KEY_CFG() ... )`. The `buffer_s` parameter is an unsigned integer to defines an internal buffer used to store configuration data temporarily. After the buffer size, must have a no comma (`,`) separated list of `KEY_CFG(key, value)`. The `key` parameter is a `const char *` string that will be associated to the `value` paramter. The `value` can be of the type `int`, `double`, `char`, `bool` or `const char *`. In case the module does not require a configuration, use the `NULL_CFG` macro instead of `CONFIG()` macro function.

> Every module have your own set of configuration params, see documentation of every one.

##### The `OPTIONS(...)` paramter:
Macro function used to define extra options of the application, like the **channel managers**. The parameters must be in a no comma (`,`) separated list, and can be:
 - `CH_MGR(transport, tx, rx)`: Macro function to define a channel manager. The `transport` parameter must be an instance of a transport module. The `tx` and `rx` parameters indicate the total of transmit and receive channels, respectively;
 - `DEBUG(serial, baud_rate)`: Macro function to define a serial interface used to debug output. The `serial` parameter must be an instance of `HardwareSerial`. The `baud_rate` defines the data speed for serial setup.

### More complex example
For better understanding, a more complex example of sketch structure:

```c++
// Includes
#include <elrond-ino.hpp>

// Module instances
elrond::DigitalLed led;
elrond::runtime::Serial serial;

SETUP(
    MODULES(
        INSTANCE(led, CONFIG(100,
            KEY_CFG("pin", 13)
            KEY_CFG("channel", 0)
        )),
        INSTANCE(serial, CONFIG(100,
            KEY_CFG("serial", 0)
        ))
    ),
    OPTIONS(
        CH_MGR(serial, 0, 1)
    )
)
```

In this example, the channel manager is defined for a receive channel by the `serial` module. The `led` module will listen to channel `0`. When this channel is triggered, the digital pin `13` will be triggered and the connected LED will flash (built-in led on Arduino boards).

## Elrond modules
The Internal modules from **Elrond Common Library** are available. More details see [Elrond Common Library - Internal Modules](https://github.com/edwino-stein/elrond-common#internal-modules).

### elrond::runtime::Serial
This is a Serial/UART transport module. The module configuration is:
 - **serial** (int): Index of Arduino serial object;
> Arduino **Uno** and **Nano** have the baud rate defined to `9600`.
> Arduino **Mega** and **Esp32** have the baud rate defined to `115200`.

### Experimental and unstable modules
This modules are unstable and not recommend to use yet.
 - `elrond::runtime::modules::UdpWifi`: **Udp** transport module;
 - `elrond::runtime::modules::WifiManager`: **Wifi Manager** for Esp32;

> Maybe will be modified or removed in the future.
