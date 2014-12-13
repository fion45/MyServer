#include "StdAfx.h"
#include "WebsocketDataMessage.h"


WebsocketDataMessage::WebsocketDataMessage(const char* buffer, int serviceId)
	: MyDataMessage(serviceId, WSDataMessage)
{
	//Éú³ÉcontentµÄ buffer


	jsonStr.assign(buffer);
	Encode();
}

WebsocketDataMessage::~WebsocketDataMessage(void)
{

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
	return *((FCIIContent*)mBuffer);
}