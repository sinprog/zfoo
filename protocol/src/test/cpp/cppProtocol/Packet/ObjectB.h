#ifndef ZFOO_OBJECTB_H
#define ZFOO_OBJECTB_H

#include "cppProtocol/ByteBuffer.h"

namespace zfoo {

    // @author jaysunxiao
    // @version 3.0
    class ObjectB : public IPacket {
    public:
        bool flag;

        ~ObjectB() override = default;

        static ObjectB valueOf(bool flag) {
            auto packet = ObjectB();
            packet.flag = flag;
            return packet;
        }

        int16_t protocolId() override {
            return 103;
        }

        bool operator<(const ObjectB &_) const {
            if (flag < _.flag) { return true; }
            if (_.flag < flag) { return false; }
            return false;
        }
    };


    class ObjectBRegistration : public IProtocolRegistration {
    public:
        int16_t protocolId() override {
            return 103;
        }

        void write(ByteBuffer &buffer, IPacket *packet) override {
            if (buffer.writePacketFlag(packet)) {
                return;
            }
            auto *message = (ObjectB *) packet;
            buffer.writeBool(message->flag);
        }

        IPacket *read(ByteBuffer &buffer) override {
            auto *packet = new ObjectB();
            if (!buffer.readBool()) {
                return packet;
            }
            bool result0 = buffer.readBool();
            packet->flag = result0;
            return packet;
        }
    };
}

#endif
