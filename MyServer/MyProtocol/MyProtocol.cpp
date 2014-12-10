// WebsocketProtocol.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MyProtocol.h"
#include "MyConnectionContext.h"
#include "WebsocketHandshakeMessage.h"
#include "MyHeartbeatMessage.h"
#include "MyDataMessage.h"



// This is the constructor of a class that has been exported.
// see WebsocketProtocol.h for the class definition
MyProtocol::MyProtocol()
{

}

int MyProtocol::tryDeframeIncomingPacket(PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, ConnectionContext* pContext)
{
	if (buffer.GetDataSize() == 0)
		return Protocol::eIncompletePacket;
	MyConnectionContext* pCxt = (MyConnectionContext*)pContext;
	if (pCxt->GetStage() == MyConnectionContext::Initialized)
	{
		if (WebsocketHandshakeMessage::IsHandshakeMessage(buffer.GetBuffer()))
		{
			WebsocketHandshakeMessage* pMessage = new WebsocketHandshakeMessage(buffer.GetBuffer(), buffer.GetDataSize());
			serviceId = HandshakeOpt;
			nExtractedBytes = buffer.GetDataSize();
			pPacket = pMessage;
			return Protocol::Success;
		}
		else if (MyDataMessage::IsMyDataMessage(buffer.GetBuffer(), buffer.GetDataSize()))
		{
			MyHeartbeatMessage* pMessage = new MyHeartbeatMessage(buffer.GetBuffer(), HeadbeatOpt);
			if (pMessage->GetServiceId() != HeadbeatOpt)
			{
				return Protocol::eIncompletePacket;
			}
			else
			{
				serviceId = HeadbeatOpt;
				nExtractedBytes = buffer.GetDataSize();
				pPacket = pMessage;
				return Protocol::Success;
			}
		}
		return Protocol::eIncompletePacket;
	}
	if (MyDataMessage::IsMyDataMessage(buffer.GetBuffer(), buffer.GetDataSize()))
	{
		MyDataMessage* pMessage = new MyDataMessage(buffer.GetBuffer(), UnknowOpt, MyMessage::DataMessage);
		serviceId = pMessage->GetServiceId();
		nExtractedBytes = buffer.GetDataSize();
		pPacket = pMessage;
		return Protocol::Success;
	}
	return Protocol::eIncompletePacket;
}

int MyProtocol::frameOutgoingPacket(PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes)
{
	return Protocol::eUndefinedFailure;
}

int MyProtocol::decodeIncomingPacket(PushFramework::IncomingPacket* pPacket, int& serviceId)
{
	return Protocol::Success;
}

int MyProtocol::encodeOutgoingPacket(PushFramework::OutgoingPacket& packet)
{
	return Protocol::Success;
}

