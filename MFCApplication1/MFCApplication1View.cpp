
// MFCApplication1View.cpp : implementation of the CMFCApplication1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#include "LayoutControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCApplication1View construction/destruction

CMFCApplication1View::CMFCApplication1View()
	: CFormView(CMFCApplication1View::IDD)
{
	// TODO: add construction code here

	m_bReady = FALSE;
	m_MainPanel = new LayoutPanelForm();
}

CMFCApplication1View::~CMFCApplication1View()
{
	delete m_MainPanel;
}

void CMFCApplication1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL1, m_Label1);
	DDX_Control(pDX, IDC_LABEL2, m_Label2);
	DDX_Control(pDX, IDC_LABEL3, m_Label3);
	DDX_Control(pDX, IDC_LABEL4, m_Label4);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_CHECK1, m_CheckBox1);

	m_bReady = TRUE;
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


// CMFCApplication1View diagnostics

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View message handlers

int CMFCApplication1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_MainPanel->m_nTopMargin = 6;
	m_MainPanel->m_nBottomMargin = 6;
	m_MainPanel->m_nLeftMargin = 6;
	m_MainPanel->m_nRightMargin = 6;
	m_MainPanel->m_nSpacing = 4;

	LayoutControl* label1 = new LayoutControl();
	label1->attachWnd(&m_Label1);
	label1->setMinSize(73, 21);

	LayoutControl* item1 = new LayoutControl();
	item1->attachWnd(&m_Edit1);
	item1->setMinSize(73, 21);

	LayoutControl* label2 = new LayoutControl();
	label2->attachWnd(&m_Label2);
	label2->setMinSize(73, 21);

	LayoutControl* item2 = new LayoutControl();
	item2->attachWnd(&m_Combo1);
	item2->setMinSize(73, 21);

	LayoutControl* label3 = new LayoutControl();
	label3->attachWnd(&m_Label3);
	label3->setMinSize(73, 21);

	LayoutControl* item3 = new LayoutControl();
	item3->attachWnd(&m_Edit2);
	item3->setMinSize(73, 21);
	item3->setVerticalPolicy(LayoutItem::EXPANDING);

	LayoutControl* label4 = new LayoutControl();
	label4->attachWnd(&m_Label4);
	label4->setMinSize(73, 21);

	LayoutControl* item4 = new LayoutControl();
	item4->attachWnd(&m_CheckBox1);
	item4->setMinSize(73, 21);

	m_MainPanel->addLine(label1, item1);
	m_MainPanel->addLine(label2, item2);
	m_MainPanel->addLine(label3, item3);
	m_MainPanel->addLine(label4, item4);

	return 0;
}

void CMFCApplication1View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (m_MainPanel)
	{
		m_MainPanel->setPosition(0, 0);
		m_MainPanel->resize(cx, cy);
		if (m_bReady)
			m_MainPanel->layout();
	}
}
