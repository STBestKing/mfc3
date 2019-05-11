
// mfc3Dlg.h: 头文件
//

#pragma once


// Cmfc3Dlg 对话框
class Cmfc3Dlg : public CDialogEx
{
// 构造
public:
	Cmfc3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Grade;
	CString m_ID;
	CListBox m_Log;
	CListCtrl m_Inquiry;
	CString m_Name;
	CTreeCtrl m_TreeCon;
	afx_msg void OnBnClickedAdd();
	HTREEITEM root, root1, root2, root3;
	CString m_Sub1;
	CString m_Sub2;
	CString m_Sub3;
	afx_msg void OnBnClickedReset();
	afx_msg void OnNMDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedClear();
	CString m_Average;
	afx_msg void OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
};
