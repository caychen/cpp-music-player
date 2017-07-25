// PlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Player.h"
#include "PlayerDlg.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPlayerDlg �Ի���
CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPlayerDlg::IDD, pParent)
, m_model(0)
, m_defaultFileName(_T(""))
, m_savePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX2, m_player);
	DDX_Control(pDX, IDC_LIST1, m_musicList);
	DDX_Radio(pDX, IDC_RADIO1, m_model);
}

BEGIN_MESSAGE_MAP(CPlayerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADDBTN, &CPlayerDlg::OnAddMusic)
	ON_BN_CLICKED(IDC_DELETEBTN, &CPlayerDlg::OnDeleteMusic)
	ON_BN_CLICKED(IDC_PLAYBTN, &CPlayerDlg::OnPlayMusic)
	ON_BN_CLICKED(IDC_PAUSEBTN, &CPlayerDlg::OnPauseMusic)
	ON_BN_CLICKED(IDC_LASTBTN, &CPlayerDlg::OnLastMusic)
	ON_BN_CLICKED(IDC_NEXTBTN, &CPlayerDlg::OnNextMusic)
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDC_LIST1, &CPlayerDlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_ABOUT, &CPlayerDlg::OnBnAbout)
END_MESSAGE_MAP()


// CPlayerDlg ��Ϣ�������

BOOL CPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	char CurrentProgramPath[MAX_PATH];     
	GetModuleFileName(NULL,CurrentProgramPath,MAX_PATH);   
	CString ExcelFilePathName =  CurrentProgramPath;//ExcelFilePathName��ʾexcel�ļ���·�����ļ��� 
	CString SaveFileName;
	int nPointPos = ExcelFilePathName.ReverseFind('\\');

	if(nPointPos != -1)
	{
		ExcelFilePathName = ExcelFilePathName.Left(nPointPos);
	}

	//SaveFileName += _T("\\Data.xls");
	ExcelFilePathName += _T("\\List.txt");

	FILE *fp;
	fp = fopen(ExcelFilePathName,"r");
	if(fp == NULL)
	{
		fp = fopen(ExcelFilePathName,"w");
	}
	fclose(fp);

	CStdioFile ioFile(ExcelFilePathName,CFile::modeRead);
	CString str;

	while(ioFile.ReadString(str))
	{
		m_musicList.AddString(str);
	}
	ioFile.Close();

	if(m_musicList.GetCount() != 0)
		m_musicList.SetCurSel(0);
	else
	{
		((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_NEXTBTN))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_LASTBTN))->EnableWindow(FALSE);
	}

	//SetWindowPos(NULL,0,0,480,340,SWP_NOMOVE);//������ƶ�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPlayerDlg::OnAddMusic()
{
	// TODO: Add your control notification handler code here
	char  szFileFilter[] = 
		"MP3 File(*.mp3)|*.mp3|"
		"WMA File(*.wma)|*.wma|"
		"WMV File(*.wmv)|*.wmv|"
		"ALL File(*.*)|*.*|| ";//�ļ����͹���

	CString PathName;

	CFileDialog  dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFileFilter);

	if(dlg.DoModal() == IDOK)
	{
		PathName = dlg.GetPathName();
		m_musicList.AddString(PathName);
		OnSaveMusic();
	}

	((CButton*)GetDlgItem(IDC_NEXTBTN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_LASTBTN))->EnableWindow(TRUE);


	int state = m_player.GetPlayState();
	
	if(3 == state)//����״̬
	{
		m_musicList.SetCurSel(m_musicList.GetCurSel());
		((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(TRUE);
	}
	else //�ǲ���״̬
	{
		((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);
		m_musicList.SetCurSel(m_musicList.GetCount() - 1);
	}

}

void CPlayerDlg::OnSaveMusic(void)
{
	CString strExePath = getSavePath(m_savePath);
	strExePath += "\\List.txt";

	CStdioFile ioFile;
	ioFile.Open(strExePath,CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	int listCount = m_musicList.GetCount();

	CString str;
	for(int i = 0;i < listCount;++i)
	{
		m_musicList.GetText(i,str);
		str += "\n";
		ioFile.WriteString(str);
	}
	ioFile.Close();
}

void CPlayerDlg::OnDeleteMusic()
{
	// TODO: Add your control notification handler code here
	int state = m_player.GetPlayState();
	int index;

	if(3 == state)//����״̬
	{
		CString currentMusic = m_player.GetUrl();
		CString cursorMusic;
		m_musicList.GetText(m_musicList.GetCurSel(),cursorMusic);

		m_musicList.DeleteString(m_musicList.GetCurSel());
		if(!m_musicList.GetCount())
		{
			m_player.close();
			OnSaveMusic();
			((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_NEXTBTN))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_LASTBTN))->EnableWindow(FALSE);
			KillTimer(1);
			return;
		}

		if(currentMusic == cursorMusic)
			OnNextMusic();
	}
	else
	{
		m_musicList.DeleteString(m_musicList.GetCurSel());
		index = m_musicList.GetCurSel() + 1 ;
		if(index >= m_musicList.GetCount())
			index = 0;

		m_musicList.SetCurSel(index);
	}
	OnSaveMusic();
}

void CPlayerDlg::OnPlayMusic()
{
	// TODO: Add your control notification handler code here
	int index = m_musicList.GetCurSel();
	if(-1 == index)
	{
		index = 0;
		m_musicList.SetCurSel(index);
	}

	CString str;
	m_musicList.GetText(index,str);
	m_player.SetUrl(str);
	SetTimer(1,1000,NULL);//�ڵ������ʱ�ʹ�����ʱ��

	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(TRUE);
}

void CPlayerDlg::OnPauseMusic()
{
	// TODO: Add your control notification handler code here
	m_player.close();
	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);
	KillTimer(1);
}

