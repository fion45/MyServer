#include "StdAfx.h"
#include "MySocketClient.h"

MySocketClient::MySocketClient(std::string pseudo)
{
    this->pseudo =  pseudo;
}

MySocketClient::~MySocketClient(void)
{
}

PushFramework::CLIENT_KEY MySocketClient::getKey()
{
    return pseudo.c_str();
}
