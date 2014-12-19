#pragma once
#include "Symbols.h"

// This class is exported from the WebsocketProtocol.dll
class MYPROTOCOL_API MyMessage : public IncomingPacket, public OutgoingPacket
{
public:
	enum
	{
		WSHandshake = 0,
		WSDataMessage,
		HeartbeatMessage,
		DataMessage
	};
	MyMessage(int type)
	{
		this->type = type;
	}
	~MyMessage(void)
	{
		//
	}
	int GetType()
	{
		return type;
	}
private:
	int type;
};
