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
		ConnectedStage
	};
	enum
	{
		WebSocketProtocol = 1,
		FCIIProtocol = 2
	};
	MyConnectionContext();
	~MyConnectionContext();

	int GetStage();
	void SetStage(int stage);

	int GetProtocol();
	void SetProtocol(int protocol);

	bool IsWebSocket();
	bool IsFCII();
private:
	int stage;
	int protocol;
};

