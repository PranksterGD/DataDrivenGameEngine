#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(HashmapTest)
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

		TEST_METHOD(HashmapDefaultConstructor)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);
		}


		TEST_METHOD(HashmapCopyConstructor)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			intMap.Insert(intPairs[0]);
			pointerMap.Insert(pointerPairs[0]);
			charMap.Insert(charPairs[0]);
			stringMap.Insert(stringPairs[0]);
			fooMap.Insert(fooPairs[0]);

			intMap.Insert(intPairs[1]);
			pointerMap.Insert(pointerPairs[1]);
			charMap.Insert(charPairs[1]);
			stringMap.Insert(stringPairs[1]);
			fooMap.Insert(fooPairs[1]);

			Hashmap<int32_t, int32_t> otherIntMap = intMap;
			Hashmap<int32_t*, int32_t> otherPointerMap = pointerMap;
			Hashmap<char*, int32_t> otherCharMap = charMap;
			Hashmap<string, int32_t> otherStringMap = stringMap;
			Hashmap<Foo, int32_t, FooHash> otherFooMap = fooMap;

			Assert::IsTrue(intMap[intPairs[0].first] == otherIntMap[intPairs[0].first]);
			Assert::IsTrue(pointerMap[pointerPairs[0].first] == otherPointerMap[pointerPairs[0].first]);
			Assert::IsTrue(charMap[charPairs[0].first] == otherCharMap[charPairs[0].first]);
			Assert::IsTrue(stringMap[stringPairs[0].first] == otherStringMap[stringPairs[0].first]);
			Assert::IsTrue(fooMap[fooPairs[0].first] == otherFooMap[fooPairs[0].first]);

			Assert::IsTrue(intMap[intPairs[1].first] == otherIntMap[intPairs[1].first]);
			Assert::IsTrue(pointerMap[pointerPairs[1].first] == otherPointerMap[pointerPairs[1].first]);
			Assert::IsTrue(charMap[charPairs[1].first] == otherCharMap[charPairs[1].first]);
			Assert::IsTrue(stringMap[stringPairs[1].first] == otherStringMap[stringPairs[1].first]);
			Assert::IsTrue(fooMap[fooPairs[1].first] == otherFooMap[fooPairs[1].first]);
		}

		TEST_METHOD(HashmapMoveCopyConstructor)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			intMap.Insert(intPairs[0]);
			pointerMap.Insert(pointerPairs[0]);
			charMap.Insert(charPairs[0]);
			stringMap.Insert(stringPairs[0]);
			fooMap.Insert(fooPairs[0]);

			intMap.Insert(intPairs[1]);
			pointerMap.Insert(pointerPairs[1]);
			charMap.Insert(charPairs[1]);
			stringMap.Insert(stringPairs[1]);
			fooMap.Insert(fooPairs[1]);

			Hashmap<int32_t, int32_t> otherIntMap = move(intMap);
			Hashmap<int32_t*, int32_t> otherPointerMap = move(pointerMap);
			Hashmap<char*, int32_t> otherCharMap = move(charMap);
			Hashmap<string, int32_t> otherStringMap = move(stringMap);
			Hashmap<Foo, int32_t, FooHash> otherFooMap = move(fooMap);

			Assert::IsTrue(otherIntMap[intPairs[0].first] == intPairs[0].second);
			Assert::IsTrue(otherPointerMap[pointerPairs[0].first] == pointerPairs[0].second);
			Assert::IsTrue(otherCharMap[charPairs[0].first] == charPairs[0].second);
			Assert::IsTrue(otherStringMap[stringPairs[0].first] == stringPairs[0].second);
			Assert::IsTrue(otherFooMap[fooPairs[0].first] == fooPairs[0].second);
		}

		TEST_METHOD(HashmapAssignmentOperator)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			intMap.Insert(intPairs[0]);
			pointerMap.Insert(pointerPairs[0]);
			charMap.Insert(charPairs[0]);
			stringMap.Insert(stringPairs[0]);
			fooMap.Insert(fooPairs[0]);

			intMap.Insert(intPairs[1]);
			pointerMap.Insert(pointerPairs[1]);
			charMap.Insert(charPairs[1]);
			stringMap.Insert(stringPairs[1]);
			fooMap.Insert(fooPairs[1]);

			Hashmap<int32_t, int32_t> otherIntMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> otherPointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> otherCharMap(numberOfBuckets);
			Hashmap<string, int32_t> otherStringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> otherFooMap(numberOfBuckets);

			otherIntMap = intMap;
			otherPointerMap = pointerMap;
			otherCharMap = charMap;
			otherStringMap = stringMap;
			otherFooMap = fooMap;

			Assert::IsTrue(intMap[intPairs[0].first] == otherIntMap[intPairs[0].first]);
			Assert::IsTrue(pointerMap[pointerPairs[0].first] == otherPointerMap[pointerPairs[0].first]);
			Assert::IsTrue(charMap[charPairs[0].first] == otherCharMap[charPairs[0].first]);
			Assert::IsTrue(stringMap[stringPairs[0].first] == otherStringMap[stringPairs[0].first]);
			Assert::IsTrue(fooMap[fooPairs[0].first] == otherFooMap[fooPairs[0].first]);

			Assert::IsTrue(intMap[intPairs[1].first] == otherIntMap[intPairs[1].first]);
			Assert::IsTrue(pointerMap[pointerPairs[1].first] == otherPointerMap[pointerPairs[1].first]);
			Assert::IsTrue(charMap[charPairs[1].first] == otherCharMap[charPairs[1].first]);
			Assert::IsTrue(stringMap[stringPairs[1].first] == otherStringMap[stringPairs[1].first]);
			Assert::IsTrue(fooMap[fooPairs[1].first] == otherFooMap[fooPairs[1].first]);
		}

		TEST_METHOD(HashmapMoveAssignmentConstructor)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			intMap.Insert(intPairs[0]);
			pointerMap.Insert(pointerPairs[0]);
			charMap.Insert(charPairs[0]);
			stringMap.Insert(stringPairs[0]);
			fooMap.Insert(fooPairs[0]);

			intMap.Insert(intPairs[1]);
			pointerMap.Insert(pointerPairs[1]);
			charMap.Insert(charPairs[1]);
			stringMap.Insert(stringPairs[1]);
			fooMap.Insert(fooPairs[1]);

			Hashmap<int32_t, int32_t> otherIntMap;
			Hashmap<int32_t*, int32_t> otherPointerMap;
			Hashmap<char*, int32_t> otherCharMap;
			Hashmap<string, int32_t> otherStringMap;
			Hashmap<Foo, int32_t, FooHash> otherFooMap;

			otherIntMap = move(intMap);
			otherPointerMap = move(pointerMap);
			otherCharMap = move(charMap);
			otherStringMap = move(stringMap);
			otherFooMap = move(fooMap);

			Assert::IsTrue(otherIntMap[intPairs[0].first] == intPairs[0].second);
			Assert::IsTrue(otherPointerMap[pointerPairs[0].first] == pointerPairs[0].second);
			Assert::IsTrue(otherCharMap[charPairs[0].first] == charPairs[0].second);
			Assert::IsTrue(otherStringMap[stringPairs[0].first] == stringPairs[0].second);
			Assert::IsTrue(otherFooMap[fooPairs[0].first] == fooPairs[0].second);
		}

		TEST_METHOD(HashmapDestructor)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			intMap.Insert(intPairs[0]);
			pointerMap.Insert(pointerPairs[0]);
			charMap.Insert(charPairs[0]);
			stringMap.Insert(stringPairs[0]);
			fooMap.Insert(fooPairs[0]);

			intMap.Insert(intPairs[1]);
			pointerMap.Insert(pointerPairs[1]);
			charMap.Insert(charPairs[1]);
			stringMap.Insert(stringPairs[1]);
			fooMap.Insert(fooPairs[1]);
		}

		TEST_METHOD(HashmapFind)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			intMapIt = intMap.Find(intPairs[0].first);
			pointerMapIt = pointerMap.Find(pointerPairs[0].first);
			charMapIt = charMap.Find(charPairs[0].first);
			stringMapIt = stringMap.Find(stringPairs[0].first);
			fooMapIt = fooMap.Find(fooPairs[0].first);

			Assert::IsTrue(intMapIt == intMap.end());
			Assert::IsTrue(pointerMapIt == pointerMap.end());
			Assert::IsTrue(charMapIt == charMap.end());
			Assert::IsTrue(stringMapIt == stringMap.end());
			Assert::IsTrue(fooMapIt == fooMap.end());

			for (int32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);

				intMapIt = intMap.Find(intPairs[i].first);
				pointerMapIt = pointerMap.Find(pointerPairs[i].first);
				charMapIt = charMap.Find(charPairs[i].first);
				stringMapIt = stringMap.Find(stringPairs[i].first);
				fooMapIt = fooMap.Find(fooPairs[i].first);

				Assert::IsTrue(*intMapIt == intPairs[i]);
				Assert::IsTrue(*pointerMapIt == pointerPairs[i]);
				Assert::IsTrue(*charMapIt == charPairs[i]);
				Assert::IsTrue(*stringMapIt == stringPairs[i]);
				Assert::IsTrue(*fooMapIt == fooPairs[i]);
			}

			intMap[intPairs[0].first] = intPairs[0].first;
			intMapIt = intMap.Find(intPairs[0].first);

			Assert::IsTrue((*intMapIt).first == intPairs[0].first);
		}

		TEST_METHOD(HashmapInsert)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			Hashmap<int32_t, int32_t>::Iterator otherIntMapIt;
			Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt;
			Hashmap<char*, int32_t>::Iterator otherCharMapIt;
			Hashmap<string, int32_t>::Iterator otherStringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt;

			uint32_t size = 0;

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMapIt = intMap.Insert(intPairs[i]);
				pointerMapIt = pointerMap.Insert(pointerPairs[i]);
				charMapIt = charMap.Insert(charPairs[i]);
				stringMapIt = stringMap.Insert(stringPairs[i]);
				fooMapIt = fooMap.Insert(fooPairs[i]);

				++size;

				Assert::IsTrue(*intMapIt == intPairs[i]);
				Assert::IsTrue(*pointerMapIt == pointerPairs[i]);
				Assert::IsTrue(*charMapIt == charPairs[i]);
				Assert::IsTrue(*stringMapIt == stringPairs[i]);
				Assert::IsTrue(*fooMapIt == fooPairs[i]);

				Assert::AreEqual(size, intMap.Size());
				Assert::AreEqual(size, pointerMap.Size());
				Assert::AreEqual(size, charMap.Size());
				Assert::AreEqual(size, stringMap.Size());
				Assert::AreEqual(size, fooMap.Size());
			}

			otherIntMapIt = intMap.Insert(intPairs[4]);
			otherPointerMapIt = pointerMap.Insert(pointerPairs[4]);
			otherCharMapIt = charMap.Insert(charPairs[4]);
			otherStringMapIt = stringMap.Insert(stringPairs[4]);
			otherFooMapIt = fooMap.Insert(fooPairs[4]);

			Assert::IsTrue(intMapIt == otherIntMapIt);
			Assert::IsTrue(pointerMapIt == otherPointerMapIt);
			Assert::IsTrue(charMapIt == otherCharMapIt);
			Assert::IsTrue(stringMapIt == otherStringMapIt);
			Assert::IsTrue(fooMapIt == otherFooMapIt);
		}

		TEST_METHOD(HashmapSubscriptOperator)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			for (uint32_t i = 0; i < numberOfTestElements - 1; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);

				Assert::IsTrue(intMap[intPairs[i].first] == intPairs[i].second);
				Assert::IsTrue(pointerMap[pointerPairs[i].first] == pointerPairs[i].second);
				Assert::IsTrue(charMap[charPairs[i].first] == charPairs[i].second);
				Assert::IsTrue(stringMap[stringPairs[i].first] == stringPairs[i].second);
				Assert::IsTrue(fooMap[fooPairs[i].first] == fooPairs[i].second);
			}

			const Hashmap<int32_t, int32_t>& constIntMap = intMap;
			const Hashmap<int32_t*, int32_t>& constPointerMap = pointerMap;
			const Hashmap<char*, int32_t>& constCharMap = charMap;
			const Hashmap<string, int32_t>& constStringMap = stringMap;
			const Hashmap<Foo, int32_t, FooHash>& constFooMap = fooMap;

			Assert::IsTrue(constIntMap[intPairs[0].first] == intPairs[0].second);
			Assert::IsTrue(constPointerMap[pointerPairs[0].first] == pointerPairs[0].second);
			Assert::IsTrue(constCharMap[charPairs[0].first] == charPairs[0].second);
			Assert::IsTrue(constStringMap[stringPairs[0].first] == stringPairs[0].second);
			Assert::IsTrue(constFooMap[fooPairs[0].first] == fooPairs[0].second);

			int32_t a = 5;
			int32_t *b = &a;
			Foo c(100, 100);
			std::pair<int32_t, int32_t> intTestPair = { 10000,50 };
			std::pair<int32_t*, int32_t> pointerTestPair = { b,10 };
			std::pair<char*, int32_t> charTestPair = { "qwerty", 10 };
			std::pair<string, int32_t> stringTestPair = { "asdfg", 10 };
			std::pair<Foo, int32_t> fooTestPair = { c,10 };

			auto intSubscriptException = [&constIntMap, &intTestPair] {constIntMap[intTestPair.first]; };
			auto pointerSubscriptException = [&constPointerMap, &pointerTestPair] {constPointerMap[pointerTestPair.first]; };
			auto charSubscriptException = [&constCharMap, &charTestPair] {constCharMap[charTestPair.first]; };
			auto stringSubscriptException = [&constStringMap, &stringTestPair] {constStringMap[stringTestPair.first]; };
			auto fooSubscriptException = [&constFooMap, &fooTestPair] {constFooMap[fooTestPair.first]; };

			Assert::ExpectException<exception>(intSubscriptException);
			Assert::ExpectException<exception>(pointerSubscriptException);
			Assert::ExpectException<exception>(charSubscriptException);
			Assert::ExpectException<exception>(stringSubscriptException);
			Assert::ExpectException<exception>(fooSubscriptException);

			intMap[intTestPair.first] = intTestPair.second;
			pointerMap[pointerTestPair.first] = pointerTestPair.second;
			charMap[charTestPair.first] = charTestPair.second;
			stringMap[stringTestPair.first] = stringTestPair.second;
			fooMap[fooTestPair.first] = fooTestPair.second;

			Assert::IsTrue(intTestPair.second == intMap[intTestPair.first]);
			Assert::IsTrue(pointerTestPair.second == pointerMap[pointerTestPair.first]);
			Assert::IsTrue(charTestPair.second == charMap[charTestPair.first]);
			Assert::IsTrue(stringTestPair.second == stringMap[stringTestPair.first]);
			Assert::IsTrue(fooTestPair.second == fooMap[fooTestPair.first]);
		}

		TEST_METHOD(HashmapRemove)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			uint32_t size = 0;

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);

				++size;
			}

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Remove(intPairs[i].first);
				pointerMap.Remove(pointerPairs[i].first);
				charMap.Remove(charPairs[i].first);
				stringMap.Remove(stringPairs[i].first);
				fooMap.Remove(fooPairs[i].first);

				--size;

				intMapIt = intMap.Find(intPairs[i].first);
				pointerMapIt = pointerMap.Find(pointerPairs[i].first);
				charMapIt = charMap.Find(charPairs[i].first);
				stringMapIt = stringMap.Find(stringPairs[i].first);
				fooMapIt = fooMap.Find(fooPairs[i].first);

				Assert::IsTrue(intMapIt == intMap.end());
				Assert::IsTrue(pointerMapIt == pointerMap.end());
				Assert::IsTrue(charMapIt == charMap.end());
				Assert::IsTrue(stringMapIt == stringMap.end());
				Assert::IsTrue(fooMapIt == fooMap.end());

				Assert::AreEqual(size, intMap.Size());
				Assert::AreEqual(size, pointerMap.Size());
				Assert::AreEqual(size, charMap.Size());
				Assert::AreEqual(size, stringMap.Size());
				Assert::AreEqual(size, fooMap.Size());
			}

			intMap.Remove(intPairs[0].first);
			pointerMap.Remove(pointerPairs[0].first);
			charMap.Remove(charPairs[0].first);
			stringMap.Remove(stringPairs[0].first);
			fooMap.Remove(fooPairs[0].first);
		}

		TEST_METHOD(HashmapClear)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);
			}

			intMap.Clear();
			pointerMap.Clear();
			charMap.Clear();
			stringMap.Clear();
			fooMap.Clear();

			Assert::AreEqual(0U, intMap.Size());
			Assert::AreEqual(0U, pointerMap.Size());
			Assert::AreEqual(0U, charMap.Size());
			Assert::AreEqual(0U, stringMap.Size());
			Assert::AreEqual(0U, fooMap.Size());
		}

		TEST_METHOD(HashmapSize)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Assert::AreEqual(0U, intMap.Size());
			Assert::AreEqual(0U, pointerMap.Size());
			Assert::AreEqual(0U, charMap.Size());
			Assert::AreEqual(0U, stringMap.Size());
			Assert::AreEqual(0U, fooMap.Size());

			uint32_t size = 0;

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);

				++size;
			
				Assert::AreEqual(size, intMap.Size());
				Assert::AreEqual(size, pointerMap.Size());
				Assert::AreEqual(size, charMap.Size());
				Assert::AreEqual(size, stringMap.Size());
				Assert::AreEqual(size, fooMap.Size());
			}
		}

		TEST_METHOD(HashmapContainsKey)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Assert::IsFalse(intMap.ContainsKey(intPairs[0].first));
			Assert::IsFalse(pointerMap.ContainsKey(pointerPairs[0].first));
			Assert::IsFalse(charMap.ContainsKey(charPairs[0].first));
			Assert::IsFalse(stringMap.ContainsKey(stringPairs[0].first));
			Assert::IsFalse(fooMap.ContainsKey(fooPairs[0].first));

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);

				Assert::IsTrue(intMap.ContainsKey(intPairs[i].first));
				Assert::IsTrue(pointerMap.ContainsKey(pointerPairs[i].first));
				Assert::IsTrue(charMap.ContainsKey(charPairs[i].first));
				Assert::IsTrue(stringMap.ContainsKey(stringPairs[i].first));
				Assert::IsTrue(fooMap.ContainsKey(fooPairs[i].first));
			}
		}

		TEST_METHOD(HashmapBegin)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Assert::IsTrue(intMap.begin() == intMap.end());
			Assert::IsTrue(pointerMap.begin() == pointerMap.end());
			Assert::IsTrue(charMap.begin() == charMap.end());
			Assert::IsTrue(stringMap.begin() == stringMap.end());
			Assert::IsTrue(fooMap.begin() == fooMap.end());

			intMap.Insert(intPairs[0]);
			pointerMap.Insert(pointerPairs[0]);
			charMap.Insert(charPairs[0]);
			stringMap.Insert(stringPairs[0]);
			fooMap.Insert(fooPairs[0]);

			Assert::IsTrue(*(intMap.begin()) == intPairs[0]);
			Assert::IsTrue(*(pointerMap.begin()) == pointerPairs[0]);
			Assert::IsTrue(*(charMap.begin()) == charPairs[0]);
			Assert::IsTrue(*(stringMap.begin()) == stringPairs[0]);
			Assert::IsTrue(*(fooMap.begin()) == fooPairs[0]);	
		}

		TEST_METHOD(HashmapEnd)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Hashmap<int32_t, int32_t>::Iterator intMapIt = intMap.end();
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt = pointerMap.end();
			Hashmap<char*, int32_t>::Iterator charMapIt = charMap.end();
			Hashmap<string, int32_t>::Iterator stringMapIt = stringMap.end();
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt = fooMap.end();

			auto intEndException = [intMapIt] {*intMapIt; };
			auto pointerEndException = [pointerMapIt] {*pointerMapIt; };
			auto charEndException = [charMapIt] {*charMapIt; };
			auto stringEndException = [stringMapIt] {*stringMapIt; };
			auto fooEndException = [fooMapIt] {*fooMapIt; };

			Assert::ExpectException<exception>(intEndException);
			Assert::ExpectException<exception>(pointerEndException);
			Assert::ExpectException<exception>(charEndException);
			Assert::ExpectException<exception>(stringEndException);
			Assert::ExpectException<exception>(fooEndException);
		}

		TEST_METHOD(IteratorDefaultConstructor)
		{
			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;
		}

		TEST_METHOD(IteratorCopyConstructor)
		{
			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			Hashmap<int32_t, int32_t>::Iterator otherIntMapIt = intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt = pointerMapIt;
			Hashmap<char*, int32_t>::Iterator otherCharMapIt = charMapIt;
			Hashmap<string, int32_t>::Iterator otherStringMapIt = stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt = fooMapIt;

			Assert::IsTrue(intMapIt == otherIntMapIt);
			Assert::IsTrue(pointerMapIt == otherPointerMapIt);
			Assert::IsTrue(charMapIt == otherCharMapIt);
			Assert::IsTrue(stringMapIt == otherStringMapIt);
			Assert::IsTrue(fooMapIt == otherFooMapIt);
		}

		TEST_METHOD(IteratorAssignmentOperator)
		{
			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			Hashmap<int32_t, int32_t>::Iterator otherIntMapIt;
			Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt;
			Hashmap<char*, int32_t>::Iterator otherCharMapIt;
			Hashmap<string, int32_t>::Iterator otherStringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt;

			otherIntMapIt = intMapIt;
			otherPointerMapIt = pointerMapIt;
			otherCharMapIt = charMapIt;
			otherStringMapIt = stringMapIt;
			otherFooMapIt = fooMapIt;

			Assert::IsTrue(intMapIt == otherIntMapIt);
			Assert::IsTrue(pointerMapIt == otherPointerMapIt);
			Assert::IsTrue(charMapIt == otherCharMapIt);
			Assert::IsTrue(stringMapIt == otherStringMapIt);
			Assert::IsTrue(fooMapIt == otherFooMapIt);
		}

		TEST_METHOD(IteratorPreIncrement)
		{

			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);
			}

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			auto intIncrementException = [&intMapIt] {++intMapIt; };
			auto pointerIncrementException = [&pointerMapIt] {++pointerMapIt; };
			auto charIncrementException = [&charMapIt] {++charMapIt; };
			auto stringIncrementException = [&stringMapIt] {++stringMapIt; };
			auto fooIncrementException = [&fooMapIt] {++fooMapIt; };

			Assert::ExpectException<exception>(intIncrementException);
			Assert::ExpectException<exception>(pointerIncrementException);
			Assert::ExpectException<exception>(charIncrementException);
			Assert::ExpectException<exception>(stringIncrementException);
			Assert::ExpectException<exception>(fooIncrementException);

			intMapIt = intMap.begin();
			pointerMapIt = pointerMap.begin();
			charMapIt = charMap.begin();
			stringMapIt = stringMap.begin();
			fooMapIt = fooMap.begin();

			Hashmap<int32_t, int32_t>::Iterator otherIntMapIt = intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt = pointerMapIt;
			Hashmap<char*, int32_t>::Iterator otherCharMapIt = charMapIt;
			Hashmap<string, int32_t>::Iterator otherStringMapIt = stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt = fooMapIt;

			Assert::IsFalse(otherIntMapIt == ++intMapIt);
			Assert::IsFalse(otherPointerMapIt == ++pointerMapIt);
			Assert::IsFalse(otherCharMapIt == ++charMapIt);
			Assert::IsFalse(otherStringMapIt == ++stringMapIt);
			Assert::IsFalse(otherFooMapIt == ++fooMapIt);		

			intMapIt = intMap.end();
			pointerMapIt = pointerMap.end();
			charMapIt = charMap.end();
			stringMapIt = stringMap.end();
			fooMapIt = fooMap.end();

			++intMapIt;
			++pointerMapIt;
			++charMapIt;
			++stringMapIt;
			++fooMapIt;

			Assert::IsTrue(intMapIt == intMap.end());
			Assert::IsTrue(pointerMapIt == pointerMap.end());
			Assert::IsTrue(charMapIt == charMap.end());
			Assert::IsTrue(stringMapIt == stringMap.end());
			Assert::IsTrue(fooMapIt == fooMap.end());
		}

		TEST_METHOD(IteratorPostIncrement)
		{

			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMap.Insert(intPairs[i]);
				pointerMap.Insert(pointerPairs[i]);
				charMap.Insert(charPairs[i]);
				stringMap.Insert(stringPairs[i]);
				fooMap.Insert(fooPairs[i]);
			}

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			auto intIncrementException = [&intMapIt] {intMapIt++; };
			auto pointerIncrementException = [&pointerMapIt] {pointerMapIt++; };
			auto charIncrementException = [&charMapIt] {charMapIt++; };
			auto stringIncrementException = [&stringMapIt] {stringMapIt++; };
			auto fooIncrementException = [&fooMapIt] {fooMapIt++; };

			Assert::ExpectException<exception>(intIncrementException);
			Assert::ExpectException<exception>(pointerIncrementException);
			Assert::ExpectException<exception>(charIncrementException);
			Assert::ExpectException<exception>(stringIncrementException);
			Assert::ExpectException<exception>(fooIncrementException);

			intMapIt = intMap.begin();
			pointerMapIt = pointerMap.begin();
			charMapIt = charMap.begin();
			stringMapIt = stringMap.begin();
			fooMapIt = fooMap.begin();

			Hashmap<int32_t, int32_t>::Iterator otherIntMapIt = intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt = pointerMapIt;
			Hashmap<char*, int32_t>::Iterator otherCharMapIt = charMapIt;
			Hashmap<string, int32_t>::Iterator otherStringMapIt = stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt = fooMapIt;

			Assert::IsTrue(otherIntMapIt == intMapIt++);
			Assert::IsTrue(otherPointerMapIt == pointerMapIt++);
			Assert::IsTrue(otherCharMapIt == charMapIt++);
			Assert::IsTrue(otherStringMapIt == stringMapIt++);
			Assert::IsTrue(otherFooMapIt == fooMapIt++);

			intMapIt = intMap.end();
			pointerMapIt = pointerMap.end();
			charMapIt = charMap.end();
			stringMapIt = stringMap.end();
			fooMapIt = fooMap.end();

			intMapIt++;
			pointerMapIt++;
			charMapIt++;
			stringMapIt++;
			fooMapIt++;

			Assert::IsTrue(intMapIt == intMap.end());
			Assert::IsTrue(pointerMapIt == pointerMap.end());
			Assert::IsTrue(charMapIt == charMap.end());
			Assert::IsTrue(stringMapIt == stringMap.end());
			Assert::IsTrue(fooMapIt == fooMap.end());
		}

		TEST_METHOD(IteratorDeferenceOperator)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			const Hashmap<int32_t, int32_t>::Iterator& constIntMapIt = intMapIt;
			const Hashmap<int32_t*, int32_t>::Iterator& constPointerMapIt = pointerMapIt;
			const Hashmap<char*, int32_t>::Iterator& constCharMapIt = charMapIt;
			const Hashmap<string, int32_t>::Iterator& constStringMapIt = stringMapIt;
			const Hashmap<Foo, int32_t, FooHash>::Iterator& constFooMapIt = fooMapIt;

			auto intIncrementException = [intMapIt] {*intMapIt; };
			auto pointerIncrementException = [pointerMapIt] {*pointerMapIt;};
			auto charIncrementException = [charMapIt] {*charMapIt; };
			auto stringIncrementException = [stringMapIt] {*stringMapIt;};
			auto fooIncrementException = [fooMapIt] {*fooMapIt;};

			auto constIntIncrementException = [constIntMapIt] {*constIntMapIt; };
			auto constPointerIncrementException = [constPointerMapIt] {*constPointerMapIt; };
			auto constCharIncrementException = [constCharMapIt] {*constCharMapIt; };
			auto constStringIncrementException = [constStringMapIt] {*constStringMapIt; };
			auto constFooIncrementException = [constFooMapIt] {*constFooMapIt; };

			Assert::ExpectException<exception>(intIncrementException);
			Assert::ExpectException<exception>(pointerIncrementException);
			Assert::ExpectException<exception>(charIncrementException);
			Assert::ExpectException<exception>(stringIncrementException);
			Assert::ExpectException<exception>(fooIncrementException);

			Assert::ExpectException<exception>(constIntIncrementException);
			Assert::ExpectException<exception>(constPointerIncrementException);
			Assert::ExpectException<exception>(constCharIncrementException);
			Assert::ExpectException<exception>(constStringIncrementException);
			Assert::ExpectException<exception>(constFooIncrementException);

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMapIt = intMap.Insert(intPairs[i]);
				pointerMapIt = pointerMap.Insert(pointerPairs[i]);
				charMapIt = charMap.Insert(charPairs[i]);
				stringMapIt = stringMap.Insert(stringPairs[i]);
				fooMapIt = fooMap.Insert(fooPairs[i]);

				Assert::IsTrue(*intMapIt == intPairs[i]);
				Assert::IsTrue(*pointerMapIt == pointerPairs[i]);
				Assert::IsTrue(*charMapIt == charPairs[i]);
				Assert::IsTrue(*stringMapIt == stringPairs[i]);
				Assert::IsTrue(*fooMapIt == fooPairs[i]);
			}

			const Hashmap<int32_t, int32_t>::Iterator& otherConstIntMapIt = intMapIt;
			const Hashmap<int32_t*, int32_t>::Iterator& otherConstPointerMapIt = pointerMapIt;
			const Hashmap<char*, int32_t>::Iterator& otherConstCharMapIt = charMapIt;
			const Hashmap<string, int32_t>::Iterator& otherConstStringMapIt = stringMapIt;
			const Hashmap<Foo, int32_t, FooHash>::Iterator& otherConstFooMapIt = fooMapIt;

			Assert::IsTrue(*otherConstIntMapIt == intPairs[4]);
			Assert::IsTrue(*otherConstPointerMapIt == pointerPairs[4]);
			Assert::IsTrue(*otherConstCharMapIt == charPairs[4]);
			Assert::IsTrue(*otherConstStringMapIt == stringPairs[4]);
			Assert::IsTrue(*otherConstFooMapIt == fooPairs[4]);

			intMapIt = intMap.end();
			pointerMapIt = pointerMap.end();
			charMapIt = charMap.end();
			stringMapIt = stringMap.end();
			fooMapIt = fooMap.end();

			auto intIncrementException2 = [intMapIt] {*intMapIt; };
			auto pointerIncrementException2 = [pointerMapIt] {*pointerMapIt; };
			auto charIncrementException2 = [charMapIt] {*charMapIt; };
			auto stringIncrementException2 = [stringMapIt] {*stringMapIt; };
			auto fooIncrementException2 = [fooMapIt] {*fooMapIt; };

			Assert::ExpectException<exception>(intIncrementException2);
			Assert::ExpectException<exception>(pointerIncrementException2);
			Assert::ExpectException<exception>(charIncrementException2);
			Assert::ExpectException<exception>(stringIncrementException2);
			Assert::ExpectException<exception>(fooIncrementException2);

			const Hashmap<int32_t, int32_t>::Iterator& otherConstIntMapIt2 = intMapIt;
			const Hashmap<int32_t*, int32_t>::Iterator& otherConstPointerMapIt2 = pointerMapIt;
			const Hashmap<char*, int32_t>::Iterator& otherConstCharMapIt2 = charMapIt;
			const Hashmap<string, int32_t>::Iterator& otherConstStringMapIt2 = stringMapIt;
			const Hashmap<Foo, int32_t, FooHash>::Iterator& otherConstFooMapIt2 = fooMapIt;

			auto constIntIncrementException2 = [otherConstIntMapIt2] {*otherConstIntMapIt2; };
			auto constPointerIncrementException2 = [otherConstPointerMapIt2] {*otherConstPointerMapIt2; };
			auto constCharIncrementException2 = [otherConstCharMapIt2] {*otherConstCharMapIt2; };
			auto constStringIncrementException2 = [otherConstStringMapIt2] {*otherConstStringMapIt2; };
			auto constFooIncrementException2 = [otherConstFooMapIt2] {*otherConstFooMapIt2; };

			Assert::ExpectException<exception>(constIntIncrementException2);
			Assert::ExpectException<exception>(constPointerIncrementException2);
			Assert::ExpectException<exception>(constCharIncrementException2);
			Assert::ExpectException<exception>(constStringIncrementException2);
			Assert::ExpectException<exception>(constFooIncrementException2);
		}

		TEST_METHOD(IteratorArrowOperator)
		{
			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			Hashmap<int32_t, int32_t>::Iterator* intMapItPointer = &intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator* pointerMapItPointer = &pointerMapIt;
			Hashmap<char*, int32_t>::Iterator* charMapItPointer = &charMapIt;
			Hashmap<string, int32_t>::Iterator* stringMapItPointer = &stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator* fooMapItPointer = &fooMapIt;

			const Hashmap<int32_t, int32_t>::Iterator* constIntMapItPointer = &intMapIt;
			const Hashmap<int32_t*, int32_t>::Iterator* constPointerMapItPointer = &pointerMapIt;
			const Hashmap<char*, int32_t>::Iterator* constCharMapItPointer = &charMapIt;
			const Hashmap<string, int32_t>::Iterator* constStringMapItPointer = &stringMapIt;
			const Hashmap<Foo, int32_t, FooHash>::Iterator* constFooMapItPointer = &fooMapIt;

			auto intIncrementException = [intMapItPointer] {intMapItPointer->operator->(); };
			auto pointerIncrementException = [pointerMapItPointer] {pointerMapItPointer->operator->(); };
			auto charIncrementException = [charMapItPointer] {charMapItPointer->operator->(); };
			auto stringIncrementException = [stringMapItPointer] {stringMapItPointer->operator->(); };
			auto fooIncrementException = [fooMapItPointer] {fooMapItPointer->operator->(); };

			auto constIntIncrementException = [constIntMapItPointer] {constIntMapItPointer->operator->(); };
			auto constPointerIncrementException = [constPointerMapItPointer] {constPointerMapItPointer->operator->(); };
			auto constCharIncrementException = [constCharMapItPointer] {constCharMapItPointer->operator->(); };
			auto constStringIncrementException = [constStringMapItPointer] {constStringMapItPointer->operator->(); };
			auto constFooIncrementException = [constFooMapItPointer] {constFooMapItPointer->operator->(); };

			Assert::ExpectException<exception>(intIncrementException);
			Assert::ExpectException<exception>(pointerIncrementException);
			Assert::ExpectException<exception>(charIncrementException);
			Assert::ExpectException<exception>(stringIncrementException);
			Assert::ExpectException<exception>(fooIncrementException);

			Assert::ExpectException<exception>(constIntIncrementException);
			Assert::ExpectException<exception>(constPointerIncrementException);
			Assert::ExpectException<exception>(constCharIncrementException);
			Assert::ExpectException<exception>(constStringIncrementException);
			Assert::ExpectException<exception>(constFooIncrementException);

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				*intMapItPointer = intMap.Insert(intPairs[i]);
				*pointerMapItPointer = pointerMap.Insert(pointerPairs[i]);
				*charMapItPointer = charMap.Insert(charPairs[i]);
				*stringMapItPointer = stringMap.Insert(stringPairs[i]);
				*fooMapItPointer = fooMap.Insert(fooPairs[i]);

				Assert::IsTrue(*intMapItPointer->operator->() == intPairs[i]);
				Assert::IsTrue(*pointerMapItPointer->operator->() == pointerPairs[i]);
				Assert::IsTrue(*charMapItPointer->operator->() == charPairs[i]);
				Assert::IsTrue(*stringMapItPointer->operator->() == stringPairs[i]);
				Assert::IsTrue(*fooMapItPointer->operator->() == fooPairs[i]);
			}

			const Hashmap<int32_t, int32_t>::Iterator* otherConstIntMapIt = intMapItPointer;
			const Hashmap<int32_t*, int32_t>::Iterator* otherConstPointerMapIt = pointerMapItPointer;
			const Hashmap<char*, int32_t>::Iterator* otherConstCharMapIt = charMapItPointer;
			const Hashmap<string, int32_t>::Iterator* otherConstStringMapIt = stringMapItPointer;
			const Hashmap<Foo, int32_t, FooHash>::Iterator* otherConstFooMapIt = fooMapItPointer;

			Assert::IsTrue(*otherConstIntMapIt->operator->() == intPairs[4]);
			Assert::IsTrue(*otherConstPointerMapIt->operator->() == pointerPairs[4]);
			Assert::IsTrue(*otherConstCharMapIt->operator->() == charPairs[4]);
			Assert::IsTrue(*otherConstStringMapIt->operator->() == stringPairs[4]);
			Assert::IsTrue(*otherConstFooMapIt->operator->() == fooPairs[4]);
		}

		TEST_METHOD(IteratorEquality)
		{

			Hashmap<int32_t, int32_t>::Iterator intMapIt;
			Hashmap<int32_t*, int32_t>::Iterator pointerMapIt;
			Hashmap<char*, int32_t>::Iterator charMapIt;
			Hashmap<string, int32_t>::Iterator stringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt;

			Hashmap<int32_t, int32_t>::Iterator otherIntMapIt;
			Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt;
			Hashmap<char*, int32_t>::Iterator otherCharMapIt;
			Hashmap<string, int32_t>::Iterator otherStringMapIt;
			Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt;

			Assert::IsTrue(intMapIt == otherIntMapIt);
			Assert::IsTrue(pointerMapIt == otherPointerMapIt);
			Assert::IsTrue(charMapIt == otherCharMapIt);
			Assert::IsTrue(stringMapIt == otherStringMapIt);
			Assert::IsTrue(fooMapIt == otherFooMapIt);

			Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
			Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
			Hashmap<char*, int32_t> charMap(numberOfBuckets);
			Hashmap<string, int32_t> stringMap(numberOfBuckets);
			Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

			for (uint32_t i = 0; i < numberOfTestElements; ++i)
			{
				intMapIt = intMap.Insert(intPairs[i]);
				pointerMapIt = pointerMap.Insert(pointerPairs[i]);
				charMapIt = charMap.Insert(charPairs[i]);
				stringMapIt = stringMap.Insert(stringPairs[i]);
				fooMapIt = fooMap.Insert(fooPairs[i]);

				otherIntMapIt = intMapIt;
				otherPointerMapIt = pointerMapIt;
				otherCharMapIt = charMapIt;
				otherStringMapIt = stringMapIt;
				otherFooMapIt = fooMapIt;

				Assert::IsTrue(intMapIt == otherIntMapIt);
				Assert::IsTrue(pointerMapIt == otherPointerMapIt);
				Assert::IsTrue(charMapIt == otherCharMapIt);
				Assert::IsTrue(stringMapIt == otherStringMapIt);
				Assert::IsTrue(fooMapIt == otherFooMapIt);
			}
		}

			TEST_METHOD(IteratorInequality)
			{
				Hashmap<int32_t, int32_t> intMap(numberOfBuckets);
				Hashmap<int32_t*, int32_t> pointerMap(numberOfBuckets);
				Hashmap<char*, int32_t> charMap(numberOfBuckets);
				Hashmap<string, int32_t> stringMap(numberOfBuckets);
				Hashmap<Foo, int32_t, FooHash> fooMap(numberOfBuckets);

				Hashmap<int32_t, int32_t> otherIntMap(numberOfBuckets);
				Hashmap<int32_t*, int32_t> otherPointerMap(numberOfBuckets);
				Hashmap<char*, int32_t> otherCharMap(numberOfBuckets);
				Hashmap<string, int32_t> otherStringMap(numberOfBuckets);
				Hashmap<Foo, int32_t, FooHash> otherFooMap(numberOfBuckets);

				Hashmap<int32_t, int32_t>::Iterator intMapIt = intMap.begin();
				Hashmap<int32_t*, int32_t>::Iterator pointerMapIt = pointerMap.begin();
				Hashmap<char*, int32_t>::Iterator charMapIt = charMap.begin();
				Hashmap<string, int32_t>::Iterator stringMapIt = stringMap.begin();
				Hashmap<Foo, int32_t, FooHash>::Iterator fooMapIt = fooMap.begin();

				Hashmap<int32_t, int32_t>::Iterator otherIntMapIt = otherIntMap.begin();
				Hashmap<int32_t*, int32_t>::Iterator otherPointerMapIt = otherPointerMap.begin();
				Hashmap<char*, int32_t>::Iterator otherCharMapIt = otherCharMap.begin();
				Hashmap<string, int32_t>::Iterator otherStringMapIt = otherStringMap.begin();
				Hashmap<Foo, int32_t, FooHash>::Iterator otherFooMapIt = otherFooMap.begin();

				Assert::IsTrue(intMapIt != otherIntMapIt);
				Assert::IsTrue(pointerMapIt != otherPointerMapIt);
				Assert::IsTrue(charMapIt != otherCharMapIt);
				Assert::IsTrue(stringMapIt != otherStringMapIt);
				Assert::IsTrue(fooMapIt != otherFooMapIt);

				intMapIt = intMap.Insert(intPairs[0]);
				pointerMapIt = pointerMap.Insert(pointerPairs[0]);
				charMapIt = charMap.Insert(charPairs[0]);
				stringMapIt = stringMap.Insert(stringPairs[0]);
				fooMapIt = fooMap.Insert(fooPairs[0]);

				otherIntMapIt = intMap.Insert(intPairs[1]);
				otherPointerMapIt = pointerMap.Insert(pointerPairs[1]);
				otherCharMapIt = charMap.Insert(charPairs[1]);
				otherStringMapIt = stringMap.Insert(stringPairs[1]);
				otherFooMapIt = fooMap.Insert(fooPairs[1]);

				Assert::IsTrue(intMapIt != otherIntMapIt);
				Assert::IsTrue(pointerMapIt != otherPointerMapIt);
				Assert::IsTrue(charMapIt != otherCharMapIt);
				Assert::IsTrue(stringMapIt != otherStringMapIt);
				Assert::IsTrue(fooMapIt != otherFooMapIt);

				otherIntMapIt = intMap.Insert(std::pair<uint32_t, int32_t>(intPairs[1].first, 10));
				otherPointerMapIt = pointerMap.Insert(std::pair<int32_t*, int32_t>(pointerPairs[1].first, 10));
				otherCharMapIt = charMap.Insert(std::pair<char*, int32_t>(charPairs[1].first, 10));
				otherStringMapIt = stringMap.Insert(std::pair<string, int32_t>(stringPairs[1].first, 10));
				otherFooMapIt = fooMap.Insert(std::pair<Foo, int32_t>(fooPairs[1].first, 10));

				Assert::IsTrue(intMapIt != otherIntMapIt);
				Assert::IsTrue(pointerMapIt != otherPointerMapIt);
				Assert::IsTrue(charMapIt != otherCharMapIt);
				Assert::IsTrue(stringMapIt != otherStringMapIt);
				Assert::IsTrue(fooMapIt != otherFooMapIt);

			}

	private:
		static _CrtMemState sStartMemState;
		static const int32_t numberOfBuckets = 3;
		static const int32_t numberOfTestElements = 5;

		std::int32_t testVariable1 = 10;
		std::int32_t testVariable2 = 20;
		std::int32_t testVariable3 = 30;
		std::int32_t testVariable4 = 40;
		std::int32_t testVariable5 = 50;

		std::int32_t* pointerTestVariable1 = &testVariable1;
		std::int32_t* pointerTestVariable2 = &testVariable2;
		std::int32_t* pointerTestVariable3 = &testVariable3;
		std::int32_t* pointerTestVariable4 = &testVariable4;
		std::int32_t* pointerTestVariable5 = &testVariable5;

		Foo fooTestVariable1 = { 1, 10 };
		Foo fooTestVariable2 = { 2, 20 };
		Foo fooTestVariable3 = { 3, 30 };
		Foo fooTestVariable4 = { 4, 40 };
		Foo fooTestVariable5 = { 5, 50 };

		std::pair<int32_t, int32_t> intPairs[numberOfTestElements] = { { 1,10 },{ 2,20 },{ 3,30 },{ 4,40 },{ 5,50 } };
		std::pair<int32_t*, int32_t> pointerPairs[numberOfTestElements] = { {pointerTestVariable1, 10}, {pointerTestVariable2, 20} , {pointerTestVariable3, 30},  {pointerTestVariable4, 40}, {pointerTestVariable5, 50} };
		std::pair<char*, int32_t> charPairs[numberOfTestElements] = { { "Hi",10 },{ "Hello",20},{ "Hiya",30},{ "Howdy", 40} ,{"Hai", 50} };
		std::pair<string, int32_t> stringPairs[numberOfTestElements] = { { "Hi",10 },{ "Hello",20 },{ "Hiya",30},{ "Howdy", 40}, {"Hai", 50} };
		std::pair<Foo, int32_t> fooPairs[numberOfTestElements] = { {fooTestVariable1, 10}, {fooTestVariable2,20}, {fooTestVariable3,30}, {fooTestVariable4,40}, {fooTestVariable5,50} };

	};
	_CrtMemState HashmapTest::sStartMemState;
}