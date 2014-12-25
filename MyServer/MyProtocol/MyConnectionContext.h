#pragma once
#include "Symbols.h"
#include "Protocol.h"

class MYPROTOCOL_API MyConnectionContext : public PushFramework::ConnectionContext
{
public:
	enum
	{
		Initialized = 0,
		HandshakeStage,
		HeartbeatStage,
		ConnectedStage,
		LoginedStage
	};
	enum
	{
		UnknowedProtocol = 0,
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

