#pragma once
#include "Symbols.h"
#include "MyDataMessage.h"

class MyHeartbeatMessage : public MyDataMessage
{
public:
	MyHeartbeatMessage(const char* buffer, int bufLen,int serviceId);
	~MyHeartbeatMessage();

	static bool IsHeartbeatMessage(const char* buffer, int bLen);
};

