// FilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "FilterDlg.h"
//#include <queue>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void debug(char *msg, ...);
//class CService;


LONG ParentOldWndProc;
HWND PrevFocus;

CImageList CFilterDlg::m_ImageList;
int CFilterDlg::m_nDefaultImageIdx = 8;

/////////////////////////////////////////////////////////////////////////////
// CFilterDlg dialog


CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/, IDispatch* pCont_1C)
	: CDialog(CFilterDlg::IDD, pParent)
{
	if (!m_ImageList.GetSafeHandle())
	{
		m_ImageList.Create(16, 16, ILC_COLOR, 0, 10);
		SetDefaultImageList();
	}

	m_pCont_1C = pCont_1C;
	m_flags = 0;
}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterDlg)
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialog)
	//{{AFX_MSG_MAP(CFilterDlg)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TREE1, OnCustomDraw)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterDlg message handlers

LRESULT ParentNewWndProc (HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_CLOSE) return 0;
	return ::CallWindowProcA((WNDPROC)ParentOldWndProc,Wnd,Msg,wParam,lParam);
}

long CFilterDlg::GetFullAutoWidth()
{
	long nWidth = m_width;

	HDC dc = ::GetDC(m_tree.m_hWnd);
	HFONT fnt = CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY,
		DEFAULT_PITCH,"MS Sans Serif");
	::SelectObject(dc, fnt);

	CString currstrvalue;
	for(int i = 0; i < m_values.GetSize(); i++)
	{
		currstrvalue = m_values[i];
		SIZE sz;
		::GetTextExtentPoint32(dc, currstrvalue, currstrvalue. GetLength(), &sz);
		nWidth = __max(nWidth, sz.cx);
	}
	
	nWidth += 16 + 15 + (GetSystemMetrics(SM_CXBORDER) * 4) + GetSystemMetrics(SM_CXVSCROLL);
	nWidth = __min(nWidth, GetSystemMetrics(SM_CXFULLSCREEN) - 20);
	
	::DeleteObject(fnt);
	::ReleaseDC(m_tree.m_hWnd, dc);

	return nWidth;
}

long CFilterDlg::GetTreeAutoWidth()
{
	long nWidth = m_width;

	HDC dc = ::GetDC(m_tree.m_hWnd);
	HFONT fnt = CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY,
		DEFAULT_PITCH,"MS Sans Serif");
	::SelectObject(dc, fnt);
	
	CString currstrvalue;
	HTREEITEM item = m_tree.GetNextItem(TVI_ROOT,TVGN_CHILD);
	while (item)
	{
		int i = m_tree.GetItemData(item);
		currstrvalue = m_values[i];
		SIZE sz;
		::GetTextExtentPoint32(dc, currstrvalue, currstrvalue. GetLength(), &sz);
		nWidth = __max(nWidth, sz.cx);

		item = m_tree.GetNextItem(item, TVGN_NEXT);
	}
	
	nWidth += 16 + 15 + (GetSystemMetrics(SM_CXBORDER) * 4) + GetSystemMetrics(SM_CXVSCROLL);
	// nWidth = __min(nWidth, GetSystemMetrics(SM_CXFULLSCREEN) - 20);
	
	::DeleteObject(fnt);
	::ReleaseDC(m_tree.m_hWnd, dc);

	return nWidth;
}

void CFilterDlg::SetDefaultImageList()
{
	m_nDefaultImageIdx = 8;
	m_ImageList.SetImageCount(0);

	CBitmap Pic;
	COLORREF Pal = RGB(0, 0, 0);

	int nID[] = {IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3, IDB_BITMAP4, IDB_BITMAP5,
		IDB_BITMAP6, IDB_BITMAP7, IDB_BITMAP8, IDB_BITMAP9, IDB_BITMAP10};

	int nCount = sizeof(nID) /sizeof(int);
	for(int i = 0; i < nCount; i++)
	{
		Pic.LoadBitmap(nID[i]);
		m_ImageList.Add(&Pic, Pal);
		Pic.DeleteObject();
	}
}

