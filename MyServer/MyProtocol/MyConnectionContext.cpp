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
