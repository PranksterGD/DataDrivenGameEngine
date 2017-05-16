#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(DatumTest)
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
			Datum a;
		}

		TEST_METHOD(CopyConstructor)
		{

			Datum a;
			a = &fooTestVariable1;
			Datum b = a;
			Assert::IsTrue(b == a);

			a.Clear();

			RTTI* f = fooTestVariableArray1;
			a.SetStorage(&f, 3);
			Datum c = a;
			Assert::IsTrue(a == c);
		}

		TEST_METHOD(MoveCopyConstructor)
		{
			Datum a;
			a = &fooTestVariable1;
			Datum b = a;
			Datum c = move(a);
			Assert::IsTrue(b == c);
			Assert::IsTrue(a.Size() == 0);

			b.Clear();

			RTTI* f = fooTestVariableArray1;
			b.SetStorage(&f, 3);
			a = b;
			Datum d = move(a);
			Assert::IsTrue(d == b);
		}

		TEST_METHOD(DatumAssignment)
		{
			Datum a, b;

			a = &fooTestVariable1;
			b = &fooTestVariable2;
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();

			RTTI* f = fooTestVariableArray1;
			RTTI* f2 = fooTestVariableArray2;
			a.SetStorage(&f, 3);
			b = &fooTestVariable2;
			b = a;
			Assert::IsTrue(a == b);

			b.Clear();
			a.Clear();

			b.SetStorage(&f, 3);
			a = &fooTestVariable1;
			b = a;
			Assert::IsTrue(a == b);

			b.Clear();
			a.Clear();

			b.SetStorage(&f2, 3);
			a.SetStorage(&f, 3);
			b = a;
			Assert::IsTrue(a == b);

			b.Clear();
			a.Clear();

			a.PushBack(10);
			a.PushBack(20);
			a.PushBack(30);

			b = a;
			Assert::IsTrue(b == a);

			a.Clear();
			b.Clear();

			a.PushBack(10.0f);
			a.PushBack(20.0f);
			a.PushBack(30.0f);
			
			b = a;
			Assert::IsTrue(b == a);

			a.Clear();
			b.Clear();

			a.PushBack("hello");
			a.PushBack("hi");
			a.PushBack("bye");

			b = a;
			Assert::IsTrue(b == a);

			a.Clear();
			b.Clear();

			a.PushBack(glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			a.PushBack(glm::vec4(30.0f));

			b = a;
			Assert::IsTrue(b == a);

			a.Clear();
			b.Clear();

			a.PushBack(glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0f));
			a.PushBack(glm::mat4(30.0f));

			b = a;
			Assert::IsTrue(b == a);

			a.Clear();
			b.Clear();

			a.PushBack(&fooTestVariable1);
			a.PushBack(&fooTestVariable2);
			a.PushBack(&fooTestVariable3);

			b = a;
			Assert::IsTrue(b == a);

			a.Clear();
			b.Clear();

			Scope s1;
			Scope s2;
			Scope s3;

			a.PushBack(&s1);
			a.PushBack(&s2);
			a.PushBack(&s3);

			b = a;
			Assert::IsTrue(b == a);
		}

		TEST_METHOD(IntAssignment)
		{
			Datum a;
			a = 10;
			Assert::IsTrue(a == 10);
			a = 20;
			Assert::IsTrue(a == 20);
			Datum b;
			b.SetType(DatumType::STRING);
			auto typeException = [&b] {b = 20; };
			Assert::ExpectException<exception>(typeException);
		}

		TEST_METHOD(FloatAssigment)
		{
			Datum a;
			a = 10.0f;
			Assert::IsTrue(a == 10.0f);
			a = 20.0f;
			Assert::IsTrue(a == 20.0f);
			Datum b;
			b.SetType(DatumType::INTEGER);
			auto typeException = [&b] {b = 20.0f; };
			Assert::ExpectException<exception>(typeException);
		}

		TEST_METHOD(StringAssigment)
		{
			Datum a;
			a = "Hello";
			Assert::IsTrue(a == "Hello");
			a = "Hai";
			Assert::IsTrue(a == "Hai");
			Datum b;
			b.SetType(DatumType::INTEGER);
			auto typeException = [&b] {b = "Hiya"; };
			Assert::ExpectException<exception>(typeException);
		}

		TEST_METHOD(VectorAssignment)
		{
			Datum a;
			a = glm::vec4();
			Assert::IsTrue(a == glm::vec4());
			a = glm::vec4(10.0f);
			Assert::IsTrue(a == glm::vec4(10.0f));
			Datum b;
			b.SetType(DatumType::INTEGER);
			auto typeException = [&b] {b = glm::vec4(); };
			Assert::ExpectException<exception>(typeException);
		}

		TEST_METHOD(MatrixAssignment)
		{
			Datum a;
			a = glm::mat4();
			Assert::IsTrue(a == glm::mat4());
			a = glm::mat4(10.0f);
			Assert::IsTrue(a == glm::mat4(10.0f));
			Datum b;
			b.SetType(DatumType::INTEGER);
			auto typeException = [&b] {b = glm::mat4(); };
			Assert::ExpectException<exception>(typeException);
		}

		TEST_METHOD(PointerAssignment)
		{
			Datum a;
			a = &fooTestVariable1;
			Assert::IsTrue(a == &fooTestVariable1);
			a = &fooTestVariable2;
			Assert::IsTrue(a == &fooTestVariable2);
			Datum b;
			Foo f;
			b.SetType(DatumType::INTEGER);
			auto typeException = [&b, &f] {b = & f; };
			Assert::ExpectException<exception>(typeException);
		}

		TEST_METHOD(Destructor)
		{
			Datum a;
			a = &fooTestVariable1;
			a.PushBack(&fooTestVariable2);
			a.PushBack(&fooTestVariable3);
		}

		TEST_METHOD(Type)
		{
			Datum a;
			Assert::IsTrue(a.Type() == DatumType::INVALID);

			a.SetType(DatumType::INTEGER);
			Assert::IsTrue(a.Type() == DatumType::INTEGER);

			a.Clear();
			a.SetType(DatumType::FLOAT);
			Assert::IsTrue(a.Type() == DatumType::FLOAT);

			a.Clear();
			a.SetType(DatumType::STRING);
			Assert::IsTrue(a.Type() == DatumType::STRING);

			a.Clear();
			a.SetType(DatumType::VECTOR);
			Assert::IsTrue(a.Type() == DatumType::VECTOR);

			a.Clear();
			a.SetType(DatumType::MATRIX);
			Assert::IsTrue(a.Type() == DatumType::MATRIX);

			a.Clear();
			a.SetType(DatumType::POINTER);
			Assert::IsTrue(a.Type() == DatumType::POINTER);
		}

		TEST_METHOD(SetType)
		{
			Datum a;
			a.SetType(DatumType::INTEGER);
			Assert::IsTrue(a.Type() == DatumType::INTEGER);
			
			auto typeException = [&a] {a.SetType(DatumType::FLOAT); };
			Assert::ExpectException<exception>(typeException);

			Datum b;
			b.SetType(DatumType::FLOAT);
			Assert::IsTrue(b.Type() == DatumType::FLOAT);

			Datum c;
			c.SetType(DatumType::STRING);
			Assert::IsTrue(c.Type() == DatumType::STRING);

			Datum d;
			d.SetType(DatumType::VECTOR);
			Assert::IsTrue(d.Type() == DatumType::VECTOR);

			Datum e;
			e.SetType(DatumType::MATRIX);
			Assert::IsTrue(e.Type() == DatumType::MATRIX);

			Datum f;
			f.SetType(DatumType::POINTER);
			Assert::IsTrue(f.Type() == DatumType::POINTER);
		}

		TEST_METHOD(Size)
		{
			Datum a;
			Assert::IsTrue(a.Size() == 0);

			a.PushBack(10);
			Assert::IsTrue(a.Size() == 1);
		}

		TEST_METHOD(Capacity)
		{
			Datum a;
			Assert::IsTrue(a.Capacity() == 0);

			a = 10;
			a.Reserve(5);
			Assert::IsTrue(a.Capacity() == 5);
		}

		TEST_METHOD(Resize)
		{
			Datum a;
			auto typeException = [&a] {a.ReSize(1); };
			Assert::ExpectException<exception>(typeException);

			a.SetStorage(intTestVariableArray1, 3);
			auto typeException2 = [&a] {a.ReSize(1); };
			Assert::ExpectException<exception>(typeException2);

			a.Clear();

			a = 10;
			a.ReSize(5);
			Assert::IsTrue(a.Size() == 5);
			a.ReSize(4);
			Assert::IsTrue(a.Size() == 4);

			a.Clear();

			a = 10.0f;
			a.ReSize(5);
			Assert::IsTrue(a.Size() == 5);

			a.Clear();

			a = "Hello";
			a.ReSize(5);
			Assert::IsTrue(a.Size() == 5);

			a.Clear();

			a = glm::vec4(10.0f);
			a.ReSize(5);
			Assert::IsTrue(a.Size() == 5);

			a.Clear();

			a = glm::mat4(10.0f);
			a.ReSize(5);
			Assert::IsTrue(a.Size() == 5);

			a.Clear();

			a = &fooTestVariable3;
			a.ReSize(5);
			Assert::IsTrue(a.Size() == 5);

			a.Clear();

			a.PushBack(10);
			a.PushBack(20);
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);

			a.Clear();

			a.PushBack(10.0f);
			a.PushBack(20.0f);
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);

			a.Clear();

			a.PushBack("hello");
			a.PushBack("bye");
			a.PushBack("goodbye");
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);

			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);

			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0f));
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);

			a.Clear();

			a.PushBack(&fooTestVariable3);
			a.PushBack(&fooTestVariable1);
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);

			a.Clear();
			
			Scope s1;
			Scope s2;
			a.PushBack(&s1);
			a.PushBack(&s2);
			a.ReSize(1);
			Assert::IsTrue(a.Size() == 1);
		}

		TEST_METHOD(Clear)
		{
			Datum a;

			a.PushBack(10);
			a.PushBack(20);
			a.Clear();

			a.PushBack(10.0f);
			a.PushBack(20.0f);
			a.Clear();

			a.PushBack("hello");
			a.PushBack("bye");
			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0f));
			a.Clear();

			a.PushBack(&fooTestVariable3);
			a.PushBack(&fooTestVariable1);
			a.Clear();
		}

		TEST_METHOD(IntSetStorage)
		{
			Datum a;
			a.PushBack(10);
			a.SetStorage(intTestVariableArray1, numberOfTestElements);

			Datum b;
			b.SetType(DatumType::FLOAT);
			int array[3] = { 10,20,30 };
			auto expression = [&b, &array] {b.SetStorage(array, numberOfTestElements); };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&b, &array]{ b.SetStorage(array, 0); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(FloatSetStorage)
		{
			Datum a;
			float array[3] = { 10.0f, 20.0f, 30.0f };
			int32_t intArray[3] = { 10,20,30 };
			a.PushBack(10.0f);
			a.SetStorage(array, numberOfTestElements);

			Datum b;
			b.SetType(DatumType::FLOAT);

			auto expression = [&b, &intArray]{ b.SetStorage(intArray, numberOfTestElements); };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&b, &array]{ b.SetStorage(array, 0); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(StringSetStorage)
		{
			Datum a;
			string array[3] = {"Hello", "Hi" , "Bye"};
			int32_t intArray[3] = { 10,20,30 };
			a.PushBack("qwerty");
			a.SetStorage(array, numberOfTestElements);

			Datum b;
			b.SetType(DatumType::STRING);

			auto expression = [&b, &intArray] { b.SetStorage(intArray, numberOfTestElements); };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&b, &array]{ b.SetStorage(array, 0); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(VectorSetStorage)
		{
			Datum a;
			glm::vec4 array[3] = { glm::vec4(10.0f), glm::vec4(20.0f), glm::vec4(30.0f)};
			int32_t intArray[3] = { 10,20,30 };
			a.PushBack(glm::vec4(40.0f));
			a.SetStorage(array, numberOfTestElements);

			Datum b;
			b.SetType(DatumType::VECTOR);

			auto expression = [&b, &intArray] { b.SetStorage(intArray, numberOfTestElements); };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&b, &array]{ b.SetStorage(array, 0); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(MatrixSetStorage)
		{
			Datum a;
			glm::mat4 array[3] = { glm::mat4(10.0f), glm::mat4(20.0f), glm::mat4(30.0f) };
			int32_t intArray[3] = { 10,20,30 };
			a.PushBack(glm::mat4(40.0f));
			a.SetStorage(array, numberOfTestElements);

			Datum b;
			b.SetType(DatumType::MATRIX);

			auto expression = [&b, &intArray] { b.SetStorage(intArray, numberOfTestElements); };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&b, &array]{ b.SetStorage(array, 0); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(PointerSetStorage)
		{
			Datum a;
			RTTI* array[3] = { &fooTestVariable1, &fooTestVariable2, &fooTestVariable3 };
			int32_t intArray[3] = { 10,20,30 };
			a.PushBack(&fooTestVariable3);
			a.SetStorage(array, numberOfTestElements);

			Datum b;
			b.SetType(DatumType::POINTER);

			auto expression = [&b, &intArray] { b.SetStorage(intArray, numberOfTestElements); };
			Assert::ExpectException<exception>(expression);

			auto expression2 = [&b, &array] { b.SetStorage(array, 0); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(DatumEquality)
		{
			Datum a;
			Datum b;
			a.SetStorage(intTestVariableArray1, numberOfTestElements);
			Assert::IsFalse(a == b);

			a.Clear();

			a.PushBack(10);
			a.PushBack(20);
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();

			a.PushBack(10.0f);
			a.PushBack(20.0f);
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();

			a.PushBack("Hello");
			a.PushBack("Hi");
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0));
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();

			a.PushBack(&fooTestVariable3);
			a.PushBack(&fooTestVariable2);
			b = a;
			Assert::IsTrue(a == b);

			a.Clear();

			Scope s1;
			Scope s2;

			s1.Append("Hello");
			s2.AppendScope("Hiya");
			a.PushBack(&s1);
			a.PushBack(&s2);
			b = a;
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(IntEquality)
		{
			Datum a;
			a.PushBack(10);
			Assert::IsTrue(a == 10);
		}

		TEST_METHOD(FloatEquality)
		{
			Datum a;
			a.PushBack(10.0f);
			Assert::IsTrue(a == 10.0f);
		}

		TEST_METHOD(StringEquality)
		{
			Datum a;
			a.PushBack("Hello");
			Assert::IsTrue(a == "Hello");
		}

		TEST_METHOD(VectorEquality)
		{
			Datum a;
			a.PushBack(glm::vec4(10.0f));
			Assert::IsTrue(a == glm::vec4(10.0f));
		}

		TEST_METHOD(MatrixEquality)
		{
			Datum a;
			a.PushBack(glm::mat4(10.0f));
			Assert::IsTrue(a == glm::mat4(10.0f));
		}

		TEST_METHOD(PointerEquality)
		{
			Datum a;
			a.PushBack(&fooTestVariable3);
			Assert::IsTrue(a == &fooTestVariable3);
		}

		TEST_METHOD(ScopeEquality)
		{
			Datum a;
			Scope b;
			a.PushBack(&b);
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(DatumIneqaulity)
		{
			Datum a;
			Datum b;
			a.SetStorage(intTestVariableArray1, numberOfTestElements);
			Assert::IsTrue(a != b);

			a.Clear();

			a.PushBack(10);
			a.PushBack(20);
			b = a;
			Assert::IsFalse(a != b);

			a.Clear();

			a.PushBack(10.0f);
			a.PushBack(20.0f);
			b = a;
			Assert::IsFalse(a != b);

			a.Clear();

			a.PushBack("Hello");
			a.PushBack("Hi");
			b = a;
			Assert::IsFalse(a != b);

			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			b = a;
			Assert::IsFalse(a != b);

			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0));
			b = a;
			Assert::IsFalse(a != b);

			a.Clear();

			a.PushBack(&fooTestVariable3);
			a.PushBack(&fooTestVariable2);
			b = a;
			Assert::IsFalse(a != b);
		}

		TEST_METHOD(IntInequality)
		{
			Datum a;
			a.PushBack(10);
			Assert::IsFalse(a != 10);
		}

		TEST_METHOD(FloatInequality)
		{
			Datum a;
			a.PushBack(10.0f);
			Assert::IsFalse(a != 10.0f);
		}

		TEST_METHOD(StringInequality)
		{
			Datum a;
			a.PushBack("Hello");
			Assert::IsFalse(a != "Hello");
		}

		TEST_METHOD(VectorInequality)
		{
			Datum a;
			a.PushBack(glm::vec4(10.0f));
			Assert::IsFalse(a != glm::vec4(10.0f));
		}

		TEST_METHOD(MatrixInequality)
		{
			Datum a;
			a.PushBack(glm::mat4(10.0f));
			Assert::IsFalse(a != glm::mat4(10.0f));
		}

		TEST_METHOD(PointerInequality)
		{
			Datum a;
			a.PushBack(&fooTestVariable3);
			Assert::IsFalse(a != &fooTestVariable3);
		}

		TEST_METHOD(ScopeInequality)
		{
			Datum a;
			Scope b;
			a.PushBack(&b);
			Assert::IsFalse(a != b);
		}

		TEST_METHOD(IntSet)
		{
			Datum a;
			auto expression = [&a] {a.Set(10); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::FLOAT);
			auto expression2 = [&a] {a.Set(10); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(10);
			a.PushBack(20);
			a.Set(30,1);
			Assert::IsTrue(a.Get<int32_t&>(1) == 30);
		}

		TEST_METHOD(FloatSet)
		{
			Datum a;
			auto expression = [&a] {a.Set(10.0f); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			auto expression2 = [&a] {a.Set(10.0f); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(10.0f);
			a.PushBack(20.0f);
			a.Set(30.0f, 1);
			Assert::IsTrue(a.Get<float&>(1) == 30.0f);
		}

		TEST_METHOD(StringSet)
		{
			Datum a;
			auto expression = [&a] {a.Set("Hi"); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			auto expression2 = [&a] {a.Set("Hi"); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack("Hi");
			a.PushBack("Hello");
			a.Set("Bye", 1);
			Assert::IsTrue(a.Get<string&>(1) == "Bye");
		}

		TEST_METHOD(VectorSet)
		{
			Datum a;
			auto expression = [&a] {a.Set(glm::vec4(10.0f)); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			auto expression2 = [&a] {a.Set(glm::vec4(10.0f)); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			a.Set(glm::vec4(30.0f), 1);
			Assert::IsTrue(a.Get<glm::vec4&>(1) == glm::vec4(30.0f));
		}

		TEST_METHOD(MatrixSet)
		{
			Datum a;
			auto expression = [&a] {a.Set(glm::mat4(10.0f)); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			auto expression2 = [&a] {a.Set(glm::mat4(10.0f)); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0f));
			a.Set(glm::mat4(30.0f), 1);
			Assert::IsTrue(a.Get<glm::mat4&>(1) == glm::mat4(30.0f));
		}

		TEST_METHOD(PointerSet)
		{
			Datum a;
			Foo f(10, 20);
			Foo f2(20, 10);
			auto expression = [&a, &f] {a.Set(&f); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			auto expression2 = [&a, &f] {a.Set(&f); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(&f);
			a.PushBack(&f2);
			a.Set(&f, 1);
			Assert::IsTrue(a.Get<RTTI*&>(1) == &f);
		}

		TEST_METHOD(ScopeSet)
		{
			Datum a;
			Scope b;
			Scope c;

			auto expression = [&a, &b] {a.Set(&b); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			auto expression2 = [&a, &b] {a.Set(&b); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(&b);
			a.PushBack(&c);
			a.Set(&b, 1);
			Assert::IsTrue(a.Get<Scope*&>(1) == &b);
		}

		TEST_METHOD(IntPushBack)
		{
			Datum a;
			a.SetType(DatumType::FLOAT);

			auto expression = [&a] {a.PushBack(10); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack(10);
			Assert::IsTrue(a.Get<int32_t&>(0) == 10);
			Assert::IsTrue(a.Size() == 1);
			a.PushBack(20);
			Assert::IsTrue(a.Get<int32_t&>(1) == 20);
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(FloatPushBack)
		{
			Datum a;
			a.SetType(DatumType::INTEGER);

			auto expression = [&a] {a.PushBack(10.0f); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack(10.0f);
			Assert::IsTrue(a.Get<float&>(0) == 10.0f);
			Assert::IsTrue(a.Size() == 1);
			a.PushBack(20.0f);
			Assert::IsTrue(a.Get<float&>(1) == 20.0f);
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(StringPushBack)
		{
			Datum a;
			a.SetType(DatumType::FLOAT);

			auto expression = [&a] {a.PushBack("Hi"); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack("Hello");
			Assert::IsTrue(a.Get<string&>(0) == "Hello");
			Assert::IsTrue(a.Size() == 1);
			a.PushBack("Bye");
			Assert::IsTrue(a.Get<string&>(1) == "Bye");
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(VectorPushBack)
		{
			Datum a;
			a.SetType(DatumType::FLOAT);

			auto expression = [&a] {a.PushBack(glm::vec4(10.0f)); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			Assert::IsTrue(a.Get<glm::vec4&>(0) == glm::vec4(10.0f));
			Assert::IsTrue(a.Size() == 1);
			a.PushBack(glm::vec4(20.0f));
			Assert::IsTrue(a.Get<glm::vec4&>(1) == glm::vec4(20.0f));
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(MatrixPushBack)
		{
			Datum a;
			a.SetType(DatumType::FLOAT);

			auto expression = [&a] {a.PushBack(glm::mat4(10.0f)); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			Assert::IsTrue(a.Get<glm::mat4&>(0) == glm::mat4(10.0f));
			Assert::IsTrue(a.Size() == 1);
			a.PushBack(glm::mat4(20.0f));
			Assert::IsTrue(a.Get<glm::mat4&>(1) == glm::mat4(20.0f));
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(PointerPushBack)
		{
			Datum a;
			a.SetType(DatumType::FLOAT);
			Foo f(10, 20);
			Foo f2(20, 10);
			auto expression = [&a, &f] {a.PushBack(&f); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack(&f);
			Assert::IsTrue(a.Get<RTTI*&>(0) == &f);
			Assert::IsTrue(a.Size() == 1);
			a.PushBack(&f2);
			Assert::IsTrue(a.Get<RTTI*&>(1) == &f2);
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(ScopePushBack)
		{
			Datum a;
			a.SetType(DatumType::FLOAT);
			Scope b;
			Scope c;
			auto expression = [&a, &b] {a.PushBack(&b); };
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.PushBack(&b);
			Assert::IsTrue(a.Get<Scope*&>(0) == &b);
			Assert::IsTrue(a.Size() == 1);
			a.PushBack(&c);
			Assert::IsTrue(a.Get<Scope*&>(1) == &c);
			Assert::IsTrue(a.Size() == 2);
		}

		TEST_METHOD(IntGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::INTEGER);
			auto expression = [&a] {a.Get<int32_t&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const int32_t&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(10.0f);
			auto expression3 = [&a] {a.Get<int32_t&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get<const int32_t&>(); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			a.PushBack(10);
			Assert::IsTrue(a.Get<int32_t&>(0) == 10);
			Assert::IsTrue(b->Get<const int32_t&>(0) == 10);
			a.PushBack(20);
			Assert::IsTrue(a.Get<int32_t&>(1) == 20);
			Assert::IsTrue(b->Get<const int32_t&>(1) == 20);
		}

		TEST_METHOD(FloatGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::FLOAT);
			auto expression = [&a] {a.Get<float&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const float&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack("Hi");
			auto expression3 = [&a] {a.Get<float&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get < const float &> (); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			a.PushBack(10.0f);
			Assert::IsTrue(a.Get<float&>(0) == 10.0f);
			Assert::IsTrue(b->Get<const float&>(0) == 10.0f);
			a.PushBack(20.0f);
			Assert::IsTrue(a.Get<float&>(1) == 20.0f);
			Assert::IsTrue(b->Get<const float&>(1) == 20.0f);
		}

		TEST_METHOD(StringGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::STRING);
			auto expression = [&a] {a.Get<string&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const string&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(10);
			auto expression3 = [&a] {a.Get<string&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get<const string&>(); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			a.PushBack("Hi");
			Assert::IsTrue(a.Get<string&>(0) == "Hi");
			Assert::IsTrue(b->Get<const string&>(0) == "Hi");
			a.PushBack("Hello");
			Assert::IsTrue(a.Get<string&>(1) == "Hello");
			Assert::IsTrue(b->Get<const string&>(1) == "Hello");
		}

		TEST_METHOD(VectorGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::VECTOR);
			auto expression = [&a] {a.Get<glm::vec4&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const glm::vec4&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(10);
			auto expression3 = [&a] {a.Get<glm::vec4&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get<const glm::vec4&>(); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			a.PushBack(glm::vec4(10.0f));
			Assert::IsTrue(a.Get<glm::vec4&>(0) == glm::vec4(10.0f));
			Assert::IsTrue(b->Get<const glm::vec4&>(0) == glm::vec4(10.0f));
			a.PushBack(glm::vec4(20.0f));
			Assert::IsTrue(a.Get<glm::vec4&>(1) == glm::vec4(20.0f));
			Assert::IsTrue(b->Get<const glm::vec4&>(1) == glm::vec4(20.0f));
		}

		TEST_METHOD(MatrixGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::MATRIX);
			auto expression = [&a] {a.Get<glm::mat4&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const glm::mat4&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack(10);
			auto expression3 = [&a] {a.Get<glm::mat4&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get<const glm::mat4&>(); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			a.PushBack(glm::mat4(10.0f));
			Assert::IsTrue(a.Get<glm::mat4&>(0) == glm::mat4(10.0f));
			Assert::IsTrue(b->Get<const glm::mat4&>(0) == glm::mat4(10.0f));
			a.PushBack(glm::mat4(20.0f));
			Assert::IsTrue(a.Get<glm::mat4&>(1) == glm::mat4(20.0f));
			Assert::IsTrue(b->Get<const glm::mat4&>(1) == glm::mat4(20.0f));
		}

		TEST_METHOD(RTTIGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::POINTER);
			auto expression = [&a] {a.Get<RTTI*&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const RTTI*&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack("Hi");
			auto expression3 = [&a] {a.Get<RTTI*&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get < const RTTI*&>(); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			a.PushBack(&fooTestVariable1);
			Assert::IsTrue(a.Get<RTTI*&>(0) == &fooTestVariable1);
			Assert::IsTrue(b->Get<const RTTI*&>(0) == &fooTestVariable1);
			a.PushBack(&fooTestVariable2);
			Assert::IsTrue(a.Get<RTTI*&>(1) == &fooTestVariable2);
			Assert::IsTrue(b->Get<const RTTI*&>(1) == &fooTestVariable2);
		}

		TEST_METHOD(ScopeGet)
		{
			Datum a;
			const Datum* b = &a;
			a.SetType(DatumType::TABLE);
			auto expression = [&a] {a.Get<Scope*&>(); };
			Assert::ExpectException<exception>(expression);
			auto expression2 = [&b] {b->Get<const Scope*&>(); };
			Assert::ExpectException<exception>(expression2);

			a.Clear();

			a.PushBack("Hi");
			auto expression3 = [&a] {a.Get<Scope*&>(); };
			Assert::ExpectException<exception>(expression3);
			auto expression4 = [&b] {b->Get < const Scope*&>(); };
			Assert::ExpectException<exception>(expression4);

			a.Clear();

			Scope s;
			Scope s2;

			a.PushBack(&s);
			Assert::IsTrue(a.Get<Scope*&>(0) == &s);
			Assert::IsTrue(b->Get<const Scope*&>(0) == &s);
			a.PushBack(&s2);
			Assert::IsTrue(a.Get<Scope*&>(1) == &s2);
			Assert::IsTrue(b->Get<const Scope*&>(1) == &s2);
		}

		TEST_METHOD(ToString)
		{
			Datum a;
			string value;
			auto expression = [&a] {a.ToString(); };
			Assert::ExpectException<exception>(expression);

			a.PushBack(intTestVariable1);
			Datum b;
			b.PushBack(intTestVariable2);
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();

			a.PushBack(10.0f);
			b.PushBack(20.0f);
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();

			a.PushBack(glm::vec4(10.0f));
			b.PushBack(glm::vec4(20.0f));
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();

			a.PushBack(glm::mat4(10.0f));
			b.PushBack(glm::mat4(20.0f));
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();

			a.PushBack("Hello");
			b.PushBack("Hi");
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();
		}

		TEST_METHOD(SetFromString)
		{
			Datum a;
			Datum b;
			string value;
			auto expression = [&a] {a.SetFromString("Invalid serialization."); };
			Assert::ExpectException<exception>(expression);

			a.PushBack(intTestVariable1);

			b.PushBack(intTestVariable2);
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);
			Assert::ExpectException<exception>(expression);

			a.Clear();
			b.Clear();

			a.PushBack(10.0f);
			b.PushBack(20.0f);
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);
			Assert::ExpectException<exception>(expression);

			a.Clear();
			b.Clear();

			a.PushBack("Hello");
			b.PushBack("Hi");
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);

			a.Clear();
			b.Clear();

			a.PushBack(glm::vec4(10.0f));
			b.PushBack(glm::vec4(20.0f));
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);
			Assert::ExpectException<exception>(expression);

			a.Clear();
			b.Clear();

			a.PushBack(glm::mat4(10.0f));
			b.PushBack(glm::mat4(20.0f));
			b.SetFromString(a.ToString());
			Assert::IsTrue(a == b);
			Assert::ExpectException<exception>(expression);

			a.Clear();
			b.Clear();
		}

		TEST_METHOD(Reserve)
		{
			Datum a;
			auto expression = [&a] {a.Reserve(5); };
			Assert::ExpectException<exception>(expression);

			a.SetType(DatumType::INTEGER);
			a.SetStorage(intTestVariableArray1, 3);
			Assert::ExpectException<exception>(expression);

			a.Clear();

			a.SetType(DatumType::INTEGER);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);

			a.Clear();

			a.SetType(DatumType::FLOAT);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);

			a.Clear();

			a.SetType(DatumType::STRING);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);

			a.Clear();

			a.SetType(DatumType::VECTOR);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);

			a.Clear();

			a.SetType(DatumType::MATRIX);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);

			a.Clear();

			a.SetType(DatumType::POINTER);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);

			a.Clear();

			a.SetType(DatumType::TABLE);
			a.Reserve(defaultCapacity);
			Assert::AreEqual(a.Capacity(), defaultCapacity);
		}

		TEST_METHOD(Remove)
		{
			Datum a;
			Scope s1;
			Scope s2;
			Scope s3;

			bool b;
			a.PushBack(&s1);
			a.PushBack(&s2);
			a.PushBack(&s3);

			b = a.Remove(&s2);

			Assert::IsTrue(a.Get<Scope*&>(1) != &s2);
			Assert::IsTrue(b);

			Scope s4;

			b = a.Remove(&s4);

			Assert::IsFalse(b);
		}

	private:
		static _CrtMemState sStartMemState;
		static const int32_t numberOfBuckets = 3;
		static const int32_t numberOfTestElements = 5;

		static const  uint32_t maxNumberOfElements = 3;
		static const uint32_t defaultCapacity = 3;
		static const uint32_t defaultSize = 0;
		int32_t intTestVariable1 = 10;
		int32_t intTestVariable2 = 20;
		int32_t intTestVariable3 = 30;

		int32_t intTestVariableArray1[maxNumberOfElements] = { 10,20,30 };
		int32_t intTestVariableArray2[maxNumberOfElements] = { 30,20,10 };

		Foo fooTestVariable1 = Foo(1, 10);
		Foo fooTestVariable2 = Foo(2, 30);
		Foo fooTestVariable3 = Foo(2, 30);

		Foo fooTestVariableArray1[maxNumberOfElements] = { fooTestVariable1, fooTestVariable2, fooTestVariable3 };
		Foo fooTestVariableArray2[maxNumberOfElements] = { fooTestVariable3, fooTestVariable2, fooTestVariable1 };

		std::int32_t* pointerTestVariable1 = &intTestVariable1;
		std::int32_t* pointerTestVariable2 = &intTestVariable2;
		std::int32_t* pointerTestVariable3 = &intTestVariable3;

		std::int32_t* pointerTestVariableArray1[maxNumberOfElements] = { pointerTestVariable1, pointerTestVariable2,
			pointerTestVariable3 };

		std::int32_t* pointerTestVariableArray2[maxNumberOfElements] = { pointerTestVariable3, pointerTestVariable2,
			pointerTestVariable1 };

	};
	_CrtMemState DatumTest::sStartMemState;
}