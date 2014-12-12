// WebsocketProtocol.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MyProtocol.h"
#include "MyConnectionContext.h"
#include "WebsocketHandshakeMessage.h"
#include "WebsocketDataMessage.h"
#include "MyHeartbeatMessage.h"
#include "MyDataMessage.h"



// This is the constructor of a class that has been exported.
// see WebsocketProtocol.h for the class definition
MyProtocol::MyProtocol()
{

}

int MyProtocol::tryDeframeIncomingPacket(PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, ConnectionContext* pContext)
{
	PushFramework::DataBuffer* dbPtr = &buffer;
	if (dbPtr->GetDataSize() == 0)
		return Protocol::eIncompletePacket;
	MyConnectionContext* pCxt = (MyConnectionContext*)pContext;
	if (pCxt->GetStage() == MyConnectionContext::Initialized)
	{
		if (WebsocketHandshakeMessage::IsHandshakeMessage(dbPtr->GetBuffer()))
		{
			WebsocketHandshakeMessage* pMessage = new WebsocketHandshakeMessage(dbPtr->GetBuffer(), dbPtr->GetDataSize());
			serviceId = HandshakeOpt;
			nExtractedBytes = dbPtr->GetDataSize();
			pPacket = pMessage;
			pCxt->SetStage(MyConnectionContext::HandshakeStage);
			return Protocol::Success;
		}
		else if (MyHeartbeatMessage::IsHeartbeatMessage(dbPtr->GetBuffer(), dbPtr->GetDataSize()))
		{
			MyHeartbeatMessage* pMessage = new MyHeartbeatMessage(dbPtr->GetBuffer(), dbPtr->GetDataSize(), UnknowOpt);

			pCxt->SetStage(MyConnectionContext::HandshakeStage);
			return Protocol::Success;
		}
	}
	else if (pCxt->IsWebSocket())
	{
		//In the other cases, we should expect a data message : 
		int nMinExpectedSize = 6;
		if (dbPtr->GetDataSize() < nMinExpectedSize)
			return Protocol::eIncompletePacket;

		BYTE payloadFlags = dbPtr->getAt(0);
		if (payloadFlags != 129)
			return Protocol::eUndefinedFailure;

		BYTE basicSize = dbPtr->getAt(1) & 0x7F;
		unsigned __int64 payloadSize;
		int masksOffset;

		if (basicSize <= 125)
		{
			payloadSize = basicSize;
			masksOffset = 2;
		}
		else if (basicSize == 126)
		{
			nMinExpectedSize += 2;
			if (dbPtr->GetDataSize() < nMinExpectedSize)
				return Protocol::eIncompletePacket;
			payloadSize = ntohs(*(u_short*)(dbPtr->GetBuffer() + 2));
			masksOffset = 4;
		}
		else if (basicSize == 127)
		{
			nMinExpectedSize += 8;
			if (dbPtr->GetDataSize() < nMinExpectedSize)
				return Protocol::eIncompletePacket;
			payloadSize = ntohl(*(u_long*)(dbPtr->GetBuffer() + 2));
			masksOffset = 10;
		}
		else
			return Protocol::eUndefinedFailure;

		nMinExpectedSize += payloadSize;
		if (dbPtr->GetDataSize() < nMinExpectedSize)
			return Protocol::eIncompletePacket;

		BYTE masks[4];
		memcpy(masks, dbPtr->GetBuffer() + masksOffset, 4);

		char* payload = new char[payloadSize + 1];
		memcpy(payload, dbPtr->GetBuffer() + masksOffset + 4, payloadSize);
		for (unsigned __int64 i = 0; i < payloadSize; i++) {
			payload[i] = (payload[i] ^ masks[i % 4]);
		}
		payload[payloadSize] = '\0';

		WebsocketDataMessage* pMessage = new WebsocketDataMessage(payload, UnknowOpt);
		delete payload;

		if (!pCxt->IsFCII())
		{
			serviceId = WebsocketOpt;
			nExtractedBytes = dbPtr->GetDataSize();
			pPacket = pMessage;
			return Protocol::Success;
		}
		else
		{

		}
	}
	if (pCxt->IsFCII())
	{
		//MyDataMessage* pMessage = new MyDataMessage();
	}
	return Protocol::eIncompletePacket;
}

int MyProtocol::frameOutgoingPacket(PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes)
{
	MyMessage& message = (MyMessage&)packet;
	switch (message.GetType())
	{
	case MyMessage::WSHandshake:
	{
		WebsocketHandshakeMessage& handshake = (WebsocketHandshakeMessage&)message;
		string strRaw = handshake.Serialize();
		if (strRaw.size() > buffer.getRemainingSize())
			return Protocol::eInsufficientBuffer;
		buffer.Append((char*)strRaw.c_str(), strRaw.size());
		nWrittenBytes = strRaw.size();
		return Protocol::Success;
	}
	case MyMessage::WSDataMessage:
	{
		return Protocol::Success;
	}
	case MyMessage::HeartbeatMessage:
		return Protocol::Success;
	case MyMessage::DataMessage:
		return Protocol::Success;
	default:
		return Protocol::eUndefinedFailure;
	}
}

int MyProtocol::decodeIncomingPacket(PushFramework::IncomingPacket* pPacket, int& serviceId)
{
	MyMessage* pMessage = (MyMessage*)pPacket;
	switch (pMessage->GetType())
	{
	case MyMessage::WSHandshake:
		return Protocol::Success;
	case MyMessage::WSDataMessage:
		return Protocol::Success;
	case MyMessage::HeartbeatMessage:
		return Protocol::Success;
	case MyMessage::DataMessage:
		return Protocol::Success;
	default:
		return Protocol::eUndefinedFailure;
	}
}

int MyProtocol::encodeOutgoingPacket(PushFramework::OutgoingPacket& packet)
{
	MyMessage& message = (MyMessage&)packet;
	switch (message.GetType())
	{
	case MyMessage::WSHandshake:
		return Protocol::Success;
	case MyMessage::WSDataMessage:
		return Protocol::Success;
	case MyMessage::HeartbeatMessage:
		return Protocol::Success;
	case MyMessage::DataMessage:
		return Protocol::Success;
	default:
		return Protocol::eUndefinedFailure;
	}
}

