#ifndef RTHLAYOUTPANELGRID_H
#define RTHLAYOUTPANELGRID_H

#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "layoutpanel.h"

namespace RthLayout
{
	class RTHLAYOUT_API LayoutPanelGrid : public LayoutPanel
	{
	public:
		LayoutPanelGrid(void);
		virtual ~LayoutPanelGrid(void);

		virtual void setGrid(UINT rows, UINT cols);
		virtual void insertItem(UINT row, UINT col, LayoutItem* item);

		void removeItem(UINT row, UINT col);

		virtual void layout();

	protected:
		void addItem(LayoutItem* item) { /*nothing*/ }

	protected:
		UINT m_nRows;
		UINT m_nCols;
	};
}

#endif // RTHLAYOUTPANELGRID_H

