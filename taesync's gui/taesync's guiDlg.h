
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
	// //src
	CString src;
	// �ռ���
	CString name;
	CString access_key;
	CString secret_key;
	CString dir;
	CString bandwidth;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	// �����ļ���
	CString conf_name;
};
