#include "pch.h"
#include "State.h"

CState::CState(STATE_TYPE state) :
    m_state(state),
    m_AI()
{
}

CState::~CState()
{
}

STATE_TYPE CState::GetType()
{
    return m_state;
}

CAI* CState::GetAI()
{
    return m_AI;
}
