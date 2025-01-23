#pragma once
#include <memory>
#include <stack>

#include "State.h"

using StatePtr = std::unique_ptr<State>;

class StateStack
{
public:
	StateStack() : _is_removing(false), _is_adding(false), _is_replacing(false) {}
	~StateStack() {}

	void AddState(StatePtr newState, bool is_replacing = true);
	void RemoveState();

	void ProcessStateChanges();

	StatePtr& GetActiveState();

private:
	std::stack<StatePtr> states;
	StatePtr _newstate;

	bool _is_removing;
	bool _is_adding;
	bool _is_replacing;


};

