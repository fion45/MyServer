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
	//�Ƿ��WebSocket����������
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
