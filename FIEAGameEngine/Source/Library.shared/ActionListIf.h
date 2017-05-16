#pragma once
#include "ActionList.h"

namespace FieaGameEngine
{
	class ActionListIf : public ActionList
	{
		RTTI_DECLARATIONS(ActionListIf, ActionList)

	public:

		/**Constructor for the ActionListIf.
		* @param: name- The name of the ActionListIf, defaulted to an empty string is no name is specified.*/
		ActionListIf(std::string name = "");

		/**Copy constructor for the ActionListIf.
		* @param otherActionList- The other ActionListIf that is to be copied from.*/
		ActionListIf(const ActionListIf& otherActionList);

		/**Move constructor for the ActionListIf.
		* @param otherActionList- The other ActionListIf that is to be moved from.*/
		ActionListIf(ActionListIf&& otherActionList);

		/**Assignment operator for the ActionListIf.
		* @param otherActionList- The other ActionListIf that is to be assigned to.
		* @return- A reference to the other Entity after assignment.*/
		ActionListIf& operator=(ActionListIf&& otherActionList);

		/**Move assignment operator for the ActionListIf.
		* @param otherActionList - The other ActionListIf that is to be moved to.
		* @return- A reference to the ActionListIf after moving.*/
		ActionListIf& operator=(const ActionListIf& otherActionList);

		/**Function that updates the ActionListIf and calls update on either the then or else action depending
		* on the condition.
		* @param worldState- A reference to the worldState of the game. */
		virtual void Update(WorldState& worldState);

		/**Destructor of the ActionListIf that is defaulted. */
		virtual ~ActionListIf() = default;

		/**Function that is used to set the condition that the action checks upon.
		* @param condition- The new condtion.*/
		void SetCondition(std::int32_t condtion);

		/**Function that is used to get the condition that the action checks upon.
		* @return- An integer that is the condtion.*/
		std::int32_t GetCondition() const;

		/**Function that is used to get the action that would fire when the condition is true.
		* @return- An action pointer that points to the then action.*/
		Action* GetThenAction();

		/**Function that is used to get the action that would fire when the condition is true.
		* @return- A constant action pointer that points to the then action.*/
		const Action* GetThenAction() const;

		/**Function that is used to get the action that would fire when the condition is true.
		* @return- An action pointer that points to the else action.*/
		Action* GetElseAction();

		/**Function that is used to get the action that would fire when the condition is true.
		* @return- A constant action pointer that points to the else action.*/
		const Action* GetElseAction() const;

		virtual Scope* Copy() const override;

	protected:

		void InitalizeSignatures();

		void FixExternals();

	private:

		std::int32_t mCondtion;

		static std::string sConditionTag;
		static std::string sThenTag;
		static std::string sElseTag;
	};

	ConcreteActionFactory(ActionListIf)
}