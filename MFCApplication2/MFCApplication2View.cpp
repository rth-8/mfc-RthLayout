
// MFCApplication2View.cpp : implementation of the CMFCApplication2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#include "LayoutControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCApplication2View construction/destruction

CMFCApplication2View::CMFCApplication2View()
	: CFormView(CMFCApplication2View::IDD)
{
	// TODO: add construction code here
	m_bReady = false;
}

CMFCApplication2View::~CMFCApplication2View()
{
}

void CMFCApplication2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Control1);
	DDX_Control(pDX, IDC_STATIC2, m_Control2);
	DDX_Control(pDX, IDC_STATIC3, m_Control3);

	m_bReady = true;
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMFCApplication2View diagnostics

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View message handlers

void CMFCApplication2View::testHorizontalLayout1(LayoutPanelHorizontal* panel)
{
	LayoutControl* ctrl1 = new LayoutControl();
	ctrl1->attachWnd(&m_Control1);
	ctrl1->setMinSize(50, 20);

	LayoutControl* ctrl2 = new LayoutControl();
	ctrl2->attachWnd(&m_Control2);
	ctrl2->setMinSize(50, 20);

	LayoutControl* ctrl3 = new LayoutControl();
	ctrl3->attachWnd(&m_Control3);
	ctrl3->setMinSize(50, 20);

	panel->addItem(ctrl1);
	panel->addItem(ctrl2);
	panel->addItem(ctrl3);
}

void CMFCApplication2View::testHorizontalLayout2(LayoutPanelHorizontal* panel)
{
	LayoutControl* ctrl1 = new LayoutControl();
	ctrl1->attachWnd(&m_Control1);
	ctrl1->setMinSize(50, 20);

	LayoutControl* ctrl2 = new LayoutControl();
	ctrl2->attachWnd(&m_Control2);
	ctrl2->setMinSize(50, 20);
	ctrl2->setHorizontalPolicy(LayoutItem::EXPANDING);

	LayoutControl* ctrl3 = new LayoutControl();
	ctrl3->attachWnd(&m_Control3);
	ctrl3->setMinSize(50, 20);

	panel->addItem(ctrl1);
	panel->addItem(ctrl2);
	panel->addItem(ctrl3);
}

void CMFCApplication2View::testVerticalLayout1(LayoutPanelVertical* panel)
{
	LayoutControl* ctrl1 = new LayoutControl();
	ctrl1->attachWnd(&m_Control1);
	ctrl1->setMinSize(50, 20);

	LayoutControl* ctrl2 = new LayoutControl();
	ctrl2->attachWnd(&m_Control2);
	ctrl2->setMinSize(50, 20);

	LayoutControl* ctrl3 = new LayoutControl();
	ctrl3->attachWnd(&m_Control3);
	ctrl3->setMinSize(50, 20);

	panel->addItem(ctrl1);
	panel->addItem(ctrl2);
	panel->addItem(ctrl3);
}

void CMFCApplication2View::testVerticalLayout2(LayoutPanelVertical* panel)
{
	LayoutControl* ctrl1 = new LayoutControl();
	ctrl1->attachWnd(&m_Control1);
	ctrl1->setMinSize(50, 20);

	LayoutControl* ctrl2 = new LayoutControl();
	ctrl2->attachWnd(&m_Control2);
	ctrl2->setMinSize(50, 20);
	ctrl2->setVerticalPolicy(LayoutItem::EXPANDING);

	LayoutControl* ctrl3 = new LayoutControl();
	ctrl3->attachWnd(&m_Control3);
	ctrl3->setMinSize(50, 20);

	panel->addItem(ctrl1);
	panel->addItem(ctrl2);
	panel->addItem(ctrl3);
}

void CMFCApplication2View::testVerticalLayout3(LayoutPanelVertical* panel)
{
	LayoutControl* ctrl1 = new LayoutControl();
	ctrl1->attachWnd(&m_Control1);
	ctrl1->setMinSize(50, 20);
	ctrl1->setVerticalPolicy(LayoutItem::EXPANDING);

	LayoutControl* ctrl2 = new LayoutControl();
	ctrl2->attachWnd(&m_Control2);
	ctrl2->setMinSize(50, 20);
	ctrl2->setVerticalPolicy(LayoutItem::EXPANDING);

	LayoutControl* ctrl3 = new LayoutControl();
	ctrl3->attachWnd(&m_Control3);
	ctrl3->setMinSize(50, 20);
	ctrl3->setVerticalPolicy(LayoutItem::EXPANDING);

	panel->addItem(ctrl1);
	panel->addItem(ctrl2);
	panel->addItem(ctrl3);
}

void CMFCApplication2View::testVerticalLayout4(LayoutPanelVertical* panel)
{
	LayoutControl* ctrl1 = new LayoutControl();
	ctrl1->attachWnd(&m_Control1);
	ctrl1->setMinSize(50, 20);
	ctrl1->setPolicy(LayoutItem::EXPANDING, LayoutItem::EXPANDING);

	LayoutControl* ctrl2 = new LayoutControl();
	ctrl2->attachWnd(&m_Control2);
	ctrl2->setMinSize(50, 20);
	ctrl2->setPolicy(LayoutItem::EXPANDING, LayoutItem::EXPANDING);

	LayoutControl* ctrl3 = new LayoutControl();
	ctrl3->attachWnd(&m_Control3);
	ctrl3->setMinSize(50, 20);
	ctrl3->setPolicy(LayoutItem::EXPANDING, LayoutItem::EXPANDING);

	panel->addItem(ctrl1);
	panel->addItem(ctrl2);
	panel->addItem(ctrl3);
}

int CMFCApplication2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//m_MainPanel = new LayoutPanelHorizontal();
	m_MainPanel = new LayoutPanelVertical();

	//testHorizontalLayout1((LayoutPanelHorizontal*)m_MainPanel);
	//testHorizontalLayout2((LayoutPanelHorizontal*)m_MainPanel);

	//testVerticalLayout1((LayoutPanelVertical*)m_MainPanel);
	//testVerticalLayout2((LayoutPanelVertical*)m_MainPanel);
	//testVerticalLayout3((LayoutPanelVertical*)m_MainPanel);
	testVerticalLayout4((LayoutPanelVertical*)m_MainPanel);

	return 0;
}


void CMFCApplication2View::OnSize(UINT nType, int cx, int cy)
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
