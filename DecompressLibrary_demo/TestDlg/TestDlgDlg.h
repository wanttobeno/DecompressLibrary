// TestDlgDlg.h : header file
//

#if !defined(AFX_TESTDLGDLG_H__AAC3981C_944B_4C79_B726_75BF045E4097__INCLUDED_)
#define AFX_TESTDLGDLG_H__AAC3981C_944B_4C79_B726_75BF045E4097__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DecompressLibrary/DecompressClass.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

class CTestDlgDlg : public CDialog
{
// Construction
public:
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlgDlg)
	enum { IDD = IDD_TESTDLG_DIALOG };
	CString	m_szArchiveName;
	CString	m_szArchiveType;
	BOOL	m_fIsFile;
	CString	m_szFileName;
	int	m_nFilePosition;
	int	m_nFilesCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpenArchiveBtn();
	afx_msg void OnButtonReadFileBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// decompress object
	CDecompressClass	m_Decompress;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLGDLG_H__AAC3981C_944B_4C79_B726_75BF045E4097__INCLUDED_)
