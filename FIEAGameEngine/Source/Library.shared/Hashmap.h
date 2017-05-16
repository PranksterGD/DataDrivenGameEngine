#pragma once
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"
namespace FieaGameEngine
{
	template<typename TKey, typename TValue, typename HashFunctor = DefaultHash<TKey> >
	class Hashmap
	{
	typedef std::pair<TKey, TValue> PairType;
	typedef SList<PairType> ChainType;
	typedef Vector<ChainType> BucketType;
	public:
		class Iterator
		{
			friend class Hashmap;
		public:
			/**The default constructor for the iterator. */
			Iterator();

			/**The assignment operator for the iterator.
			* @param otherIterator- The other Iterator to which the current iterator is to be
			assigned to.*/
			~Iterator() = default;

			/**The copy constructor for the iterator.
			* @param otherIterator- The other Iterator from which the current iterator is to be
			copied from.*/
			Iterator(const Iterator& otherIterator) = default;

			/**The pre increment operator for the iterator.
			* @return Reference to the iterator after increment.
			* @exception Throws exception if the operator is called on an iterator that does not have an owner. */
			Iterator& operator++();

			/**The post increment operator for the iterator.
			* @return A copy of the iterator before increment.
			* @exception Throws exception if the operator is called on an iterator that does not have an owner. */
			Iterator operator++(int);

			/**The deference operator for the iterator.
			* @return A reference of the pair pointed to by the iterator.
			* @exception Throws exception if the operator is called on an iterator that does not have an owner
			 or is at the end of the hashmap */
			PairType& operator*();

			/**The const version  deference operator for the iterator.
			* @return A const  reference of the pair pointed to by the iterator.
			* @exception Throws exception if the operator is called on an iterator that does not have an owner
			or is at the end of the hashmap */
			const PairType& operator* () const;

			/**The arrow operator for the iterator.
			* @return A pointer to the pair pointed to by the iterator.
			* @exception Throws exception if the operator is called on an iterator that does not have an owner
			or is at the end of the hashmap */
			PairType* operator->();

			/**The arrow operator for the iterator.
			* @return A const pointer to the pair pointed to by the iterator.
			* @exception Throws exception if the operator is called on an iterator that does not have an owner
			or is at the end of the hashmap */
			const PairType* operator-> () const;

			/**The equality operator for the iterator
			* @param otherIterator- The iterator to be compared against
			* @return A boolean: True- the iterators are equal. False-They are not equal*/
			bool operator==(const Iterator& otherIterator) const;

			/**The inequality operator for the iterator
			* @param otherIterator- The iterator to be compared against
			* @return A boolean: True- the iterators are not equal. False-They are  equal*/
			bool operator!=(const Iterator& otherIterator) const;

			/**The assignment operator for the iterator.
			* @param otherIterator- The other Iterator to which the current iterator is to be
			assigned to.*/
			Iterator& operator=(const Iterator& otherIterator) = default;

		private:
			Iterator(typename ChainType::Iterator sListIterator, std::uint32_t bucketNumber, const Hashmap& owner);
			typename ChainType::Iterator mSlistIterator;
			std::uint32_t mBucketNumber;
			const Hashmap* mOwner;
		};

		/** The constructor that creates a hashmap with a certain number of buckets.
		* @param numberOfBuckets- The number of buckets of the hashmap
		* @default The numberOfBuckets is defaulted to 11 if no value is passed in*/
		explicit Hashmap(std::uint32_t NumberOfBuckets = 11);

		/**The copy constructor for the hashmap.
		* @param otherHashmap- The other hashmap from which the current hashmap is to be
		copied from.*/
		Hashmap(const Hashmap& otherHashmap) = default;

		Hashmap(Hashmap&& otherHashmap) = default;

		/**The assignment operator for the hashmap.
		* @param otherHashmap- The other hashmap to which the current hashmap is to be
		assigned to.*/
		Hashmap& operator=(const Hashmap& otherHashmap) = default;

		Hashmap& operator=(Hashmap&& otherHashmap) = default;

		/** The destructor for the hashmap that ensures that there are no memory leaks */
		~Hashmap()= default;

		/** Function that searches the hashmap for a certain key.
		* @param Key- The key to be searched for.
		* @return An Iterator pointing to the pair that contains the found key. Returns end if the key 
		 is not found.*/
		Iterator Find(const TKey& Key) const;

		Iterator Find(const TKey& key, std::uint32_t& index) const;

		/** Function that takes a Pair and tries to insert it into the hashmap/
		* @param Pair- The pair that is to be inserted.
		* @return An Iterator pointing to the pair that was inserted. If the pair already exists in the hashmap,
		 returns a reference to the pair that was found. */
		Iterator Insert(const PairType& Pair);

		Iterator Insert(const PairType& Pair, bool& inserted);

		/** Subscript operator for the hashmap. 
		* @param Key- The key for which the value is required.
		* @return- A reference to the Value portion of the key, value pair. If the key does not exist in the 
		* hashmap, inserts it into the hashmap with a default constructed value.*/
		TValue& operator[](const TKey& Key);

		/** Const Subscript operator for the hashmap.
		* @param Key- The key for which the value is required.
		* @return- A const reference to the Value portion of the key, value pair.
		* @exception- Throws an exception if the key does not exist in the hashmap. */
		const TValue& operator[](const TKey& Key) const;

		/** Function that removes a certain pair from the hashmap.
		* @param key- The key of the pair that is to be removed.*/
		void Remove(const TKey& Key);

		/** Function that removes all the pairs from the hashmap. */
		void Clear();

		/** Function that gives the size of the hashmap
		* @return The number of elements in the hashmap as an unsigned int.*/
		std::uint32_t Size() const;

		/** Function that tells if a certain key exists in the hashmap.
		* @param key- The key to be searched for.
		* @return A boolean- True if the key exists in the hashmap, false otherwise. */
		bool ContainsKey(const TKey& Key) const;

		/** Function that returns an iterator pointing to the first element of the hashmap.
		*@return An iterator pointing to the first element of the hashmap.*/
		Iterator begin() const;

		/** Function that returns a constant iterator that is out of the hashmap.
		*@return A constant iterator that is out of the hashmap .*/
		Iterator end() const;

		bool operator==(const Hashmap& otherHashmap) const ;

		bool operator!=(const Hashmap& otherHashmap) const;

	private:
		std::uint32_t mSize;
		BucketType mBucket;
		HashFunctor mHashFunctor;
	};
}

#include "Hashmap.inl"
