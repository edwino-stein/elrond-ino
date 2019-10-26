#if !defined  _ELROND_RUNTIME_DEBUG_OUT_HPP
    #define _ELROND_RUNTIME_DEBUG_OUT_HPP

    #include "rtTypes.hpp"

    namespace elrond {
        namespace runtime {

            #if defined GENERIC_STD_PLATFORM

                class VirtualSerial {

                    protected:
                        std::ostream &os;

                    public:

                        VirtualSerial(std::ostream &os);

                        void begin(unsigned long baud);
                        operator bool();

                        void print(const char c[]);
                        void print(char c);
                        void print(unsigned char c);
                        void print(int i);
                        void print(unsigned int i);
                        void print(long l);
                        void print(unsigned long l);
                        void print(double d);
                        void println(void);
                        void flush();
                };

                using SerialT = VirtualSerial;

            #elif defined INO_PLATFORM
                using SerialT = HardwareSerial;
            #endif

            class DebugOut : public elrond::interfaces::DebugOutInterface {

                public:

                    struct DOWrapper {
                        SerialT &debugOut;
                        void (*initSerial)(void);
                        DOWrapper(SerialT &debugOut, elrond::runtime::RuntimeApp &app, void (*initSerial)(void));
                    };

                    DOWrapper *wrapper = nullptr;

                    const elrond::interfaces::DebugOutInterface& put(const char c[]) const override;
                    const elrond::interfaces::DebugOutInterface& put(char c) const override;
                    const elrond::interfaces::DebugOutInterface& put(unsigned char c) const override;
                    const elrond::interfaces::DebugOutInterface& put(int i) const override;
                    const elrond::interfaces::DebugOutInterface& put(unsigned int i) const override;
                    const elrond::interfaces::DebugOutInterface& put(long l) const override;
                    const elrond::interfaces::DebugOutInterface& put(unsigned long l) const override;
                    const elrond::interfaces::DebugOutInterface& put(double d) const override;

                    const elrond::interfaces::DebugOutInterface& putLn(const char c[]) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(char c) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(unsigned char c) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(int i) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(unsigned int i) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(long l) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(unsigned long l) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(double d) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(void) const override;

                    const elrond::interfaces::DebugOutInterface& flush() const override;

                    #if defined INO_PLATFORM

                        const elrond::interfaces::DebugOutInterface& put(const __FlashStringHelper *fs) const override;
                        const elrond::interfaces::DebugOutInterface& putLn(const __FlashStringHelper *fs) const override;

                        const elrond::interfaces::DebugOutInterface& put(const Printable& p) const override;
                        const elrond::interfaces::DebugOutInterface& putLn(const Printable& p) const override;

                        const elrond::interfaces::DebugOutInterface& put(const String &s) const override;
                        const elrond::interfaces::DebugOutInterface& putLn(const String &s) const override;

                    #endif
            };
        }
    }


#endif
