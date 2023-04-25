#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "LayoutControl.h"
#include "LayoutPanelVertical.h"
using namespace RthLayout;

#include <memory>
#include <stdlib.h>
#include <time.h>
#include <exception>

#define MAIN_W 400
#define MAIN_H 400

namespace RthLayoutUnitTests
{		
	void FormettedLog(const char* msg, ...)
	{
		va_list args;
		va_start(args, msg);

		char buffer[1024];
		vsnprintf(buffer, 1024, msg, args);

		va_end(args);

		Logger::WriteMessage(buffer);
	}

	TEST_CLASS(LayoutPanelVerticalTests)
	{
	public:
		
		TEST_CLASS_INITIALIZE(methodName) 
		{
			srand(time(NULL));
		}
		
		TEST_METHOD(LayoutTest_AllFixed)
		{
			LayoutPanelVertical* panel = new LayoutPanelVertical();
			std::auto_ptr<LayoutPanelVertical> ptr(panel);

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

			panel->resize(MAIN_W, MAIN_H);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_y = 0;
			Assert::AreEqual(expected_y, item1->getY());
			expected_y = item1->getY() + item1->getHeight();
			Assert::AreEqual(expected_y, item2->getY());
			expected_y = item2->getY() + item2->getHeight();
			Assert::AreEqual(expected_y, item3->getY());

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			Assert::AreEqual<UINT>(30, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			Assert::AreEqual<UINT>(66, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_OneExpanding_Horizontal)
		{
			LayoutPanelVertical* panel = new LayoutPanelVertical();
			std::auto_ptr<LayoutPanelVertical> ptr(panel);

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

			panel->resize(MAIN_W, MAIN_H);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_y = 0;
			Assert::AreEqual(expected_y, item1->getY());
			expected_y = item1->getY() + item1->getHeight();
			Assert::AreEqual(expected_y, item2->getY());
			expected_y = item2->getY() + item2->getHeight();
			Assert::AreEqual(expected_y, item3->getY());

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			int expected_w = panel->getWidth();
			Assert::AreEqual<UINT>(expected_w, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			Assert::AreEqual<UINT>(66, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_OneExpanding_Vertical)
		{
			LayoutPanelVertical* panel = new LayoutPanelVertical();
			std::auto_ptr<LayoutPanelVertical> ptr(panel);

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

			panel->resize(MAIN_W, MAIN_H);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_y = 0;
			Assert::AreEqual(expected_y, item1->getY());
			expected_y = item1->getY() + item1->getHeight();
			Assert::AreEqual(expected_y, item2->getY());
			expected_y = item2->getY() + item2->getHeight();
			Assert::AreEqual(expected_y, item3->getY());

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(87, item1->getHeight());

			Assert::AreEqual<UINT>(30, item2->getWidth());
			Assert::AreEqual<UINT>(40, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			int expected_h = panel->getHeight() - 87 - 40;
			Assert::AreEqual<UINT>(expected_h, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_AllExpanding_Vertical)
		{
			LayoutPanelVertical* panel = new LayoutPanelVertical();
			std::auto_ptr<LayoutPanelVertical> ptr(panel);

			LayoutControl* item1 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr1(item1);
			LayoutControl* item2 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr2(item2);
			LayoutControl* item3 = new LayoutControl();
			std::auto_ptr<LayoutControl> iptr3(item3);

			item1->setMinSize(25, 87);
			item2->setMinSize(30, 40);
			item3->setMinSize(11, 66);

			item1->setVerticalPolicy(LayoutItem::EXPANDING);
			item2->setVerticalPolicy(LayoutItem::EXPANDING);
			item3->setVerticalPolicy(LayoutItem::EXPANDING);

			panel->addItem(item1);
			panel->addItem(item2);
			panel->addItem(item3);

			panel->resize(MAIN_W, MAIN_H);
			panel->layout();

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_y = 0;
			Assert::AreEqual(expected_y, item1->getY());
			expected_y = item1->getY() + item1->getHeight();
			Assert::AreEqual(expected_y, item2->getY());
			expected_y = item2->getY() + item2->getHeight();
			Assert::AreEqual(expected_y, item3->getY());

			int expected_h = panel->getHeight() / 3;

			Assert::AreEqual<UINT>(25, item1->getWidth());
			Assert::AreEqual<UINT>(expected_h, item1->getHeight());

			Assert::AreEqual<UINT>(30, item2->getWidth());
			Assert::AreEqual<UINT>(expected_h, item2->getHeight());

			Assert::AreEqual<UINT>(11, item3->getWidth());
			Assert::AreEqual<UINT>(expected_h, item3->getHeight());
		}

		TEST_METHOD(LayoutTest_AllExpanding_Both)
		{
			LayoutPanelVertical* panel = new LayoutPanelVertical();
			std::auto_ptr<LayoutPanelVertical> ptr(panel);

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

			FormettedLog("item1 w = %d\n", item1->getWidth());
			FormettedLog("item1 h = %d\n", item1->getHeight());

			panel->resize(MAIN_W, MAIN_H);
			panel->layout();

			FormettedLog("item1 w = %d\n", item1->getWidth());
			FormettedLog("item1 h = %d\n", item1->getHeight());

			iptr1.release();
			iptr2.release();
			iptr3.release();

			int expected_y = 0;
			Assert::AreEqual(expected_y, item1->getY());
			expected_y = item1->getY() + item1->getHeight();
			Assert::AreEqual(expected_y, item2->getY());
			expected_y = item2->getY() + item2->getHeight();
			Assert::AreEqual(expected_y, item3->getY());

			UINT expected_w = panel->getWidth();
			UINT expected_h = panel->getHeight() / 3;

			FormettedLog("expected_w = %d\n", expected_w);
			FormettedLog("expected_h = %d\n", expected_h);

			Assert::AreEqual<UINT>(expected_w, item1->getWidth());
			Assert::AreEqual<UINT>(expected_h, item1->getHeight());

			Assert::AreEqual<UINT>(expected_w, item2->getWidth());
			Assert::AreEqual<UINT>(expected_h, item2->getHeight());

			Assert::AreEqual<UINT>(expected_w, item3->getWidth());
			Assert::AreEqual<UINT>(expected_h, item3->getHeight());
		}
	};
}
