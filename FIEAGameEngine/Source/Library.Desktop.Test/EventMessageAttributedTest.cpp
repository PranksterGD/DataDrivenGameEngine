#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::chrono;
using namespace FieaGameEngine;
using namespace UnitTest;

namespace LibraryDesktopTest
{
	TEST_CLASS(EventMessageAttributedTest)
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
			EventMessageAttributed a;

			Assert::IsTrue(a.GetSubType() == "");
			Assert::IsTrue(a.GetWorldState() == nullptr);
			Assert::IsTrue(a.IsPrescribedAttribute(EventMessageAttributed::sSubtypeTag));

			WorldState s;

			EventMessageAttributed b("Thing", &s);

			Assert::IsTrue(b.GetSubType() == "Thing");
			Assert::IsTrue(b.GetWorldState() == &s);
		}

		TEST_METHOD(CopyConstrutor)
		{
			WorldState s;

			EventMessageAttributed a("Thing", &s);

			Assert::IsTrue(a.GetSubType() == "Thing");
			Assert::IsTrue(a.GetWorldState() == &s);

			EventMessageAttributed b = a;

			Assert::IsTrue(b == a);
			Assert::IsTrue(b.GetSubType() == a.GetSubType());
			Assert::IsTrue(b.GetWorldState() == a.GetWorldState());
		}

		TEST_METHOD(AssignmentOperator)
		{
			WorldState s;

			EventMessageAttributed a("Thing", &s);

			Assert::IsTrue(a.GetSubType() == "Thing");
			Assert::IsTrue(a.GetWorldState() == &s);

			EventMessageAttributed b;
			b= a;

			Assert::IsTrue(b == a);
			Assert::IsTrue(b.GetSubType() == a.GetSubType());
			Assert::IsTrue(b.GetWorldState() == a.GetWorldState());
		}

		TEST_METHOD(MoveCopyConstrutor)
		{
			WorldState s;

			EventMessageAttributed a("Thing", &s);

			Assert::IsTrue(a.GetSubType() == "Thing");
			Assert::IsTrue(a.GetWorldState() == &s);

			EventMessageAttributed b = a;

			EventMessageAttributed c = move(a);

			Assert::IsTrue(b == c);
			Assert::IsTrue(b.GetSubType() == c.GetSubType());
			Assert::IsTrue(b.GetWorldState() == c.GetWorldState());

			Assert::IsTrue(a.GetSubType() == "");
			Assert::IsTrue(a.GetWorldState() == nullptr);
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			WorldState s;

			EventMessageAttributed a("Thing", &s);

			Assert::IsTrue(a.GetSubType() == "Thing");
			Assert::IsTrue(a.GetWorldState() == &s);

			EventMessageAttributed b = a;

			EventMessageAttributed c;
			c= move(a);

			Assert::IsTrue(b == c);
			Assert::IsTrue(b.GetSubType() == c.GetSubType());
			Assert::IsTrue(b.GetWorldState() == c.GetWorldState());

			Assert::IsTrue(a.GetSubType() == "");
			Assert::IsTrue(a.GetWorldState() == nullptr);
		}

		TEST_METHOD(GetSetSubtype)
		{
			EventMessageAttributed a;
			
			Assert::IsTrue(a.GetSubType() == "");

			a.SetSubType("Thing");
			
			Assert::IsTrue(a.GetSubType() == "Thing");
		}

		TEST_METHOD(GetSetWorldState)
		{
			EventMessageAttributed a;

			Assert::IsTrue(a.GetWorldState() == nullptr);

			WorldState s;

			a.SetWorldState(s);

			Assert::IsTrue(a.GetWorldState() == &s);
		}

		TEST_METHOD(Copy)
		{
			EventMessageAttributed a;

			Scope* s = a.Copy();

			Assert::IsTrue(s->Is("EventMessageAttributed"));

			delete s;
		}

		TEST_METHOD(EventMessageAttributedRTTI)
		{
			EventMessageAttributed a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("EventMessageAttributed"));
			Assert::IsTrue(r->Is(EventMessageAttributed::TypeIdClass()));
			Assert::IsTrue(r->As<EventMessageAttributed>() != nullptr);
			Assert::IsTrue(a.TypeName() == "EventMessageAttributed");
			Assert::IsTrue(a.TypeIdClass() == EventMessageAttributed::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == EventMessageAttributed::TypeIdClass());
			RTTI* r2 = r->QueryInterface(EventMessageAttributed::TypeIdClass());
			Assert::IsTrue(r2->Is("EventMessageAttributed"));

			a.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState EventMessageAttributedTest::sStartMemState;
}