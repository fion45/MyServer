#pragma once
#include "Symbols.h"
#include "Protocol.h"

class MyConnectionContext : public PushFramework::ConnectionContext
{
public:
	enum
	{
		Initialized = 0,
		HandshakeStage,
		HeartbeatStage,
		LoginStage,
		ConnectedStage
	};
	MyConnectionContext();
	~MyConnectionContext();

	int GetStage();
	void SetStage(int stage);

private:
	int stage;
};

