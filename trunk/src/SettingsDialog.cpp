// SettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "AnaLog.h"
#include "SettingsDialog.h"
#include "FolderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog dialog


CSettingsDialog::CSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDialog)
	m_Show_Confirmation_Msg = FALSE;
	m_QCAT_Version = -1;
	m_HTML_frames = -1;
	//}}AFX_DATA_INIT
}


void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDialog)
	DDX_Control(pDX, IDC_FRAME_SPLIT, m_FrameSplit);
	DDX_Check(pDX, IDC_SHOW_CONFIRM_MSG, m_Show_Confirmation_Msg);
	DDX_Radio(pDX, IDC_QCAT4, m_QCAT_Version);
	DDX_Radio(pDX, IDC_HTML_Vert, m_HTML_frames);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDialog, CDialog)
	//{{AFX_MSG_MAP(CSettingsDialog)
	ON_BN_CLICKED(IDC_HTML_Vert, OnRadioVframes)
	ON_BN_CLICKED(IDC_HTML_Horz, OnRadioHframes)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_FRAME_SPLIT, OnReleasedcaptureFrameSplit)
	ON_BN_CLICKED(IDC_QCAT4, OnQcat4)
	ON_BN_CLICKED(IDC_QCAT5, OnQcat5)
	ON_BN_CLICKED(IDC_QCAT6, OnQcat6)
	ON_BN_CLICKED(IDC_QCAT7, OnQcat7)
	ON_BN_CLICKED(IDC_APEX5, OnApex5)
	ON_BN_CLICKED(IDC_APEX6, OnApex6)
	ON_BN_CLICKED(IDC_APEX7, OnApex7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog message handlers

BOOL CSettingsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_FrameSplit.SetRange(1, 100, false); //Set range of frame slit slider
	m_FrameSplit.SetTicFreq(10);
	m_FrameSplit.SetPos(m_FrameSplitPosition); //Set the initial position to the user current selection

	UpdateData(false); //Make sure that the dialog box displayes the correct settings when it diplays

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDialog::OnOK() 
{
	UpdateData(true); //Make sure the user chosen settings are written to the dialog box variables associated with the controls
	
	CDialog::OnOK();
}

void CSettingsDialog::OnRadioVframes() 
{
	m_PrefferedHTML	= "Vertical"; //Set the log tipe to vertical when the user ckicks the corresponding radio button
}

void CSettingsDialog::OnRadioHframes() 
{
	m_PrefferedHTML	= "Horizontal"; //Set the log tipe to horizontal when the user ckicks the corresponding radio button
}

//This function is called every time the user clicks the frame split slider
void CSettingsDialog::OnReleasedcaptureFrameSplit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_FrameSplitPosition != m_FrameSplit.GetPos())
	{
		m_FrameSplitPosition = m_FrameSplit.GetPos();

		//Writes the "IndexHorizontal.html" so to slit the frames according to the user selection
		ofstream OutHorizHTMLFile(m_ExecutablePath + "IndexHorizontal.html");
		OutHorizHTMLFile << "<html>\n<frameset rows=\"";
		OutHorizHTMLFile << m_FrameSplitPosition << "%,";
		OutHorizHTMLFile << 100 - m_FrameSplitPosition << "%\">\n";
		OutHorizHTMLFile << "<frame src=\"LeftFrame.html\">\n<frame src=\"RightFrame.html\" name=\"showframe\">\n";
		OutHorizHTMLFile << "</frameset>\n</html>";

		//Writes the "IndexVertical.html" so to slit the frames according to the user selection
		ofstream OutVerticalHTMLFile(m_ExecutablePath + "IndexVertical.html");
		OutVerticalHTMLFile << "<html>\n<frameset cols=\"";
		OutVerticalHTMLFile << m_FrameSplitPosition << "%,";
		OutVerticalHTMLFile << 100 - m_FrameSplitPosition << "%\">\n";
		OutVerticalHTMLFile << "<frame src=\"LeftFrame.html\">\n<frame src=\"RightFrame.html\" name=\"showframe\">\n";
		OutVerticalHTMLFile << "</frameset>\n</html>";
	}
	m_FrameSplitPosition = m_FrameSplit.GetPos();

	*pResult = 0;
}

void CSettingsDialog::OnQcat4() 
{
	m_QCATVersion = "QCAT4";
}

void CSettingsDialog::OnQcat5() 
{
	m_QCATVersion = "QCAT5";
}

void CSettingsDialog::OnQcat6() 
{
	m_QCATVersion = "QCAT6";
}

void CSettingsDialog::OnQcat7() 
{
	m_QCATVersion = "QCAT7";
}

void CSettingsDialog::OnApex5() 
{
	m_QCATVersion = "APEX5";
}

void CSettingsDialog::OnApex6() 
{
	m_QCATVersion = "APEX6";
}

void CSettingsDialog::OnApex7() 
{
	m_QCATVersion = "APEX7";
}
