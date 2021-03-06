// MyServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "WebsocketService.h"
#include "RoutedCommunicationService.h"
#include "MyClientFactory.h"
#include <process.h>

class MyServer : public Server
{
public:
	MyServer()
	{
		//
	}
	~MyServer()
	{
		//
	}
protected:
	virtual void disposeOutgoingPacket(OutgoingPacket* pPacket)
	{
		delete pPacket;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	MyServer server;
	server.registerService(WebsocketOpt, new WebsocketService, "WebService");

	server.setClientFactory(new MyClientFactory);
	server.setMaxConnections(100);
	server.setLoginExpiryDuration(60);

	server.setProtocol(new MyProtocol);

	server.createListener(81);

	try
	{
		server.start(true);
	}
	catch (std::exception& e)
	{
		cout << "Failed to start server. Exception : " << e.what() << std::endl;
		return 0;
	}

	while (true)
	{
		char ch;

		cin >> ch;

		if (ch == 'q')
		{
			break;
		}
	}
	server.stop();

	return 0;
}

