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
	return true;
}