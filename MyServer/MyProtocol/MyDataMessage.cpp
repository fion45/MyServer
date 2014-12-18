#include "stdafx.h"
#include "MyDataMessage.h"
#include "FCIIDefined.h"
#include "MyProtocol.h"


MyDataMessage::MyDataMessage(const char* buffer, int bufLen, int serviceId, int type) : MyMessage(type)
{
	mServiceId = serviceId;
	mBLen = bufLen;
	mBuffer = new char[mBLen];
	CopyMemory(mBuffer, buffer, mBLen);
	if (type != HeartbeatMessage)
	{
		mContent = (FCIIContent*)mBuffer;
		mServiceId = mContent->MainCMD;
	}
}


MyDataMessage::~MyDataMessage()
{
	delete[] mBuffer;
}


bool MyDataMessage::IsMyDataMessage(const char* buffer, int bLen)
{
	FCIIContent* content = (FCIIContent*)buffer;

	//ÅÐ¶Ï³¤¶È
	if (content->DataLen + CONTENTLEN != bLen)
		return false;
	//ÅÐ¶Ïchecksum
	UINT16 tmpCS = 0;
	for (int i = 0; i < content->DataLen; i++)
	{
		tmpCS += *(content->Data + i);
	}
	if (tmpCS != content->CheckSum)
		return false;
	return true;
}

int MyDataMessage::GetServiceId()
{
	return mServiceId;
}

int MyDataMessage::GetBufLen()
{
	return mBLen;
}
