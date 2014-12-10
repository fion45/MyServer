#include "stdafx.h"
#include "MyDataMessage.h"
#include "FCIIDefined.h"


MyDataMessage::MyDataMessage(const char* buffer, int serviceId,int type)
	: MyMessage(type)
{
	mServiceId = serviceId;
	mBLen = strlen(buffer);
	mBuffer = new char[mBLen];
	CopyMemory(mBuffer, buffer, mBLen);	
	FCIIContent* content = (FCIIContent*)mBuffer;
	switch (content->MainCMD)
	{
		case 0:
		{
			SetServiceId();
			break;
		}
	}
}


MyDataMessage::~MyDataMessage()
{
	delete[] mBuffer;
}


bool MyDataMessage::IsMyDataMessage(const char* buffer, int bLen)
{
	//ÅÐ¶Ï³¤¶È

	//ÅÐ¶Ïchecksum

	return true;
}



