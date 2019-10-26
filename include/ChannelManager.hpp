#if !defined  _ELROND_RUNTIME_CHANNEL_MANAGER_HPP
    #define _ELROND_RUNTIME_CHANNEL_MANAGER_HPP

    #include "rtTypes.hpp"

    namespace elrond {
        namespace runtime {

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            class ChannelManager : public elrond::channel::BaseChannelManager {
                protected:

                    elrond::byte txBuffer[ELROND_PROTOCOL_CALC_BUFFER(TXS)];
                    elrond::channel::RxChannel *rxChannels[RXS];

                    void rxTrigger(const elrond::sizeT ch, const elrond::word data) override;
                    elrond::byte *getTxBuffer() const override;

                public:
                    ChannelManager(elrond::modules::BaseTransportModule &transport, elrond::runtime::RuntimeApp &app);

                    void addRxListener(const elrond::sizeT ch, elrond::channel::RxChannel *rx) override;
                    elrond::sizeT getTotalTx() const override;
                    elrond::sizeT getTotalRx() const override;
            };

            /*  ****************************************************************
                ****** Implementation for elrond::runtime::ChannelManager ******
                ****************************************************************/

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            ChannelManager<TXS, RXS>::ChannelManager(elrond::modules::BaseTransportModule &transport, elrond::runtime::RuntimeApp &app):
            elrond::channel::BaseChannelManager(transport){
                for(elrond::sizeT i = 0; i < RXS; ++i) this->rxChannels[i] = nullptr;
                app.pushChannelManager((elrond::channel::BaseChannelManager *) this);
            }

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            void ChannelManager<TXS, RXS>::ChannelManager::addRxListener(const elrond::sizeT ch, elrond::channel::RxChannel *rx){
                if(ch >= RXS) return;
                elrond::channel::RxChannel **c = &(this->rxChannels[ch]);
                while(*c != nullptr){
                    c = &((*c)->_nextNode);
                }
                *c = rx;
            }

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            void ChannelManager<TXS, RXS>::rxTrigger(const elrond::sizeT ch, elrond::word data){
                if(ch >= RXS) return;
                elrond::channel::RxChannel *c = this->rxChannels[ch];
                while(c != nullptr){
                    c->trigger(data);
                    c = c->_nextNode;
                }
            }

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            elrond::byte *ChannelManager<TXS, RXS>::getTxBuffer() const {
                return (elrond::byte *) &(this->txBuffer[0]);
            }

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            elrond::sizeT ChannelManager<TXS, RXS>::getTotalTx() const {
                return TXS;
            }

            template<elrond::sizeT TXS, elrond::sizeT RXS>
            elrond::sizeT ChannelManager<TXS, RXS>::getTotalRx() const {
                return RXS;
            }
        }
    }

#endif
