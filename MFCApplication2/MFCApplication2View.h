
// MFCApplication2View.h : interface of the CMFCApplication2View class
//

#pragma once

#include "resource.h"

#include "afxwin.h"

#include "LayoutPanel.h"
#include "LayoutPanelHorizontal.h"
#include "LayoutPanelVertical.h"
using namespace RthLayout;

class CMFCApplication2View : public CFormView
{
protected: // create from serialization only
	CMFCApplication2View();
	DECLARE_DYNCREATE(CMFCApplication2View)

public:
	enum{ IDD = IDD_MFCAPPLICATION2_FORM };

// Attributes
public:
	CMFCApplication2Doc* GetDocument() const;

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
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	void testHorizontalLayout1(LayoutPanelHorizontal* panel);
	void testHorizontalLayout2(LayoutPanelHorizontal* panel);

	void testVerticalLayout1(LayoutPanelVertical* panel);
	void testVerticalLayout2(LayoutPanelVertical* panel);
	void testVerticalLayout3(LayoutPanelVertical* panel);
	void testVerticalLayout4(LayoutPanelVertical* panel);

private:
	bool m_bReady;
	LayoutPanel* m_MainPanel;

public:
	CStatic m_Control1;
	CStatic m_Control2;
	CStatic m_Control3;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in MFCApplication2View.cpp
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

