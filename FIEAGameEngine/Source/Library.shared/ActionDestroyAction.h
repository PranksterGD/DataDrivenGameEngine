#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"
#include "Action.h"

namespace FieaGameEngine
{
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action)

	public:

		/**Constructor for the ActionDestroyAction.
		* @param: name- The name of the ActionDestroyAction, defaulted to an empty string is no name is specified.*/
		ActionDestroyAction(std::string name = "",std::string instanceName = "");

		/**Copy constructor for the ActionDestroyAction.
		* @param otherActionDestroyAction- The other ActionDestroyAction that is to be copied from.*/
		ActionDestroyAction(const ActionDestroyAction& otherActionDestroyAction);

		/**Move constructor for the ActionDestroyAction.
		* @param otherActionDestroyAction- The other ActionDestroyAction that is to be moved from.*/
		ActionDestroyAction(ActionDestroyAction&& otherActionDestroyAction);

		/**Assignment operator for the ActionDestroyAction.
		* @param otherActionDestroyAction- The other ActionDestroyAction that is to be assigned to.
		* @return- A reference to the other ActionDestroyAction after assignment.*/
		ActionDestroyAction& operator=(ActionDestroyAction&& otherActionDestroyAction);

		/**Move assignment operator for the ActionDestroyAction.
		* @param otherActionDestroyAction - The other ActionDestroyAction that is to be moved to.
		* @return- A reference to the ActionDestroyAction after moving.*/
		ActionDestroyAction& operator=(const ActionDestroyAction& otherActionDestroyAction);

		/**Function that is used to set the name of the action that this ActionCreateAction destroys.
		* @param className- The name of action to be destroyed.*/
		void SetDestroyedInstanceName(std::string InstanceName);

		/**Function that is used to get the name of action that this ActionCreateAction destroys.
		* @return -  A string reference that contains the string of the name of action
		that this ActionCreateAction destroys. */
		std::string& GetDestroyedInstanceName();

		/**Function that is used to get the name of action that this ActionCreateAction destroys.
		* @return -  A constant string reference that contains the string of the name of action
		that this ActionCreateAction destroys. */
		const std::string& GetDestroyedInstanceName() const;

		/**Function that updates the ActionDestroyAction and destroys the specified action.
		* @param worldState- A reference to the worldState of the game. */
		virtual void Update(WorldState& worldState);

		virtual Scope* Copy() const override;

		/**Destructor of the ActionDestroyAction that is defaulted. */
		virtual ~ActionDestroyAction() = default;

	protected:

		void InitalizeSignatures();

		void FixExternals();

	private:

		std::string mInstanceName;
	};

	ConcreteActionFactory(ActionDestroyAction)

}