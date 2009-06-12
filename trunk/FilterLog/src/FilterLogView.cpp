// FilterLogView.cpp : implementation of the CFilterLogView class
//

#include "stdafx.h"
#include "FilterLog.h"

#include "FilterLogDoc.h"
#include "FilterLogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView

IMPLEMENT_DYNCREATE(CFilterLogView, CListView)

BEGIN_MESSAGE_MAP(CFilterLogView, CListView)
	//{{AFX_MSG_MAP(CFilterLogView)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_COMMAND(ID_EDIT_CHECKALL, OnEditCheckall)
	ON_COMMAND(ID_EDIT_UNCHECKALL, OnEditUncheckall)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView construction/destruction

CFilterLogView::CFilterLogView()
{
	// TODO: add construction code here

}

CFilterLogView::~CFilterLogView()
{
}

BOOL CFilterLogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView drawing

void CFilterLogView::OnDraw(CDC* pDC)
{
	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFilterLogView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl &CtrlLView = GetListCtrl();

	for (int count = NoStringArrayElements - 1; count >= 0; count--)
	{
		CtrlLView.DeleteColumn(count);
	}

	CtrlLView.InsertColumn(0, "String", LVCFMT_LEFT, 400);
	CtrlLView.InsertColumn(1, "Colour", LVCFMT_LEFT, 100);
	CtrlLView.InsertColumn(2, "Comment", LVCFMT_LEFT, 250);
	CtrlLView.InsertColumn(3, "Replace", LVCFMT_LEFT, 100); 
	CtrlLView.InsertColumn(4, "With", LVCFMT_LEFT, 80); 

	CtrlLView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	ModifyStyle(NULL, LVS_REPORT, 0);

	UpdateView();
}

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView printing

BOOL CFilterLogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFilterLogView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFilterLogView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView diagnostics

#ifdef _DEBUG
void CFilterLogView::AssertValid() const
{
	CListView::AssertValid();
}

void CFilterLogView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFilterLogDoc* CFilterLogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilterLogDoc)));
	return (CFilterLogDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView message handlers

CEdit* CFilterLogView::EditSubLabel(int nItem, int nCol)
{
	// The returned pointer should not be saved

	CListCtrl &CtrlLView = GetListCtrl();

	// Make sure that the item is visible
	if( !CtrlLView.EnsureVisible( nItem, TRUE ) ) return NULL;

	// Make sure that nCol is valid
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if( nCol >= nColumnCount || CtrlLView.GetColumnWidth(nCol) < 5 )
		return NULL;

	// Get the column offset
	int offset = 0;
	for( int i = 0; i < nCol; i++ )
		offset += CtrlLView.GetColumnWidth( i );

	CRect rect;
	CtrlLView.GetItemRect( nItem, &rect, LVIR_BOUNDS );

	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect( &rcClient );
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		CtrlLView.Scroll( size );
		rect.left -= size.cx;
	}

	// Get Column alignment
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;
	CtrlLView.GetColumn( nCol, &lvcol );
	DWORD dwStyle ;
	if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
	else if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
	else dwStyle = ES_CENTER;

	rect.left += offset+4;
	rect.right = rect.left + CtrlLView.GetColumnWidth( nCol ) - 3 ;
	if( rect.right > rcClient.right) rect.right = rcClient.right;

	dwStyle |= WS_BORDER|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL;
	CEdit *pEdit = new CInPlaceEdit(nItem, nCol, CtrlLView.GetItemText( nItem, nCol ));
	pEdit->Create( dwStyle, rect, this, IDC_IPEDIT );


	return pEdit;
}

/////////////////////////////////////////////////////////////////////////////
// CFilterLogView message handlers

