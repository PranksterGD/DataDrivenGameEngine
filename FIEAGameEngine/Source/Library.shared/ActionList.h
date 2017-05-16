#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"
#include "Action.h"

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:

		/**Constructor for the ActionList.
		* @param: name- The name of the ActionList, defaulted to an empty string is no name is specified.*/
		ActionList(std::string name = "");

		/**Copy constructor for the ActionList.
		* @param otherActionList- The other ActionList that is to be copied from.*/
		ActionList(const ActionList& otherActionList);

		/**Move constructor for the ActionList.
		* @param otherActionList- The other ActionList that is to be moved from.*/
		ActionList(ActionList&& otherActionList);

		/**Assignment operator for the ActionList.
		* @param otherActionList- The other ActionList that is to be assigned to.
		* @return- A reference to the other ActionList after assignment.*/
		ActionList& operator=(ActionList&& otherActionList);

		/**Move assignment operator for the ActionList.
		* @param otherActionList - The other ActionList that is to be moved to.
		* @return- A reference to the ActionList after moving.*/
		ActionList& operator=(const ActionList& otherActionList);

		/**Function that updates the ActionList and all elements within it.
		* @param worldState- A reference to the worldState of the game. */
		virtual void Update(WorldState& worldState);

		/**Function that returns a datum containing all the actions held within the action list.
		/* @return- A datum containing all the actions held within the action list.*/
		Datum& Actions();

		/**Function that returns a datum containing all the actions held within the action list.
		/* @return- A constant datum containing all the actions held within the action list.*/
		const Datum& Actions() const;

		/**Destructor of the ActionList that is defaulted. */
		virtual ~ActionList() = default;

		/**Function that creates a new action.
		* @param className- The type of action to be created.
		* @param instanceName- The name of the action to be created.
		* @return - An action pointer pointing to the newly created action.*/
		 Action* CreateAction(const std::string& className, const std::string& instanceName);

		 virtual Scope* Copy() const override;


	protected:

		void InitalizeSignatures();

		void FixExternals();
	};

	ConcreteActionFactory(ActionList)
}