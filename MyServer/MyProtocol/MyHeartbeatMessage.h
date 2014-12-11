#pragma once
#include "Symbols.h"
#include "MyDataMessage.h"

class MyHeartbeatMessage : public MyDataMessage
{
public:
	MyHeartbeatMessage(const char* buffer, int serviceId);
	~MyHeartbeatMessage();


};

