#pragma once
#include "Symbols.h"
#include "MyDataMessage.h"

class WebsocketDataMessage : public MyDataMessage
{
private:
	string jsonStr;
	char* contentBuf;
public:
	WebsocketDataMessage(const char* buffer, int serviceId);
	~WebsocketDataMessage(void);
	
    bool Encode();
	bool Decode();

	FCIIContent GetContent();
};

