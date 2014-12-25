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
	SAFE_DELETEARRPTR(mDataBuf);
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
		tmpCS += *(&(content->Data) + i);
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

bool MyDataMessage::IsEnd()
{
	return GetContentData() != NULL;
}

char* MyDataMessage::GetContentData()
{
	if (mDataBuf == NULL)
	{
		if (mContent->Identify == mContent->NextIdentify)
		{
			mDataBuf = new char[mContent->DataLen + 1];
			CopyMemory(mDataBuf, &(mContent->Data), mContent->DataLen);
			mDataBuf[mContent->DataLen] = '\0';
		}
		else
		{
			int tmpLen = mBLen;
			mDataBuf = new char[tmpLen];
			ZeroMemory(mDataBuf, tmpLen);
			char* bufPtr = mBuffer;
			//FCIIContent* content = mContent;
			//CopyMemory(mDataBuf, &(content->Data), content->DataLen);
			FCIIContent* content;
			do
			{
				content = (FCIIContent*)bufPtr;
				CopyMemory(mDataBuf, &(content->Data), content->DataLen);
				bufPtr += (MyDataMessage::CONTENTLEN + content->DataLen);
			} while (bufPtr - mBuffer < mBLen && content->Identify != content->NextIdentify);
			if (content->Identify != content->NextIdentify)
				SAFE_DELETEARRPTR(mDataBuf);
		}
	}
	return mDataBuf;
}


bool MyDataMessage::GetJsonReaderForData(Json::Value &root)
{
	char* DataPtr = GetContentData();
	if (DataPtr == NULL)
		return false;
	string tmpStr(DataPtr, mBLen);
	Json::Reader reader;
	return reader.parse(tmpStr, root);
}
