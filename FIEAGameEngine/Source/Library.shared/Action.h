#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class Entity;

	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)

	public:

		/**Constructor for the Action.
		* @param: name- The name of the Action, defaulted to an empty string is no name is specified.*/
		Action(std::string name = "");

		/**Copy constructor for the Action.
		* @param otherAction- The other Action that is to be copied from.*/
		Action(const Action& otherAction);

		/**Move constructor for the Action.
		* @param otherAction- The other Action that is to be moved from.*/
		Action(Action&& otherAction);

		/**Assignment operator for the Action.
		* @param otherAction The other Action that is to be assigned to.
		* @return- A reference to the other Action after assignment.*/
		Action& operator=(Action&& otherAction);

		/**Move assignment operator for the Action.
		* @param otherAction- The other Action that is to be moved to.
		* @return- A reference to the Action after moving.*/
		Action& operator=(const Action& otherAction);

		/**Function that returns the name of the Action.
		* @return - A constant reference to a string that contains the name of the Action.*/
		const std::string& Name() const;

		/**Function that returns the name of the Action.
		* @return - A reference to a string that contains the name of the Action.*/
		std::string& Name();

		/**Function that is used to the set the name of the Action.
		* @param name- The new name of the Action.*/
		void SetName(const std::string& name);

		/**Function that updates the Action and all elements within it.
		* @param worldState- A reference to the worldState of the game. */
		virtual void Update(WorldState& worldState) = 0;

		/**Destructor of the Action that is defaulted. */
		virtual ~Action() = default;

	protected:

		void InitalizeSignatures();

		void FixExternals();

		std::string mName;
	};

#define ConcreteActionFactory(ConcreteProductT) ConcreteFactory(ConcreteProductT, Action)
}