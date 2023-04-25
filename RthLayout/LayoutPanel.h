#ifndef RTHLAYOUTPANEL_H
#define RTHLAYOUTPANEL_H

#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport) 
#else
#define RTHLAYOUT_API __declspec(dllimport) 
#endif

#include "LayoutItem.h"

namespace RthLayout
{
	//panel is container for items
	//panel takes ownership of items as long as they are not manually removed
	//panel deletes all items it owns
	//controls attached to layout items are not deleted
	class RTHLAYOUT_API LayoutPanel : public LayoutItem
	{
		DECLARE_DYNAMIC(LayoutPanel)

	public:
		LayoutPanel(void);
		virtual ~LayoutPanel(void);

		//takes ownership as long as item is not manually removed
		virtual void addItem(LayoutItem* item);

		void removeItem(LayoutItem* item);
		void removeItem(UINT pos);

		UINT getItemsCount();
		LayoutItem* getItemAt(UINT pos) throw(...);

		void computeMinWidth();
		void computeMinHeight();

		virtual void layout() = 0;

	private:
		UINT findItem(LayoutItem* item);

	public:
		UINT m_nLeftMargin;
		UINT m_nRightMargin;
		UINT m_nTopMargin;
		UINT m_nBottomMargin;
		UINT m_nSpacing;

	protected:
		CTypedPtrArray<CPtrArray, LayoutItem*> m_cItems;

	};
}

#endif // RTHLAYOUTPANEL_H