// HitTestEx	- Determine the row index and column index for a point
// Returns	- the row index or -1 if point is not over a row
// point	- point to be tested.
// col		- to hold the column index
int CFilterLogView::HitTestEx(CPoint &point, int *col) const
{
	CListCtrl &CtrlLView = GetListCtrl();

	int colnum = 0;
	int row = CtrlLView.HitTest( point, NULL );

	if( col ) *col = 0;

	// Make sure that the ListView is in LVS_REPORT
	if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
		return row;

	// Get the top and bottom row visible
	row = CtrlLView.GetTopIndex();
	int bottom = row + CtrlLView.GetCountPerPage();
	if( bottom > CtrlLView.GetItemCount() )
		bottom = CtrlLView.GetItemCount();

	// Get the number of columns
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();

	// Loop through the visible rows
	for( ;row <=bottom;row++)
	{
		// Get bounding rect of item and check whether point falls in it.
		CRect rect;
		CtrlLView.GetItemRect( row, &rect, LVIR_BOUNDS );
		if( rect.PtInRect(point) )
		{
			// Now find the column
			for( colnum = 0; colnum < nColumnCount; colnum++ )
			{
				int colwidth = CtrlLView.GetColumnWidth(colnum);
				if( point.x >= rect.left
					&& point.x <= (rect.left + colwidth ) )
				{
					if( col ) *col = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

void CFilterLogView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl &CtrlLView = GetListCtrl();

	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM	*plvItem = &pDispInfo->item;

	if (plvItem->pszText != NULL)
	{
		if (CtrlLView.GetItemCount() == plvItem->iItem + 1) // if the user is editing the empty item..
		{
			if (plvItem->pszText != (CString)"..." && plvItem->pszText != (CString)"") //if the user has actually entered text...
			{
				//add a new item to the data structure
				CStringArray *Row = new CStringArray;
				Row->SetSize(NoStringArrayElements,1);
				pDoc->FilterData.Add(Row);
				// set the item text with the user-entered text
				CStringArray *Temp = reinterpret_cast<CStringArray *>(pDoc->FilterData[(int)plvItem->iItem]);
				Temp->SetAt((UINT)plvItem->iSubItem + 1,(CString)plvItem->pszText);
				pDoc->FilterData.SetAt((UINT)plvItem->iItem,Temp);
				//add an new empty item to the view as well
				int Lastindex = CtrlLView.GetItemCount();
				CtrlLView.SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
				CtrlLView.InsertItem(Lastindex, "...");
				CtrlLView.SetCheck(plvItem->iItem, true); //set the new line as checked
				pDoc->SetModifiedFlag(); //tell the document that the user has changed someting 
			}
		}
		else // if the user is editing an item with is not the last one..
		{
			//change the text in the view
			CtrlLView.SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
			//change the text in the data structure
			CStringArray *Temp = reinterpret_cast<CStringArray *>(pDoc->FilterData[(int)plvItem->iItem]);
			Temp->SetAt((UINT)plvItem->iSubItem + 1,(CString)plvItem->pszText);
			pDoc->FilterData.SetAt((UINT)plvItem->iItem,Temp);
			pDoc->SetModifiedFlag(); //tell the document that the user has changed someting 
		}
	}	
	
	*pResult = 0;
}

void CFilterLogView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( GetFocus() != this ) SetFocus();	
	CListView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CFilterLogView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( GetFocus() != this ) SetFocus();	
	CListView::OnHScroll(nSBCode, nPos, pScrollBar);
}

// This function is based on the article "Deleting a Multiple Selection of Rows in a 
// Listview Control". 
void CFilterLogView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl &CtrlLView = GetListCtrl();

	if (nChar == 46)  // 46 corresponds to the delete key
	{
		int NoItems = CtrlLView.GetItemCount();

		CListCtrl &CtrlLView = GetListCtrl();

		int nSelRows = CtrlLView.GetSelectedCount();

		int* pnArrayOfSelRows = new int[nSelRows];
		
		int nTemp = nSelRows;
		
		POSITION pos = CtrlLView.GetFirstSelectedItemPosition();
		int i = CtrlLView.GetNextSelectedItem(pos);
		
		while (i != -1)
		{
			nTemp = nTemp-1;
			pnArrayOfSelRows[nTemp] = i;
			i = CtrlLView.GetNextSelectedItem(pos);
		}
		
		
		for(int j=0; j < nSelRows; j++)
		{
			if (pnArrayOfSelRows[j] < NoItems - 1)
			{
				CtrlLView.DeleteItem(pnArrayOfSelRows[j]);
				pDoc->FilterData.RemoveAt(pnArrayOfSelRows[j]);
			}
		}
	
		delete(pnArrayOfSelRows);
		pnArrayOfSelRows = NULL;
	}
		
	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFilterLogView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CListCtrl &CtrlLView = GetListCtrl();
	
	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int index=0;

	int colnum=0;

	if(( index = HitTestEx( point, &colnum )) != -1 )
	{
		if ((index < CtrlLView.GetItemCount() - 1) || colnum == 0)
		{
			if (colnum == 1) // If the user is editing the second column, use a combobox editing
			{
				CStringList lstItems;
				CString key, value;
				POSITION pos = pDoc->m_ColorMap.GetStartPosition();
				while (pos != NULL)
				{
					pDoc->m_ColorMap.GetNextAssoc(pos, key, value);
					lstItems.AddTail(key);
				}
				ShowInPlaceList( index, colnum, lstItems, 0 );
			}
			else
				EditSubLabel( index, colnum );
		}
	}
	else
		CtrlLView.SetItemState(index,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	
	CListView::OnLButtonDblClk(nFlags, point);
}

// ShowInPlaceList		- Creates an in-place drop down list for any 
//				- cell in the list view control
// Returns			- A temporary pointer to the combo-box control
// nItem			- The row index of the cell
// nCol				- The column index of the cell
// lstItems			- A list of strings to populate the control with
// nSel				- Index of the initial selection in the drop down list
CComboBox* CFilterLogView::ShowInPlaceList(int nItem, int nCol, CStringList &lstItems, int nSel)
{
	// The returned pointer should not be saved

	CListCtrl &CtrlLView = GetListCtrl();

	// Make sure that the item is visible
	if( !CtrlLView.EnsureVisible( nItem, TRUE ) ) return NULL;

	// Make sure that nCol is valid 
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if( nCol >= nColumnCount || CtrlLView.GetColumnWidth(nCol) < 10 )
		return NULL;

	// Get the column offset
	int offset = 0;
	for( int i = 0; i < nCol; i++ )
		offset += CtrlLView.GetColumnWidth( i );

	CRect rect;
	CtrlLView.GetItemRect( nItem, &rect, LVIR_BOUNDS );

	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect( &rcClient );
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		CtrlLView.Scroll( size );
		rect.left -= size.cx;
	}

	rect.left += offset+4;
	rect.right = rect.left + CtrlLView.GetColumnWidth( nCol ) - 3 ;
	int height = rect.bottom-rect.top;
	rect.bottom += 5*height;
	if( rect.right > rcClient.right) rect.right = rcClient.right;

	DWORD dwStyle = WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL
					|CBS_DROPDOWNLIST|CBS_DISABLENOSCROLL;
	CComboBox *pList = new CInPlaceList(nItem, nCol, &lstItems, nSel);
	pList->Create( dwStyle, rect, this, IDC_IPEDIT );
	pList->SetItemHeight( -1, height);
	pList->SetHorizontalExtent( CtrlLView.GetColumnWidth( nCol ));

	return pList;
}

void CFilterLogView::UpdateView()
{
	CListCtrl &CtrlLView = GetListCtrl();

	CtrlLView.DeleteAllItems();

	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_Updating = true;

	CtrlLView.InsertItem(0, "...");
	int NoItems = pDoc->FilterData.GetSize();
	for (int i = 0; i < NoItems; i++)
	{
		CStringArray *Temp = reinterpret_cast<CStringArray *>(pDoc->FilterData[i]);
		int nItem;
		nItem = CtrlLView.InsertItem(i, Temp->GetAt(1));
		CtrlLView.SetItemText(nItem, 1, Temp->GetAt(2));
		CtrlLView.SetItemText(nItem, 2, Temp->GetAt(3));
		CtrlLView.SetItemText(nItem, 3, Temp->GetAt(4));
		CtrlLView.SetItemText(nItem, 4, Temp->GetAt(5));
		if (Temp->GetAt(0) == "ON")
			CtrlLView.SetCheck(nItem,true);
	}

	pDoc->m_Updating = false;
}

void CFilterLogView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	*pResult = 0;

	CListCtrl &CtrlLView = GetListCtrl();

	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_Updating)
		return;

	for (int i = 0; i < CtrlLView.GetItemCount() - 1; i++)
	{
		CStringArray *Temp = reinterpret_cast<CStringArray *>(pDoc->FilterData[i]);
		if (CtrlLView.GetCheck(i))
		{	
			if (Temp->GetAt(0) == "OFF")
				pDoc->SetModifiedFlag();
			Temp->SetAt(0 , "ON");
		}
		else
		{
			if (Temp->GetAt(0) == "ON")
				pDoc->SetModifiedFlag();
			Temp->SetAt(0 , "OFF");
		}
		pDoc->FilterData.SetAt(i,Temp);
	}
	CtrlLView.SetCheck(CtrlLView.GetItemCount() - 1, false);
}

void CFilterLogView::OnEditCheckall() 
{
	CListCtrl &CtrlLView = GetListCtrl();

	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString str;
	for (int i = 0; i < CtrlLView.GetItemCount() - 1; i++)
	{
		CtrlLView.SetCheck(i, true);
		CStringArray *Temp = reinterpret_cast<CStringArray *>(pDoc->FilterData[i]);
		Temp->SetAt(0 , "ON");
		pDoc->FilterData.SetAt(i,Temp);
	}
}

void CFilterLogView::OnEditUncheckall() 
{
	CListCtrl &CtrlLView = GetListCtrl();

	CFilterLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString str;
	for (int i = 0; i < CtrlLView.GetItemCount() - 1; i++)
	{
		CtrlLView.SetCheck(i, false);
		CStringArray *Temp = reinterpret_cast<CStringArray *>(pDoc->FilterData[i]);
		Temp->SetAt(0 , "OFF");
		pDoc->FilterData.SetAt(i,Temp);
	}
}
