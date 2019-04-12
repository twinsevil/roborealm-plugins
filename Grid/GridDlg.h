#if !defined(AFX_GRIDDLG_H__04140C98_2B0C_42C9_8AEE_1A79A6AAFFF4__INCLUDED_)
#define AFX_GRIDDLG_H__04140C98_2B0C_42C9_8AEE_1A79A6AAFFF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SwapColorDlg.h : header file
//

#include "afxwin.h"
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// SwapColorDlg dialog


class GridDlg : public ModuleDlg
{
  CFont font;

// Construction
public:
	GridDlg(CWnd* pParent = NULL);   // standard constructor
	static int GetId();
	char *GetDisplay();
	char *GetName();
	int Process(unsigned char *data, short int *tmp, unsigned char *tmp2, int left, int top, int width, int height);
	void Annotate(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height);
  int GetIDD();
  bool Initialize();
  void Destroy();
  void SaveValues();
  void LoadValues();


  bool ColorChoise(int color, unsigned char* RGB);

// Dialog Data
	//{{AFX_DATA(SwapColorDlg)
	enum { IDD = IDD_GRID };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SwapColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SwapColorDlg)
	afx_msg void OnHelp();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
	CButton m_Check1;
	CButton m_Check2;
	CComboBox m_ComboBoxColor;
	CComboBox m_ComboBoxThikness;

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();

	bool m_bChk1; // переменная флага Check1
	bool m_bChk2; // переменная флага Check2

	int color;    // индекс выбранной строки в ComboBoxColor
	int thikness; // индекс выбранной строки в ComboBoxThikness
	
	// объекты группы горизонтальных линиий
	CSpinButtonCtrl m_Spin1;
	CEdit m_EditCount1;
	CSpinButtonCtrl m_Spin2;
	CEdit m_EditStep1;
	CSpinButtonCtrl m_Spin3;
	CEdit m_EditX1;
	CSpinButtonCtrl m_Spin5;
	CEdit m_EditX2;
	CSpinButtonCtrl m_Spin4;
	CEdit m_EditY1;
	CSpinButtonCtrl m_Spin6;
	CEdit m_EditY2;

	// объекты группы вертикальных линиий
	CSpinButtonCtrl m_Spin7;
	CEdit m_EditCount2;
	CSpinButtonCtrl m_Spin8;
	CEdit m_EditStep2;
	CSpinButtonCtrl m_Spin9;
	CEdit m_EditX3;
	CSpinButtonCtrl m_Spin11;
	CEdit m_EditX4;
	CSpinButtonCtrl m_Spin10;
	CEdit m_EditY3;
	CSpinButtonCtrl m_Spin12;
	CEdit m_EditY4;

	// переменные горизонтальных линий
	CString strX1;
	CString strX2;
	CString strY1;
	CString strY2;
	CString strCount1;
	CString strStep1;

	// переменные вертикальных линий
	CString strX3;
	CString strX4;
	CString strY3;
	CString strY4;
	CString strCount2;
	CString strStep2;
	
	afx_msg void OnEnChangeY1();
	afx_msg void OnEnChangeC1();
	afx_msg void OnEnChangeS1();
	afx_msg void OnEnChangeX1();
	afx_msg void OnEnChangeX2();
	afx_msg void OnEnChangeC2();
	afx_msg void OnEnChangeS2();
	afx_msg void OnEnChangeX3();
	afx_msg void OnEnChangeY3();
	afx_msg void OnEnChangeX4();
	afx_msg void OnEnChangeY4();
	afx_msg void OnCbnSelendokColor();
	afx_msg void OnCbnSelendokThikness();
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWAPCOLORDLG_H__04140C98_2B0C_42C9_8AEE_1A79A6AAFFF4__INCLUDED_)
