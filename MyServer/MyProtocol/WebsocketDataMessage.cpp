#include "StdAfx.h"
#include "WebsocketDataMessage.h"
#include "json/json.h"


WebsocketDataMessage::WebsocketDataMessage(const char* buffer, int serviceId)
	: MyDataMessage(serviceId, WSDataMessage)
{
	//Éú³ÉcontentµÄ buffer
	mJsonStr.assign(buffer);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(mJsonStr, root))
	{
		UINT16 tmpIdentify = root["Identify"].asUInt();
		UINT16 tmpCheckSum = root["CheckSum"].asUInt();
		UINT16 tmpMainCMD = root["MainCMD"].asUInt();
		UINT16 tmpSubCMD = root["SubCMD"].asUInt();
		UINT16 tmpIsRequest = root["IsRequest"].asUInt();
		UINT16 tmpErrCode = root["ErrCode"].asUInt();
		UINT16 tmpNextIdentify = root["NextIdentify"].asUInt();
		UINT16 tmpReserve = root["Reserve"].asUInt();
		UINT32 tmpDataLen = root["DataLen"].asUInt();
		string tmpData = root["Data"].asString();

		mServiceId = tmpMainCMD;
		mBLen = MyDataMessage::CONTENTLEN + tmpDataLen;
		mBuffer = new char[mBLen];
		char* bufPtr = mBuffer;
		int UINT16Size = sizeof(UINT16), UINT32Size = sizeof(UINT32);
		*(UINT16*)bufPtr = tmpIdentify;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpCheckSum;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpMainCMD;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpSubCMD;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpIsRequest;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpErrCode;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpNextIdentify;
		bufPtr += UINT16Size;
		*(UINT16*)bufPtr = tmpReserve;
		bufPtr += UINT16Size;
		*(UINT32*)bufPtr = tmpDataLen;
		bufPtr += UINT32Size;
		CopyMemory(bufPtr, tmpData.data(), tmpData.length());
		mContent = (FCIIContent*)mBuffer;

		mIsFCIIDataTag = true;
	}
	else
	{
		mIsFCIIDataTag = false;
	}
	//Encode();
}

WebsocketDataMessage::~WebsocketDataMessage(void)
{
	if (mIsFCIIDataTag)
		SAFE_DELETEARRPTR(mBuffer);
}

//bool WebsocketDataMessage::Encode()
//{
//
//	return true;
//}
//
//bool WebsocketDataMessage::Decode()
//{
//	return true;
//}

FCIIContent* WebsocketDataMessage::GetContent()
{
	return mContent;
}