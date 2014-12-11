#include "stdafx.h"
#include "MyDataMessage.h"
#include "FCIIDefined.h"
#include "MyProtocol.h"


MyDataMessage::MyDataMessage(const char* buffer, int serviceId, int type) : MyMessage(type)
{
	mServiceId = serviceId;
	mBLen = strlen(buffer);
	mBuffer = new char[mBLen];
	CopyMemory(mBuffer, buffer, mBLen);
	if (type != HeartbeatMessage)
	{
		FCIIContent* content = (FCIIContent*)mBuffer;
		mServiceId = content->MainCMD;
	}
}


MyDataMessage::~MyDataMessage()
{
	delete[] mBuffer;
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


