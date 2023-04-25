#include "stdafx.h"
#include "LayoutPanelForm.h"

namespace RthLayout
{
	LayoutPanelForm::LayoutPanelForm(void) 
		: LayoutPanelGrid()
	{
		m_nCols = 2;
	}


	LayoutPanelForm::~LayoutPanelForm(void)
	{
	}

	void LayoutPanelForm::addLine(LayoutItem* caption, LayoutItem* item)
	{
		LayoutPanelGrid::setGrid(++m_nRows, 2);

		LayoutPanelGrid::insertItem(m_nRows-1, 0, caption);
		LayoutPanelGrid::insertItem(m_nRows-1, 1, item);
	}

	void LayoutPanelForm::layout()
	{
		TRACE(_T("FORM (%d x %d)!\n"), m_nRows, m_nCols);

		if (m_nRows < 1 || m_nCols < 1)
			return; //nothing to layout

		UINT cnt = m_cItems.GetSize();
		for (UINT i=0; i<cnt; ++i)
		{
			if (!m_cItems[i]) //empty cell
				continue;

			if (i%2 != 0)
				m_cItems[i]->setHorizontalPolicy(LayoutItem::EXPANDING);
			else
				m_cItems[i]->setHorizontalPolicy(LayoutItem::FIXED);
		}

		LayoutPanelGrid::layout();
	}
}
