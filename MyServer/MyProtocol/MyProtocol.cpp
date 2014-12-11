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
			pCxt->SetStage(MyConnectionContext::HandshakeStage);
			return Protocol::Success;
		}
		else if (MyDataMessage::IsMyDataMessage(buffer.GetBuffer(), buffer.GetDataSize()))
		{
			MyHeartbeatMessage* pMessage = new MyHeartbeatMessage(buffer.GetBuffer(), HeadbeatOpt);
			if (pMessage->GetServiceId() != (int)HeadbeatOpt)
			{
				return Protocol::eIncompletePacket;
			}
			else
			{
				serviceId = HeadbeatOpt;
				nExtractedBytes = buffer.GetDataSize();
				pPacket = pMessage;
				pCxt->SetStage(MyConnectionContext::HeartbeatStage);
				return Protocol::Success;
			}
		}
		return Protocol::eIncompletePacket;
	}
	if (MyDataMessage::IsMyDataMessage(buffer.GetBuffer(), buffer.GetDataSize()))
	{
		MyDataMessage* pMessage = new MyDataMessage(buffer.GetBuffer(), UnknowOpt, MyMessage::DataMessage);
		serviceId = (int)pMessage->GetServiceId();
		nExtractedBytes = buffer.GetDataSize();
		pPacket = pMessage;
		return Protocol::Success;
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

