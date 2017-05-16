#pragma once
namespace FieaGameEngine
{
	template<class AbstractProductT>
	typename Factory<AbstractProductT>::FactoryMap Factory<AbstractProductT>::sFactoryTable;

	template<class AbstractProductT>
	typename Factory<AbstractProductT>::Iterator Factory<AbstractProductT>::begin()
	{
		return sFactoryTable.begin();
	}

	template<class AbstractProductT>
	typename Factory<AbstractProductT>::Iterator Factory<AbstractProductT>::end()
	{
		return sFactoryTable.end();
	}

	template<class AbstractProductT>
	Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& className)
	{
		Factory<AbstractProductT>*  returnFactory = nullptr;

		Hashmap<std::string, Factory<AbstractProductT>*>::Iterator it = sFactoryTable.Find(className);

		if (it != sFactoryTable.end())
		{
			returnFactory = it->second;
		}

		return returnFactory;
	}

	template<class AbstractProductT>
	AbstractProductT* Factory<AbstractProductT>::Create(const std::string& className)
	{
		AbstractProductT* returnPointer = nullptr;
		Hashmap<std::string, Factory<AbstractProductT>*>::Iterator it = sFactoryTable.Find(className);

		if (it != sFactoryTable.end())
		{
			returnPointer = it->second->Create();
		}

		return returnPointer;
	}

	template<class AbstractProductT>
	void Factory<AbstractProductT>::Add(Factory<AbstractProductT>* factory)
	{
		std::pair<std::string, Factory<AbstractProductT>*> pair = { factory->ClassName(), factory };

		sFactoryTable.Insert(pair);
	}

	template<class AbstractProductT>
	void Factory<AbstractProductT>::Remove(Factory<AbstractProductT>* factory)
	{
		if (Find(factory->ClassName()) == factory)
		{
			sFactoryTable.Remove(factory->ClassName());
		}
	}
}