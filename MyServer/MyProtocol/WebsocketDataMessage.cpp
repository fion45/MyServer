#include "StdAfx.h"
#include "WebsocketDataMessage.h"


WebsocketDataMessage::WebsocketDataMessage(const char* buffer, int serviceId)
	: MyDataMessage(buffer, serviceId, WSDataMessage)
{
	jsonStr.assign(buffer);
	Encode();
}

WebsocketDataMessage::~WebsocketDataMessage(void)
{
	delete[] contentBuf;
}

bool WebsocketDataMessage::Encode()
{

	return true;
}

bool WebsocketDataMessage::Decode()
{
	return true;
}

FCIIContent WebsocketDataMessage::GetContent()
{
	return *((FCIIContent*)contentBuf);
}
