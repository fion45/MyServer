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
		UINT tmpIdentify = root["Identify"].asUInt();
		UINT tmpCheckSum = root["CheckSum"].asUInt();
		UINT tmpMainCMD = root["MainCMD"].asUInt();
		UINT tmpSubCMD = root["SubCMD"].asUInt();
		UINT tmpIsRequest = root["IsRequest"].asUInt();
		UINT tmpErrCode = root["ErrCode"].asUInt();
		UINT tmpDataLen = root["DataLen"].asUInt();
		string tmpData = root["Data"].asString();

		mServiceId = tmpMainCMD;
		mBLen = MyDataMessage::CONTENTLEN + tmpDataLen;
		mBuffer = new char[mBLen];

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

FCIIContent WebsocketDataMessage::GetContent()
{
	return *((FCIIContent*)mBuffer);
}