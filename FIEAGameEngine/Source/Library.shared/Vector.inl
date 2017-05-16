namespace FieaGameEngine
{

	/************************************************************************/
	/* Vector Implementation
	/************************************************************************/
	template<typename T>
	Vector<T>::Vector(std::uint32_t capacity):
		mSize(0), mCapacity(0), mBuffer(nullptr)
	{
		Reserve(capacity);
	}

	template<typename T>
	Vector<T>::~Vector()
	{
		Destroy();
	}

	template<typename T>
	T& Vector<T>::operator[](const std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds");
		}
		return *(mBuffer + index);
	}

	template<typename T>
	const T& Vector<T>::operator[](const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds");
		}
		return *(mBuffer + index);
	}

	template<typename T>
	void Vector<T>::PopBack()
	{
		if (!IsEmpty())
		{
			mBuffer[--mSize].~T();
		}

	}

	template<typename T>
	bool Vector<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	template<typename T>
	T& Vector<T>::Front()
	{
		
		return const_cast<T&>(const_cast<const Vector* >(this)->Front());
	}

	template<typename T>
	const T& Vector<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("Vector is empty");
		}
		return *mBuffer;
	}

	template<typename T>
	const T& Vector<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("Vector is empty");
		}
		return *(mBuffer + mSize - 1);
	}

	template<typename T>
	T& Vector<T>::Back()
	{
		return const_cast<T&>(const_cast<const Vector*>(this)->Back());

	}

	template<typename T>
	std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	std::uint32_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(mBuffer, *this);
	}

	template<typename T>
	typename const Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator (mBuffer+ mSize, *this);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& value)
	{
		if (mSize == mCapacity)
		{
			uint32_t newCapacity = mCapacity+Realloate();
			Reserve(newCapacity);
		}
		new (mBuffer + mSize) T(value);
		++mSize;

		return Iterator(mBuffer + mSize - 1, *this);
	}


	template<typename T>
	Vector<T>::Vector(const Vector& otherVector):
		mBuffer(nullptr), mSize(otherVector.mSize), mCapacity(otherVector.mCapacity)
	{
		DeepCopy(otherVector);
	}

	template<typename T>
	Vector<T>::Vector(Vector&& otherVector) :
		mSize(otherVector.mSize), mCapacity(otherVector.mCapacity), mBuffer(otherVector.mBuffer)
	{
		otherVector.mBuffer = nullptr;
		otherVector.mSize = 0;
		otherVector.mCapacity = 0;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector& otherVector)
	{
		if (this != &otherVector)
		{
			Clear();
			free(mBuffer);
			mSize = otherVector.mSize;
			mCapacity = otherVector.mCapacity;
			DeepCopy(otherVector);
		}
		return *this;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector&& otherVector)
	{
		if (this != &otherVector)
		{
			Clear();
			free(mBuffer);

			mSize = otherVector.mSize;
			mCapacity = otherVector.mCapacity;
			mBuffer = otherVector.mBuffer;

			otherVector.mBuffer = nullptr;
			otherVector.mSize = 0;
			otherVector.mCapacity = 0;
		}
		return *this;
	}

	template<typename T>
	T& Vector<T>::At(const std::uint32_t index)
	{
		return (*this)[index];
	}

	template<typename T>
	const T& Vector<T>::At(const std::uint32_t index) const
	{
		return (*this)[index];
	}

	template<typename T>
	void Vector<T>::Reserve(std::uint32_t newCapacity)
	{
		if (newCapacity > mCapacity)
		{
			mCapacity = newCapacity;
			mBuffer = (T*)realloc(mBuffer, sizeof(T)*mCapacity);
		}
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value) const
	{
		Iterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (*it == value)
			{
				break;
			}
		}
		return it;
	}

	template<typename T>
	void Vector<T>::Clear()
	{
		for (T &value : *this)
		{
			value.~T();
		}


		mSize = 0;
		ShrinkToFit();
		Reserve(defaultCapacity);
	}

	template<typename T>
	void Vector<T>::Destroy()
	{
		Clear();
		free(mBuffer);
		mCapacity = 0;
	}

	template<typename T>
	void Vector<T>::Remove(const T& value)
	{
		if (!IsEmpty())
		{
			Iterator it = Find(value);
			Iterator iterationIterator = it;
			if (it != end())
			{
				while (++iterationIterator != end())
				{
					*it.mData = *(iterationIterator);
					++it;
				}
				(mBuffer + mSize - 1)->~T();
				--mSize;
			}
		}	
	}

	template<typename T>
	void Vector<T>::Remove(typename Vector<T>::Iterator& start, typename Vector<T>::Iterator& finish)
	{
		uint32_t numberofDeletes = 0;
		Iterator finishIterator =finish++;
		if (start.mData < finish.mData)
		{
			for (; start != finish; ++start)
			{
				if (++finishIterator != end())
				{
					*start = *finishIterator;
					finishIterator.mData->~T();
				}
				else
				{
					start.mData->~T();
				}
				++numberofDeletes;
			}
			while (++finishIterator != end())
			{
				new ((finish++).mData) T(*finishIterator);
				finishIterator.mData->~T();

			}
			mSize -= numberofDeletes;
		}	
	}

	template<typename T>
	void Vector<T>::ShrinkToFit()
	{
		if (mSize != mCapacity)
		{
			mCapacity = 0;
			Reserve(mSize);
		}
	}

	template<typename T>
	void Vector<T>::DeepCopy(const Vector& otherVector)
	{
		mBuffer = (T*)malloc(sizeof(T)*mCapacity);
		T* iterationPointer = mBuffer;
		for (T value : otherVector)
		{
			new (iterationPointer++) T(value);
		}
	}

	template<typename T>
	uint32_t Vector<T>::Realloate()
	{

		return mCapacity + 1;
	}


	/************************************************************************/
	/* Iterator Implementation
	/************************************************************************/

	template<typename T>
	Vector<T>::Iterator::Iterator() :
		mData(nullptr), mOwner(nullptr)
	{

	}

	template<typename T>
	Vector<T>::Iterator::Iterator(const Iterator& otherIterator) :
		mData(otherIterator.mData), mOwner(otherIterator.mOwner)
	{

	}

	template<typename T>
	Vector<T>::Iterator::Iterator(T* data, const Vector& owner) :
		mData(data), mOwner(&owner)
	{

	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& otherIterator) 
	{
		if (this != &otherIterator)
		{
			mData=otherIterator.mData;
			mOwner = otherIterator.mOwner;
		}
		return *this;
	}

	template<typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& otherIterator) const
	{
		return(mOwner == otherIterator.mOwner && mData == otherIterator.mData);
	}

	template<typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& otherIterator) const
	{
		return !(*this == otherIterator);
	}

	template<typename T>
	typename Vector<T>::Iterator&  Vector<T>::Iterator::operator++ ()
	{
		if (mOwner==nullptr||*this!=mOwner->end())
		{
			++mData;
		}

		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator  Vector<T>::Iterator::operator++ (int)
	{
		Iterator temp(*this);
		operator++();
		return temp;
	}

	template<typename T>
	T&  Vector<T>::Iterator::operator*()
	{
		if (mOwner == nullptr || *this == mOwner->end())
		{
			throw std::exception("Invalid access");
		}
		return *mData;
	}

	template<typename T>
	const T&  Vector<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr || *this == mOwner->end())
		{
			throw std::exception("Invalid access");
		}
		return *mData;
	}
}