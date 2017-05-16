#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;
using namespace std::chrono;

namespace LibraryDesktopTest
{
	TEST_CLASS(WorldParsingTest)
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

#pragma region ParseTesting

		TEST_METHOD(TestParsing)
		{
			XmlParseMaster master;


			EntityFactory f1;
			ActionListFactory f2;
			ActionListIfFactory f3;
			ActionCreateActionFactory f4;
			ActionDestroyActionFactory f5;
			ActionEventFactory f6;

			ReactionAttributedFactory f7;

			XmlParseHelperTable::SharedData data;
			master.SetSharedData(&data);

			XmlParseHelperTable tableHelper;
			master.AddHelper(tableHelper);

			XmlParseHelperInteger intHelper;
			master.AddHelper(intHelper);

			XmlParseHelperFloat floatHelper;
			master.AddHelper(floatHelper);

			XmlParseHelperString stringHelper;
			master.AddHelper(stringHelper);

			XmlParseHelperVector vectorHelper;
			master.AddHelper(vectorHelper);

			XmlParseHelperMatrix matrixHelper;
			master.AddHelper(matrixHelper);

			XmlParseHelperEntity entityHelper;
			master.AddHelper(entityHelper);

			XmlParseHelperSector sectorHelper;
			master.AddHelper(sectorHelper);

			XmlParseHelperWorld worldHelper;
			master.AddHelper(worldHelper);

			XmlParseHelperAction actionHelper;
			master.AddHelper(actionHelper);

			XmlparseHelperActionListIf ifActionHelper;
			master.AddHelper(ifActionHelper);

			XmlParseHelperReaction reactionHelper;
			master.AddHelper(reactionHelper);

			master.ParseFromFile("World.xml");

			Assert::IsTrue(data.Depth() == 0);

			Assert::IsTrue(data.mScope != nullptr);
			Assert::IsTrue(data.mScope->Is("World"));

			World* world = data.mScope->As<World>();
			Assert::IsTrue(world->Name() == "PaulzWorld");

			Datum sectorDatum = world->Sectors();

			Assert::IsTrue(sectorDatum.Get<Scope*&>()->Is("Sector"));
			
			Sector* sector = sectorDatum.Get<Scope*&>()->As<Sector>();
			Assert::IsTrue(sector->Name() == "AwesomeTown");

			Datum* reactionsDatum = sector->Find("Reactions");

			Assert::IsNotNull(reactionsDatum);
			Assert::IsTrue(reactionsDatum->Size() == 1U);
			Assert::IsTrue(reactionsDatum->Get<Scope*&>()->Is("ReactionAttributed"));

			ReactionAttributed* reaction = reactionsDatum->Get<Scope*&>()->As<ReactionAttributed>();

			Datum* subtypesDatum = reaction->Find("Subtype");

			Assert::IsNotNull(subtypesDatum);
			Assert::IsTrue(subtypesDatum->Size() == 1U);
			Assert::IsTrue(subtypesDatum->Get<string&>() == "Thing");

			reaction;

			Datum entityDatum = sector->Entities();

			Assert::IsTrue(entityDatum.Get<Scope*&>()->Is("Entity"));

			Entity* entity = entityDatum.Get<Scope*&>()->As<Entity>();
			Assert::IsTrue(entity->Name() == "Paul");

			Datum actionsDatum = entity->Actions();

			Assert::IsTrue(actionsDatum.Get<Scope*&>()->Is("Action"));
			Assert::IsTrue(actionsDatum.Get<Scope*&>()->Is("ActionList"));

			ActionList* list = actionsDatum.Get<Scope*&>()->As<ActionList>();

			Assert::AreEqual(list->Actions().Size(), 4U);

			WorldState state;
			world->Update(state);
			Assert::IsTrue(world->GetEventQueue().Size() == 1U);
			state.mGameTime.SetCurrentTime(state.mGameTime.CurrentTime() + milliseconds(20));
			world->Update(state);
			Assert::IsTrue(world->GetEventQueue().Size() == 0U);
		}

		TEST_METHOD(TestExceptions)
		{
			XmlParseMaster master;

			XmlParseHelperTable::SharedData data;
			master.SetSharedData(&data);

			XmlParseHelperEntity entityHelper;
			master.AddHelper(entityHelper);

			XmlParseHelperSector sectorHelper;
			master.AddHelper(sectorHelper);

			XmlParseHelperWorld worldHelper;
			master.AddHelper(worldHelper);

			const char* worldText = "<World name = 'PaulzWorld'> <World name ='Health'/> </World>";
			auto worldException = [&master, worldText] {master.Parse(worldText, sizeof(worldText)); };
			Assert::ExpectException<exception>(worldException);

			const char* sectorText = "<Sector name = 'AwesomeTown' />";
			auto sectorException = [&master, sectorText] {master.Parse(sectorText, sizeof(sectorText)); };
			Assert::ExpectException<exception>(sectorException);

			const char* entityText = "<Entity name = 'Paul' />";
			auto entityException = [&master, entityText] {master.Parse(entityText, sizeof(entityText)); };
			Assert::ExpectException<exception>(entityException);

			const char* actionText = "<Action class ='ActionEvent' name = 'Paul' />";
			auto actionException = [&master, actionText] {master.Parse(actionText, sizeof(actionText)); };
			Assert::ExpectException<exception>(actionException);

			const char* ifText = "<if />";
			auto ifException = [&master, ifText] {master.Parse(ifText, sizeof(ifText)); };
			Assert::ExpectException<exception>(ifException);

			const char* reactionText = "<Reaction class ='ReactionAttribute' name = 'Paul' />";
			auto reactionException = [&master, reactionText] {master.Parse(reactionText, sizeof(reactionText)); };
			Assert::ExpectException<exception>(reactionException);
		}

#pragma  endregion ParseTesting

#pragma region HelperTesting

		TEST_METHOD(TestClones)
		{
			IXmlParseHelper* helper;

			XmlParseHelperEntity entityHelper;
			helper = entityHelper.Clone();
			XmlParseHelperEntity* entityHelper2 = dynamic_cast<XmlParseHelperEntity*>(helper);
			Assert::IsTrue(entityHelper2 != nullptr);
			delete(helper);

			XmlParseHelperSector sectorHelper;
			helper = sectorHelper.Clone();
			XmlParseHelperSector* sectorHelper2 = dynamic_cast<XmlParseHelperSector*>(helper);
			Assert::IsTrue(sectorHelper2 != nullptr);
			delete(helper);

			XmlParseHelperWorld worldHelper;
			helper = worldHelper.Clone();
			XmlParseHelperWorld* worldHelper2 = dynamic_cast<XmlParseHelperWorld*>(helper);
			Assert::IsTrue(worldHelper2 != nullptr);
			delete(helper);
		}

#pragma endregion HelperTesting

	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState WorldParsingTest::sStartMemState;
}