#ifndef RTHLAYOUTPANELVERTICAL_H
#define RTHLAYOUTPANELVERTICAL_H

#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "layoutpanel.h"

namespace RthLayout
{
	class RTHLAYOUT_API LayoutPanelVertical : public LayoutPanel
	{
	public:
		LayoutPanelVertical(void);
		virtual ~LayoutPanelVertical(void);

		virtual void layout();
	};
}

#endif // RTHLAYOUTPANELVERTICAL_H
