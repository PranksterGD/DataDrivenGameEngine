#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"
#include "Action.h"

namespace FieaGameEngine
{
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action)

	public:

		/**Constructor for the ActionCreateAction.
		* @param: name- The name of the ActionCreateAction, defaulted to an empty string is no name is specified.*/
		ActionCreateAction(std::string name = "", std::string className = "", std::string instanceName = "");

		/**Copy constructor for the ActionCreateAction.
		* @param otherActionCreateAction- The other ActionCreateAction that is to be copied from.*/
		ActionCreateAction(const ActionCreateAction& otherActionCreateAction);

		/**Move constructor for the ActionCreateAction.
		* @param otherActionCreateAction- The other ActionCreateAction that is to be moved from.*/
		ActionCreateAction(ActionCreateAction&& otherActionCreateAction);

		/**Assignment operator for the ActionCreateAction.
		* @param otherActionCreateAction- The other ActionCreateAction that is to be assigned to.
		* @return- A reference to the other Entity after assignment.*/
		ActionCreateAction& operator=(ActionCreateAction&& otherActionCreateAction);

		/**Move assignment operator for the ActionCreateAction.
		* @param otherActionCreateAction - The other ActionCreateAction that is to be moved to.
		* @return- A reference to the ActionCreateAction after moving.*/
		ActionCreateAction& operator=(const ActionCreateAction& otherActionCreateAction);

		/**Function that is used to set the type of the action that this ActionCreateAction creates.
		* @param className- The type of action to be created.*/
		void SetCreatedClassName(std::string className);

		/**Function that is used to set the name of the action that this ActionCreateAction creates.
		* @param className- The name of action to be created.*/
		void SetCreatedInstanceName(std::string InstanceName);

		/**Function that is used to get the type of action that this ActionCreateAction creates.
		* @return -  A string reference that contains the string of the type of action 
		that this ActionCreateAction creates. */
		std::string& GetCreatedClassName();

		/**Function that is used to get the type of action that this ActionCreateAction creates.
		* @return -  A constant string reference that contains the string of the type of action
		that this ActionCreateAction creates. */
		const std::string& GetCreatedClassName() const;

		/**Function that is used to get the name of action that this ActionCreateAction creates.
		* @return -  A string reference that contains the string of the name of action
		that this ActionCreateAction creates. */
		std::string& GetCreatedInstanceName();

		/**Function that is used to get the name of action that this ActionCreateAction creates.
		* @return -  A constant string reference that contains the string of the name of action
		that this ActionCreateAction creates. */
		const std::string& GetCreatedInstanceName() const;

		/**Function that updates the ActionCreateAction and destroys the specified action.
		* @param worldState- A reference to the worldState of the game. */
		virtual void Update(WorldState& worldState);

		/**Destructor of the ActionCreateAction that is defaulted. */
		virtual ~ActionCreateAction() = default;

		virtual Scope* Copy() const override;

	protected:

		void InitalizeSignatures();

		void FixExternals();

	private:

		std::string mInstanceName;

		std::string mClassName;
	};

	ConcreteActionFactory(ActionCreateAction)
}