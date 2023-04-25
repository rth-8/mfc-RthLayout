#include "stdafx.h"
#include "LayoutPanelGrid.h"
#include "LayoutControl.h"

namespace RthLayout
{
	LayoutPanelGrid::LayoutPanelGrid(void)
		: m_nRows(0)
		, m_nCols(0)
	{
	}

	LayoutPanelGrid::~LayoutPanelGrid(void)
	{
	}

	void LayoutPanelGrid::setGrid(UINT rows, UINT cols)
	{
		if (rows < m_nRows || cols < m_nCols)
		{
			UINT idx;
			for (UINT i = m_nRows-1; i >= 0; --i)
			{
				for (UINT j = m_nCols-1; j >= 0; --j)
				{
					idx = i * m_nCols + j;
					if (i > rows || j > cols && m_cItems[idx])
						delete m_cItems[idx];
				}
			}
		}

		m_nRows = rows;
		m_nCols = cols;

		UINT size = m_nRows * m_nCols;
		m_cItems.SetSize(size);
	}

	void LayoutPanelGrid::insertItem(UINT row, UINT col, LayoutItem* item)
	{
		ASSERT(row >= 0 && row < m_nRows);
		ASSERT(col >= 0 && col < m_nCols);

		UINT idx = row * m_nCols + col;
	
		m_cItems.InsertAt(idx, item);
	}

	void LayoutPanelGrid::removeItem(UINT row, UINT col)
	{
		ASSERT(row >= 0 && row < m_nRows);
		ASSERT(col >= 0 && col < m_nCols);

		UINT idx = row * m_nCols + col;

		delete m_cItems[idx];

		m_cItems.SetAt(idx, NULL); //empty cell
	}

