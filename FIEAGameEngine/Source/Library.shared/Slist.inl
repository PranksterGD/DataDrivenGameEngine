namespace FieaGameEngine
{

	/************************************************************************/
	/* SList Implementation
	/************************************************************************/
	template<typename T>
	SList<T>::SList() :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{

	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& value)
	{
		mFront = new Node(value, mFront);

		if (mBack == nullptr)
		{
			mBack = mFront;
		}
		mSize++;

		return begin();
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& value)
	{
		Node* back = new Node(value);
		if (IsEmpty())
		{
			mFront = back;
		}
		else
		{
			mBack->Next = back;
		}

		mBack = back;
		mSize++;

		return Iterator(mBack, this);
	}

	template<typename T>
	T SList<T>::PopFront()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty");
		}
		else
		{
			T value = mFront->Data;
			Node *front = mFront;
			mFront = mFront->Next;
			delete(front);
			mSize--;
			return value;
		}
	}

	template<typename T>
	bool SList<T>::IsEmpty() const
	{
		return(mFront == nullptr);
	}

	template<typename T>
	const T& SList<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty");
		}

		return mFront->Data;
	}

	template<typename T>
	const T& SList<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty");
		}

		return mBack->Data;
	}

	template<typename T>
	T& SList<T>::Front()
	{
		return const_cast<T&> (const_cast<const SList*> (this)->Front());
	}

	template<typename T>
	T& SList<T>::Back()
	{
		return const_cast<T&> (const_cast<const SList*> (this)->Back());
	}

	template<typename T>
	std::uint32_t SList<T>::Size()
	{
		return mSize;
	}

	template<typename T>
	SList<T>::SList(const SList& otherList) :
		mSize(0), mFront(nullptr), mBack(nullptr)
	{
		CopyNodes(otherList);
	}

	template<typename T>
	SList<T>::SList(SList&& otherList) :
		mSize(otherList.mSize), mFront(otherList.mFront), mBack(otherList.mBack)
	{
		otherList.mFront = nullptr;
		otherList.mBack = nullptr;
		otherList.mSize = 0;
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList& otherList)
	{
		if (this != &otherList)
		{
			Clear();
			CopyNodes(otherList);
		}

		return *this;
	}

	template<typename T>
	SList<T>& SList<T>::operator=(SList&& otherList)
	{
		if (this != &otherList)
		{
			Clear();
			mFront = otherList.mFront;
			mBack = otherList.mBack;
			mSize = otherList.mSize;

			otherList.mFront = nullptr;
			otherList.mBack = nullptr;
			otherList.mSize = 0;
		}

		return *this;
	}

	template<typename T>
	void SList<T>::CopyNodes(const SList<T>& otherList)
	{
		for (Iterator it = otherList.begin(); it != otherList.end(); ++it)
		{
			PushBack(it.mNode->Data);
		}
	}

	template<typename T>
	void SList<T>::Clear()
	{
		while (mFront != nullptr)
		{
			PopFront();
		}
	}

	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(mFront, this);
	}

	template<typename T>
	typename const SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(nullptr, this);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		Iterator it;
		bool isFound = false;
		for (it = this->begin(); it != this->end(); ++it)
		{
			if (*it == value)
			{
				isFound = true;
				break;
			}
		}
		if (!isFound)
		{
			it = this->end();
		}

		return it;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::InsertAfter(const T& value, typename SList<T>::Iterator it)
	{
		Iterator returnIt;
		if (it.mOwner == this)
		{
			if (it != end())
			{
				Node* newNode = new Node(value, it.mNode->Next);
				it.mNode->Next = newNode;
				mSize++;
				returnIt.mNode = newNode;
				returnIt.mOwner = this;
			}
			else
			{
				returnIt = PushBack(value);
			}

			return returnIt;
		}
		else
		{
			throw std::exception("Invalid Owner");
		}

	}

	template<typename T>
	void SList<T>::Remove(const T& value)
	{
		Iterator it = Find(value);
		Iterator otherIt = begin();
		if (it != end())
		{
			if (it == otherIt)
			{
				mFront = it.mNode->Next;
				delete it.mNode;
			}
			else
				if (it.mNode == mBack)
				{
					while (otherIt != end())
					{
						if (otherIt.mNode->Next == it.mNode)
						{
							otherIt.mNode->Next = nullptr;
							mBack = otherIt.mNode;
							delete it.mNode;
							break;
						}
						++otherIt;
					}
				}
				else
				{
					Node* nodeToDelete = it.mNode->Next;
					it.mNode->Data = nodeToDelete->Data;
					it.mNode->Next = nodeToDelete->Next;
					if (nodeToDelete == mBack)
					{
						mBack = it.mNode;
					}
					delete nodeToDelete;
				}
			mSize--;
		}
	}

	/************************************************************************/
	/* Node Implementation
	/************************************************************************/

	template<typename T>
	SList<T>::Node::Node(T data, Node* next = nullptr) :
		Data(data), Next(next)
	{

	}

	template<typename T>
	SList<T>::Node::Node() :
		Next(nullptr)
	{

	}

	/************************************************************************/
	/* Iterator Implementation
	/************************************************************************/

	template<typename T>
	SList<T>::Iterator::Iterator() :
		mNode(nullptr), mOwner(nullptr)
	{

	}

	template<typename T>
	SList<T>::Iterator::Iterator(Node* Node, const SList* owner) :
		mNode(Node), mOwner(owner)
	{

	}

	template<typename T>
	bool SList<T>::Iterator::operator==(const Iterator& otherIterator) const
	{
		return(mOwner == otherIterator.mOwner && mNode == otherIterator.mNode);
	}

	template<typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& otherIterator) const
	{
		return !(*this == otherIterator);
	}

	template<typename T>
	typename SList<T>::Iterator&  SList<T>::Iterator::operator++ ()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->Next;
		}

		return *this;
	}

	template<typename T>
	typename SList<T>::Iterator  SList<T>::Iterator::operator++ (int)
	{
		Iterator temp(*this);
		operator++();
		return temp;
	}

	template<typename T>
	T&  SList<T>::Iterator::operator*()
	{
		if (*this == mOwner->end())
		{
			throw std::exception("Invalid access");
		}
		return mNode->Data;
	}

	template<typename T>
	const T&  SList<T>::Iterator::operator*() const
	{
		return mNode->Data;
	}

	template<typename T>
	SList<T>::Iterator::~Iterator()
	{

	}
}
