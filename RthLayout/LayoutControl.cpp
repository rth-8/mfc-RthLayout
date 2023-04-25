#include "stdafx.h"
#include "LayoutControl.h"

namespace RthLayout
{
	IMPLEMENT_DYNAMIC(LayoutControl, LayoutItem)

	LayoutControl::LayoutControl(void)
		: m_ctrlWnd(NULL)
	{
		m_MinSize.SetSize(0, 0);
	}

	LayoutControl::~LayoutControl(void)
	{
	}

	void LayoutControl::attachWnd(CWnd* wnd)
	{
		m_ctrlWnd = wnd;
	}

	void LayoutControl::detachWnd()
	{
		//Do NOT delete control!
		m_ctrlWnd = NULL;
	}

	CWnd* LayoutControl::getWnd()
	{
		return m_ctrlWnd;
	}

	void LayoutControl::setPosition(int x, int y)
	{
		LayoutItem::setPosition(x, y);

		if (m_ctrlWnd && m_ctrlWnd->m_hWnd)
		{
			TRACE(_T("LayoutControl::setPosition: [ %d, %d ]\n"), x, y);
			m_ctrlWnd->MoveWindow(m_Pos.x, m_Pos.y, m_Size.cx, m_Size.cy);
		}
	}

	bool LayoutControl::resize(int w, int h)
	{
		bool res = LayoutItem::resize(w, h);

		if (res && m_ctrlWnd && m_ctrlWnd->m_hWnd)
		{
			TRACE(_T("LayoutControl::resize: ( %d x %d )\n"), m_Size.cx, m_Size.cy);
			m_ctrlWnd->MoveWindow(m_Pos.x, m_Pos.y, m_Size.cx, m_Size.cy);
		}

		return res;
	}

	bool LayoutControl::setMinSize(int w, int h)
	{
		bool res = LayoutItem::setMinSize(w, h);

		if (res && m_ctrlWnd && m_ctrlWnd->m_hWnd)
		{
			TRACE(_T("LayoutControl::resize: ( %d x %d )\n"), m_Size.cx, m_Size.cy);
			m_ctrlWnd->MoveWindow(m_Pos.x, m_Pos.y, m_Size.cx, m_Size.cy);
		}

		return res;
	}
}