CString CFilterDlg::SetImageList(CString csList)
{
	if (!m_ImageList.GetSafeHandle())
		m_ImageList.Create(16, 16, ILC_COLOR, 0, 10);

	m_nDefaultImageIdx = 0;
	m_ImageList.SetImageCount(0);

	CBitmap Pic;
	COLORREF Pal = RGB(0, 0, 0);

	CString csErrList;
	LPCTSTR ptr = csList, start;
	while(*ptr)
	{
		start = ptr;
		while(*ptr && *ptr != '\r' && *ptr != '\n')
			ptr++;

		CString item(start, ptr - start);
		item.TrimLeft();
		item.TrimRight();
		if(!item.IsEmpty())
		{
			HBITMAP hPic = (HBITMAP)LoadImage(NULL, item, IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE);
			if (hPic)
			{
				Pic.Attach(hPic);
				m_ImageList.Add(&Pic, Pal);
				Pic.DeleteObject();
			}
			else
			{
				if (!csErrList.IsEmpty())
					csErrList += "\n\r";

				csErrList += item;
			}
		}
		while(*ptr=='\r' || *ptr=='\n') ptr++;
	}

	if (m_ImageList.GetImageCount() == 0)
		SetDefaultImageList();

	return csErrList;
}

BOOL CFilterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// ћожно зафигачить список с пометками, но пока не будем
	//m_tree.ModifyStyle( TVS_CHECKBOXES, 0 );
	//m_tree.ModifyStyle( 0, TVS_CHECKBOXES );
	
/*
	//[+]metaeditor, добавл€ем иконки в список
	HIMAGELIST TreeImgList = ImageList_Create(16,16,ILC_COLOR,1,1);
	ImageList_ReplaceIcon(TreeImgList, -1, LoadIcon(_Module.m_hInst,MAKEINTRESOURCE(101)));

	::SendMessage(m_tree.m_hWnd, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)TreeImgList);
	//[+]_
*/
	m_edit.SetMargins(2,2);
	CRect rc;
	GetWindowRect(rc);

	//[+]metaeditor - автоширина (ред. kms)
	if (m_width == 1)
		m_width = GetFullAutoWidth();
	//[+]_

	::SendMessage(m_tree.m_hWnd, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)m_ImageList.GetSafeHandle());
//#define TVS_EX_MULTISELECT  0x0002
//	ModifyStyleEx(0, TVS_EX_MULTISELECT);

	if (m_width > 1)
		rc.right = rc.left + m_width;
	if (m_height > 0)
		rc.bottom = rc.top + m_height;
	
	m_tree.GetWindowRect(m_rcTree);
	ScreenToClient(m_rcTree);
	m_edit.GetWindowRect(m_rcEdit);
	ScreenToClient(m_rcEdit);

	if(m_flags & FVF_USE_INIT_STR)
		m_edit.SetWindowText(m_Caption);

	m_lock=false;
	
	//m_flags = FVF_USE_CAPTION;
	//m_flags = FVF_IN_SUBSTR;
	//m_flags=FVF_IN_MOUSEPOS;
	//m_flags=FVF_IN_CARETPOS;
	if(m_flags & FVF_USE_CAPTION)
	{

		ModifyStyle(0, WS_CAPTION|WS_SYSMENU);

//		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER);
//		SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
		SetWindowText(m_Caption);

		//+ kms
		// http://www.1cpp.ru/forum/YaBB.pl?num=1166186697/104#104
		MoveWindow(0, 0, 0, 0, FALSE);

		CMenu* pMenu=GetSystemMenu(FALSE);
		pMenu->DeleteMenu(SC_MAXIMIZE,MF_BYCOMMAND);
		pMenu->DeleteMenu(SC_MINIMIZE,MF_BYCOMMAND);
		pMenu->DeleteMenu(SC_RESTORE ,MF_BYCOMMAND);

	}

	int fontH=0;
	if(m_flags & FVF_IN_MOUSEPOS)
		GetCursorPos(&m_point);
	else if(m_flags & FVF_IN_CARETPOS)
	{
		::GetCaretPos(&m_point);
		HWND hFocus=::GetFocus();
		
		::ClientToScreen(hFocus,&m_point);
		HDC dc=::GetDC(hFocus);
		SIZE sz;
		::GetTextExtentPoint(dc," ",1,&sz);
		fontH=sz.cy;
		
		::ReleaseDC(hFocus,dc);
		m_point.y+=fontH;
	}
	else if(!(m_flags & FVF_IN_CALLERPOS))
	{
		m_point.x=rc.left;
		m_point.y=rc.top;
	}

	int w = rc.Width(), h = rc.Height();
	rc.top = m_point.y;
	rc.left = m_point.x;
	rc.right = rc.left + w;
	rc.bottom = rc.top + h;
	m_up = false;
	int sw = GetSystemMetrics(SM_CXFULLSCREEN);
	int sh = GetSystemMetrics(SM_CYFULLSCREEN);
	if(rc.right > sw)
	{
		int dw = rc.right - sw;
		rc.right -= dw;
		rc.left -= dw;
	}
	if(rc.bottom > sh)
	{
		m_up = true;
		h += fontH;
		rc.bottom -= h;
		rc.top -= h;
	}
	
	MoveWindow(rc);

	CRect rctree;
	m_tree.GetClientRect(rctree);
	m_diff=rc.Height()-rctree.Height();
	if(m_tree.GetStyle() & WS_HSCROLL)
		m_diff-=GetSystemMetrics(SM_CYHSCROLL);


	m_lock = true;
	FillTree();
	m_lock = false;

	m_ParenthWnd = ::GetParent(m_hWnd);
	m_ParentSubClassed = FALSE;
	if ((::GetWindowLongA(m_ParenthWnd,GWL_EXSTYLE) & WS_EX_TOOLWINDOW) != 0){
		ParentOldWndProc = ::SetWindowLongA(m_ParenthWnd,GWL_WNDPROC,(LONG)&ParentNewWndProc);
		m_ParentSubClassed = TRUE;
	}
	return TRUE;
}

