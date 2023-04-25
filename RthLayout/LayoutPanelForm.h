#ifndef RTHLAYOUTPANELFORM_H
#define RTHLAYOUTPANELFORM_H

#ifdef RTHLAYOUT_EXPORTS
#pragma message ("DLLEXPORT")
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#pragma message ("DLL IMPORT")
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "layoutpanelgrid.h"

namespace RthLayout
{
	class RTHLAYOUT_API LayoutPanelForm : public LayoutPanelGrid
	{
	public:
		LayoutPanelForm(void);
		virtual ~LayoutPanelForm(void);

		void addLine(LayoutItem* caption, LayoutItem* item);

		virtual void layout();

	protected:	
		void addItem(LayoutItem* item) { /*nothing*/ }
		void setGrid(UINT rows, UINT cols) { /*nothing*/ }
		void insertItem(UINT row, UINT col, LayoutItem* item) { /*nothing*/ }
	};
}

#endif // RTHLAYOUTPANELFORM_H
