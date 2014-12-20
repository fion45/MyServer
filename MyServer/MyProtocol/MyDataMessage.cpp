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
	mContent = (FCIIContent*)mBuffer;
	if (type != HeartbeatMessage)
	{
		mServiceId = mContent->MainCMD;
	}
}

MyDataMessage::MyDataMessage(int serviceId, int type) : MyMessage(type)
{
	mServiceId = serviceId;
	mBLen = 0;
	mBuffer = NULL;
}


MyDataMessage::~MyDataMessage()
{
	SAFE_DELETEARRPTR(mBuffer);
}


bool MyDataMessage::IsMyDataMessage(const char* buffer, int bLen)
{
	FCIIContent* content = (FCIIContent*)buffer;

	//�жϳ���
	if (content->DataLen + CONTENTLEN != bLen)
		return false;
	//�ж�checksum
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
