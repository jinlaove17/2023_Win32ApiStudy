#include "pch.h"
#include "StateMachine.h"

#include "State.h"

CStateMachine::CStateMachine() :
	m_previousState(),
	m_currentState()
{
}

CStateMachine::~CStateMachine()
{
}

void CStateMachine::SetCurrentState(CState* state)
{
	if (m_currentState == nullptr)
	{
		m_currentState = state;
		m_currentState->Enter(GetOwner());
	}
}

CState* CStateMachine::GetPreviousState()
{
	return m_previousState;
}

CState* CStateMachine::GetCurrentState()
{
	return m_currentState;
}

void CStateMachine::ChangeState(CState* state)
{
	if ((state != nullptr) && (m_currentState != state))
	{
		m_currentState->Exit(GetOwner());
		m_previousState = m_currentState;
		m_currentState = state;
		m_currentState->Enter(GetOwner());
	}
}

void CStateMachine::Update()
{
	if (m_currentState != nullptr)
	{
		m_currentState->Update(GetOwner());
	}
}

void CStateMachine::Render(HDC hDC)
{
}
