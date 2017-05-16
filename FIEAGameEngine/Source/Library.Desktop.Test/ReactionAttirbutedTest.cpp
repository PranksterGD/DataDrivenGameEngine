#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(ReactionAttirubtedTest)
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
			ReactionAttributed a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("Actions"));
			Assert::IsTrue(a.IsPrescribedAttribute("Subtype"));

			Assert::IsTrue(a.Name() == string());

		}

		TEST_METHOD(CopyConstructor)
		{
			ReactionAttributed reactionAttribute("RealList");

			ActionListFactory b;
			ReactionAttributedFactory a;
			reactionAttribute.CreateAction("ActionList", "ChildList");

			ReactionAttributed otherreactionAttribute(reactionAttribute);

			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("Actions"));
			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("Subtype"));

			Assert::IsTrue(otherreactionAttribute == reactionAttribute);
		}

		TEST_METHOD(AssignmentOperator)
		{
			ReactionAttributed reactionAttribute("RealList");

			ActionListFactory b;
			ReactionAttributedFactory a;
			reactionAttribute.CreateAction("ActionList", "ChildList");

			ReactionAttributed otherreactionAttribute;
			otherreactionAttribute =reactionAttribute;

			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("Actions"));
			Assert::IsTrue(otherreactionAttribute.IsPrescribedAttribute("Subtype"));

			Assert::IsTrue(otherreactionAttribute == reactionAttribute);

		}

		TEST_METHOD(MoveConstructor)
		{
			ReactionAttributed reactionAttribute("RealList");

			ActionListFactory a;
			reactionAttribute.CreateAction("ActionList", "ChildList");

			ReactionAttributed otherreactionAttribute(reactionAttribute);

			ReactionAttributed movedreactionAttribute(move(reactionAttribute));

			Assert::IsTrue(movedreactionAttribute.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedreactionAttribute.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedreactionAttribute.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(movedreactionAttribute == otherreactionAttribute);

			Assert::IsTrue(reactionAttribute.Name() == string());
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			ReactionAttributed reactionAttribute("RealList");

			ActionListFactory a;
			reactionAttribute.CreateAction("ActionList", "ChildList");

			ReactionAttributed otherreactionAttribute(reactionAttribute);

			ReactionAttributed movedreactionAttribute;
			movedreactionAttribute =move(reactionAttribute);

			Assert::IsTrue(movedreactionAttribute.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedreactionAttribute.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedreactionAttribute.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(movedreactionAttribute == otherreactionAttribute);

			Assert::IsTrue(reactionAttribute.Name() == string());
		}

		TEST_METHOD(Copy)
		{
			ReactionAttributed a;

			Scope* s = a.Copy();

			Assert::IsTrue(s->Is("ReactionAttributed"));

			delete s;
		}

		TEST_METHOD(Notify)
		{
			WorldState s;

			EventMessageAttributed message("OtherThing", &s);

			message.Append("Something");

			Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(message);

			ReactionAttributed a;

			Datum* subtypesDatum = a.Find("Subtype");

			subtypesDatum->PushBack("Thing");
			subtypesDatum->PushBack("OtherThing");

			Assert::IsNull(a.Find("Something"));
			Assert::IsTrue(s.mCurrentAction != &a);

			a.Notify(*event);

			Assert::IsNotNull(a.Find("Something"));
			Assert::IsTrue(s.mCurrentAction == &a);

			delete event;
		}

		TEST_METHOD(ReactionReactionAttributedRTTI)
		{
			ReactionAttributed a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("ReactionAttributed"));
			Assert::IsTrue(r->Is(ReactionAttributed::TypeIdClass()));
			Assert::IsTrue(r->As<ReactionAttributed>() != nullptr);
			Assert::IsTrue(a.TypeName() == "ReactionAttributed");
			Assert::IsTrue(a.TypeIdClass() == ReactionAttributed::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == ReactionAttributed::TypeIdClass());
			RTTI* r2 = r->QueryInterface(ReactionAttributed::TypeIdClass());
			Assert::IsTrue(r2->Is("ReactionAttributed"));

			a.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState ReactionAttirubtedTest::sStartMemState;
}