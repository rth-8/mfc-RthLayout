#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "LayoutControl.h"
#include "LayoutPanel.h"
using namespace RthLayout;

#include <memory>
#include <stdlib.h>
#include <time.h>
#include <exception>

class LayoutItemMock : public LayoutItem
{
public:
	virtual void layout() { };
};

class LayoutPanelMock : public LayoutPanel
{
public:
	virtual void layout() { };
};


namespace RthLayoutUnitTests
{		
	TEST_CLASS(LayoutPanelTests)
	{
	public:
		
		TEST_CLASS_INITIALIZE(methodName) 
		{
			srand(time(NULL));
		}

		TEST_METHOD(CTor1)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			Assert::IsNotNull(panel);
		}

		TEST_METHOD(CTor2)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);
			
			//          expected, actual
			Assert::AreEqual(0, panel->getX(), _T("Unexpected X."));
			Assert::AreEqual(0, panel->getY(), _T("Unexpected Y."));

			Assert::AreEqual(0, (int)panel->getMinWidth(), _T("Unexpected minimum width."));
			Assert::AreEqual(0, (int)panel->getMinHeight(), _T("Unexpected minimum height."));

			Assert::AreEqual(0, (int)panel->getWidth(), _T("Unexpected width."));
			Assert::AreEqual(0, (int)panel->getHeight(), _T("Unexpected height."));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetPosition)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			int x = rand() % 1000 - 500;
			int y = rand() % 1000 - 500;

			panel->setPosition(x, y);

			Assert::AreEqual(x, panel->getX(), _T("Unexpected X."));
			Assert::AreEqual(y, panel->getY(), _T("Unexpected Y."));
		}

		TEST_METHOD(Resize)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->resize(50, 60);

			Assert::AreEqual(true, result, _T("Setting minimum size failed!"));
			Assert::AreEqual(50, (int)panel->getWidth(), _T("Unexpected width."));
			Assert::AreEqual(60, (int)panel->getHeight(), _T("Unexpected height."));
		}

		TEST_METHOD(SetMinimumSize)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setMinSize(10, 10);

			Assert::AreEqual(true, result, _T("Setting minimum size failed!"));
			Assert::AreEqual(10, (int)panel->getMinWidth(), _T("Unexpected minimum width."));
			Assert::AreEqual(10, (int)panel->getMinHeight(), _T("Unexpected minimum height."));
		}

		TEST_METHOD(Resize_BelowMinimum)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setMinSize(20, 20);

			Assert::AreEqual(true, result, _T("Setting minimum size failed!"));

			result = panel->resize(10, 10);

			Assert::AreEqual(false, result, _T("Resize below minimum size succeeded!"));

			Assert::AreEqual(20, (int)panel->getWidth(), _T("Unexpected width."));
			Assert::AreEqual(20, (int)panel->getHeight(), _T("Unexpected height."));
		}

		TEST_METHOD(Resize_NegativeWidth)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->resize(-10, 10);

			Assert::AreEqual(false, result, _T("Setting negative width succeeded!"));
		}
		
		TEST_METHOD(Resize_NegativeHeight)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->resize(10, -10);

			Assert::AreEqual(false, result, _T("Setting negative height succeeded!"));
		}

		TEST_METHOD(SetMinimumSize_NegativeWidth)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			
			bool result = panel->resize(-10, 10);

			Assert::AreEqual(false, result, _T("Setting negative minimum width succeeded!"));
		}

		TEST_METHOD(SetMinimumSize_NegativeHeight)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->resize(10, -10);

			Assert::AreEqual(false, result, _T("Setting negative minimum height succeeded!"));
		}

		TEST_METHOD(SetLayoutPolicy)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setPolicy(LayoutItem::EXPANDING, LayoutItem::PREFFERED);

			Assert::AreEqual(true, result, _T("Setting policies failed!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::PREFFERED, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicy_HorizontalInvalid)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setPolicy((LayoutItem::LayoutPolicy)1, LayoutItem::PREFFERED);

			Assert::AreEqual(false, result, _T("Setting invalid horizontal policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}
		
		TEST_METHOD(SetLayoutPolicy_VerticalInvalid)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setPolicy(LayoutItem::PREFFERED, (LayoutItem::LayoutPolicy)1);

			Assert::AreEqual(false, result, _T("Setting invalid vertical policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicy_BothInvalid)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setPolicy((LayoutItem::LayoutPolicy)1, (LayoutItem::LayoutPolicy)1);

			Assert::AreEqual(false, result, _T("Setting invalid policies succeeded!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyHorizontal)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setHorizontalPolicy(LayoutItem::PREFFERED);

			Assert::AreEqual(true, result, _T("Setting horizontal policy failed!"));

			Assert::AreEqual((int)LayoutItem::PREFFERED, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyHorizontal_Invalid)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setHorizontalPolicy((LayoutItem::LayoutPolicy)-50);

			Assert::AreEqual(false, result, _T("Setting invalid horizontal policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyVertical)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setVerticalPolicy(LayoutItem::PREFFERED);

			Assert::AreEqual(true, result, _T("Setting vertical policy failed!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::PREFFERED, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyVertical_Invalid)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			bool result = panel->setVerticalPolicy((LayoutItem::LayoutPolicy)-50);

			Assert::AreEqual(false, result, _T("Setting invalid vertical policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)panel->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(DTor) 
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(DTor)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();

			LayoutItemMock* item1 = new LayoutItemMock();
			LayoutItemMock* item2 = new LayoutItemMock();
			LayoutItemMock* item3 = new LayoutItemMock();

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);
			
			delete panel;

			//???
		}

		TEST_METHOD(AddItems)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			int cnt = rand() % 50 + 10;

			for (int i=0; i<cnt; ++i)
			{
				int type = rand() % 3;
				switch (type)
				{
				case 0:
					panel->addItem(new LayoutItemMock());
					break;
				case 1:
					panel->addItem(new LayoutControl());
					break;
				case 2:
					panel->addItem(new LayoutPanelMock());
					break;
				}
			}

			Assert::AreEqual(cnt, (int)panel->getItemsCount());
		}

		TEST_METHOD(GetItem_InsideRange)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			int cnt = rand() % 50 + 10;

			for (int i=0; i<cnt; ++i)
				panel->addItem(new LayoutItemMock());

			Assert::AreEqual(cnt, (int)panel->getItemsCount());

			int idx = rand() % cnt;

			LayoutItem* it = panel->getItemAt(idx);

			Assert::IsNotNull(it);
		}

		TEST_METHOD(GetItem_OutsideRange)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			int cnt = rand() % 50 + 10;

			for (int i=0; i<cnt; ++i)
				panel->addItem(new LayoutItemMock());

			Assert::AreEqual(cnt, (int)panel->getItemsCount());
			
			int idx = cnt + 10;

			auto funPtr = [panel,idx] { panel->getItemAt(idx); };
			Assert::ExpectException<std::out_of_range>(funPtr, _T("Exception was not thrown!"));
		}

		TEST_METHOD(RemoveItem1)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			LayoutItemMock* item1 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr1(item1);
			LayoutItemMock* item2 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr2(item2);
			LayoutItemMock* item3 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr3(item3);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			iptr1.release();
			iptr2.release();
			iptr3.release();

			Assert::AreEqual(3, (int)panel->getItemsCount());
			
			panel->removeItem(item2);

			Assert::AreEqual(2, (int)panel->getItemsCount());
			Assert::IsNotNull(item2);
		}

		TEST_METHOD(RemoveItem2)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			LayoutItemMock* item1 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr1(item1);
			LayoutItemMock* item2 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr2(item2);
			LayoutItemMock* item3 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr3(item3);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			iptr1.release();
			iptr2.release();
			iptr3.release();

			Assert::AreEqual(3, (int)panel->getItemsCount());
			
			panel->removeItem(1);

			Assert::AreEqual(2, (int)panel->getItemsCount());
			Assert::IsNotNull(item2);
		}

		TEST_METHOD(RemoveItem_OutsideRange)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			LayoutItemMock* item1 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr1(item1);
			LayoutItemMock* item2 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr2(item2);
			LayoutItemMock* item3 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr3(item3);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			iptr1.release();
			iptr2.release();
			iptr3.release();

			auto funPtr = [panel] { panel->removeItem(10); };
			Assert::ExpectException<std::out_of_range>(funPtr, _T("Exception was not thrown!"));
		}

		TEST_METHOD(ComputeMinimumSize)
		{
			LayoutPanelMock* panel = new LayoutPanelMock();
			std::auto_ptr<LayoutPanelMock> ptr(panel);

			LayoutItemMock* item1 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr1(item1);
			LayoutItemMock* item2 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr2(item2);
			LayoutItemMock* item3 = new LayoutItemMock();
			std::auto_ptr<LayoutItemMock> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->computeMinWidth();
			panel->computeMinHeight();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			Assert::AreEqual(30, (int)panel->getMinWidth(), _T("Minumim width was not computed!"));
			Assert::AreEqual(87, (int)panel->getMinHeight(), _T("Minumim height was not computed!"));
		}

	};
}
