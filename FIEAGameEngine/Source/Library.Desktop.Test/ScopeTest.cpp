#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(ScopeTest)
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
			Scope a;
			Assert::IsTrue(a.GetParent() == nullptr);

			Scope b(10);
			Assert::IsTrue(b.GetParent() == nullptr);
		}

		TEST_METHOD(CopyConstructor)
		{
			Scope a;
			a.Append(testString1) = 10;
			a.AppendScope(testString2);

			Scope b(a);

			Assert::IsTrue(a == b);
		}

		TEST_METHOD(MoveCopyConstructor)
		{
			Scope a;
			a.Append(testString1) = 10;
			a.AppendScope(testString2);

			Scope b(a);

			Scope c = move(a);

			Assert::IsTrue(c == b);
		}

		TEST_METHOD(AssignmentOperator)
		{
			Scope a;
			a.Append(testString1) = 10;
			a.AppendScope(testString2);

			Scope b;
			b = a;

			Assert::IsTrue(a == b);

			a.Clear();
			a = b;

			Assert::IsTrue(a == b);
		}

		TEST_METHOD(MoveAssignmentConstructor)
		{
			Scope a;
			a.Append(testString1) = 10;
			a.AppendScope(testString2);

			Scope b(a);

			Scope c;
			c= move(a);

			Assert::IsTrue(c == b);

			Scope d = c.AppendScope(testString3);
			d = move(b);
		}

		TEST_METHOD(ScopeRTTI)
		{
			Scope a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("Scope"));
			Assert::IsTrue(r->Is(Scope::TypeIdClass()));
			Assert::IsTrue(r->As<Scope>() != nullptr);
			Assert::IsTrue(a.TypeName() == "Scope");
			Assert::IsTrue(a.TypeIdClass() == Scope::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == Scope::TypeIdClass());
			RTTI* r2 =r->QueryInterface(Scope::TypeIdClass());
			Assert::IsTrue(r2->Is("Scope"));
		}

		TEST_METHOD(Find)
		{
			Scope a;
			a.Append(testString1);

			const Scope* b = &a;

			Datum* pointer = a.Find(testString1);
			Assert::IsFalse(pointer == nullptr);

			const Datum* constPointer = b->Find(testString1);
			Assert::IsFalse(constPointer == nullptr);

			pointer = a.Find(testString2);
			constPointer = b->Find(testString2);

			Assert::IsTrue(pointer == nullptr);
			Assert::IsTrue(constPointer == nullptr);
		}

		TEST_METHOD(Search)
		{
			Scope a;
			a.Append(testString1);
			Scope*s;
			const Scope* constScope = &a;
			Datum* d = a.Search(testString1, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &a);

			const Datum* constD = constScope->Search(testString1, &s);
			Assert::IsFalse(constD == nullptr);
			Assert::IsTrue(s == &a);

			Scope b;
			b.Append(testString2);
			a.Adopt(b, testString3);

			d = b.Search(testString1, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &a);

			constD = b.Search(testString1, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &a);

			d = b.Search(testString3, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &a);

			constD = b.Search(testString1, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &a);

			d = b.Search(testString2, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &b);

			constD = b.Search(testString1, &s);
			Assert::IsFalse(d == nullptr);
			Assert::IsTrue(s == &a);
		}

		TEST_METHOD(Append)
		{
			Scope a;
			Datum& d = a.Append(testString1);
			d.PushBack(10);
			Assert::IsTrue(a[testString1] == d);

			d = a.Append(testString1);

			auto expression = [&d] {d.PushBack(10.0f); };
			Assert::ExpectException<exception>(expression);

			Datum& b = a.Append(testString2);
			b.PushBack(glm::vec4(10.0f));
			Assert::IsTrue(a[testString2] == b);
		}

		TEST_METHOD(AppendScope)
		{
			Scope a;

			Scope& b= a.AppendScope(testString1);
			Assert::IsTrue(a[testString1] == b);

			a.AppendScope(testString3);
			Datum& d= a.Append(testString2);
			d.SetType(DatumType::INTEGER);
			
			string testString = testString2;
			auto expression = [&a, &testString] {a.AppendScope(testString); };
			Assert::ExpectException<exception>(expression);

			Scope c;
			c.AppendScope(testString2);
			c.AppendScope(testString2);
			c.AppendScope(testString3);
		}

		TEST_METHOD(Adopt)
		{
			Scope a;
			Scope b;
			Datum& d = a.Append(testString1);
			d = 10;
			Assert::IsTrue(a[testString1] == d);

			string testString = testString1;
			auto expression = [&a, &b, &testString] {a.Adopt(b, testString); };
			Assert::ExpectException<exception>(expression);

			Scope c;
			c.Append(testString4);
			a.Adopt(c, testString4);
			Assert::IsTrue(a[testString4] == c);
			b.Append(testString2);
			a.Adopt(b, testString2);

			Assert::IsTrue(&a == b.GetParent());

			Scope& s = c.AppendScope(testString3);

			a.Adopt(s, testString4);
			auto expression2 = [&a, testString] {a.Adopt(a, testString); };
			Assert::ExpectException<exception>(expression);
		}

		TEST_METHOD(GetParent)
		{
			Scope a;
			const Scope*c = &a;
			Assert::IsTrue(a.GetParent() == nullptr);
			Assert::IsTrue(c->GetParent() == nullptr);

			Scope b;
			const Scope*d = &b;
			a.Adopt(b, testString3);
			Assert::IsTrue(b.GetParent() == &a);
			Assert::IsTrue(d->GetParent() == &a);
		}

		TEST_METHOD(IndexBracketOperator)
		{
			Scope a;
			const Scope*s = &a;
			s;
			Datum& b = a.Append(testString1);
			b = 10;

			Datum& c = a.Append(testString2);
			c = 10.0f;

			Assert::IsTrue(a[0] == b);
			Assert::IsTrue(a[1] == c);	

			Assert::IsTrue(s->operator[](0) == b);
			Assert::IsTrue(s->operator[](1) == c);

			auto expression = [&a] {a[2]; };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&s] {s->operator[](2); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(StringBracketOperator)
		{
			Scope a;
			Datum& d = a[testString1];
			d.PushBack(10);

			d = a[testString1];

			auto expression = [&d] {d.PushBack(10.0f); };
			Assert::ExpectException<exception>(expression);

			d = a[testString2];
			d.PushBack(glm::vec4(10.0f));

			const Scope* s = &a;

			d = s->operator[](testString2);
			d.PushBack(glm::vec4(20.0f));

			d = s->operator[](testString1);
			Assert::ExpectException<exception>(expression);

			string testString = testString3;
			auto expression2 = [&s, &testString] {s->operator[](testString); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(EqualityOperator)
		{
			Scope a;
			Scope b;

			Assert::IsTrue(a == b);

			a.Append(testString1);

			Assert::IsFalse(a == b);

			Datum& d =b.Append(testString1);

			Assert::IsTrue(a == b);

			d.PushBack(10);

			Assert::IsFalse(a == b);
		}

		TEST_METHOD(InequalityOperator)
		{
			Scope a;
			Scope b;

			Assert::IsFalse(a != b);

			a.Append(testString1);

			Assert::IsTrue(a != b);

			Datum& d = b.Append(testString1);

			Assert::IsFalse(a != b);

			d.PushBack(10);

			Assert::IsTrue(a != b);
		}

		
		TEST_METHOD(Clear)
		{
			Scope a;

			a.Append(testString1) = 10;
			a.Append(testString2) = 20;
			a.Append(testString3) = 30;

			a.Clear();

			Assert::IsTrue(a[testString1] != 10);
			Assert::IsTrue(a[testString2] != 20);
			Assert::IsTrue(a[testString3] != 30);

			Scope& b = a.AppendScope(testString1);
			Scope& c = a.AppendScope(testString2);
			Scope& d = a.AppendScope(testString3);

			a.Clear();

			Assert::IsTrue(a[testString1] != b);
			Assert::IsTrue(a[testString2] != c);
			Assert::IsTrue(a[testString3] != d);

			
		}
	private:
		static _CrtMemState sStartMemState;

		string testString1 = "Hello";
		string testString2 = "Hiya";
		string testString3 = "Hey";
		string testString4 = "Hi";
		
	};
	_CrtMemState ScopeTest::sStartMemState;
}