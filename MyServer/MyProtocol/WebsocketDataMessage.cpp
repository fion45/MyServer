#include "StdAfx.h"
#include "WebsocketDataMessage.h"


WebsocketDataMessage::WebsocketDataMessage(const char* buffer, int serviceId)
	: MyDataMessage(buffer, serviceId, WSDataMessage)
{

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
