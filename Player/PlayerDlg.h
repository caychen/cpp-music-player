// PlayerDlg.h : 头文件
//

#pragma once
#include "wmpplayer4.h"
#include "afxwin.h"

// CPlayerDlg 对话框
class CPlayerDlg : public CDialog
{
// 构造
public:
	CPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