void CFilterDlg::OnDestroy() 
{
	if (m_ParentSubClassed == TRUE){
	  ::SetWindowLongA(m_ParenthWnd,GWL_WNDPROC,ParentOldWndProc);
	  ::SetFocus(PrevFocus);
	}
	CDialog::OnDestroy();
}

void CFilterDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize.x=150;
	lpMMI->ptMinTrackSize.y=25;
}

void CFilterDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_tree.m_hWnd)
	{
		CRect rc;
		GetClientRect(rc);
		m_rcEdit.right=m_rcTree.right=rc.right;
		m_rcTree.bottom=rc.bottom;
		m_edit.MoveWindow(m_rcEdit);
		m_tree.MoveWindow(m_rcTree);
		
	}
}

void CFilterDlg::AddString(CString& item)
{
	item.TrimRight();
	item.TrimLeft();
	if(!item.IsEmpty())
	{
		int nDataBegin = item.ReverseFind('|');
		int nItemBegin = item.Find('#');

		CString csItem;
		CString csData;
		int nImgIdx = m_nDefaultImageIdx;

		if (nItemBegin != -1)
		{
			CString csImgIdx = item.Left(nItemBegin);
			int idx = __max(0, atoi(csImgIdx) -1);
			if (idx < m_ImageList.GetImageCount())
				nImgIdx = idx;

		}
		nItemBegin++;

		if (nDataBegin == -1)
			csItem = item.Mid(nItemBegin);
		else
		{
			csItem = item.Mid(nItemBegin, nDataBegin - nItemBegin);
			csData = item.Mid(nDataBegin + 1);
		}


		if (!csItem.IsEmpty())
		{
			if( m_flags & FVF_SORT )
				que.push(SValue(csItem, csData, nImgIdx));
			else
			{
				m_values.Add(csItem);
				m_AdditionalData.Add(csData);
				m_imgidx.Add(nImgIdx);
			}
		}
	}
}

void CFilterDlg::RemoveAll()
{
	m_values.RemoveAll();
	m_AdditionalData.RemoveAll();
	m_imgidx.RemoveAll();
}

void CFilterDlg::FillVals(CString& vals)
{
	while (!que.empty()) que.pop();

	m_values.RemoveAll();
	m_AdditionalData.RemoveAll();
	m_imgidx.RemoveAll();

	LPCTSTR ptr = vals, start;
	while(*ptr)
	{
		start=ptr;
		while(*ptr && *ptr!='\r' && *ptr!='\n') ptr++;

		CString item(start, ptr - start);
		AddString(item);

		while(*ptr=='\r' || *ptr=='\n') ptr++;
	}

	while (!que.empty())
	{
		SValue &pVal = que.top();
		m_values.Add(pVal.m_val);
		m_AdditionalData.Add(pVal.m_data);
		m_imgidx.Add(pVal.m_imgidx);

		que.pop();
	}
}

