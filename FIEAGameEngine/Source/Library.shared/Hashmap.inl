namespace FieaGameEngine
{
#pragma region Hashmap
	template<typename TKey, typename TValue, typename HashFunctor>
	Hashmap<TKey, TValue, HashFunctor>::Hashmap(std::uint32_t numberOfBuckets) :
		 mSize(0), mBucket(numberOfBuckets)
	{
		for (std::uint32_t i = 0; i < numberOfBuckets; ++i)
		{
			mBucket.PushBack(ChainType());
		}
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	void Hashmap<TKey, TValue, HashFunctor>::Clear()
	{
		for (ChainType& chain : mBucket)
		{
			chain.Clear();
		}

		mSize = 0;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Find(const TKey& key) const
	{
		std::uint32_t index;
		Iterator it =Find(key, index);
		return it;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Find(const TKey& key, std::uint32_t & index) const
	{
		uint32_t hashValue = mHashFunctor(key);
		hashValue %= mBucket.Size();

		ChainType::Iterator it;
		Iterator returnIt = end();
		const ChainType& chain = mBucket[hashValue];

		for (it = chain.begin(); it != chain.end(); ++it)
		{
			if ((*it).first == key)
			{
				returnIt = Iterator(it, hashValue, *this);
				break;
			}
		}

		index = hashValue;
		return returnIt;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Insert(const PairType& pair)
	{
		bool inserted;
		Iterator it = Insert(pair, inserted);
		return it;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Insert(const PairType& pair, bool& inserted)
	{
		std::uint32_t index;
		Iterator findIt = Find(pair.first, index);
		if (findIt == end())
		{
			ChainType::Iterator slistIterator = mBucket[index].PushBack(pair);
			findIt = Iterator(slistIterator, index, *this);
			++mSize;
			inserted = true;
		}
		else
		{
			inserted = false;
		}

		return findIt;
	}



	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::begin() const
	{
		std::uint32_t bucketNumber = 0;
		Iterator it = end();

		if (mSize > 0)
		{
			while (mBucket[bucketNumber].IsEmpty())
			{
				++bucketNumber;
			}

			it = Iterator(mBucket[bucketNumber].begin(), bucketNumber, *this);
		}

		return it;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::end() const
	{
		return Iterator(ChainType::Iterator(), mBucket.Size(), *this);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	const TValue& Hashmap<TKey, TValue, HashFunctor>::operator[](const TKey& key) const
	{
		Iterator it = Find(key);

		if (it == end())
		{
			throw std::exception("No such Key exists");
		}

		return (*it).second;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	TValue& Hashmap<TKey, TValue, HashFunctor>::operator[](const TKey& key)
	{
		return Insert(PairType(key, TValue()))->second;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	void Hashmap<TKey, TValue, HashFunctor>::Remove(const TKey& key)
	{
		Iterator it = Find(key);

		if (it != end())
		{
			mBucket[it.mBucketNumber].Remove(*it);
			--mSize;
		}
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	bool Hashmap<TKey, TValue, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return Find(key) != end();
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	std::uint32_t Hashmap<TKey, TValue, HashFunctor>::Size() const
	{
		return mSize;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	bool Hashmap<TKey, TValue, HashFunctor>::operator==(const Hashmap& otherHashmap) const
	{
		bool isEqual = otherHashmap.mSize == mSize;

		if (isEqual)
		{
			for (PairType value : otherHashmap)
			{
				Iterator it = Find(value.first);
				if (it == end() || value.second != it->second)
				{
					isEqual = false;
					break;
				}
			}
		}

		return isEqual;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	bool Hashmap<TKey, TValue, HashFunctor>::operator!=(const Hashmap& otherHashmap) const 
	{
		return !(*this == otherHashmap);
	}


#pragma endregion Hashmap

#pragma region Iterator
	template<typename TKey, typename TValue, typename HashFunctor>
	Hashmap<typename TKey, typename TValue, typename HashFunctor>::Iterator::Iterator():
		mOwner(nullptr), mBucketNumber(0)
	{

	}

	template<typename TKey, typename TValue, typename HashFunctor>
	Hashmap<typename TKey, typename TValue, typename HashFunctor>::Iterator::Iterator(typename ChainType::Iterator sListIterator, std::uint32_t bucketNumber, const Hashmap& owner) :
		mSlistIterator(sListIterator), mBucketNumber(bucketNumber), mOwner(&owner)
	{

	}

	template<typename TKey, typename TValue, typename HashFunctor>
	bool Hashmap<TKey, TValue, HashFunctor>::Iterator::operator==(const Iterator& otherIterator) const
	{
		return(mOwner == otherIterator.mOwner && mBucketNumber == otherIterator.mBucketNumber && mSlistIterator == otherIterator.mSlistIterator);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	bool Hashmap<TKey, TValue, HashFunctor>::Iterator::operator!=(const Iterator& otherIterator) const
	{
		return !(*this == otherIterator);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator& Hashmap<TKey, TValue, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("No Owner");
		}
		if (*this != mOwner->end())
		{
			if (++mSlistIterator == mOwner->mBucket[mBucketNumber].end())
			{
				while (++mBucketNumber < mOwner->mBucket.Size() && mOwner->mBucket[mBucketNumber].IsEmpty())
				{

				}

				mSlistIterator = mOwner->end().mSlistIterator;

				if (mBucketNumber != mOwner->mBucket.Size())
				{
					mSlistIterator = mOwner->mBucket[mBucketNumber].begin();
				}
			}
		}

		return *this;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Iterator::operator++(int)
	{
		Iterator temp(*this);
		operator++();
		return temp;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::PairType&  Hashmap<TKey, TValue, HashFunctor>::Iterator::operator*()
	{

		return const_cast <PairType&>(const_cast<const Iterator*> (this)->operator*());
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	const typename Hashmap<TKey, TValue, HashFunctor>::PairType&  Hashmap<TKey, TValue, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner==nullptr || *this == mOwner->end())
		{
			throw std::exception("Invalid Access");
		}

		return *mSlistIterator;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	const typename Hashmap<TKey, TValue, HashFunctor>::PairType*  Hashmap<TKey, TValue, HashFunctor>::Iterator::operator->() const
	{
		if (mOwner == nullptr || *this == mOwner->end())
		{
			throw std::exception("Invalid Access");
		}

		return &(*mSlistIterator);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	typename Hashmap<TKey, TValue, HashFunctor>::PairType*  Hashmap<TKey, TValue, HashFunctor>::Iterator::operator->()
	{
		return const_cast <PairType*>(const_cast<const Iterator*> (this)->operator->());
	}
#pragma endregion Iterator
}