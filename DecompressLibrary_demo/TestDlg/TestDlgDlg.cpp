// TestDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"

const char*	g_szArchiveType[]={
	"UNKNOWN_ARCHIVE",
		"ZIP_ARCHIVE",
		"GZIP_ARCHIVE",
		"TAR_GZIP_ARCHIVE"
};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlgDlg)
	m_szArchiveName = _T("");
	m_szArchiveType = _T("");
	m_fIsFile = FALSE;
	m_szFileName = _T("");
	m_nFilePosition = 0;
	m_nFilesCount = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlgDlg)
	DDX_Text(pDX, IDC_ARCHIVE_NAME, m_szArchiveName);
	DDX_Text(pDX, IDC_ARCHIVE_TYPE, m_szArchiveType);
	DDX_Check(pDX, IDC_CHECK_IS_FILE, m_fIsFile);
	DDX_Text(pDX, IDC_FILE_NAME, m_szFileName);
	DDX_Text(pDX, IDC_FILE_POSITION, m_nFilePosition);
	DDX_Text(pDX, IDC_FILES_COUNT, m_nFilesCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ARCHIVE_BTN, OnButtonOpenArchiveBtn)
	ON_BN_CLICKED(IDC_BUTTON_READ_FILE_BTN, OnButtonReadFileBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg message handlers

BOOL CTestDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlgDlg::OnButtonOpenArchiveBtn() 
{
	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg (TRUE, NULL, NULL, OFN_FILEMUSTEXIST, NULL, this);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if( fileDlg.DoModal ()==IDOK )
	{
		// close the current archive if any
		m_Decompress.CloseArchive();

		m_szArchiveName = fileDlg.GetPathName();

		// now open it
		if (!m_Decompress.OpenArchive(m_szArchiveName))
		{
			AfxMessageBox(m_Decompress.GetErrorText());
			m_szArchiveName = "";
			UpdateData(FALSE);
			return;
		}

		// we opened, display type of archive
		m_szArchiveType = g_szArchiveType[m_Decompress.m_nArchiveType];

		// get also the count
		m_nFilesCount = m_Decompress.GetCompressedFilesCount();

		// clear the current list
		GetDlgItem(IDC_FILE_TEXT)->SetWindowText("");
		m_fIsFile = FALSE;
		m_szFileName = "";

		UpdateData(FALSE);
	}
}

void CTestDlgDlg::OnButtonReadFileBtn() 
{
	UpdateData();
	char* pBuffer;
	int nLen;
	if (!m_Decompress.GetArchiveFile(m_nFilePosition, 
									&pBuffer, 
									nLen,
									m_fIsFile,
									m_szFileName))
	{
		AfxMessageBox(m_Decompress.GetErrorText());
		return;
	}

	// now populate the rich edit
	GetDlgItem(IDC_FILE_TEXT)->SetWindowText(pBuffer);
	
	UpdateData(FALSE);
}
