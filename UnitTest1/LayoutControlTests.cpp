#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "LayoutControl.h"
using namespace RthLayout;

#include <memory>
#include <stdlib.h>
#include <time.h>

namespace RthLayoutUnitTests
{		
	TEST_CLASS(LayoutControlTests)
	{
	public:
		
		TEST_CLASS_INITIALIZE(methodName) 
		{
			srand(time(NULL));
		}

		TEST_METHOD(CTor1)
		{
			LayoutControl* item = new LayoutControl();
			std::auto_ptr<LayoutControl> ptr(item);

			Assert::IsNotNull(item);
		}

		TEST_METHOD(CTor2)
		{
			LayoutControl* item = new LayoutControl();
			std::auto_ptr<LayoutControl> ptr(item);
			
			//          expected, actual
			Assert::AreEqual(0, item->getX(), _T("Unexpected X."));
			Assert::AreEqual(0, item->getY(), _T("Unexpected Y."));

			Assert::AreEqual(0, (int)item->getMinWidth(), _T("Unexpected minimum width."));
			Assert::AreEqual(0, (int)item->getMinHeight(), _T("Unexpected minimum height."));

			Assert::AreEqual(0, (int)item->getWidth(), _T("Unexpected width."));
			Assert::AreEqual(0, (int)item->getHeight(), _T("Unexpected height."));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetPosition)
		{
			LayoutControl* item = new LayoutControl();
			std::auto_ptr<LayoutControl> ptr(item);

			int x = rand() % 1000 - 500;
			int y = rand() % 1000 - 500;

			item->setPosition(x, y);

			Assert::AreEqual(x, item->getX(), _T("Unexpected X."));
			Assert::AreEqual(y, item->getY(), _T("Unexpected Y."));
		}

		TEST_METHOD(Resize)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->resize(50, 60);

			Assert::AreEqual(true, result, _T("Setting minimum size failed!"));
			Assert::AreEqual(50, (int)item->getWidth(), _T("Unexpected width."));
			Assert::AreEqual(60, (int)item->getHeight(), _T("Unexpected height."));
		}

		TEST_METHOD(SetMinimumSize)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setMinSize(10, 10);

			Assert::AreEqual(true, result, _T("Setting minimum size failed!"));
			Assert::AreEqual(10, (int)item->getMinWidth(), _T("Unexpected minimum width."));
			Assert::AreEqual(10, (int)item->getMinHeight(), _T("Unexpected minimum height."));
		}

		TEST_METHOD(Resize_BelowMinimum)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setMinSize(20, 20);

			Assert::AreEqual(true, result, _T("Setting minimum size failed!"));

			result = item->resize(10, 10);

			Assert::AreEqual(false, result, _T("Resize below minimum size succeeded!"));

			Assert::AreEqual(20, (int)item->getWidth(), _T("Unexpected width."));
			Assert::AreEqual(20, (int)item->getHeight(), _T("Unexpected height."));
		}

		TEST_METHOD(Resize_NegativeWidth)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->resize(-10, 10);

			Assert::AreEqual(false, result, _T("Setting negative width succeeded!"));
		}
		
		TEST_METHOD(Resize_NegativeHeight)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->resize(10, -10);

			Assert::AreEqual(false, result, _T("Setting negative height succeeded!"));
		}

		TEST_METHOD(SetMinimumSize_NegativeWidth)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->resize(-10, 10);

			Assert::AreEqual(false, result, _T("Setting negative minimum width succeeded!"));
		}

		TEST_METHOD(SetMinimumSize_NegativeHeight)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->resize(10, -10);

			Assert::AreEqual(false, result, _T("Setting negative minimum height succeeded!"));
		}

		TEST_METHOD(SetLayoutPolicy)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setPolicy(LayoutItem::EXPANDING, LayoutItem::PREFFERED);

			Assert::AreEqual(true, result, _T("Setting policies failed!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::PREFFERED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicy_HorizontalInvalid)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setPolicy((LayoutItem::LayoutPolicy)1, LayoutItem::PREFFERED);

			Assert::AreEqual(false, result, _T("Setting invalid horizontal policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}
		
		TEST_METHOD(SetLayoutPolicy_VerticalInvalid)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setPolicy(LayoutItem::PREFFERED, (LayoutItem::LayoutPolicy)1);

			Assert::AreEqual(false, result, _T("Setting invalid vertical policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicy_BothInvalid)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setPolicy((LayoutItem::LayoutPolicy)1, (LayoutItem::LayoutPolicy)1);

			Assert::AreEqual(false, result, _T("Setting invalid policies succeeded!"));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyHorizontal)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setHorizontalPolicy(LayoutItem::EXPANDING);

			Assert::AreEqual(true, result, _T("Setting horizontal policy failed!"));

			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyHorizontal_Invalid)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setHorizontalPolicy((LayoutItem::LayoutPolicy)-50);

			Assert::AreEqual(false, result, _T("Setting invalid horizontal policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyVertical)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setVerticalPolicy(LayoutItem::EXPANDING);

			Assert::AreEqual(true, result, _T("Setting vertical policy failed!"));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::EXPANDING, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(SetLayoutPolicyVertical_Invalid)
		{
			LayoutControl* item = new LayoutControl();
			
			bool result = item->setVerticalPolicy((LayoutItem::LayoutPolicy)-50);

			Assert::AreEqual(false, result, _T("Setting invalid vertical policy succeeded!"));

			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getHorizontalPolicy(), 
				_T("Unexpected horizontal policy."));
			Assert::AreEqual((int)LayoutItem::FIXED, (int)item->getVerticalPolicy(), 
				_T("Unexpected vertical policy."));
		}

		TEST_METHOD(AttachControl)
		{
			LayoutControl* item = new LayoutControl();
			std::auto_ptr<LayoutControl> ptr1(item);

			CButton* control = new CButton();
			std::auto_ptr<CButton> ptr2(control);

			item->attachWnd(control);

			CWnd* check = item->getWnd();

			Assert::IsNotNull(check);
			Assert::IsTrue(control == check);
		}

		TEST_METHOD(DetachControl)
		{
			LayoutControl* item = new LayoutControl();
			std::auto_ptr<LayoutControl> ptr1(item);

			CButton* control = new CButton();
			std::auto_ptr<CButton> ptr2(control);

			item->attachWnd(control);

			CWnd* check = item->getWnd();

			Assert::IsNotNull(check);
			Assert::IsTrue(control == check);

			item->detachWnd();

			check = item->getWnd();

			Assert::IsNull(check);
		}
	};
}
