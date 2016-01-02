
// taesync's guiDlg.cpp : ʵ���ļ�
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


// CtaesyncsguiDlg ��Ϣ�������

BOOL CtaesyncsguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CStdioFile inFile;
	CString text;
	//��������ļ��Ƿ����
	if (!PathFileExists("conf.properties"))
	{
		MessageBox("�����ļ������ڣ��봴����","��һ������",MB_ICONWARNING);
		CConfig new_set;
		new_set.DoModal();

		//��·�����õ����ı�����
		inFile.Open("conf.properties",CFile::modeRead);
		inFile.ReadString(text);
		text.Replace("src=","");
		SetDlgItemText(IDC_EDIT1, text);
		inFile.Close();    

	}
	else{
		//��ȡĬ������
		inFile.Open("conf.properties",CFile::modeRead);
		inFile.ReadString(text);
		text.Replace("src=","");
		SetDlgItemText(IDC_EDIT1, text);
		inFile.Close();
	}

	//�޸�group boxΪʹ��Ĭ������
	SetDlgItemText(IDC_GROUPBOX1,_T("ʹ��Ĭ��Ŀ¼"));
	//�޸ĸ��ı���





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



void CtaesyncsguiDlg::OnBnClickedButtonSet()
{
	// ����
	CConfig x;
	x.DoModal();




}


void CtaesyncsguiDlg::OnBnClickedButtonBrow()
{
	// ����ϴ�Ŀ¼

	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·��   
	CString upselect_dir;  
	ZeroMemory(szPath, sizeof(szPath));     
	BROWSEINFO bi;     
	bi.hwndOwner = m_hWnd;     
	bi.pidlRoot = NULL;     
	bi.pszDisplayName = szPath;     
	bi.lpszTitle = "��ѡ����Ҫ�ϴ���Ŀ¼��";     
	bi.ulFlags = 0;     
	bi.lpfn = NULL;     
	bi.lParam = 0;     
	bi.iImage = 0;     
	//����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);     
	if(lp && SHGetPathFromIDList(lp, szPath))     
	{  
		for(int i=0;i<=MAX_PATH;i++)
			if (szPath[i]=='\\')
				szPath[i]='/';
		upselect_dir.Format("%s",  szPath);  
		SetDlgItemText(IDC_EDIT1, upselect_dir); 
		SetDlgItemText(IDC_GROUPBOX1,_T("ʹ���Զ���Ŀ¼"));

	}  
	else     
		MessageBox("��Ч��Ŀ¼��������ѡ��"); 

}


void CtaesyncsguiDlg::OnBnClickedButtonUp()
{
	// �ϴ�����

	//��ȡִ�в���

	CString exe_path;
	char   c_path[MAX_PATH];  
	GetCurrentDirectory(MAX_PATH,c_path);
	exe_path.Format("%s",c_path);
	exe_path.Replace("\\","/");
	exe_path="-local "+exe_path+"/conf.properties";
	//MessageBox(exe_path);

	//�ж���Ĭ�ϻ����Զ���
	CString main_ifdefault;
	GetDlgItemText(IDC_GROUPBOX1,main_ifdefault);

	//ѡ��ͬ��ִ���߼�
	int call_result=33;    //�жϵ��ý��

	if(main_ifdefault=="ʹ��Ĭ��Ŀ¼")
		call_result=int(ShellExecute(NULL,"open","taesync.exe",exe_path,NULL,SW_SHOWNORMAL));
	else
	{	//�û��Զ�����Ŀ¼��Ҫ���������ļ���
		//�ȸ������ı��������
		UpdateData(TRUE);
		CStdioFile inFile;
		CString main_newconf;
		CString text;			//��ȡ��ÿһ�ж��仯��
		inFile.Open("conf.properties",CFile::modeRead);		//����infile���󣬶�ȡ���޸�src����

		inFile.ReadString(text);		//��ȡ��1��src=F:/test�������ı����޸�
		main_newconf="src="+main_src+"\r\n";
		inFile.ReadString(text);				//��2��namespace�������
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//��3��ak�������
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//��4��sk�������
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//��5��dst�������
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//��6��debug�������
		main_newconf=main_newconf+text+"\r\n";
		inFile.ReadString(text);				//��7��bandwidth�������
		main_newconf=main_newconf+text;
		inFile.Close();							//�������ļ�


		//�������ļ���ȷ


		//Ҫд���ļ����ַ���Ϊmain_newconf
		CFile cf;
		try{
			cf.Open("conf.properties", CFile::modeCreate|CFile::modeWrite);
		}
		catch(CFileException e){
			MessageBox("���ļ�����");
		}

		int len = main_newconf.GetLength();
		cf.Write(main_newconf.GetBuffer(len), len);

		main_newconf.ReleaseBuffer();
		cf.Close();
		MessageBox("�����ļ�Ϊconf.properties\r\n"+main_newconf,"�����ļ��ѱ���",MB_ICONINFORMATION);
		//��д����,����
		call_result=int(ShellExecute(NULL,"open","taesync.exe",exe_path,NULL,SW_SHOWNORMAL));

	}


	//�жϵ��ý��
	CString display_result;
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
}
