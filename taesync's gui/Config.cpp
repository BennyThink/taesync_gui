// Config.cpp : 实现文件
//

#include "stdafx.h"
#include "taesync's gui.h"
#include "Config.h"
#include "afxdialogex.h"
#include <shlwapi.h>
#include <fstream>
#pragma comment(lib,"Shlwapi.lib")

// CConfig 对话框

IMPLEMENT_DYNAMIC(CConfig, CDialogEx)

CConfig::CConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfig::IDD, pParent)
	, set_src(_T(""))
	, set_name(_T(""))
	, set_access_key(_T(""))
	, set_secret_key(_T(""))
	, set_dst_dir(_T(""))
	, set_bandwidth(_T(""))
{

}

CConfig::~CConfig()
{
}

void CConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, set_src);
	DDX_Text(pDX, IDC_EDIT2, set_name);
	DDX_Text(pDX, IDC_EDIT3, set_access_key);
	DDX_Text(pDX, IDC_EDIT4, set_secret_key);
	DDX_Text(pDX, IDC_EDIT5, set_dst_dir);
	DDX_Text(pDX, IDC_EDIT6, set_bandwidth);
}


BEGIN_MESSAGE_MAP(CConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MAKE, &CConfig::OnBnClickedButtonMake)
	ON_BN_CLICKED(IDC_BUTTON_SETB, &CConfig::OnBnClickedButtonSetb)
END_MESSAGE_MAP()


// CConfig 消息处理程序


void CConfig::OnBnClickedButtonMake()
{
	//生成配置文件
	UpdateData(TRUE);  //获取用户输入

	if(set_src==""||set_name==""||set_access_key==""||set_secret_key=="")
		MessageBox("同步目录、空间名称、ak、sk不可为空","提示",MB_ICONSTOP);
	else
	{

		if (set_dst_dir=="")
			set_dst_dir="/";	//默认百川路径
		if(set_bandwidth=="")
			set_bandwidth="1024";	//默认速度




		//要写入文件的字符串为set_string
		CString set_string="src=";
		set_string=set_string+set_src+"\r\nnamespace="+set_name+"\r\naccessKey="+set_access_key+
			"\r\nsecretKey="+set_secret_key+"\r\ndstDir="+set_dst_dir+"\r\nisDebug=true\r\nbandWidthLimit="
			+set_bandwidth;




		CFile cf;
		try{
			cf.Open("conf.properties", CFile::modeCreate|CFile::modeWrite);
		}
		catch(CFileException *e){
			MessageBox("打开文件错误");
			delete e;
		}

		int len = set_string.GetLength();
		cf.Write(set_string.GetBuffer(len), len);
		cf.Close();
		set_string.ReleaseBuffer();

		MessageBox("配置文件为conf.properties\r\n"+set_string,"配置文件已保存",MB_ICONINFORMATION);
		this->EndDialog(len);
}
}

	void CConfig::OnBnClickedButtonSetb()
	{
		//设置的浏览目录
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


		}  
		else     
			MessageBox("无效的目录，请重新选择"); 
	}
