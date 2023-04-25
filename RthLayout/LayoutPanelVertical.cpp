#include "stdafx.h"
#include "LayoutPanelVertical.h"
#include "LayoutControl.h"

namespace RthLayout
{
	LayoutPanelVertical::LayoutPanelVertical(void)
	{
	}

	LayoutPanelVertical::~LayoutPanelVertical(void)
	{
	}

	void LayoutPanelVertical::layout()
	{
		UINT cnt = m_cItems.GetSize();
		TRACE("cnt = %d\n", cnt);
		if (cnt == 0)
			return; //nothing to layout

		TRACE(_T("total height: %d\n"), m_Size.cy);
		//reserved = total minus margins and spacing among all items
		UINT reserved_h = m_Size.cy - m_nTopMargin - m_nBottomMargin - (cnt-1)*m_nSpacing;

		//1st pass

		UINT preferred_cnt = 0;
		UINT expanding_cnt = 0;
		for (UINT i=0; i<cnt; ++i)
		{
			if (m_cItems[i]->getVerticalPolicy() == LayoutItem::PREFFERED)
				preferred_cnt++;
			else
				if (m_cItems[i]->getVerticalPolicy() == LayoutItem::EXPANDING)
				expanding_cnt++;
		}

		TRACE(_T("preferred: %d, expanding: %d\n"), preferred_cnt, expanding_cnt);

		UINT ih = reserved_h;
		if (preferred_cnt == cnt && expanding_cnt == 0) //allocate height evenly among all items
		{
			ih = reserved_h / cnt;
		}
		else
		if (preferred_cnt == 0 && expanding_cnt == cnt) //allocate height evenly among all items
		{
			ih = reserved_h / cnt;
		}
		else
		{
			//3rd pass (optional)
			for (UINT i=0; i<cnt; ++i)
			{
				if (expanding_cnt > 0 && m_cItems[i]->getVerticalPolicy() < LayoutItem::EXPANDING)
					ih -= m_cItems[i]->getMinHeight();
				else
				if (expanding_cnt == 0 && preferred_cnt > 0 && m_cItems[i]->getVerticalPolicy() < LayoutItem::PREFFERED)
					ih -= m_cItems[i]->getMinHeight();
			}

			//finally divide remaining height among EXPANDING items
			if (expanding_cnt > 0)
				ih /= expanding_cnt;
		}

		UINT iw = this->getWidth() - m_nLeftMargin - m_nRightMargin;

		//2nd pass
		UINT y = m_Pos.y + m_nTopMargin;
		for (UINT i=0; i<cnt; ++i)
		{
			if (m_cItems[i]->IsKindOf(RUNTIME_CLASS(LayoutPanel)))
				((LayoutPanel*)m_cItems[i])->computeMinHeight();

			//calculate width
			UINT tmp_w = m_cItems[i]->getMinWidth();
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::EXPANDING)
				tmp_w = iw;

			//calculate height
			UINT tmp_h = m_cItems[i]->getMinHeight();
			if (m_cItems[i]->getVerticalPolicy() == LayoutItem::PREFFERED && expanding_cnt == 0)
			{
				tmp_h = ih;
			}
			else
			if (m_cItems[i]->getVerticalPolicy() == LayoutItem::EXPANDING)
			{
				tmp_h = ih;
			}
			
			//resize
			m_cItems[i]->resize(tmp_w, tmp_h);

			//calculate position
			if (i > 0)
				y = m_cItems[i-1]->getY() + m_cItems[i-1]->getHeight() + m_nSpacing;
			
			//layout
			//Note: horizontal alignment is always LEFT (or RIGHT), based on current variant (LTR or RTL)
			m_cItems[i]->setPosition(m_Pos.x + m_nLeftMargin, y);

			//layout childern (if panel)
			m_cItems[i]->layout();
		}
	}
}