CString CFilterDlg::FilterValue(CString vals, CString cap, short flags,long x,long y, long w, long h, IDispatch* pCont_1C, LONG kbd_timeout)
{
	CFilterDlg dlg(NULL, pCont_1C);

	dlg.m_Caption=cap;
	dlg.m_flags = flags;
	dlg.m_timeout = kbd_timeout;

	HWND hFocus;
	bool iscombo = false;
	bool islist = false;

	hFocus = GetAnyFocus();
	PrevFocus = hFocus;

	if(flags & FVF_AUTOFILL_FROM_COMBOBOX)
	{
		char clname[15];
		::GetClassNameA(hFocus,(LPSTR)clname,14);
		clname[15] = '\0';
		CString strclname(clname); 
		if (strclname.CompareNoCase("edit")==0)
		{
			hFocus = ::GetParent(hFocus);
			::GetClassNameA(hFocus,(LPSTR)clname,14);
			clname[15] = '\0';
			strclname = CString(clname);
		}

		iscombo = strclname.CompareNoCase("combobox")==0 ? true : false;
		if (!iscombo) islist = strclname.CompareNoCase("listbox")==0 ? true : false;
		
		if (iscombo || islist)
		{
			vals = GetWndText(hFocus, true);
			CRect rcfocus;
			::GetWindowRect(hFocus,rcfocus);
			x = rcfocus.left;
			y = iscombo ? rcfocus.bottom : rcfocus.top;
			flags = flags | FVF_IN_CALLERPOS;
		}
	}

	dlg.FillVals(vals);

	dlg.m_point.x = x;
	dlg.m_point.y = y;
	
	dlg.m_width = w;
	dlg.m_height = h;

	char* c_str; 
	c_str= new char[5+1];

	//if (w>0) dlg.m_width = w;
	//if (h>0) dlg.m_height = h;

	dlg.DoModal();

	if ((!dlg.m_result.IsEmpty()) && (iscombo || islist))
	{
		UINT msgSelectString = iscombo ? CB_SELECTSTRING : LB_SELECTSTRING;
		UINT msgNotifySelChange = iscombo ? CBN_SELCHANGE : LBN_SELCHANGE;
		int retErr = iscombo ? CB_ERR : LB_ERR;
		int ret = ::SendMessageA (hFocus, msgSelectString, -1, (long)(LPCSTR)dlg.m_result);
		::SetFocus(hFocus);
		if (ret == retErr) 
			dlg.m_result = iscombo ? "CB_ERR" : "LB_ERR";
		else
		{		
		//скажем диалогу что в комбобоксе или листбоксе сменилс€ пункт
		::SendMessageA(::GetParent(hFocus),
			WM_COMMAND,
			MAKEWPARAM(::GetDlgCtrlID(hFocus),msgNotifySelChange),
			(long)hFocus);
		}
	}

	//debug("Choice: %s", (LPCSTR)dlg.m_result);

	return dlg.m_result;
}



CString CFilterDlg::FilterValue(CString cap, short flags,long x,long y, long w, long h)
{
	m_Caption = cap;
	m_flags = flags;

	//FillVals(vals);
	//debug("Arrays filled");

	m_point.x = x;
	m_point.y = y;
	
	m_width = w;
	m_height = h;

	DoModal();

	return m_result;
}

