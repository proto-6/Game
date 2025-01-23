#include "StateStack.h"

void StateStack::AddState(StatePtr newState, bool is_replacing)
{
	this->_is_adding = true;
	this->_is_replacing = is_replacing;

	this->_newstate = std::move(newState);


}

void StateStack::RemoveState()
{
	this->_is_removing = true;
}

void StateStack::ProcessStateChanges()
{
	if (this->_is_removing && !this->states.empty())
	{
		this->states.pop();

		if (!this->states.empty())
		{
			this->states.top()->Resume();
		}

		this->_is_removing = false;
	}

	if (this->_is_adding)
	{
		if (!this->states.empty())
		{
			if (this->_is_replacing)
			{
				this->states.pop();
			}
			else
			{
				this->states.top()->Pause();
			}
		}

		this->states.push(std::move(this->_newstate));
		this->states.top()->Init();
		this->_is_adding = false;

		
	}
}

StatePtr& StateStack::GetActiveState()
{
	return this->states.top();

}
