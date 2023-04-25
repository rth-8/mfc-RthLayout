#include "stdafx.h"
#include "LayoutPanelHorizontal.h"
#include "LayoutControl.h"

namespace RthLayout
{
	LayoutPanelHorizontal::LayoutPanelHorizontal(void)
	{
	}


	LayoutPanelHorizontal::~LayoutPanelHorizontal(void)
	{
	}

	void LayoutPanelHorizontal::layout()
	{
		UINT cnt = m_cItems.GetSize();
		TRACE("cnt = %d\n", cnt);
		if (cnt == 0)
			return;

		UINT reserved_w = m_Size.cx - m_nLeftMargin - m_nRightMargin - (cnt-1)*m_nSpacing;

		//1st pass

		UINT preferred_cnt = 0;
		UINT expanding_cnt = 0;
		for (UINT i=0; i<cnt; ++i)
		{
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::PREFFERED)
				preferred_cnt++;
			else
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::EXPANDING)
				expanding_cnt++;
		}

		TRACE(_T("preferred: %d, expanding: %d\n"), preferred_cnt, expanding_cnt);

		UINT iw = reserved_w;
		if (preferred_cnt == cnt && expanding_cnt == 0) 
		{ //all items have PREFERRED policy and there is no EXPANDING policy -> allocate height evenly among all items
			iw = reserved_w / cnt;
		}
		else
		if (preferred_cnt == 0 && expanding_cnt == cnt)
		{ //all items have EXPANDING policy and there is no PREFERRED policy -> allocate height evenly among all items
			iw = reserved_w / cnt;
		}
		else
		{ 
			//there is combination of policies 
			// -> extract minimum widths for each item which has FIXED policy
			// -> if there is at least one EXPANDING policy, extract also widths for each item with PREFERRED policy

			//3rd pass (optional)
			for (UINT i=0; i<cnt; ++i)
			{
				//if layouting panel, we have to calculate its minimum width based on containing controls
				if (m_cItems[i]->IsKindOf(RUNTIME_CLASS(LayoutPanel)))
					((LayoutPanel*)m_cItems[i])->computeMinWidth();

				if (expanding_cnt > 0 && m_cItems[i]->getHorizontalPolicy() < LayoutItem::EXPANDING)
					iw -= m_cItems[i]->getMinWidth();
				else
				if (expanding_cnt == 0 && preferred_cnt > 0 && m_cItems[i]->getHorizontalPolicy() < LayoutItem::PREFFERED)
					iw -= m_cItems[i]->getMinWidth();
			}

			//finally divide remaining width among EXPANDING items
			if (expanding_cnt > 0)
				iw /= expanding_cnt;
		}

		//height of item in case of VERTICAL stretch (EXPANDING policy only)
		UINT ih = this->getHeight() - m_nTopMargin - m_nBottomMargin;

		//2nd pass
		UINT x = m_Pos.x + m_nLeftMargin; //starting x position
		for (UINT i=0; i<cnt; ++i)
		{
			//if layouting panel, we have to calculate its minimum width based on containing controls
			if (m_cItems[i]->IsKindOf(RUNTIME_CLASS(LayoutPanel)))
				((LayoutPanel*)m_cItems[i])->computeMinWidth();

			//calculate height
			//if item is not EXPANDING, give it minimum height (default)
			UINT tmp_h = m_cItems[i]->getMinHeight();
			if (m_cItems[i]->getVerticalPolicy() == LayoutItem::EXPANDING)
				tmp_h = ih;

			//calculate width
			UINT tmp_w = m_cItems[i]->getMinWidth(); //minimum w is default (FIXED layout policy)
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::PREFFERED && expanding_cnt == 0)
			{ //if layout ploicy is PREFERRED and there are no other items with EXPANDING policy, give item calculated w
				tmp_w = iw;
			}
			else
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::EXPANDING)
			{ //if layout plicy is EXPANDING, give item calculated w no matter of other policies
				tmp_w = iw;
			}
			
			//resize
			m_cItems[i]->resize(tmp_w, tmp_h);

			//calculate position
			if (i > 0) //move to next position based on previously layouted item, with spacing taken into account
				x = m_cItems[i-1]->getX() + m_cItems[i-1]->getWidth() + m_nSpacing; 
			
			//layout
			//Note: vertical alignment is always centered, if item is not vertically EXPANDING
			UINT y = m_Pos.y + m_nTopMargin;
			if (m_cItems[i]->getVerticalPolicy() != LayoutItem::EXPANDING)
				y = m_Pos.x + m_Size.cy / 2 - m_cItems[i]->getHeight() / 2;
			m_cItems[i]->setPosition(x, y);

			//layout childern (if panel)
			m_cItems[i]->layout();
		}
	}
}