void CFilterDlg::RefreshData(CString& filter)
{
	HRESULT hr;
	LPOLESTR Name = L"FilterValue_OnFilterChange";
	DISPID DispID[1];

	hr = m_pCont_1C->GetIDsOfNames(IID_NULL, &Name, 1, LOCALE_USER_DEFAULT, DispID);
	if( hr != S_OK ) return;

	DISPPARAMS dispparams;
	VARIANT varg[10];
	VARIANT varResult;
	//UINT uArgErr;

	#define DISPATCH_zeroArgErr 0x00080000
	#define DISPATCH_zeroExcepInfo 0x00040000
	#define DISPATCH_zeroVarResult 0x00020000

	dispparams.cArgs = 1;
	dispparams.cNamedArgs = 0;
	varg[0].vt = VT_BSTR;
	varg[0].bstrVal = filter.AllocSysString();
	/*
	varg[1].vt = VT_BSTR;
	varg[1].bstrVal = L"Param1";
	*/
	varResult.vt = VT_BSTR;
	varResult.bstrVal = L"";

	dispparams.rgvarg = varg;

	SetCursor( ::LoadCursor(NULL, IDC_WAIT) );
 
	hr = m_pCont_1C->Invoke(DispID[0], IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD | DISPATCH_zeroArgErr | DISPATCH_zeroExcepInfo, 
		&dispparams, 
		&varResult, 
		NULL, 
		NULL); //&uArgErr);

	SysFreeString(varg[0].bstrVal);

	if( hr == S_OK )
	{
		if( varResult.vt == VT_BSTR )
		{
			CString vals(varResult.bstrVal);
			SysFreeString(varResult.bstrVal);
			FillVals(vals);
		}
	}

	SetCursor( ::LoadCursor(NULL, IDC_ARROW) );
	//debug("Data refresh");
}

#define FILTER_FIT 0x01
#define FILTER_FULLFIT 0x02

void FillFilterKeys(CStringArray& keys, CString& filter)
{
	LPCTSTR ptr=filter;
	LPCSTR start;

	while(*ptr)
	{
		start = ptr;
		while(*ptr && *ptr!=' ')
			ptr++;
		keys.Add(CString(start, ptr-start));
		while(*ptr==' ')
			ptr++;
	}
}

short CheckByFilter(CStringArray& keys, CString& str)
{
	int keyCount = keys.GetSize();
	short res = 0;

	for(int j=0; j<keyCount; j++)
	{
		int pos = str.Find(keys[j]);
		if (pos < 0)
		{
			res = 0;
			break;
		}
		else if( pos == 0 ) //точное совпадение
		{
			res |= FILTER_FIT;
			res |= FILTER_FULLFIT;
		}
		else
		{
			res |= FILTER_FIT;
		}
	}

	return res;
}

void CFilterDlg::FillTree()
{
	CString filter;
	m_edit.GetWindowText(filter);
	filter.MakeLower();
	int count = m_values.GetSize();
	m_tree.SendMessage(WM_SETREDRAW,FALSE);
	m_tree.DeleteAllItems();
	m_TreeItems.RemoveAll();

	if(filter.IsEmpty())
	{
		for(int i=0;i<count;i++)
		{
			HTREEITEM hItem = m_tree.InsertItem(m_values[i]);
			m_tree.SetItemData(hItem, i);
			m_tree.SetItemImage(hItem, m_imgidx[i], m_imgidx[i]);
			m_TreeItems.Add(hItem);
		}
	}
	else
	{
		if(m_flags & FVF_IN_SUBSTR)
		{
			CStringArray keys;
			FillFilterKeys(keys, filter);

			int keyCount=keys.GetSize();
			HTREEITEM newSelectionItem = NULL;
			for(int i=0;i<count;i++)
			{
				CString txt = m_values[i];
				txt.MakeLower();

				short filter_res = CheckByFilter(keys, txt);
				bool add = filter_res & FILTER_FIT;
				bool bNewSelection = filter_res & FILTER_FULLFIT;

				if( add ) 
				{
					HTREEITEM newItem = m_tree.InsertItem(m_values[i]);
					m_TreeItems.Add(newItem);
					m_tree.SetItemData(newItem, i);
					m_tree.SetItemImage(newItem, m_imgidx[i], m_imgidx[i]);
					//m_tree.SetCheck(newItem, TRUE);

					if (bNewSelection && !newSelectionItem)
						newSelectionItem = newItem;
				}
			}

			if (newSelectionItem) {
				m_tree.Select(newSelectionItem, TVGN_CARET);
			}
		}
		else
		{
			for(int i=0;i<count;i++)
			{
				CString txt = m_values[i];
				txt.MakeLower();
				if(!txt.Find(filter))
				{
					HTREEITEM hItem = m_tree.InsertItem(m_values[i]);
					m_TreeItems.Add(hItem);
					m_tree.SetItemData(hItem, i);
					m_tree.SetItemImage(hItem, m_imgidx[i], m_imgidx[i]);
				}
			}
		}
	}
	

	HTREEITEM selectedItem = m_tree.GetSelectedItem();
	if (!selectedItem) 
	{
		HTREEITEM item = m_tree.GetNextItem(TVI_ROOT,TVGN_CHILD);
		if (item)
			m_tree.Select(item, TVGN_CARET);
	}

	
	m_tree.SendMessage(WM_SETREDRAW,TRUE);
	ReSize();
}

