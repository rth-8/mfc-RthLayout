#ifndef RTHLAYOUTCONTROL_H
#define RTHLAYOUTCONTROL_H

#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "LayoutItem.h"

namespace RthLayout
{
	class RTHLAYOUT_API LayoutControl : public LayoutItem
	{
		DECLARE_DYNAMIC(LayoutControl)

	public:
		LayoutControl(void);
		virtual ~LayoutControl(void);

		//doesn't take ownership
		void attachWnd(CWnd* wnd);
		void detachWnd();

		CWnd* getWnd();

		virtual void setPosition(int x, int y);
		virtual bool resize(int w, int h);
		virtual bool setMinSize(int w, int h);

		virtual void layout() {};

	private:
		CWnd* m_ctrlWnd;
	};

}

#endif // RTHLAYOUTCONTROL_H