void CPlayerDlg::OnLastMusic()
{
	// TODO: Add your control notification handler code here
	CString str;
	int index;

	if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() 
		|| ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())//˳����ߵ���
	{
		index = m_musicList.GetCurSel();
		if(index == 0)
			index = m_musicList.GetCount() - 1;
		else
			index -= 1;

		m_musicList.GetText(index,str);
		m_player.SetUrl(str);
		m_musicList.SetCurSel(index);
	}

	else if(((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())//���
	{
		srand(time(NULL));
		m_musicList.SetCurSel(rand() % (m_musicList.GetCount()));
		m_musicList.GetText(m_musicList.GetCurSel(),str);
		m_player.SetUrl(str);
	}
}

void CPlayerDlg::OnNextMusic()
{
	// TODO: Add your control notification handler code here
	CString str;
	int index;

	if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()
		|| ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())//˳����ߵ���
	{
		index = m_musicList.GetCurSel() + 1 ;
		if(index >= m_musicList.GetCount())
			index = 0;

		m_musicList.GetText(index,str);
		m_player.SetUrl(str);
		m_musicList.SetCurSel(index);
	}

	else if(((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())//���
	{
		srand(time(NULL));
		m_musicList.SetCurSel(rand() % (m_musicList.GetCount()));
		m_musicList.GetText(m_musicList.GetCurSel(),str);
		m_player.SetUrl(str);
	}
}

void CPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int state = m_player.GetPlayState();
	CString str;
	int index;

	if(state == 1)
	{
		if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())//˳��
		{
			index = m_musicList.GetCurSel() + 1 ;
			if(index >= m_musicList.GetCount())
				index = 0;

			m_musicList.GetText(index,str);
			m_player.SetUrl(str);
			m_musicList.SetCurSel(index);
		}
		else if(((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())//����
		{
			m_musicList.GetText(m_musicList.GetCurSel(),str);
			m_player.SetUrl(str);
		}
		else if(((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())//���
		{
			srand(time(NULL));
			m_musicList.SetCurSel(rand() % (m_musicList.GetCount()));
			m_musicList.GetText(m_musicList.GetCurSel(),str);
			m_player.SetUrl(str);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CPlayerDlg::OnLbnDblclkList1()
{
	// TODO: Add your control notification handler code here
	CString str;
	int index=m_musicList.GetCurSel();
	m_musicList.GetText(index,str);
	m_player.SetUrl(str);
	SetTimer(1,1000,NULL);//�ڵ������ʱ�ʹ�����ʱ��
	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(TRUE);
}

CString CPlayerDlg::getSavePath(CString strExePath)
{
	if (strExePath.IsEmpty())
	{
		GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
		strExePath.ReleaseBuffer();
	}

	strExePath = strExePath.Left(strExePath.ReverseFind(_T('\\')));	
	return strExePath;

}

void CPlayerDlg::OnBnAbout()
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}
