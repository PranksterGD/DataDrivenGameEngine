#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(AttributedTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined (_DEBUG)

			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			Attributed::ClearPrescribedAttributes();
#if defined (_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(DefaultConstructor)
		{
			AttributedFoo a;
			Assert::IsTrue(a.GetParent() == nullptr);

			Assert::IsTrue(a.IsPrescribedAttribute("this"));

			Assert::IsTrue(a.IsPrescribedAttribute("InternalInt"));
			Assert::IsTrue(a.IsPrescribedAttribute("InternalFloat"));
			Assert::IsTrue(a.IsPrescribedAttribute("InternalString"));
			Assert::IsTrue(a.IsPrescribedAttribute("InternalVector"));
			Assert::IsTrue(a.IsPrescribedAttribute("InternalMatrix"));
			Assert::IsTrue(a.IsPrescribedAttribute("InternalRTTI"));

			Assert::IsTrue(a.Find("InternalInt")->Size() == 1);
			Assert::IsTrue(a.Find("InternalFloat")->Size() == 1);
			Assert::IsTrue(a.Find("InternalString")->Size() == 1);
			Assert::IsTrue(a.Find("InternalVector")->Size() == 1);
			Assert::IsTrue(a.Find("InternalMatrix")->Size() == 1);
			Assert::IsTrue(a.Find("InternalRTTI")->Size() == 1);

			Assert::IsTrue(a.IsPrescribedAttribute("ExternalInt"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalRTTI"));

			Assert::IsTrue(a.Find("ExternalInt")->Size() == 1);
			Assert::IsTrue(a.Find("ExternalFloat")->Size() == 1);
			Assert::IsTrue(a.Find("ExternalString")->Size() == 1);
			Assert::IsTrue(a.Find("ExternalVector")->Size() == 1);
			Assert::IsTrue(a.Find("ExternalMatrix")->Size() == 1);
			Assert::IsTrue(a.Find("ExternalRTTI")->Size() == 1);

			Assert::IsTrue(a.IsPrescribedAttribute("ExternalIntArray"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(a.IsPrescribedAttribute("ExternalRTTIArray"));

			Assert::IsTrue(a.Find("ExternalIntArray")->Size() == 5);
			Assert::IsTrue(a.Find("ExternalFloatArray")->Size() == 5);
			Assert::IsTrue(a.Find("ExternalStringArray")->Size() == 5);
			Assert::IsTrue(a.Find("ExternalVectorArray")->Size() == 5);
			Assert::IsTrue(a.Find("ExternalMatrixArray")->Size() == 5);
			Assert::IsTrue(a.Find("ExternalRTTIArray")->Size() == 5);

			Assert::IsTrue(a.IsPrescribedAttribute("ScopeAttribute"));
			Assert::IsTrue(a["ScopeAttribute"].Get<Scope*&>()->GetParent() == &a);
			Assert::IsFalse(a.IsPrescribedAttribute(testString1));

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(ExternalAssignment)
		{
			AttributedFoo a;
			Datum* d = a.Find("ExternalFloat");
			Assert::AreEqual(1U, d->Size());
			Assert::IsTrue(a["ExternalIntArray"].Get<int32_t&>() == a.mIntData);

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(CopyConstructor)
		{
			AttributedFoo a;
			a.AppendAuxiliaryAttribute(testString1);

			Attributed c;
			Assert::IsTrue(c["this"] == &c);
			AttributedFoo b(a);

			Assert::IsTrue(b == a);
			Assert::IsTrue(b["this"] != a["this"]);
			Assert::IsTrue(b["this"] == &b);
			Assert::IsTrue(b["this"].Size() == 1);
			Assert::IsTrue(b.IsPrescribedAttribute("this"));

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveCopyConstructor)
		{
			AttributedFoo a;
			Assert::IsTrue(&a["ExternalInt"].Get<int32_t&>() == &a.mIntData);
			a.mIntData = 5;
			Assert::IsTrue(&a["ExternalInt"].Get<int32_t&>() == &a.mIntData);
			a.AppendAuxiliaryAttribute(testString1);

			AttributedFoo b(a);
			Assert::IsTrue(b["ExternalInt"].Get<int32_t&>() == b.mIntData);
			AttributedFoo c = move(a);

			Assert::IsTrue(b == c);
			Assert::IsTrue(b["this"] != c["this"]);

			Assert::IsTrue(&c["ExternalInt"].Get<int32_t&>() == &c.mIntData);

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(AssignmentOperator)
		{
			AttributedFoo a;
			a.AppendAuxiliaryAttribute(testString1);

			AttributedFoo b;

			b = a;

			Assert::IsTrue(b == a);
			Assert::IsTrue(b["this"] != a["this"]);

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			AttributedFoo a;
			Assert::IsTrue(&a["ExternalInt"].Get<int32_t&>() == &a.mIntData);
			a.mIntData = 5;
			Assert::IsTrue(&a["ExternalInt"].Get<int32_t&>() == &a.mIntData);
			a.AppendAuxiliaryAttribute(testString1);

			AttributedFoo b(a);
			Assert::IsTrue(b["ExternalInt"].Get<int32_t&>() == b.mIntData);
			
			AttributedFoo c;
			c = a;

			Assert::IsTrue(b == c);
			Assert::IsTrue(b["this"] != c["this"]);

			Assert::IsTrue(&c["ExternalInt"].Get<int32_t&>() == &c.mIntData);

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(IsPrescribedAttribute)
		{
			AttributedFoo a;

			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsFalse(a.IsPrescribedAttribute(testString1));

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(IsAttribute)
		{
			AttributedFoo a;
			Assert::IsTrue(a.IsAttribute("ExternalInt"));
			Assert::IsFalse(a.IsAttribute(testString1));

			a.AppendAuxiliaryAttribute(testString1);
			Assert::IsTrue(a.IsAttribute(testString1));

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(IsAuxiliaryAttribute)
		{
			AttributedFoo a;
			Assert::IsFalse(a.IsAuxiliaryAttribute(testString1));
			a.AppendAuxiliaryAttribute(testString1);
			Assert::IsTrue(a.IsAuxiliaryAttribute(testString1));
			Assert::IsFalse(a.IsAuxiliaryAttribute("this"));

			AttributedFoo::ClearPrescribedAttributes();
		}


		TEST_METHOD(AppendAuxilaryAttribute)
		{
			AttributedFoo a;
			auto expression = [&a] {a.AppendAuxiliaryAttribute("this"); };
			Assert::ExpectException<exception>(expression);

			Assert::IsFalse(a.IsAuxiliaryAttribute(testString1));
			Datum& d = a.AppendAuxiliaryAttribute(testString1);
			Assert::IsTrue(a.IsAuxiliaryAttribute(testString1));
			Assert::IsFalse(a.IsAuxiliaryAttribute("this"));

			d = 10;
			Assert::IsTrue(a[testString1] == 10);

			AttributedFoo::ClearPrescribedAttributes();
		}

		TEST_METHOD(GetPrescribedAttributes)
		{
			AttributedFoo a;
			Vector<string> v = a.GetPrescribedAttributes();

			for (string s : v)
			{
				Assert::IsTrue(a.IsPrescribedAttribute(s));
			}

			AttributedFoo::ClearPrescribedAttributes();
		}

	private:
		static _CrtMemState sStartMemState;

		string testString1 = "Hello";
		string testString2 = "Hiya";
		string testString3 = "Hey";
		string testString4 = "Hi";

	};
	_CrtMemState AttributedTest::sStartMemState;
}