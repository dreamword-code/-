#pragma once
#include "ThreadComm.h"
#include"pch.h"
class CSerialPort
{
public:
	CSerialPort();
	~CSerialPort();
public:
	BOOL OpenComm(CString strComm);
	BOOL SetCommState(DWORD dwBaudrate, BYTE byParity, BYTE byByteSize, BYTE byStopBits);
	BOOL SetupComm(DWORD dwInQueue, DWORD dwOutQueue);
	BOOL PurgeComm(DWORD dwFlags);
	BOOL SetCommMask(DWORD dwEvtNask);
	BOOL WriteFile(
		IN LPCVOID lpBuffer, // д������ݴ洢�ĵ�ַ�����Ը�ָ���ֵΪ�׵�ַ��nNumberOfBytesToWrite���ֽڵ����ݽ�Ҫд��
		//���ڵķ������ݻ������� 
		IN DWORD nNumberOfBytesToWrite, //Ҫд������ݵ��ֽ���  
		OUT LPDWORD lpNumberOfBytesWritten,// ָ��ָ��һ��DWORD��ֵ������ֵ����ʵ��д����ֽ��� 
		IN LPOVERLAPPED lpOverlapped// �ص�����ʱ���ò���ָ��һ��OVERLAPPED�ṹ��ͬ������ʱ���ò���ΪNULL�� 
	);
	BOOL ReadFile(
		OUT LPVOID lpBuffer,// ��������ݴ洢�ĵ�ַ������������ݽ��洢���Ը�ָ���ֵΪ�׵�ַ��һƬ�ڴ���  
		IN DWORD nNumberOfBytesToRead, // Ҫ��������ݵ��ֽ���  
		OUT LPDWORD lpNumberOfBytesRead,// ָ��һ��DWORD��ֵ������ֵ���ض�����ʵ�ʶ�����ֽ���  
		IN LPOVERLAPPED lpOverlapped// �ص�����ʱ���ò���ָ��һ��OVERLAPPED�ṹ��ͬ������ʱ���ò���ΪNULL 
	);
	BOOL ClearCommError(OUT LPDWORD lpError, OUT LPCOMSTAT lpStat);

	BOOL GetOverlappedResult(
		IN LPOVERLAPPED lpOverlapped,//ָ���ص�������ʼʱָ����OVERLAPPED�ṹ  
		OUT LPDWORD lpNumberOfBytesTransferred,//ָ��һ��32λ�������ñ�����ֵ����ʵ�ʶ�д����������ֽ�����  
		IN BOOL bWait// �ò�������ָ�������Ƿ�һֱ�ȵ��ص���������������ò���ΪTRUE������ֱ�����������ŷ��أ�
		//����ò���ΪFALSE������ֱ�ӷ��أ���ʱ�������û����ɣ�ͨ������GetLastError()������
		//����ERROR_IO_INCOMPLETE�� 
	);
	void CloseComm();

public:
	void StartComm();

public:
	CThreadComm m_hThreadComm;

public:
	HANDLE m_hComm;
};

