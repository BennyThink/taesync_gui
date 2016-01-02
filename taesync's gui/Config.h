#pragma once


// CConfig 对话框

class CConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CConfig)

public:
	CConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString set_src;
	CString set_name;
	CString set_access_key;
	CString set_secret_key;
	CString set_dst_dir;
	CString set_bandwidth;
	afx_msg void OnBnClickedButtonMake();
	afx_msg void OnBnClickedButtonSetb();
};
