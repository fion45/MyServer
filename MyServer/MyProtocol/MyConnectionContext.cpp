#include "stdafx.h"
#include "MyConnectionContext.h"


MyConnectionContext::MyConnectionContext()
{
	this->stage = Initialized;
}


MyConnectionContext::~MyConnectionContext()
{
}

int MyConnectionContext::GetStage()
{
	return stage;
}

void MyConnectionContext::SetStage(int stage)
{
	this->stage = stage;
}

int MyConnectionContext::GetProtocol()
{
	return protocol;
}

void MyConnectionContext::SetProtocol(int protocol)
{
	this->protocol = protocol;
}

bool MyConnectionContext::IsWebSocket()
{
	return (protocol & WebSocketProtocol) > 0;
}

bool MyConnectionContext::IsFCII()
{
	return (protocol & FCIIProtocol) > 0;
}