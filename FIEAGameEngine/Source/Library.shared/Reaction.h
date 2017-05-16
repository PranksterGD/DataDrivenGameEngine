#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:
		/**Constructor for the Reaction.
		* @param: name- The name of the Reaction, defaulted to an empty string is no name is specified*/
		Reaction(const std::string& name = "");

		/**Destructor for the Reaction that is defaulted. */
		virtual ~Reaction() =default;

		static const std::string sReactionsTag;
	};

#define ConcreteReactionFactory(ConcreteProductT) ConcreteFactory(ConcreteProductT, Reaction)
}