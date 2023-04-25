
// MFCApplication1View.h : interface of the CMFCApplication1View class
//

#pragma once

#include "resource.h"
#include "afxwin.h"

#include "LayoutPanelForm.h"
using namespace RthLayout;

class CMFCApplication1View : public CFormView
{
protected: // create from serialization only
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

public:
	enum{ IDD = IDD_MFCAPPLICATION1_FORM };

// Attributes
public:
	CMFCApplication1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	CStatic m_Label1;
	CStatic m_Label2;
	CStatic m_Label3;
	CStatic m_Label4;
	CEdit m_Edit1;
	CComboBox m_Combo1;
	CEdit m_Edit2;
	CButton m_CheckBox1;

private:
	BOOL m_bReady;
	LayoutPanelForm* m_MainPanel;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};

#ifndef _DEBUG  // debug version in MFCApplication1View.cpp
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

