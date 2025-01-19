#include <Winsock2.h>
#include "LanServerTimeOut.h"

LanServerTimeOut::LanServerTimeOut(DWORD tickPerFrame, HANDLE hCompletionPort, LONG pqcsLimit, LanServer* pLanServer)
	:UpdateBase{ tickPerFrame,hCompletionPort,pqcsLimit }, pLanServer_{ pLanServer }
{
}

LanServerTimeOut::~LanServerTimeOut()
{
}

// Release �÷��� ���� -> time = 0 ->������ ���ÿ� Push -> id ����(Init) ->  AcceptEx -> �Ϸ����� ���� time�� ����ð����� ����
void LanServerTimeOut::Update_IMPL()
{
	ULONGLONG currentTime = GetTickCount64();
	for (int i = 0; i < pLanServer_->maxSession_; ++i)
	{
		LanSession* pSession = pLanServer_->pSessionArr_ + i;

		// RELEASE_���� �� �� ��ټ��� ������ �ɷ����� ���ؼ� �ֻ��
		// ������ Release�Ǳ� ������ ������� ��ɾ� �������� RefCnt�� �̸��о �ش� if���� ����ϴ��� Disconnect���� �ɷ���, ������ ����ϴ��� �̹� ����� ������ �ְ� ����Ŷ� �������
		if ((pSession->refCnt_ & LanSession::RELEASE_FLAG) == LanSession::RELEASE_FLAG)
			continue;

		// ������ ��Ȱ�� �Ǿ��µ� id�� ���簪�� ���� ��� ReleaseSession���� LastRecvTime�� 0���� �ٲٰ� �ʱ�ȭ���� �ش纯���� ����ð����� �ٲٱ⶧���� 0 Ȥ�� ����ð��� �д´� 
		ULONGLONG id = pSession->id_;
		ULONGLONG lastRecvTime = pSession->lastRecvTime;

		if (lastRecvTime == 0)
			continue;

		if (currentTime < lastRecvTime + pLanServer_->TIME_OUT_MILLISECONDS_) // ������ �ʿ䰡 ���
			continue;

		pLanServer_->Disconnect(id);
	}
}
