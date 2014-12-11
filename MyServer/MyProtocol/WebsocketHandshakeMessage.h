#pragma once
#include "Symbols.h"
#include "MyMessage.h"

class WebsocketHandshakeMessage : public MyMessage {
public:
	WebsocketHandshakeMessage(char* pRaw, int nSize);
	WebsocketHandshakeMessage();
	~WebsocketHandshakeMessage(void);

	bool Parse();
	
	string GetField(string key);
	void SetField(string key, string val);


	string Serialize();

	static bool IsHandshakeMessage(char* pRaw);
	static bool ProcessHandshake(WebsocketHandshakeMessage& request, WebsocketHandshakeMessage& response);
private:
	char* pRaw;
	int nSize;
	string m_method;
	string m_uri;
	string m_version;
	map<string, string> fields;
};


