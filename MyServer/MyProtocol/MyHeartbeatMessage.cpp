#include "stdafx.h"
#include "MyHeartbeatMessage.h"


MyHeartbeatMessage::MyHeartbeatMessage(const char* buffer, int serviceId)
	:MyDataMessage(buffer, serviceId, HeartbeatMessage)
{
}


MyHeartbeatMessage::~MyHeartbeatMessage()
{
}