void CFilterDlg::OnChangeFilter()
{
	if( m_lock ) return;

	m_lock = true;

	if( m_pCont_1C )
	{
		CString filter;
		m_edit.GetWindowText(filter);
		RefreshData(filter);
	}

	FillTree();

	m_lock = false;
}

void CFilterDlg::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == 101 )
	{
		if( m_lock ) return;

		KillTimer(101);
		OnChangeFilter();
	}
	else
	{
		// Call base class handler.
		CDialog::OnTimer(nIDEvent);
	}
}

void CFilterDlg::OnChangeEdit1() 
{
	if( !m_lock )
	{
		if( m_timeout == 0 )
		{
			OnChangeFilter();
		}
		else
		{
			KillTimer(101);
			SetTimer(101, m_timeout, NULL);
		}
	}
}

void CFilterDlg::ReSize()
{
	int count = m_tree.GetCount();
	//if(count > 10) count = 10;

	RECT rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	int MaxH = ((rcWorkArea.bottom - rcWorkArea.top) * 50) / 100; //отдадим 50% высоты
	int ItemH = m_tree.GetItemHeight();
	int h = count * m_tree.GetItemHeight();
	if( h > MaxH )
	{
		h = (MaxH / ItemH) * ItemH;
	}
	h += m_diff + GetSystemMetrics(SM_CXBORDER);

	CRect rc;
	GetWindowRect(rc);


	if (m_flags & FVF_AUTOWIDTH)
	{
		int nWidth = GetTreeAutoWidth();
		int nSX = GetSystemMetrics(SM_CXFULLSCREEN);
		if (rc.left + nWidth > nSX)
		{
			nWidth = nSX - rc.left;
			h += GetSystemMetrics(SM_CYHSCROLL);
		}
		rc.right = rc.left + nWidth;
	}
	else if(m_tree.GetStyle() & WS_HSCROLL)
		h += GetSystemMetrics(SM_CYHSCROLL);

	
	//[+]metaeditor - установим инициированную высоту
	CString filter;
	m_edit.GetWindowText(filter);
	bool needSetH = filter.IsEmpty() & (m_height > 0);
	
	if(m_up){
		rc.top = rc.bottom - h;
		if(needSetH) rc.top -= m_height-rc.Height();
	}
	else {
		rc.bottom = rc.top + h;
		if(needSetH) rc.bottom = rc.top + m_height;
	}


	if( rc.bottom > rcWorkArea.bottom ) rc.bottom = rcWorkArea.bottom;
	MoveWindow(rc);
}

void CFilterDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!m_lock)
	{
		if(GetKeyState(VK_SHIFT) & 0x8000) //[+]metaeditor
		{
			HTREEITEM item = m_tree.GetSelectedItem();
			if( item)
			{
				CString txt = m_tree.GetItemText(item);
				m_lock = true;
				m_edit.SetWindowText(txt);
				m_edit.SetSel(0,-1);
				m_lock=false;
			}
		}
	}
	*pResult = 1;
}


BEGIN_MESSAGE_MAP(CMyEdit,CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP();

void CMyEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	int nLen = LineLength();
	SetSel(nLen, nLen, FALSE);
}


