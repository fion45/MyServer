#include "StdAfx.h"
#include "RoutedCommunicationService.h"
#include "MySocketClient.h"
#include "WebsocketDataMessage.h"


RoutedCommunicationService::RoutedCommunicationService(void)
{
}


RoutedCommunicationService::~RoutedCommunicationService(void)
{
}

void RoutedCommunicationService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	WebsocketDataMessage& request = (WebsocketDataMessage&)(*pRequest);
	MySocketClient& client = (MySocketClient&)(*pClient);

	LogicalConnection* pRecipient = FindClient(request.GetArg1().c_str());
	if (pRecipient)
	{
		WebsocketDataMessage response(Routedcommunication);
		response.SetArguments(client.getKey(), request.GetArg2());
		pRecipient->PushPacket(&response);
		ReturnClient(pRecipient);
	}	
}
