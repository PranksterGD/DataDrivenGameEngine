#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	ConcreteFactory(Foo, RTTI);

	ConcreteFactory(Scope, RTTI);

	ConcreteFactory(AttributedFoo, Attributed);

	TEST_CLASS(FactorTest)
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
			Attributed::ClearPrescribedAttributes();
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");	
			}
#endif
		}

		TEST_METHOD(Create)
		{
			FooFactory a;
			RTTI* foo = Factory<RTTI>::Create("Foo");

			Assert::IsTrue(foo->Is(Foo::TypeIdClass()));

			ScopeFactory c;
			RTTI* scope = Factory<RTTI>::Create("Scope");

			Assert::IsTrue(scope->Is(Scope::TypeIdClass()));

			AttributedFooFactory b;
			Attributed* attributed = Factory<Attributed>::Create("AttributedFoo");
			
			Assert::IsTrue(attributed->Is(AttributedFoo::TypeIdClass()));

			RTTI* doo = Factory<RTTI>::Create("Doo");
			Assert::IsNull(doo);

			delete(foo);
			delete(attributed);
			delete(scope);
		}

		TEST_METHOD(ClassName)
		{
			FooFactory a;
			Assert::IsTrue(a.ClassName() == "Foo");

			AttributedFooFactory b;
			Assert::IsTrue(b.ClassName() == "AttributedFoo");

			ScopeFactory c;
			Assert::IsTrue(c.ClassName() == "Scope");
		}

		TEST_METHOD(TestBeginAndEnd)
		{
			FooFactory a;
			ScopeFactory c;

			Factory<RTTI>::Iterator it = Factory<RTTI>::begin();
			Assert::IsTrue(it->second == &a);

			++it;
			Assert::IsTrue(it->second == &c);

			++it;
			Assert::IsTrue(it == Factory<RTTI>::end());

			AttributedFooFactory b;

			Factory<Attributed>::Iterator it2 = Factory<Attributed>::begin();
			Assert::IsTrue(it2->second == &b);

			++it2;
			Assert::IsTrue(it2 == Factory<Attributed>::end());
		}

		TEST_METHOD(Find)
		{
			FooFactory a;
			ScopeFactory b;
			AttributedFooFactory c;

			Factory<RTTI>* RttiFactory = Factory<RTTI>::Find("Foo");
			Assert::IsTrue(RttiFactory == &a);

			Factory<RTTI>* scopeFactory = Factory<RTTI>::Find("Scope");
			Assert::IsTrue(scopeFactory == &b);

			Factory<Attributed>* attributedFooFactory = Factory<Attributed>::Find("AttributedFoo");
			Assert::IsTrue(attributedFooFactory == &c);

			Factory<RTTI>* DooFactory = Factory<RTTI>::Find("Doo");
			Assert::IsNull(DooFactory);
		}

		TEST_METHOD(Destructor)
		{
			FooFactory* a = new FooFactory();
			FooFactory* b = new FooFactory();

	
			Assert::IsTrue(Factory<RTTI>::begin() != Factory<RTTI>::end());

			delete(b);
	
			Assert::IsTrue(Factory<RTTI>::begin() != Factory<RTTI>::end());

			delete(a);

			Assert::IsTrue(Factory<RTTI>::begin() == Factory<RTTI>::end());
		
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState FactorTest::sStartMemState;
}