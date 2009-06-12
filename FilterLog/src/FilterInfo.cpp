// FilterInfo.cpp : implementation file
//

#include "stdafx.h"
#include "FilterLog.h"
#include "FilterInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterInfo dialog


CFilterInfo::CFilterInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterInfo)
	m_Chipset = _T("");
	m_Author = _T("");
	m_Comments = _T("");
	m_DateModified = _T("");
	m_FilterName = _T("");
	m_PhoneModel = _T("");
	m_SWVersion = _T("");
	m_QCATFilters = _T("");
	//}}AFX_DATA_INIT
}


void CFilterInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterInfo)
	DDX_Text(pDX, IDC_CHIPSET, m_Chipset);
	DDX_Text(pDX, IDC_AUTHOR, m_Author);
	DDX_Text(pDX, IDC_COMMENTS, m_Comments);
	DDX_Text(pDX, IDC_DATE_MODIFIED, m_DateModified);
	DDX_Text(pDX, IDC_FILTER_NAME, m_FilterName);
	DDX_Text(pDX, IDC_PHONE_MODEL, m_PhoneModel);
	DDX_Text(pDX, IDC_SW_VERSION, m_SWVersion);
	DDX_Text(pDX, IDC_QCAT_FILTERS, m_QCATFilters);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterInfo, CDialog)
	//{{AFX_MSG_MAP(CFilterInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterInfo message handlers

BOOL CFilterInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(false); //Make sure that the dialog box displayes the correct settings when it diplays
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilterInfo::OnOK() 
{
	UpdateData(true); //Make sure the user chosen settings are written to the dialog box variables associated with the controls
	
	CDialog::OnOK();
}
