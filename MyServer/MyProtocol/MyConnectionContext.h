#pragma once
#include "Symbols.h"

class MYPROTOCOL_API MyConnectionContext : public ConnectionContext
{
public:
	enum
	{
		Initialized = 0,
		HandshakeStage,
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

