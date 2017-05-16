#pragma once
#include "Hashmap.h"
#include <string>
namespace FieaGameEngine
{
	template<class AbstractProductT>
	class Factory
	{
		
	public:
		typedef Hashmap<std::string, Factory<AbstractProductT>*> FactoryMap;
		typedef typename FactoryMap::Iterator Iterator;

		/**Function that returns the name of the class that the factory knows to create.
		* @return- A string that contains the name of the class that the factory knows to create.*/
		virtual std::string ClassName() = 0;

		/**Static function for the Factory that returns a hash map iterator pointing to the first element in the hash map.
		* @return- A hash map iterator pointing to the first element in the hash map. */
		static typename Iterator begin();

		/**Static function for the Factory that returns a hash map iterator pointing to the first element past the
		end of the iterator.
		* @return- A hashmap iterator pointing to the first element past the
		end of the iterator. */
		static typename Iterator end();

	private:

		/**Function that is used to create a new instance of the product and return it through an
		abstract product interface.
		@return- An abstract product pointer pointing to the newly cleared concrete product.*/
		virtual AbstractProductT* Create() = 0;

	public:

		/**Function that searches the hash map for a class name, and returns the Factory pointer associated with the class name.
		* @param className- The name of the class to be searched for.
		* @return An abstract product factory pointer pointing to a concrete factory.*/
		static Factory<AbstractProductT>* Find(const std::string& className);

		/**Function that provides a public interface to create new instances of a specific class.
		* @param className- The name of the class to be created. 
		* @return- An abstract product pointer pointing to the newly cleared concrete product.*/
		static AbstractProductT* Create(const std::string& className);

	protected:

		static void Add(Factory<AbstractProductT>* factory);

		static void Remove(Factory<AbstractProductT>* factory);

	private:

		static FactoryMap sFactoryTable;
	};

#define  ConcreteFactory(ConcreteProductT, AbstractProductT)			\
	class ConcreteProductT ## Factory : public Factory<AbstractProductT>\
	{																	\
	public:																\
																		\
		ConcreteProductT ## Factory() { Add(this); }					\
																		\
		~ConcreteProductT ## Factory() { Remove(this); }				\
																		\
		virtual std::string ClassName()	override						\
		{return # ConcreteProductT;}									\
																		\
	private:														    \
		virtual AbstractProductT* Create() override						\
		{																\
			AbstractProductT* product = new ConcreteProductT();			\
			assert(product != nullptr);									\
			return product;												\
		}																\
	};																																	
}

#include "Factory.inl"


