#if !defined  _ELROND_RUNTIME_STATIC_CONFIG_MEMORY_HPP
    #define _ELROND_RUNTIME_STATIC_CONFIG_MEMORY_HPP

    #include "rtTypes.hpp"
    namespace elrond {
        namespace runtime {

            template<elrond::sizeT C>
            class StaticConfigMemory : public elrond::interfaces::ConfigMapMemoryInterface {

                protected:
                    elrond::byte data[C];
                    elrond::sizeT index = 0;
                    elrond::sizeT length = 0;

                public:
                    bool alloc(const elrond::sizeT length) override;
                    bool write(const elrond::byte data) override;
                    bool read(const elrond::sizeT index, elrond::byte &data) const override;
            };

            /*  ****************************************************************
                **** Implementation for elrond::runtime::StaticConfigMemory ****
                ****************************************************************/

            template<elrond::sizeT C>
            bool StaticConfigMemory<C>::alloc(const elrond::sizeT length) {
                if(this->length + length > C) return false;
                this->length += length;
                return true;
            }

            template<elrond::sizeT C>
            bool StaticConfigMemory<C>::write(const elrond::byte data) {

                //Prevent compiler error for esp32
                #if defined ESP_PLATFORM
                    if(this->index >= C) return false;
                #endif

                if(this->index >= this->length) return false;
                this->data[this->index++] = data;
                return true;
            }

            template<elrond::sizeT C>
            bool StaticConfigMemory<C>::read(const elrond::sizeT index, elrond::byte &data) const {

                //Prevent compiler error for esp32
                #if defined ESP_PLATFORM
                    if(this->index >= C) return false;
                #endif

                if(index >= this->length) return false;
                data = this->data[index];
                return true;
            }
        }
    }
#endif
