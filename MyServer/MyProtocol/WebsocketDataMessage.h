#pragma once
#include "Symbols.h"
#include "MyDataMessage.h"

class WebsocketDataMessage : public MyDataMessage
{
public:
	WebsocketDataMessage(const char* buffer, int serviceId);
	~WebsocketDataMessage(void);
	
    bool Encode();
	bool Decode();
};

