#include <winsock2.h>
#include <windows.h>
#include "CommonProtocol.h"
#include "MonitorNetServer.h"
#include "Packet.h"
#include "NetSession.h"
#include <Assert.h>
#include <unordered_set>


MonitorNetServer::MonitorNetServer()
    :NetServer{ L"MonitorNetConfig.txt" }
{
    InitializeSRWLock(&uMapLock);
}

BOOL MonitorNetServer::Start()
{
    for (DWORD i = 0; i < IOCP_WORKER_THREAD_NUM_; ++i)
        ResumeThread(hIOCPWorkerThreadArr_[i]);

    ResumeThread(hAcceptThread_);
    return TRUE;
}

BOOL MonitorNetServer::OnConnectionRequest(const SOCKADDR_IN* pSockAddrIn)
{
    return TRUE;
}

void* MonitorNetServer::OnAccept(ULONGLONG id)
{
    return nullptr;
}

void MonitorNetServer::OnRelease(ULONGLONG id)
{
    PostQueuedCompletionStatus(hcp_, 4, (ULONG_PTR)id, (LPOVERLAPPED)&OnPostOverlapped);
}
void MonitorNetServer::OnRecv(ULONGLONG id, Packet* pPacket)

{
    WORD type;
    (*pPacket) >> type;
    switch ((en_PACKET_TYPE)type)
    {
    case en_PACKET_CS_MONITOR_TOOL_REQ_LOGIN:
    {
        pPacket->MoveReadPos(32);
        NetSession* pSession = pSessionArr_ + NetSession::GET_SESSION_INDEX(id);

        // 모니터링 클라 자료구조에 추가
        AcquireSRWLockExclusive(&uMapLock);
        uMap.insert(id);
        InterlockedIncrement(&monitorClientNum_);
        ReleaseSRWLockExclusive(&uMapLock);

        // 그사이에 Release되엇으면 SendPacket이 실패함
        SmartPacket pSendPacket = PACKET_ALLOC(Net);
        (*pSendPacket) << (WORD)en_PACKET_CS_MONITOR_TOOL_RES_LOGIN << (BYTE)dfMONITOR_TOOL_LOGIN_OK;
        SendPacket(id, pSendPacket);
        break;
    }
    default:
        __debugbreak();
        break;
    }

    PACKET_FREE(pPacket);
}

void MonitorNetServer::OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket)
{
}

void MonitorNetServer::OnPost(void* order)
{
    ULONGLONG id = (ULONGLONG)order;
    OnRelease_IMPL(id);
}

void MonitorNetServer::OnLastTaskBeforeAllWorkerThreadEndBeforeShutDown()
{
}

void MonitorNetServer::OnResourceCleanAtShutDown()
{
}

void MonitorNetServer::SendToAllClient(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp)
{
    SmartPacket sp = PACKET_ALLOC(Net);
    (*sp) << (WORD)en_PACKET_CS_MONITOR_TOOL_DATA_UPDATE << serverNo << dataType << dataValue << timeStamp;
    AcquireSRWLockShared(&uMapLock);
    for (ULONGLONG id: uMap)
        SendPacket(id, sp);
    ReleaseSRWLockShared(&uMapLock);
}


void MonitorNetServer::OnRelease_IMPL(ULONGLONG id)
{
    AcquireSRWLockExclusive(&uMapLock);
    ASSERT_LOG(uMap.erase(id) != 1,L"NoExist Session Release");
    InterlockedDecrement(&monitorClientNum_);
    ReleaseSRWLockExclusive(&uMapLock);
}
