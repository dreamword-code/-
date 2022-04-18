#include "pch.h"
#include "CSerialPort.h"

CSerialPort::CSerialPort()
{
	m_hComm = NULL;
}


CSerialPort::~CSerialPort()
{
	CloseComm();
}

void CSerialPort::StartComm()
{
	m_hThreadComm.SetThreadData((DWORD)this);
	m_hThreadComm.start();
}

BOOL CSerialPort::OpenComm(CString strComm)
{
	if (NULL == m_hComm)
	{
		m_hComm = CreateFile((TCHAR*)(LPCTSTR)strComm,//COM��  
			GENERIC_READ | GENERIC_WRITE, //�������д  
			0, //��ռ��ʽ  
			NULL,
			OPEN_EXISTING, //�򿪶����Ǵ���  
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //ͬ����ʽ  
			NULL);
		if (INVALID_HANDLE_VALUE == m_hComm)
		{
			int nError = GetLastError();
			m_hComm = NULL;
			AfxMessageBox(_T("���ڴ�ʧ��"));
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSerialPort::SetCommState(DWORD dwBaudrate, BYTE byParity, BYTE byByteSize, BYTE byStopBits)
{
	if (NULL == m_hComm) return FALSE;
	DCB dcb;
	BOOL bRet = ::GetCommState(m_hComm, &dcb);
	if (!bRet)
	{
		if (m_hComm)
		{
			CloseHandle(m_hComm);
			m_hComm = NULL;
		}
		return FALSE;
	}
	dcb.BaudRate = dwBaudrate;
	dcb.Parity = byParity;
	dcb.ByteSize = byByteSize;
	dcb.StopBits = byStopBits;

	bRet = ::SetCommState(m_hComm, &dcb);
	if (!bRet)
	{
		if (m_hComm)
		{
			CloseHandle(m_hComm);
			m_hComm = NULL;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSerialPort::SetupComm(DWORD dwInQueue, DWORD dwOutQueue)
{
	if (NULL == m_hComm) return FALSE;
	return ::SetupComm(m_hComm, dwInQueue, dwOutQueue);
}

BOOL CSerialPort::PurgeComm(DWORD dwFlags)
{
	if (NULL == m_hComm) return FALSE;
	return ::PurgeComm(m_hComm, dwFlags);
}

BOOL CSerialPort::SetCommMask(DWORD dwEvtNask)
{
	if (NULL == m_hComm) return FALSE;
	return ::SetCommMask(m_hComm, dwEvtNask);
}


BOOL CSerialPort::WriteFile(
	IN LPCVOID lpBuffer, // д������ݴ洢�ĵ�ַ�����Ը�ָ���ֵΪ�׵�ַ��nNumberOfBytesToWrite���ֽڵ����ݽ�Ҫд��
	//���ڵķ������ݻ������� 
	IN DWORD nNumberOfBytesToWrite, //Ҫд������ݵ��ֽ���  
	OUT LPDWORD lpNumberOfBytesWritten,// ָ��ָ��һ��DWORD��ֵ������ֵ����ʵ��д����ֽ��� 
	IN LPOVERLAPPED lpOverlapped// �ص�����ʱ���ò���ָ��һ��OVERLAPPED�ṹ��ͬ������ʱ���ò���ΪNULL�� 
)
{
	if (NULL == m_hComm) return FALSE;
	return ::WriteFile(m_hComm, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);

}


BOOL CSerialPort::ReadFile(
	OUT LPVOID lpBuffer,// ��������ݴ洢�ĵ�ַ������������ݽ��洢���Ը�ָ���ֵΪ�׵�ַ��һƬ�ڴ���  
	IN DWORD nNumberOfBytesToRead, // Ҫ��������ݵ��ֽ���  
	OUT LPDWORD lpNumberOfBytesRead,// ָ��һ��DWORD��ֵ������ֵ���ض�����ʵ�ʶ�����ֽ���  
	IN LPOVERLAPPED lpOverlapped// �ص�����ʱ���ò���ָ��һ��OVERLAPPED�ṹ��ͬ������ʱ���ò���ΪNULL 
)
{
	if (NULL == m_hComm) return FALSE;
	return ::ReadFile(m_hComm, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

BOOL CSerialPort::ClearCommError(OUT LPDWORD lpError, OUT LPCOMSTAT lpStat)
{
	if (NULL == m_hComm) return FALSE;
	return ::ClearCommError(m_hComm, lpError, lpStat);
}

BOOL CSerialPort::GetOverlappedResult(
	IN LPOVERLAPPED lpOverlapped,//ָ���ص�������ʼʱָ����OVERLAPPED�ṹ  
	OUT LPDWORD lpNumberOfBytesTransferred,//ָ��һ��32λ�������ñ�����ֵ����ʵ�ʶ�д����������ֽ�����  
	IN BOOL bWait// �ò�������ָ�������Ƿ�һֱ�ȵ��ص���������������ò���ΪTRUE������ֱ�����������ŷ��أ�
	//����ò���ΪFALSE������ֱ�ӷ��أ���ʱ�������û����ɣ�ͨ������GetLastError()������
	//����ERROR_IO_INCOMPLETE�� 
)
{
	if (NULL == m_hComm) return FALSE;
	return ::GetOverlappedResult(m_hComm, lpOverlapped, lpNumberOfBytesTransferred, bWait);
}


void CSerialPort::CloseComm()
{
	m_hThreadComm.stop();
	if (m_hComm)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}
}

