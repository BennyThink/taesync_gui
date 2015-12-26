
// taesync's guiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "taesync's gui.h"
#include "taesync's guiDlg.h"
#include "afxdialogex.h"
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtaesyncsguiDlg �Ի���




CtaesyncsguiDlg::CtaesyncsguiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtaesyncsguiDlg::IDD, pParent)
	, src(_T(""))
	, name(_T(""))
	, access_key(_T(""))
	, secret_key(_T(""))
	, dir(_T(""))
	, bandwidth(_T(""))
	, conf_name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtaesyncsguiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, src);
	DDX_Text(pDX, IDC_EDIT5, name);
	DDX_Text(pDX, IDC_EDIT3, access_key);
	DDX_Text(pDX, IDC_EDIT4, secret_key);
	DDX_Text(pDX, IDC_EDIT2, dir);
	DDX_Text(pDX, IDC_EDIT6, bandwidth);
	DDX_Text(pDX, IDC_EDIT7, conf_name);
}

BEGIN_MESSAGE_MAP(CtaesyncsguiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtaesyncsguiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtaesyncsguiDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtaesyncsguiDlg ��Ϣ�������

BOOL CtaesyncsguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtaesyncsguiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtaesyncsguiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtaesyncsguiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtaesyncsguiDlg::OnBnClickedButton1()
{	//���������ļ�	
	
	UpdateData(TRUE);  //��ȡ�û�����
	if (dir=="")
	dir="/";	//Ĭ�ϰٴ�·��
	if(bandwidth=="")
	bandwidth="1024";	//Ĭ���ٶ�
	if(conf_name=="")
	conf_name="conf.properties";	//Ĭ�������ļ���

	
	CString f_out="src=";
	f_out=f_out+src+"\r\nnamespace="+name+"\r\naccessKey="+access_key+
		"\r\nsecretKey="+secret_key+"\r\ndstDir="+dir+"\r\nisDebug=true\r\nbandWidthLimit="
		+bandwidth;

	CString strMsg;
	strMsg.Format("%s",f_out);


	//�������ļ����浽�ļ���
	
	CFile cf;
	try{
		cf.Open(("config\\"+conf_name), CFile::modeCreate|CFile::modeWrite);

	}
	catch(CFileException e){
		//oo
		MessageBox("Open failed when write.");
	}

	int len = strMsg.GetLength();
	cf.Write(strMsg.GetBuffer(len), len);
	cf.Close();
	strMsg.ReleaseBuffer();

	MessageBox("�����ļ�·��Ϊconfig\\"+conf_name+"\r\n"+strMsg,"�����ļ��ѱ���",MB_ICONINFORMATION);

	
}


void CtaesyncsguiDlg::OnBnClickedButton2()
{	//��ʼ�ϴ�

	//��ȡ��ǰ����·������������
	
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path="-local "+path+"\\config\\"+conf_name;

	//MessageBox(path,"ִ�в���",MB_ICONINFORMATION);


	//�����Ƿ�ɹ����ж�
	CString display_result;
	int call_result=33;

	call_result=int(ShellExecute(NULL,"open","taesync.exe",path,NULL,SW_SHOWNORMAL));

	display_result.Format("%d", call_result); 

	if(call_result<=32)
		switch(call_result)
	{
		case 0:MessageBox("�ڴ治��","�򿪳������",MB_ICONWARNING);break;
		case 2:MessageBox("��ȷ��taesync.exe����","�ļ�������",MB_ICONWARNING);break;
		case 3:MessageBox("�뽫������ŵ�taesyncĿ¼��","·��������",MB_ICONWARNING);break;
		case 11:MessageBox("����������taesync.exe","exe�ļ���Ч",MB_ICONWARNING);break;
		default:MessageBox("��ȷ��taesync.exe��Ч","δ֪����",MB_ICONWARNING);break;
	}

	
	
	
	
	
	
	
	
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
