#ifndef RTHLAYOUTITEM_H
#define RTHLAYOUTITEM_H

#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "stdafx.h"

namespace RthLayout
{
	class RTHLAYOUT_API LayoutItem : public CObject
	{
		DECLARE_DYNAMIC(LayoutItem)

	public:
		enum LayoutPolicy
		{
			FIXED = 101,
			PREFFERED,
			EXPANDING,
			LAST //do not put anything beyond
		};

		LayoutItem(void);
		virtual ~LayoutItem(void);

		virtual void setPosition(int x, int y);

		int getX();
		int getY();

		virtual bool resize(int w, int h);

		UINT getWidth();
		UINT getHeight();

		virtual bool setMinSize(int w, int h);

		UINT getMinWidth();
		UINT getMinHeight();

		bool setPolicy(LayoutPolicy hPolicy, LayoutPolicy vPolicy);
		bool setHorizontalPolicy(LayoutPolicy policy);
		bool setVerticalPolicy(LayoutPolicy policy);

		LayoutPolicy getHorizontalPolicy();
		LayoutPolicy getVerticalPolicy();

		virtual void layout() = 0;

	protected:
		CPoint m_Pos;
		CSize m_Size;
		CSize m_MinSize;
		LayoutPolicy m_policyHoriz;
		LayoutPolicy m_policyVert;

	}; // class LayoutItem

} //namespace RthLayout

#endif // RTHLAYOUTITEM_H
