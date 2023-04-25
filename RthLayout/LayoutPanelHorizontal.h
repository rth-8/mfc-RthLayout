#ifndef RTHLAYOUTPANELHORIZONTAL_H
#define RTHLAYOUTPANELHORIZONTAL_H

#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "layoutpanel.h"

namespace RthLayout
{
	class RTHLAYOUT_API LayoutPanelHorizontal : public LayoutPanel
	{
	public:
		LayoutPanelHorizontal(void);
		virtual ~LayoutPanelHorizontal(void);

		virtual void layout();
	};
}

#endif // RTHLAYOUTPANELHORIZONTAL_H

