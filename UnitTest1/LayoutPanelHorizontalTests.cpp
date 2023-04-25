#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "LayoutControl.h"
#include "LayoutPanelHorizontal.h"
using namespace RthLayout;

#include <memory>
#include <stdlib.h>
#include <time.h>
#include <exception>

namespace RthLayoutUnitTests
{		
	TEST_CLASS(LayoutPanelHorizontalTests)
	{
	public:
		
		TEST_CLASS_INITIALIZE(methodName) 
		{
			srand(time(NULL));
		}
		
		TEST_METHOD(LayoutTest_AllFixed)
		{
			LayoutPanelHorizontal* panel = new LayoutPanelHorizontal();
			std::auto_ptr<LayoutPanelHorizontal> ptr(panel);

			LayoutControl* item1 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr1(item1);
			LayoutControl* item2 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr2(item2);
			LayoutControl* item3 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->resize(200, 200);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_x = 0;
			Assert::AreEqual(expected_x, item1->getX());
			expected_x = item1->getX() + item1->getWidth();
			Assert::AreEqual(expected_x, item2->getX());
			expected_x = item2->getX() + item2->getWidth();
			Assert::AreEqual(expected_x, item3->getX());

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			Assert::AreEqual<UINT>(30, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			Assert::AreEqual<UINT>(66, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_OneExpanding_Horizontal)
		{
			LayoutPanelHorizontal* panel = new LayoutPanelHorizontal();
			std::auto_ptr<LayoutPanelHorizontal> ptr(panel);

			LayoutControl* item1 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr1(item1);
			LayoutControl* item2 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr2(item2);
			LayoutControl* item3 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			item2->setHorizontalPolicy(LayoutItem::EXPANDING);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->resize(200, 200);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_x = 0;
			Assert::AreEqual(expected_x, item1->getX());
			expected_x = item1->getX() + item1->getWidth();
			Assert::AreEqual(expected_x, item2->getX());
			expected_x = item2->getX() + item2->getWidth();
			Assert::AreEqual(expected_x, item3->getX());

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			int expected_w = panel->getWidth() - 25 - 11;
			Assert::AreEqual<UINT>(expected_w, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			Assert::AreEqual<UINT>(66, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_OneExpanding_Vertical)
		{
			LayoutPanelHorizontal* panel = new LayoutPanelHorizontal();
			std::auto_ptr<LayoutPanelHorizontal> ptr(panel);

			LayoutControl* item1 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr1(item1);
			LayoutControl* item2 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr2(item2);
			LayoutControl* item3 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			item3->setVerticalPolicy(LayoutItem::EXPANDING);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->resize(200, 200);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_x = 0;
			Assert::AreEqual(expected_x, item1->getX());
			expected_x = item1->getX() + item1->getWidth();
			Assert::AreEqual(expected_x, item2->getX());
			expected_x = item2->getX() + item2->getWidth();
			Assert::AreEqual(expected_x, item3->getX());

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			Assert::AreEqual<UINT>(30, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			int expected_h = panel->getHeight();
			Assert::AreEqual<UINT>(expected_h, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_AllExpanding_Horizontal)
		{
			LayoutPanelHorizontal* panel = new LayoutPanelHorizontal();
			std::auto_ptr<LayoutPanelHorizontal> ptr(panel);

			LayoutControl* item1 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr1(item1);
			LayoutControl* item2 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr2(item2);
			LayoutControl* item3 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			item1->setHorizontalPolicy(LayoutItem::EXPANDING);
			item2->setHorizontalPolicy(LayoutItem::EXPANDING);
			item3->setHorizontalPolicy(LayoutItem::EXPANDING);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->resize(200, 200);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_x = 0;
			Assert::AreEqual(expected_x, item1->getX());
			expected_x = item1->getX() + item1->getWidth();
			Assert::AreEqual(expected_x, item2->getX());
			expected_x = item2->getX() + item2->getWidth();
			Assert::AreEqual(expected_x, item3->getX());

			int expected_w = panel->getWidth() / 3;

			Assert::AreEqual<UINT>(expected_w, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			Assert::AreEqual<UINT>(expected_w, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(expected_w, item3->getWidth());
			Assert::AreEqual<UINT>(66, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_AllExpanding_Both)
		{
			LayoutPanelHorizontal* panel = new LayoutPanelHorizontal();
			std::auto_ptr<LayoutPanelHorizontal> ptr(panel);

			LayoutControl* item1 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr1(item1);
			LayoutControl* item2 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr2(item2);
			LayoutControl* item3 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			item1->setPolicy(LayoutItem::EXPANDING, LayoutItem::EXPANDING);
			item2->setPolicy(LayoutItem::EXPANDING, LayoutItem::EXPANDING);
			item3->setPolicy(LayoutItem::EXPANDING, LayoutItem::EXPANDING);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->resize(200, 200);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_x = 0;
			Assert::AreEqual(expected_x, item1->getX());
			expected_x = item1->getX() + item1->getWidth();
			Assert::AreEqual(expected_x, item2->getX());
			expected_x = item2->getX() + item2->getWidth();
			Assert::AreEqual(expected_x, item3->getX());

			int expected_w = panel->getWidth() / 3;
			int expected_h = panel->getHeight();

			Assert::AreEqual<UINT>(expected_w, item1->getWidth());
			Assert::AreEqual<UINT>(expected_h, item1->getHeight());

			Assert::AreEqual<UINT>(expected_w, item2->getWidth());
			Assert::AreEqual<UINT>(expected_h, item2->getHeight());

			Assert::AreEqual<UINT>(expected_w, item3->getWidth());
			Assert::AreEqual<UINT>(expected_h, item3->getHeight());
		}
	};
}
