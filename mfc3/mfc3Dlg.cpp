
// mfc3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "mfc3.h"
#include "mfc3Dlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Student.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmfc3Dlg 对话框

int num = 0;
int count = 0;


//获取当前时间
CString gettime()
{
	CString tm;
	SYSTEMTIME st;
	GetLocalTime(&st);
	tm.Format("%2d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
	return tm;
}


Cmfc3Dlg::Cmfc3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC3_DIALOG, pParent)
	, m_ID(_T(""))
	, m_Name(_T(""))
	, m_Sub1(_T(""))
	, m_Sub2(_T(""))
	, m_Sub3(_T(""))
	, m_Average(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GRADE, m_Grade);
	DDX_Text(pDX, IDC_ID, m_ID);
	DDX_Control(pDX, IDC_LISTBOX, m_Log);
	DDX_Control(pDX, IDC_LISTCTRL, m_Inquiry);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_TREE1, m_TreeCon);
	DDX_Text(pDX, IDC_SUBJECT1, m_Sub1);
	DDX_Text(pDX, IDC_SUBJECT2, m_Sub2);
	DDX_Text(pDX, IDC_SUBJECT3, m_Sub3);
	DDX_Text(pDX, IDC_AVERAGE, m_Average);
}

BEGIN_MESSAGE_MAP(Cmfc3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_ADD, &Cmfc3Dlg::OnBnClickedAdd)
	ON_BN_CLICKED(BTN_RESET, &Cmfc3Dlg::OnBnClickedReset)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &Cmfc3Dlg::OnNMDblclkTree)
	ON_BN_CLICKED(BTN_CLEAR, &Cmfc3Dlg::OnBnClickedClear)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &Cmfc3Dlg::OnTvnSelchangedTree)
END_MESSAGE_MAP()


// Cmfc3Dlg 消息处理程序

BOOL Cmfc3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//添加下拉菜单选项
	m_Grade.AddString(_T("一年级"));
	m_Grade.AddString(_T("二年级"));
	m_Grade.AddString(_T("三年级"));

	//添加树形图节点 root...等变量已经声明在.h文件中
	m_TreeCon.ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
	root = this->m_TreeCon.InsertItem("年级");
	root1 = this->m_TreeCon.InsertItem("一年级", root);
	root2 = this->m_TreeCon.InsertItem("二年级", root);
	root3 = this->m_TreeCon.InsertItem("三年级", root);

	//添加List Control表头
	m_Inquiry.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);
	m_Inquiry.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 40);
	m_Inquiry.InsertColumn(1, _T("学号"), LVCFMT_LEFT, 80);
	m_Inquiry.InsertColumn(2, _T("年级"), LVCFMT_LEFT, 80);
	m_Inquiry.InsertColumn(3, _T("Sub1"), LVCFMT_LEFT, 80);
	m_Inquiry.InsertColumn(4, _T("Sub2"), LVCFMT_LEFT, 80);
	m_Inquiry.InsertColumn(5, _T("Sub3"), LVCFMT_LEFT, 80);


	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmfc3Dlg::OnPaint()
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
HCURSOR Cmfc3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfc3Dlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新编辑框信息
	UpdateData();

	//避免输入错误数据
	if (m_Name == "" || m_ID == "" || m_Sub1 == "" || m_Sub2 == "" || m_Sub3 == "")
	{
		MessageBox("输入有误");
		return;
	}

	//设置Student属性
	Student* temp = new Student();
	temp->name = m_Name.GetString();
	temp->id = m_ID.GetString();
	m_Grade.GetLBText(m_Grade.GetCurSel(), temp->grade);
	temp->sub1 = atof(m_Sub1.GetString());
	temp->sub2 = atof(m_Sub2.GetString());
	temp->sub3 = atof(m_Sub3.GetString());
	temp->calcuavr();

	//新建空句柄
	HTREEITEM handle = NULL;

	//添加节点并记录句柄
	if (temp->grade == "一年级")
	{
		handle = m_TreeCon.InsertItem(temp->name, root1);
	}
	else if (temp->grade == "二年级")
	{
		handle = m_TreeCon.InsertItem(temp->name, root2);
	}
	else if (temp->grade == "三年级")
	{
		handle = m_TreeCon.InsertItem(temp->name, root3);
	}

	//使用句柄绑定数据
	if (handle)
	{
		m_TreeCon.SetItemData(handle, (DWORD)temp);
	}

	//打印日志
	m_Log.AddString(gettime() + " ： DATA ADD");

	//ListBox自动下滑到底端
	count = m_Log.GetCount();
	m_Log.SetCurSel(count - 1);
}

//RESET按钮
void Cmfc3Dlg::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Name.SetString("");
	m_ID.SetString("");
	m_Sub1.SetString("");
	m_Sub2.SetString("");
	m_Sub3.SetString("");
	UpdateData(false);

	m_Log.AddString(gettime() + " ： DATA RESET");

	//ListBox自动下滑到底端
	count = m_Log.GetCount();
	m_Log.SetCurSel(count - 1);
}

//双击事件处理
void Cmfc3Dlg::OnNMDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString sub1, sub2, sub3;
	HTREEITEM item = m_TreeCon.GetSelectedItem();
	Student* stu = (Student*)m_TreeCon.GetItemData(item);

	if (stu)
	{
		//CString转一位小数的double
		sub1.Format("%.1f", stu->sub1);
		sub2.Format("%.1f", stu->sub2);
		sub3.Format("%.1f", stu->sub3);

		//添加行 num为全局变量记录行数
		m_Inquiry.InsertItem(num, stu->name);

		//为num行插入列数据 第一列在插入行时完成
		m_Inquiry.SetItemText(num, 1, stu->id);
		m_Inquiry.SetItemText(num, 2, stu->grade);
		m_Inquiry.SetItemText(num, 3, sub1);
		m_Inquiry.SetItemText(num, 4, sub2);
		m_Inquiry.SetItemText(num, 5, sub3);

		num++;
	}
}


void Cmfc3Dlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Log.ResetContent();
}

//选中树形图节点事件 平均分输出
void Cmfc3Dlg::OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString average;
	HTREEITEM item = m_TreeCon.GetSelectedItem();
	Student* stu = (Student*)m_TreeCon.GetItemData(item);
	if (stu)
	{
		average.Format("%.2f", stu->average);
		m_Average.SetString(average);
		UpdateData(false);
	}
}
