#include "StateStack.h"

void StateStack::AddState(StatePtr newState, bool is_replacing)
{
	this->_is_adding = true;
	this->_is_replacing = is_replacing;

	this->_new_state = std::move(newState);


}

void StateStack::RemoveState()
{
	this->_is_removing = true;
}

void StateStack::ProcessStateChanges()
{
	if (this->_is_removing && !this->_states.empty())
	{
		this->_states.pop();

		if (!this->_states.empty())
		{
			this->_states.top()->Resume();
		}

		this->_is_removing = false;
	}

	if (this->_is_adding)
	{
		if (!this->_states.empty())
		{
			if (this->_is_replacing)
			{
				this->_states.pop();
			}
			else
			{
				this->_states.top()->Pause();
			}
		}

		this->_states.push(std::move(this->_new_state));
		this->_states.top()->Init();
		this->_is_adding = false;

		
	}
}

StatePtr& StateStack::GetActiveState()
{
	return this->_states.top();

}
