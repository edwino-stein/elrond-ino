#if !defined  _ELROND_RUNTIME_APP_HPP
    #define _ELROND_RUNTIME_APP_HPP

    #include "rtTypes.hpp"

    #include "DebugOut.hpp"

    namespace elrond {
        namespace runtime {

            class RuntimeApp : public elrond::interfaces::RuntimeInterface {

                protected:
                    static void fatalError();

                public:

                    elrond::runtime::DebugOut dbo;
                    elrond::modules::BaseGpioModule &getGpioService() const override;
                    elrond::modules::BaseInputDriverModule &getInputService(const elrond::sizeT id = 0) const override;
                    elrond::channel::BaseChannelManager &getChannelManager(const elrond::sizeT id = 0) const override;
                    const elrond::interfaces::DebugOutInterface &dout() const override;

                    void onError(const char *error) override;
                    #if defined INO_PLATFORM
                        void onError(const __FlashStringHelper *error) override;
                    #endif
            };

            extern elrond::runtime::RuntimeApp __app_inst__;
        }
    }

#endif
