
// taesync's guiDlg.h : ͷ�ļ�
//

#pragma once


// CtaesyncsguiDlg �Ի���
class CtaesyncsguiDlg : public CDialogEx
{
// ����
public:
	CtaesyncsguiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TAESYNCSGUI_DIALOG };

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
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonBrow();
	afx_msg void OnBnClickedButtonUp();
	CString main_src;
};
