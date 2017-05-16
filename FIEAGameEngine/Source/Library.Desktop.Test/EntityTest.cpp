#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(EntityTest)
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
			Entity a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("Actions"));

			Assert::IsNull(a.GetSector());
			Assert::IsTrue(a.Name() == string());

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(CopyConstructor)
		{
			Sector sector;

			Entity entity("Number1");

			entity.SetSector(sector);

			Entity otherEntity(entity);

			Assert::IsTrue(otherEntity.Name() == entity.Name());
			Assert::IsTrue(otherEntity.GetSector() == entity.GetSector());

			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Actions"));

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(AssignmentOperator)
		{
			Sector sector;

			Entity entity("Number1");

			entity.SetSector(sector);

			Entity otherEntity;
			otherEntity = entity;

			Assert::IsTrue(otherEntity.Name() == entity.Name());
			Assert::IsTrue(otherEntity.GetSector() == entity.GetSector());

			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Actions"));

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveConstructor)
		{
			Sector sector;

			Entity entity("Number1");

			entity.SetSector(sector);

			Entity otherEntity(move(entity));

			Assert::IsTrue(otherEntity.Name() == "Number1");
			Assert::IsTrue(otherEntity.GetSector() == &sector);

			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(entity.Name() == string());
			Assert::IsNull(entity.GetSector());

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			Sector sector;

			Entity entity("Number1");

			entity.SetSector(sector);

			Entity otherEntity;
			otherEntity = move(entity);

			Assert::IsTrue(otherEntity.Name() == "Number1");
			Assert::IsTrue(otherEntity.GetSector() == &sector);

			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherEntity.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(entity.Name() == string());
			Assert::IsNull(entity.GetSector());

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(Name)
		{
			Entity a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const Entity* b = &a;

			Assert::IsTrue(b->Name() == "Thing");

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(SetName)
		{
			Entity a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(SetSector)
		{
			Sector s;

			Entity e;

			e.SetSector(s);

			Assert::IsTrue(e.GetSector() == &s);

			Assert::IsTrue(s.Entities().Get<Scope*&>() == &e);
			s.ClearPrescribedAttributes();
			e.ClearPrescribedAttributes();
		}

		TEST_METHOD(GetSector)
		{
			Sector s;
			Entity e;

			Assert::IsNull(e.GetSector());
			
			e.SetSector(s);

			const Entity* e2 = &e;

			Assert::IsTrue(e.GetSector() == &s);
			Assert::IsTrue(e2->GetSector() == &s);

			e.ClearPrescribedAttributes();
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			Entity e;

			e.Update(m);

			Assert::IsTrue(m.mCurrentEntity == &e);

			e.ClearPrescribedAttributes();

		}

		TEST_METHOD(EntityRTTI)
		{
			Entity a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("Entity"));
			Assert::IsTrue(r->Is(Entity::TypeIdClass()));
			Assert::IsTrue(r->As<Entity>() != nullptr);
			Assert::IsTrue(a.TypeName() == "Entity");
			Assert::IsTrue(a.TypeIdClass() == Entity::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == Entity::TypeIdClass());
			RTTI* r2 = r->QueryInterface(Entity::TypeIdClass());
			Assert::IsTrue(r2->Is("Entity"));

			a.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState EntityTest::sStartMemState;
}