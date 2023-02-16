#include "pch.h"
#include "AI.h"

#include "IdleState.h"
#include "TraceState.h"

CAI::CAI() :
	m_states(),
	m_currentState(),
	m_owner()
{
}

CAI::~CAI()
{
	SafeDelete(m_states);
}

void CAI::AddState(STATE_TYPE stateType)
{
	CState* state = GetState(stateType);

	if (state == nullptr)
	{
		switch (stateType)
		{
		case STATE_TYPE::IDLE:
			state = new CIdleState();
			break;
		case STATE_TYPE::TRACE:
			state = new CTraceState();
			break;
		}

		m_states.emplace(stateType, state);
		state->m_AI = this;
	}
}

CState* CAI::GetState(STATE_TYPE stateType)
{
	auto iter = m_states.find(stateType);

	if (iter == m_states.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAI::SetCurrentState(STATE_TYPE stateType)
{
	CState* state = GetState(stateType);

	if (state != nullptr)
	{
		m_currentState = state;
	}
}

CState* CAI::GetCurrentState()
{
	return m_currentState;
}

CMonster* CAI::GetOwner()
{
	return m_owner;
}

void CAI::ChangeState(STATE_TYPE stateType)
{
	CState* nextState = GetState(stateType);

	if ((nextState != nullptr) && (nextState != m_currentState))
	{
		m_currentState->Exit();
		m_currentState = nextState;
		m_currentState->Enter();
	}
}

void CAI::Update()
{
	m_currentState->Update();
}
