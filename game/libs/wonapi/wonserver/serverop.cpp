#include "serverop.h"
using namespace WONAPI;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerOp::ServerOp()
{
	mMaxConnectTime = 60000;
	mMaxSendTime = 60000;
	mMaxRecvTime = 60000;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ServerOp::SetMaxTimes(int theConnectTime, int theSendTime, int theRecvTime)
{
	mMaxConnectTime = theConnectTime;
	mMaxSendTime = theSendTime;
	mMaxRecvTime = theRecvTime;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
DWORD ServerOp::ConnectTime()
{
	DWORD aTime = mMaxConnectTime;
	if(!IsAsync())
		aTime = min(TimeLeft(),aTime);

	return aTime;
}
	
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
DWORD ServerOp::SendTime()
{
	DWORD aTime = mMaxSendTime;
	if(!IsAsync())
		aTime = min(TimeLeft(),aTime);

	return aTime;
}
	
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
DWORD ServerOp::RecvTime()
{
	DWORD aTime = mMaxRecvTime;
	if(!IsAsync())
		aTime = min(TimeLeft(),aTime);

	return aTime;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ServerOp::SendMsgAsync(ByteBufferPtr theMsg, int theTrackId)
{
	SendMsgOpPtr anOp = new SendMsgOp(theMsg, mSocket);
	Track(anOp,theTrackId);
	mSocket->QueueOp(anOp);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ServerOp::RecvMsgAsync(int theTrackId)
{
	RecvMsgOpPtr anOp = new RecvMsgOp(mSocket);
	Track(anOp,theTrackId);
	mSocket->QueueOp(anOp);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ServerOp::CopyMaxTimes(ServerOp *theCopyFrom)
{
	SetMaxTimes(theCopyFrom->GetMaxConnectTime(),theCopyFrom->GetMaxSendTime(),theCopyFrom->GetMaxRecvTime());
}