void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar==VK_DOWN || nChar==VK_UP || nChar==VK_PRIOR || nChar==VK_NEXT || nChar==VK_HOME || nChar==VK_END)
	{
		bool Send2List=true;
		if(nChar==VK_HOME || nChar==VK_END)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)  //[*]metaeditor
			{
				nChar == VK_HOME ? SetSel(1,1) : SetSel(LineLength(), LineLength());
				Send2List=false;
			}
			else if(!(GetKeyState(VK_SHIFT) & 0x8000))
			{
				{
					CFilterDlg* dlg=(CFilterDlg*)GetParent();
					HTREEITEM item=dlg->m_tree.GetNextItem(TVI_ROOT,TVGN_CHILD);
					if(nChar==VK_END)
					{
						int cnt=dlg->m_tree.GetCount()-1;
						for(int i=0;i<cnt;i++)
							item=dlg->m_tree.GetNextItem(item,TVGN_NEXT);
					}
					if(item)
						dlg->m_tree.Select(item,TVGN_CARET);
					return;
				}
			}
		}
		else
			
		/*{
			CFilterDlg* dlg=(CFilterDlg*)GetParent();
			HTREEITEM item = dlg->m_tree.GetSelectedItem();
			if( item)
			{
				CString txt = dlg->m_tree.GetItemText(item);
				dlg->m_lock = true;
				dlg->m_edit.SetWindowText(txt);
				dlg->m_edit.SetSel(0,-1);
				dlg->m_lock=false;
			}
		}*/

		if(Send2List)
		{
			CFilterDlg* dlg=(CFilterDlg*)GetParent();
			_AFX_THREAD_STATE* state=AfxGetThreadState();
			dlg->m_tree.SendMessage(WM_KEYDOWN,state->m_lastSentMsg.wParam,
				state->m_lastSentMsg.lParam);
			return;
		}
	}
	/*if(nChar==VK_UP || nChar==VK_DOWN)
	{
		((CFilterDlg*)GetParent())->MoveSel(nChar==VK_UP?-1:1);
		return;
	}
	*/
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

BEGIN_MESSAGE_MAP(CMyTree, CTreeCtrl)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP();

void CMyTree::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	bool goto2Edit = true;
	if(nChar == VK_DOWN || nChar == VK_UP || nChar == VK_HOME || nChar == VK_END)
	{
		HTREEITEM item = GetSelectedItem();
		if(item)
		{
			if (nChar == VK_DOWN && !GetNextItem(item, TVGN_NEXT))
			//last - select first
			{
				item = GetNextItem(TVI_ROOT, TVGN_CHILD);
				Select(item, TVGN_CARET);
				return;
			}
			else if (nChar == VK_UP && !GetNextItem(item, TVGN_PREVIOUS))
			//first - select last
			{
				int cnt = GetCount()-1;
				for (int i=0; i<cnt; i++)
					item = GetNextItem(item, TVGN_NEXT);
				Select(item, TVGN_CARET);
				return;
			}
		}

		goto2Edit = false;
	}
	else if (nChar == VK_PRIOR || nChar == VK_NEXT) {
		goto2Edit = false;
	}

	if (!goto2Edit) {
		CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CMyTree::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//CFilterDlg* dlg = (CFilterDlg*)GetParent();
	////dlg->m_edit.SetFocus();
	//_AFX_THREAD_STATE* state = AfxGetThreadState();
	//dlg->m_edit.SendMessage(WM_KEYDOWN, VkKeyScan(state->m_lastSentMsg.wParam)
	//	, state->m_lastSentMsg.lParam);
}

void CFilterDlg::MoveSel(int pos)
{
	HTREEITEM item=m_tree.GetSelectedItem();
	bool dn=true;
	if(pos<0)
		pos=-pos,dn=false;
	if(item)
	{
		for(int i=0;i<pos && item;i++)
			item=m_tree.GetNextItem(item,dn?TVGN_NEXT:TVGN_PREVIOUS);
	}
	else if(dn)
		item=m_tree.GetNextItem(TVI_ROOT,TVGN_CHILD);
	if(item)
	{
		m_tree.Select(item,TVGN_CARET);
	}
}

