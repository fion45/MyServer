/********************************************************************
	File :			BroadcastQueueInfo.h
	Creation date :	2010/6/27

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.


*********************************************************************/
#ifndef BroadcastQueueInfo__INCLUDED
#define BroadcastQueueInfo__INCLUDED

#pragma once

namespace PushFramework
{
class BroadcastQueueGroupInfo;
class BroadcastQueue;

class BroadcastQueueInfo
{
public:

    BroadcastQueueInfo(BroadcastQueue* pChannel, unsigned int uPacketQuota);

    ~BroadcastQueueInfo(void);

public:

    BroadcastQueue* pChannel;
    unsigned int uPacketQuota;
    BroadcastQueueInfo* pNext;
    BroadcastQueueGroupInfo* pParentGroup;
};

class BroadcastQueueGroupInfo
{
public:
    BroadcastQueueGroupInfo(unsigned int uPriority);
    ~BroadcastQueueGroupInfo();

    void insertChannelInfo(BroadcastQueueInfo* pChannelInfo);
public:
    unsigned int uPriority;
    BroadcastQueueInfo* pItemList;
    BroadcastQueueGroupInfo* pNextGroup;

};





}
#endif // BroadcastQueueInfo__INCLUDED

