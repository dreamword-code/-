#pragma once
#include"CThread.h"
class CThread
{
public:
	CThread();
	~CThread();

public:
	HANDLE m_hThread;//�߳̾��
	bool m_bExit;//�߳��˳���־λ
	DWORD m_dwParam;//֪ͨ�߳�ʲô�������Դ����̵߳���

public:
	void start();//�����߳�
	void stop();//ֹͣ�߳�

public:
	virtual void SetThreadData(DWORD dwParam);//�������
	virtual DWORD GetThreadData();//�������

public:
	virtual void run();

public:
	static DWORD ThreadProc(LPVOID pParam);
};