void CFilterDlg::OnOK()
{
	HTREEITEM item=m_tree.GetSelectedItem();
	
	if (!item)
	{
		if(m_flags & FVF_ALLOW_USERVAL)
			m_edit.GetWindowText(m_result);
	}
	else
	{
		if( GetKeyState(VK_SHIFT) & 0x8000 )
		{
			//m_result += "\r\n1111\r\n2222";
			int cnt = m_TreeItems.GetSize();
			int i;
			for( i=0; i < cnt; i++ )
			{
				item = m_TreeItems[i];
				if( !m_result.IsEmpty() ) m_result += "\r\n";

				m_result += m_tree.GetItemText(item);
				nSelectedItem = m_tree.GetItemData(item);

				if( m_AdditionalData.GetSize() > 0 && !(m_AdditionalData[nSelectedItem].IsEmpty()) )
				{
					m_result += "|";
					m_result += m_AdditionalData[nSelectedItem];
				}
			}
		}
		else
		{
			m_result = m_tree.GetItemText(item);
			nSelectedItem = m_tree.GetItemData(item);

			if( m_AdditionalData.GetSize() > 0 && !(m_AdditionalData[nSelectedItem].IsEmpty()) )
			{
				m_result += "|";
				m_result += m_AdditionalData[nSelectedItem];
			}
		}

	}
	CDialog::OnOK();
}

void CFilterDlg::OnCancel()
{
	/*
	HTREEITEM item=m_tree.GetSelectedItem();
	if(m_flags & FVF_ALLOW_USERVAL) {
		if (item)
			m_edit.GetWindowText(m_result);
	}
	*/

	CDialog::OnCancel();
}

void CFilterDlg::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMTVCUSTOMDRAW* ncd=(NMTVCUSTOMDRAW*)pNMHDR;
	if(ncd->nmcd.dwDrawStage==CDDS_PREPAINT)
	{
		*pResult=CDRF_NOTIFYITEMDRAW;
		return;
	}
	if(ncd->nmcd.dwDrawStage==CDDS_ITEMPREPAINT)
	{
		if(ncd->nmcd.uItemState & CDIS_SELECTED)
		{
			//::SetBkColor(ncd->nmcd.hdc,0);
			ncd->clrTextBk=0;
			ncd->clrText=0xFFFFFF;
			*pResult=CDRF_NEWFONT;
			return;
		}
	}
	*pResult = 0;
}

void CFilterDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	*pResult = 0;
}

CString CFilterDlg::GetWndText(HWND WH, bool IsListBox)
{
	CString strres = "";
	
	char clname[15];
	::GetClassNameA(WH,(LPSTR)clname,14);
	clname[15] = '\0';
	CString strclname(clname); 
	
	if (IsListBox)
	{
		bool iscombo = strclname.CompareNoCase("combobox")==0 ? true : false;
		bool islist = strclname.CompareNoCase("listbox")==0 ? true : false;
		if (iscombo || islist)
		{
			UINT msgGetCount = iscombo ? CB_GETCOUNT : LB_GETCOUNT;
			UINT msgGetItemText = iscombo ? CB_GETLBTEXT : LB_GETTEXT;
			UINT msgGetItemTextLen = iscombo ? CB_GETLBTEXTLEN : LB_GETTEXTLEN;
			
			int ItemsCount = ::SendMessageA(WH, msgGetCount, 0, 0);
			if (ItemsCount)
			{
				for(int i=0;i<ItemsCount;i++)
				{
					int textlen = ::SendMessageA(WH, msgGetItemTextLen, i, 0);
					if (textlen)
					{
						char* strItem = new char[textlen+1];
						if (strItem)
						{
							::SendMessageA(WH, msgGetItemText, i, (long)strItem);
							strres += CString(strItem) + "\r\n";
						}
						delete strItem;
					}
				}
			}
		}
	} 
	else
	{
		int cnt	= ::SendMessageA(WH,WM_GETTEXTLENGTH,0,0);
		char* strItem = new char[cnt+1];
		if (strItem)
		{
			::SendMessageA(WH, WM_GETTEXT, cnt+1, (long)strItem);
			strres = strItem;
		}
		delete strItem;
	}
	return strres;
}

HWND CFilterDlg::GetAnyFocus()
{
	HWND h=0;
	DWORD currthid =::GetCurrentThreadId();
	DWORD destthid =::GetWindowThreadProcessId(::GetForegroundWindow(),NULL);
	BOOL attached=0;
	if (currthid != destthid) 
			attached= ::AttachThreadInput(currthid,destthid,true);
	h = ::GetFocus();
	if (attached)
		::AttachThreadInput(currthid,destthid,false);
	return h;
}