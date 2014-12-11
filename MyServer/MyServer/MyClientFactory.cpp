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
	MyConnectionContext* pCxt = (MyConnectionContext*)pConnectionContext;
	switch (pCxt->GetStage())
	{
	case MyConnectionContext::HandshakeStage:
	{
		WebsocketHandshakeMessage& request = (WebsocketHandshakeMessage&)_request;
		if (!request.Parse())
		{
			return ClientFactory::RefuseAndClose;
		}

		WebsocketHandshakeMessage *pResponse = new WebsocketHandshakeMessage();
		if (WebsocketHandshakeMessage::ProcessHandshake(request, *pResponse))
		{
			lpPacket = pResponse;
			pCxt->SetStage(MyConnectionContext::LoginStage);
		}
		pCxt->SetProtocol(MyConnectionContext::WebSocketProtocol | MyConnectionContext::FCIIProtocol);
		return ClientFactory::RefuseRequest; // Will not close the connection, but we still wait for login message to create a logical client.
		break;
	}
	case MyConnectionContext::HeartbeatStage:
	{
		MyHeartbeatMessage& request = (MyHeartbeatMessage&)_request;
		//if (!request.Parse())
		//{
		//	return ClientFactory::RefuseAndClose;
		//}
		//return ClientFactory::RefuseRequest;
		pCxt->SetProtocol(MyConnectionContext::FCIIProtocol);
		break;
	}
	default:
		return ClientFactory::RefuseAndClose;
		break;
	}
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
