#pragma once
#include "Symbols.h"
#include "MyDataMessage.h"

class MYPROTOCOL_API WebsocketDataMessage : public MyDataMessage
{
private:
	string mJsonStr;
	bool mIsFCIIDataTag = false;
public:
	WebsocketDataMessage(const char* buffer, int serviceId);
	~WebsocketDataMessage(void);
	
 //   bool Encode();
	//bool Decode();

	bool IsFCIIData()
	{
		return mIsFCIIDataTag;
	}

	FCIIContent* GetContent();
};

