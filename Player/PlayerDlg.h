// PlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "wmpplayer4.h"
#include "afxwin.h"

// CPlayerDlg �Ի���
class CPlayerDlg : public CDialog
{
// ����
public:
	CPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddMusic();
	CWMPPlayer4 m_player;
	CListBox m_musicList;
	int m_model;
public:
	void OnSaveMusic(void);
public:
	afx_msg void OnDeleteMusic();
	afx_msg void OnPlayMusic();
	afx_msg void OnPauseMusic();
	afx_msg void OnLastMusic();
	afx_msg void OnNextMusic();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	afx_msg void OnLbnDblclkList1();
public:
	CString getSavePath(CString strExePath);
	CString m_defaultFileName;
	CString m_savePath;
public:
	afx_msg void OnBnAbout();
};
