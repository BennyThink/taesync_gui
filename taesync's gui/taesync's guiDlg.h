
// taesync's guiDlg.h : 头文件
//

#pragma once


// CtaesyncsguiDlg 对话框
class CtaesyncsguiDlg : public CDialogEx
{
// 构造
public:
	CtaesyncsguiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TAESYNCSGUI_DIALOG };

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
	// //src
	CString src;
	// 空间名
	CString name;
	CString access_key;
	CString secret_key;
	CString dir;
	CString bandwidth;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	// 配置文件名
	CString conf_name;
};
