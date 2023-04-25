#include "stdafx.h"
#include "LayoutItem.h"

namespace RthLayout
{
	IMPLEMENT_DYNAMIC(LayoutItem, CObject)

	LayoutItem::LayoutItem(void)
	{
		m_MinSize.SetSize(0, 0);

		m_policyHoriz = LayoutPolicy::FIXED;
		m_policyVert = LayoutPolicy::FIXED;
	}

	LayoutItem::~LayoutItem(void)
	{
	}

	void LayoutItem::setPosition(int x, int y)
	{
		m_Pos.SetPoint(x, y);
	}

	int LayoutItem::getX()
	{
		return m_Pos.x;
	}

	int LayoutItem::getY()
	{
		return m_Pos.y;
	}

	bool LayoutItem::resize(int w, int h)
	{
		if (w < 0 || h < 0)
			return false;

		if (w < m_MinSize.cx || h < m_MinSize.cy)
			return false;

		//TRACE(_T("MIN size ( %d x %d )\n"), m_MinSize.cx, m_MinSize.cy);

		TRACE(_T("LayoutItem::resize ( %d x %d )\n"), w, h);
		m_Size.SetSize(w, h);

		return true;
	}

	UINT LayoutItem::getWidth()
	{
		return m_Size.cx;
	}

	UINT LayoutItem::getHeight()
	{
		return m_Size.cy;
	}

	bool LayoutItem::setMinSize(int w, int h)
	{
		if (w < 0 || h < 0)
			return false;

		m_MinSize.SetSize(w, h);

		//if minimum size is bigger than actual size, resize to new minimum

		if (m_Size.cx < w)
			m_Size.cx = w;

		if (m_Size.cy < h)
			m_Size.cy = h;

		return true;
	}

	UINT LayoutItem::getMinWidth()
	{
		return m_MinSize.cx;
	}

	UINT LayoutItem::getMinHeight()
	{
		return m_MinSize.cy;
	}

	bool LayoutItem::setPolicy(LayoutItem::LayoutPolicy hPolicy, LayoutItem::LayoutPolicy vPolicy)
	{
		if (hPolicy >= LayoutItem::FIXED && hPolicy < LayoutItem::LAST &&
			vPolicy >= LayoutItem::FIXED && vPolicy < LayoutItem::LAST)
		{
			m_policyHoriz = hPolicy;
			m_policyVert = vPolicy;
			return true;
		}

		return false;
	}

	bool LayoutItem::setHorizontalPolicy(LayoutItem::LayoutPolicy policy)
	{
		if (policy >= LayoutItem::FIXED && policy < LayoutItem::LAST)
		{
			m_policyHoriz = policy;
			return true;
		}

		return false;
	}
	
	bool LayoutItem::setVerticalPolicy(LayoutItem::LayoutPolicy policy)
	{
		if (policy >= LayoutItem::FIXED && policy < LayoutItem::LAST)
		{
			m_policyVert = policy;
			return true;
		}

		return false;
	}

	LayoutItem::LayoutPolicy LayoutItem::getHorizontalPolicy()
	{
		return m_policyHoriz;
	}

	LayoutItem::LayoutPolicy LayoutItem::getVerticalPolicy()
	{
		return m_policyVert;
	}

} //namespace RthLayout
