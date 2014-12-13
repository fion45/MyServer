#include "stdafx.h"
#include "MyDataMessage.h"
#include "FCIIDefined.h"
#include "MyProtocol.h"

MyDataMessage::MyDataMessage(int serviceId, int type) : MyMessage(type)
{
	mServiceId = serviceId;
	mBuffer = NULL;
	mBLen = 0;
}

MyDataMessage::MyDataMessage(const char* buffer, int bufLen, int serviceId, int type) : MyMessage(type)
{
	mServiceId = serviceId;
	mBLen = bufLen;
	mBuffer = new char[mBLen];
	CopyMemory(mBuffer, buffer, mBLen);
	FCIIContent* content = (FCIIContent*)mBuffer;
	mServiceId = content->MainCMD;
}


MyDataMessage::~MyDataMessage()
{
	delete[] mBuffer;
}

void MyDataMessage::SetBuffer(const char* buffer, int bufLen)
{
	if (mBuffer != NULL)
	{
		delete[] mBuffer;
		mBuffer = NULL;
		mBLen = 0;
	}

	mBuffer = new char[mBLen];
	CopyMemory(mBuffer, buffer, mBLen);
	FCIIContent* content = (FCIIContent*)mBuffer;
	mServiceId = content->MainCMD;
}

void MyDataMessage::SetServiceId(int serviceId)
{
	mServiceId = serviceId;
}

int MyDataMessage::GetServiceId()
{
	return mServiceId;
}

FCIIContent* MyDataMessage::GetEncodedData()
{
	return (FCIIContent*)mBuffer;
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

