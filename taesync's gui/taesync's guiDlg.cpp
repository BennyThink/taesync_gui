
// taesync's guiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "taesync's gui.h"
#include "taesync's guiDlg.h"
#include "afxdialogex.h"
#include "Config.h"
#include <shlwapi.h>
#include <fstream>
#pragma comment(lib,"Shlwapi.lib")


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
	, main_src(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtaesyncsguiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, main_src);
}

BEGIN_MESSAGE_MAP(CtaesyncsguiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SET, &CtaesyncsguiDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_BROW, &CtaesyncsguiDlg::OnBnClickedButtonBrow)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CtaesyncsguiDlg::OnBnClickedButtonUp)
END_MESSAGE_MAP()


// CtaesyncsguiDlg 消息处理程序

BOOL CtaesyncsguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CStdioFile inFile;
	CString text;
	//检查配置文件是否存在
	if (!PathFileExists("conf.properties"))
	{
		MessageBox("配置文件不存在，请创建！","第一次运行",MB_ICONWARNING);
		CConfig new_set;
		new_set.DoModal();

		//将路径放置到父文本框中
		inFile.Open("conf.properties",CFile::modeRead);
		inFile.ReadString(text);
		text.Replace("src=","");
		SetDlgItemText(IDC_EDIT1, text);
		inFile.Close();    

	}
	else{
		//读取默认配置
		inFile.Open("conf.properties",CFile::modeRead);
		inFile.ReadString(text);
		text.Replace("src=","");
		SetDlgItemText(IDC_EDIT1, text);
		inFile.Close();
	}

	//修改group box为使用默认配置
	SetDlgItemText(IDC_GROUPBOX1,_T("使用默认目录"));
	//修改父文本框





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



void CtaesyncsguiDlg::OnBnClickedButtonSet()
{
	// 设置
	CConfig x;
	x.DoModal();




}


void CtaesyncsguiDlg::OnBnClickedButtonBrow()
{
	// 浏览上传目录

	char szPath[MAX_PATH];     //存放选择的目录路径   
	CString upselect_dir;  
	ZeroMemory(szPath, sizeof(szPath));     
	BROWSEINFO bi;     
	bi.hwndOwner = m_hWnd;     
	bi.pidlRoot = NULL;     
	bi.pszDisplayName = szPath;     
	bi.lpszTitle = "请选择需要上传的目录：";     
	bi.ulFlags = 0;     
	bi.lpfn = NULL;     
	bi.lParam = 0;     
	bi.iImage = 0;     
	//弹出选择目录对话框  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);     
	if(lp && SHGetPathFromIDList(lp, szPath))     
	{  
		for(int i=0;i<=MAX_PATH;i++)
			if (szPath[i]=='\\')
				szPath[i]='/';
		upselect_dir.Format("%s",  szPath);  
		SetDlgItemText(IDC_EDIT1, upselect_dir); 
		SetDlgItemText(IDC_GROUPBOX1,_T("使用自定义目录"));

	}  
	else     
		MessageBox("无效的目录，请重新选择"); 

}


void CtaesyncsguiDlg::OnBnClickedButtonUp()
{
	// 上传代码

	//获取执行参数

	CString exe_path;
	char   c_path[MAX_PATH];  
	GetCurrentDirectory(MAX_PATH,c_path);
	exe_path.Format("%s",c_path);
	exe_path.Replace("\\","/");
	exe_path="-local "+exe_path+"/conf.properties";
	//MessageBox(exe_path);

	//判断是默认还是自定义
	CString main_ifdefault;
	GetDlgItemText(IDC_GROUPBOX1,main_ifdefault);

	//选择不同的执行逻辑
	int call_result=33;    //判断调用结果

	if(main_ifdefault=="使用默认目录")
		call_result=int(ShellExecute(NULL,"open","taesync.exe",exe_path,NULL,SW_SHOWNORMAL));
	else
	{	//用户自定义了目录，要重新配置文件了
		//先更新下文本框的内容
		UpdateData(TRUE);
		CStdioFile inFile;
		CString main_newconf;
		CString text;			//读取的每一行都变化的
		inFile.Open("conf.properties",CFile::modeRead);		//定义infile对象，读取并修改src参数

		inFile.ReadString(text);		//读取第1行src=F:/test并根据文本框修改
		main_newconf="src="+main_src+"\r\n";
		inFile.ReadString(text);				//第2行namespace照样添加
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//第3行ak照样添加
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//第4行sk照样添加
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//第5行dst照样添加
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//第6行debug照样添加
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//第7行bandwidth照样添加
		main_newconf=main_newconf+text;
		inFile.Close();							//结束读文件


		//新配置文件正确


		//要写入文件的字符串为main_newconf
		CFile cf;
		try{
			cf.Open("conf.properties", CFile::modeCreate|CFile::modeWrite);
		}
		catch(CFileException e){
			MessageBox("打开文件错误");
		}

		int len = main_newconf.GetLength();
		cf.Write(main_newconf.GetBuffer(len), len);

		main_newconf.ReleaseBuffer();
		cf.Close();
		MessageBox("配置文件为conf.properties\r\n"+main_newconf,"配置文件已保存",MB_ICONINFORMATION);
		//重写结束,调用
		call_result=int(ShellExecute(NULL,"open","taesync.exe",exe_path,NULL,SW_SHOWNORMAL));

	}


	//判断调用结果
	CString display_result;
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
}
