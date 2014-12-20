#include "stdafx.h"
#include "MyHeartbeatMessage.h"


MyHeartbeatMessage::MyHeartbeatMessage(const char* buffer, int bufLen, int serviceId)
	:MyDataMessage(buffer, serviceId, HeartbeatMessage)
{
}


MyHeartbeatMessage::~MyHeartbeatMessage()
{
}

bool MyHeartbeatMessage::IsHeartbeatMessage(const char* buffer, int bLen)
{
	if (MyDataMessage::IsMyDataMessage(buffer, bLen))
	{
		FCIIContent* content = (FCIIContent*)buffer;
		return content->MainCMD == MC_Manager && content->SubCMD == M_SC_Heartbeat;
	}
	return false;
}