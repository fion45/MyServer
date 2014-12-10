#include "stdafx.h"
#include "MyClientFactory.h"


MyClientFactory::MyClientFactory()
{
}


MyClientFactory::~MyClientFactory()
{
}

int MyClientFactory::onFirstRequest(IncomingPacket& _request, ConnectionContext* pConnectionContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket)
{
	//是否从WebSocket传来的数据
	return 
}

void MyClientFactory::onClientDisconnected(LogicalConnection* pClient)
{
	Disconnect(pClient, false);
}

void MyClientFactory::disposeClient(LogicalConnection* pClient)
{
	delete pClient;
}

OutgoingPacket* MyClientFactory::onNewConnection(ConnectionContext*& pConnectionContext)
{
	pConnectionContext = new MyConnectionContext();
	return NULL;
}