	void LayoutPanelGrid::layout()
	{
		TRACE(_T("GRID (%d x %d)!\n"), m_nRows, m_nCols);

		if (m_nRows < 1 || m_nCols < 1)
			return; //nothing to layout

		//Note: Unlike horizontal (vertical) layout, in grid layout we can have empty cells.
		//      For this reason empty cells (NULL) are treated as spacers with FIXED layout policy
		//      for each direction.

		TRACE(_T("total size: %d x %d\n"), m_Size.cx, m_Size.cy);

		UINT reserved_w = m_Size.cx - m_nLeftMargin - m_nRightMargin - (m_nCols-1)*m_nSpacing;
		UINT reserved_h = m_Size.cy - m_nTopMargin - m_nBottomMargin - (m_nRows-1)*m_nSpacing;

		TRACE(_T("reserved size: %d x %d\n"), reserved_w, reserved_h);

		//-------------------------------------------------------------------------
	
		/*
				O O O  |    O
				O O O  |>   O
				O O O  |    O

				-----
				  v

				O O O

			- width of columns will be caclulated from maximal layout policy among all items in each column
			- height of rows will be calculated from maximal layout policy among all items in each row

			- in case there is at least one item with EXPANDING policy, remaining non-expanding items must be shrinked ->
			  -> for this reason also maximal width of each column is calculated from minimum widths of all items in corresponding column
			  -> -//-                 maximal height of each row   -//-               minimum heights of all items in corresponding row
		*/

		UINT idx;

		UINT preferred_h_cnt = 0;
		UINT expanding_h_cnt = 0;
		UINT preferred_v_cnt = 0;
		UINT expanding_v_cnt = 0;

		int* columnMaxPolicies = new int[m_nCols];
		UINT* columnMinMaxWidths = new UINT[m_nCols];
		for (UINT c=0; c<m_nCols; ++c)
		{
			columnMaxPolicies[c] = LayoutItem::FIXED;
			columnMinMaxWidths[c] = 0;

			for (UINT r=0; r<m_nRows; ++r)
			{
				idx = r * m_nCols + c;
			
				if (m_cItems[idx])
				{
					if (m_cItems[idx]->getHorizontalPolicy() > columnMaxPolicies[c])
						columnMaxPolicies[c] = m_cItems[idx]->getHorizontalPolicy();

					if (m_cItems[idx]->getMinWidth() > columnMinMaxWidths[c])
						columnMinMaxWidths[c] = m_cItems[idx]->getMinWidth();
				}
			}

			if (columnMaxPolicies[c] == LayoutItem::PREFFERED) 
				preferred_h_cnt++;
			else
			if (columnMaxPolicies[c] == LayoutItem::EXPANDING) 
				expanding_h_cnt++;
		}

		int* rowMaxPolicies = new int[m_nRows];
		UINT* rowMinMaxHeights = new UINT[m_nRows];
		for (UINT r=0; r<m_nRows; ++r)
		{
			rowMaxPolicies[r] = LayoutItem::FIXED;
			rowMinMaxHeights[r] = 0;

			for (UINT c=0; c<m_nCols; ++c)
			{
				idx = r * m_nCols + c;

				if (m_cItems[idx])
				{
					if (m_cItems[idx]->getVerticalPolicy() > rowMaxPolicies[r])
						rowMaxPolicies[r] = m_cItems[idx]->getVerticalPolicy();

					if (m_cItems[idx]->getMinHeight() > rowMinMaxHeights[r])
						rowMinMaxHeights[r] = m_cItems[idx]->getMinHeight();
				}
			}

			if (rowMaxPolicies[r] == LayoutItem::PREFFERED) 
				preferred_v_cnt++;
			else
			if (rowMaxPolicies[r] == LayoutItem::EXPANDING) 
				expanding_v_cnt++;
		}

		TRACE(_T("H: preferred: %d, expanding: %d\n"), preferred_h_cnt, expanding_h_cnt);
		TRACE(_T("V: preferred: %d, expanding: %d\n"), preferred_v_cnt, expanding_v_cnt);

		//-------------------------------------------------------------------------

		UINT iw = reserved_w;	//width of single column

		if (expanding_h_cnt == m_nCols)
			iw = reserved_w / m_nCols; //all columns are expanding -> reserved width will be equally distributen among all columns
		else
		if (expanding_h_cnt == 0 && preferred_h_cnt == m_nCols)
			iw = reserved_w / m_nCols; //all columns are preffered -> reserved width will be equally distributen among all columns
		else
		if (expanding_h_cnt == 0 && preferred_h_cnt == 0)
			iw = reserved_w / m_nCols; //all columns are fixed -> reserved width will be equally distributen among all columns
		else
		{
			//mixed policies
			//for each column with maximal policy FIXED, extract its calculated width from reserved width
			for (UINT c=0; c<m_nCols; ++c)
				if (columnMaxPolicies[c] == LayoutItem::FIXED)
					iw -= columnMinMaxWidths[c];

			//calculated width distribute for remaining non-fixed columns
			if (expanding_h_cnt > 0)
				iw /= expanding_h_cnt;
		}

		UINT ih = reserved_h;

		if (expanding_v_cnt == m_nRows)
			ih = reserved_h / m_nRows;
		else
		if (expanding_v_cnt == 0 && preferred_v_cnt == m_nRows)
			ih = reserved_h / m_nRows;
		else
		if (expanding_v_cnt == 0 && preferred_v_cnt == 0)
			ih = reserved_h / m_nRows;
		else
		{
			for (UINT r=0; r<m_nRows; ++r)
				if (rowMaxPolicies[r] == LayoutItem::FIXED)
					ih -= rowMinMaxHeights[r];

			if (expanding_v_cnt > 0)
				ih /= expanding_v_cnt;
		}

		//-------------------------------------------------------------------------

		// compute grid

		CArray<CRect, CRect&> grid;

		UINT x = m_Pos.x + m_nLeftMargin;
		UINT y = m_Pos.y + m_nTopMargin;

		for (UINT r=0; r<m_nRows; ++r)
		{
			x = m_Pos.x + m_nLeftMargin; //start of each row
		
			UINT rh = ih;
			if (rowMaxPolicies[r] < LayoutItem::EXPANDING && expanding_v_cnt > 0)
				rh = rowMinMaxHeights[r];

			for (UINT c=0; c<m_nCols; ++c)
			{
				UINT cw = iw;
				if (columnMaxPolicies[c] < LayoutItem::EXPANDING && expanding_h_cnt > 0)
					cw = columnMinMaxWidths[c];

				grid.Add(CRect(x, y, x + cw, y + rh));

				x += cw + m_nSpacing;
			}

			y += rh + m_nSpacing;
		}

		//-------------------------------------------------------------------------

		//layout items based on computed grid

		UINT cnt = m_cItems.GetCount();
		for (UINT i=0; i<cnt; ++i)
		{
			if (!m_cItems[i])
				continue;

			//if layouting panel, we have to calculate its minimum size based on containing controls
			if (m_cItems[i]->IsKindOf(RUNTIME_CLASS(LayoutPanel)))
			{
				((LayoutPanel*)m_cItems[i])->computeMinWidth();
				((LayoutPanel*)m_cItems[i])->computeMinHeight();
			}

			//calculate width
			UINT tmp_w = m_cItems[i]->getMinWidth();
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::EXPANDING)
				tmp_w = grid[i].Width(); //items is EXPANDING -> stretch to width of corresponding grid cell
			else
			if (m_cItems[i]->getHorizontalPolicy() == LayoutItem::PREFFERED && preferred_h_cnt == m_nCols && expanding_h_cnt == 0)
				tmp_w = grid[i].Width(); //items is PREFERRED and each other is PREFERRED too and there are no EXPANDING items
										 // -> stretch to width of corresponding grid cell

			//TODO

			//calculate height
			UINT tmp_h = m_cItems[i]->getMinHeight();
			if (m_cItems[i]->getVerticalPolicy() == LayoutItem::EXPANDING)
				tmp_h = grid[i].Height();
			else
			if (m_cItems[i]->getVerticalPolicy() == LayoutItem::PREFFERED && preferred_v_cnt == m_nCols && expanding_v_cnt == 0)
				tmp_h = grid[i].Height();

			//TODO

			//resize
			m_cItems[i]->resize(tmp_w, tmp_h);

			//calculate position
			//in case of grid, center each time
			CPoint c = grid[i].CenterPoint();
			m_cItems[i]->setPosition(
				c.x - m_cItems[i]->getWidth() / 2,
				c.y - m_cItems[i]->getHeight() / 2);

			//layout childern (if panel)
			m_cItems[i]->layout();
		}

		delete rowMaxPolicies;
		delete rowMinMaxHeights;
		delete columnMaxPolicies;
		delete columnMinMaxWidths;
	}
}
