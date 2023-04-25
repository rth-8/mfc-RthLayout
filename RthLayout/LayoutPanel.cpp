#include "stdafx.h"
#include "LayoutPanel.h"
#include "LayoutControl.h"
#include <limits.h>

namespace RthLayout
{
	IMPLEMENT_DYNAMIC(LayoutPanel, LayoutItem)

	LayoutPanel::LayoutPanel(void) 
		: LayoutItem()
		, m_nLeftMargin(0)
		, m_nRightMargin(0)
		, m_nTopMargin(0)
		, m_nBottomMargin(0)
		, m_nSpacing(0)
	{
		m_policyHoriz = LayoutPolicy::EXPANDING;
		m_policyVert = LayoutPolicy::EXPANDING;
	}

	LayoutPanel::~LayoutPanel(void)
	{
		UINT cnt = m_cItems.GetCount();
		for (UINT i=0; i<cnt; ++i)
			delete m_cItems[i];

		m_cItems.RemoveAll();
	}

	void LayoutPanel::addItem(LayoutItem* item)
	{
		m_cItems.Add(item);
	}

	UINT LayoutPanel::findItem(LayoutItem* item)
	{
		UINT cnt = m_cItems.GetCount();
		for (UINT i=0; i<cnt; ++i)
			if (m_cItems[i] == item)
				return i;

		return -1;
	}

	void LayoutPanel::removeItem(LayoutItem* item)
	{
		UINT pos = findItem(item);
		if (pos != -1)
			m_cItems.RemoveAt(pos);
	}

	void LayoutPanel::removeItem(UINT pos)
	{
		if (pos >= 0 && pos < m_cItems.GetCount())
			m_cItems.RemoveAt(pos);
		else
			throw std::out_of_range("Position out of range!");
	}

	UINT LayoutPanel::getItemsCount()
	{
		return m_cItems.GetCount();
	}

	LayoutItem* LayoutPanel::getItemAt(UINT pos)
	{
		//ASSERT(pos >= 0 && pos < m_cItems.GetCount());

		if (pos >= 0 && pos < m_cItems.GetCount())
			return m_cItems[pos];
		else
			throw std::out_of_range("Position out of range!");
	}

	//calculates maximum width from minimum widths of each items
	//resulting value is new minimum width of panel
	void LayoutPanel::computeMinWidth()
	{
		m_MinSize.cx = 0;
		UINT cnt = m_cItems.GetCount();
		for (UINT i=0; i<cnt; ++i)
		{
			if (m_cItems[i]->IsKindOf(RUNTIME_CLASS(LayoutPanel)))
				((LayoutPanel*)m_cItems[i])->computeMinWidth();

			if (m_cItems[i]->getMinWidth() > m_MinSize.cx)
				m_MinSize.cx = m_cItems[i]->getMinWidth();
		}

		TRACE(_T("LayoutPanel::computeMinWidth = %d\n"), m_MinSize.cx);
		m_Size.cx = m_MinSize.cx;
	}

	//calculates maximum heigh from minimum heights of each items
	//resulting value is new minimum height of panel
	void LayoutPanel::computeMinHeight()
	{
		m_MinSize.cy = 0;
		UINT cnt = m_cItems.GetCount();
		for (UINT i=0; i<cnt; ++i)
		{
			if (m_cItems[i]->IsKindOf(RUNTIME_CLASS(LayoutPanel)))
				((LayoutPanel*)m_cItems[i])->computeMinHeight();

			if (m_cItems[i]->getMinHeight() > m_MinSize.cy)
				m_MinSize.cy = m_cItems[i]->getMinHeight();
		}

		TRACE(_T("LayoutPanel::computeMinHeight = %d\n"), m_MinSize.cy);
		m_Size.cy = m_MinSize.cy;
	}
}
