#if !defined  _ELROND_RUNTIME_GPIO_INO_HPP
    #define _ELROND_RUNTIME_GPIO_INO_HPP

    #include "rtTypes.hpp"

    #define MAX_D2A_VALUE 0xFF
    #define MIN_D2A_VALUE 0x0

    #define MAX_ANGLE_VALUE 180
    #define MIN_ANGLE_VALUE 0

    #define MAX_ANALOG_VALUE 0x3FF
    #define MIN_ANALOG_VALUE 0x0

    #if defined ARDUINO_AVR_NANO || defined ARDUINO_AVR_UNO

        #define INO_ALLOW_PWM 0xE68
        #define INO_TOTAL_DO_PIN 14

        #if defined ARDUINO_AVR_NANO
            #define INO_TOTAL_AI_PIN 8
        #elif defined ARDUINO_AVR_UNO
            #define INO_TOTAL_AI_PIN 6
        #endif

    #elif defined ARDUINO_AVR_MEGA2560 || defined ARDUINO_AVR_MEGA

        #define INO_ALLOW_PWM 0x3FFC
        #define INO_TOTAL_DO_PIN 54
        #define INO_TOTAL_AI_PIN 16

    #elif defined ESP_PLATFORM

        #define ESP_TOTAL_DO_PIN 40

        #define ESP_ALLOW_PWM1 0xE80F014
        #define ESP_ALLOW_PWM2 0x9F

        #define ESP_PWM_FREQ 5000
        #define ESP_PWM_RESO 8

        #define ESP_SERVO_FREQ 50
        #define ESP_SERVO_RESO 16
        #define ESP_MIN_SERVO_PULSE_WIDTH 544
        #define ESP_MAX_SERVO_PULSE_WIDTH 2400
        #define ESP_SERVO_TAU_USEC 20000

        #undef MAX_ANALOG_VALUE
        #undef MIN_ANALOG_VALUE

        #define MAX_ANALOG_VALUE 0xFFF
        #define MIN_ANALOG_VALUE 0x0
        #define ESP_ALLOW_AIN 0xFF0E00F015

    #endif

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

                        #if defined ESP_PLATFORM
                            static int espGetPwmChannelByPin(const int pin);
                            static void espSetupPwmPin(const int pin, const int freq, const int res);
                            static void espPwmWrite(const int pin, const elrond::word data);
                        #endif

                    public:
                        GpioIno();
                        void attach(elrond::gpio::BaseGpioPin &pin) override;
                };
            }
        }
    }


#endif
