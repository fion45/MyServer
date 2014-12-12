#pragma once
#include "Symbols.h"
#include "Protocol.h"

enum OperationType
{
	HandshakeOpt,
	HeadbeatOpt,
	WebsocketOpt,
	UnknowOpt,
	UserOpt
};

// This class is exported from the WebsocketProtocol.dll
class MyProtocol : public PushFramework::Protocol {
public:
	MyProtocol(void);
	// TODO: add your methods here.
    virtual void disposeOutgoingPacket(PushFramework::OutgoingPacket* pPacket)
    {
        delete pPacket;
    }
    virtual void disposeIncomingPacket(PushFramework::IncomingPacket* pPacket)
    {
        delete pPacket;
    }


    virtual int encodeOutgoingPacket(PushFramework::OutgoingPacket& packet);
    virtual int frameOutgoingPacket(PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes);

	virtual int tryDeframeIncomingPacket(PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, PushFramework::ConnectionContext* pContext);
    virtual int decodeIncomingPacket(PushFramework::IncomingPacket* pPacket, int& serviceId);

};

