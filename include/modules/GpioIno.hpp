#if !defined  _ELROND_RUNTIME_GPIO_INO_HPP
    #define _ELROND_RUNTIME_GPIO_INO_HPP

    #include "rtTypes.hpp"

    #define MAX_D2A_VALUE 0xFF
    #define MIN_D2A_VALUE 0x0

    #define MAX_ANGLE_VALUE 180
    #define MIN_ANGLE_VALUE 0

    #define MAX_ANALOG_VALUE 0x3FF
    #define MIN_ANALOG_VALUE 0x0

    namespace elrond {
        namespace runtime {
            namespace modules {

                class GpioIno : public elrond::modules::BaseGpioModule {

                    protected:

                        bool isValidDPin(const int pin) const;
                        bool isValidPwmPin(const int pin) const;
                        bool isValidAPin(const int pin) const;

                        bool initDOutPin(elrond::gpio::BaseGpioPin &pin) const;
                        static elrond::word readDIO(elrond::gpio::BaseGpioPin &pin);
                        static void writeDIO(elrond::gpio::BaseGpioPin &pin, elrond::word &data);

                        bool initPwmPin(elrond::gpio::BaseGpioPin &pin) const;
                        static elrond::word readPwm(elrond::gpio::BaseGpioPin &pin);
                        static void writePwm(elrond::gpio::BaseGpioPin &pin, elrond::word &data);

                        bool initServoPin(elrond::gpio::BaseGpioPin &pin) const;
                        static elrond::word readServo(elrond::gpio::BaseGpioPin &pin);
                        static void writeServo(elrond::gpio::BaseGpioPin &pin, elrond::word &data);

                        bool initAInPin(elrond::gpio::BaseGpioPin &pin) const;
                        static elrond::word readAIn(elrond::gpio::BaseGpioPin &pin);

                    public:
                        GpioIno();
                        void attach(elrond::gpio::BaseGpioPin &pin) override;
                };
            }
        }
    }


#endif
