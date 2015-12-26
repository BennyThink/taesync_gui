
// taesync's guiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "taesync's gui.h"
#include "taesync's guiDlg.h"
#include "afxdialogex.h"
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CtaesyncsguiDlg 对话框




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


// CtaesyncsguiDlg 消息处理程序

BOOL CtaesyncsguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtaesyncsguiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtaesyncsguiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtaesyncsguiDlg::OnBnClickedButton1()
{	//生成配置文件	
	
	UpdateData(TRUE);  //获取用户输入
	if (dir=="")
	dir="/";	//默认百川路径
	if(bandwidth=="")
	bandwidth="1024";	//默认速度
	if(conf_name=="")
	conf_name="conf.properties";	//默认配置文件名

	
	CString f_out="src=";
	f_out=f_out+src+"\r\nnamespace="+name+"\r\naccessKey="+access_key+
		"\r\nsecretKey="+secret_key+"\r\ndstDir="+dir+"\r\nisDebug=true\r\nbandWidthLimit="
		+bandwidth;

	CString strMsg;
	strMsg.Format("%s",f_out);


	//将配置文件保存到文件中
	
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

	MessageBox("配置文件路径为config\\"+conf_name+"\r\n"+strMsg,"配置文件已保存",MB_ICONINFORMATION);

	
}


void CtaesyncsguiDlg::OnBnClickedButton2()
{	//开始上传

	//获取当前绝对路径并加以修饰
	
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path="-local "+path+"\\config\\"+conf_name;

	//MessageBox(path,"执行参数",MB_ICONINFORMATION);


	//调用是否成功的判断
	CString display_result;
	int call_result=33;

	call_result=int(ShellExecute(NULL,"open","taesync.exe",path,NULL,SW_SHOWNORMAL));

	display_result.Format("%d", call_result); 

	if(call_result<=32)
		switch(call_result)
	{
		case 0:MessageBox("内存不足","打开程序错误",MB_ICONWARNING);break;
		case 2:MessageBox("请确保taesync.exe存在","文件名错误",MB_ICONWARNING);break;
		case 3:MessageBox("请将本程序放到taesync目录下","路径名错误",MB_ICONWARNING);break;
		case 11:MessageBox("请重新下载taesync.exe","exe文件无效",MB_ICONWARNING);break;
		default:MessageBox("请确保taesync.exe有效","未知错误",MB_ICONWARNING);break;
	}

	
	
	
	
	
	
	
	
	
	// TODO: 在此添加控件通知处理程序代码
}
