
#include "stdafx.h"
#include "MyClientFactory.h"
#include "MySocketClient.h"
#include "UserDBHelper.h"
#include "json/json.h"


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
			pCxt->SetStage(MyConnectionContext::ConnectedStage);
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
		pCxt->SetStage(MyConnectionContext::ConnectedStage);
		pCxt->SetProtocol(MyConnectionContext::FCIIProtocol);
		return ClientFactory::RefuseRequest;
		break;
	}
	case MyConnectionContext::ConnectedStage:
	{
		//需确定连接成功,查询数据库
		MyDataMessage& message = (MyDataMessage&)_request;
		FCIIContent* contentPtr = message.GetEncodedData();
		if (contentPtr->MainCMD != MC_Manager || contentPtr->SubCMD != M_SC_Login)
		{
			return ClientFactory::RefuseAndClose;
		}
		Json::Value root;
		if (message.GetJsonReaderForData(root))
		{
			string LoginID = root["LoginID"].asString();
			string LoginPSW = root["LoginPSW"].asString();
			UserDBHelper* helper = UserDBHelper::GetInstance();
			if (helper->Login(LoginID, LoginPSW))
			{

				pCxt->SetStage(MyConnectionContext::LoginedStage);
				return ClientFactory::RefuseRequest;
			}
			else
			{
				return ClientFactory::RefuseAndClose;
			}
		}
		else
		{
			return ClientFactory::RefuseAndClose;
		}
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
