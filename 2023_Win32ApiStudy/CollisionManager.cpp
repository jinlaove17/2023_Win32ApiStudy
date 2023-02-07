#include "pch.h"
#include "CollisionManager.h"

#include "SceneManager.h"

#include "Scene.h"

#include "Object.h"

#include "Collider.h"

CCollisionManager::CCollisionManager() :
	m_layer{},
	m_prevStates()
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::SetCollisionGroup(GROUP_TYPE group1, GROUP_TYPE group2)
{
	// 더 작은 그룹 타입을 행으로, 큰 그룹 타입을 열로 사용한다.
	UINT row = (UINT)group1;
	UINT col = (UINT)group2;

	if (row > col)
	{
		swap(row, col);
	}

	col = 1 << col;

	// 이미 체크되어 있는 레이어였다면, 체크를 해제한다.
	if (m_layer[row] & col)
	{
		m_layer[row] &= ~col;
	}
	else
	{
		m_layer[row] |= col;
	}
}

void CCollisionManager::ResetCollisionGroup()
{
	memset(m_layer, 0, sizeof(UINT) * (int)GROUP_TYPE::COUNT);
}

void CCollisionManager::Update()
{
	for (UINT row = 0; row < (UINT)GROUP_TYPE::COUNT; ++row)
	{
		for (UINT col = row; col < (UINT)GROUP_TYPE::COUNT; ++col)
		{
			if (m_layer[row] & (1 << col))
			{
				UpdateCollisionGroup((GROUP_TYPE)row, (GROUP_TYPE)col);
			}
		}
	}
}

void CCollisionManager::UpdateCollisionGroup(GROUP_TYPE group1, GROUP_TYPE group2)
{
	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	const vector<CObject*>& group1Objects = currentScene->GetGroupObject(group1);
	const vector<CObject*>& group2Objects = currentScene->GetGroupObject(group2);

	for (int i = 0; i < group1Objects.size(); ++i)
	{
		CCollider* collider1 = group1Objects[i]->GetCollider();
		
		// 오브젝트1이 충돌체를 보유하지 않은 경우
		if (collider1 == nullptr)
		{
			continue;
		}

		for (int j = 0; j < group2Objects.size(); ++j)
		{
			CCollider* collider2 = group2Objects[j]->GetCollider();

			// 오브젝트2가 충돌체를 보유하지 않거나, 같은 충돌체인 경우
			if (collider2 == nullptr || collider1 == collider2)
			{
				continue;
			}

			// 두 충돌체의 이전 프레임 충돌 상태 확인
			CollisionID collisionID = {};

			collisionID.m_lowPart = collider1->GetID();
			collisionID.m_highPart = collider2->GetID();

			// 현재 프레임에 두 충돌체가 충돌한 경우
			if (IsCollided(collider1, collider2))
			{
				// 이전 프레임에도 충돌한 경우
				if (m_prevStates[collisionID.m_quadPart])
				{
					// 두 오브젝트 중 한 오브젝트라도 비활성화 되었거나, 삭제 예정인 오브젝트인 경우 두 오브젝트의 충돌을 해제시킨다.
					if (!group1Objects[i]->IsActive() || group1Objects[i]->IsDeleted() ||
						!group2Objects[j]->IsActive() || group2Objects[j]->IsDeleted())
					{
						collider1->OnCollisionExit(collider2);
						collider2->OnCollisionExit(collider1);

						m_prevStates[collisionID.m_quadPart] = false;
					}
					else
					{
						collider1->OnCollision(collider2);
						collider2->OnCollision(collider1);
					}
				}
				else
				{
					// 두 오브젝트 중 한 오브젝트라도 비활성화 되었거나, 삭제 예정인 오브젝트인 경우 두 오브젝트의 충돌은 무효화된다.
					if (group1Objects[i]->IsActive() && !group1Objects[i]->IsDeleted() &&
						group2Objects[j]->IsActive() && !group2Objects[j]->IsDeleted())
					{
						collider1->OnCollisionEnter(collider2);
						collider2->OnCollisionEnter(collider1);

						m_prevStates[collisionID.m_quadPart] = true;
					}
				}
			}
			else
			{
				// 이전 프레임에도 충돌한 경우
				if (m_prevStates[collisionID.m_quadPart])
				{
					collider1->OnCollisionExit(collider2);
					collider2->OnCollisionExit(collider1);

					m_prevStates[collisionID.m_quadPart] = false;
				}
			}
		}
	}
}

bool CCollisionManager::IsCollided(CCollider* collider1, CCollider* collider2)
{
	Vec2 position1 = collider1->GetPosition();
	const Vec2& scale1 = collider1->GetScale();

	Vec2 position2 = collider2->GetPosition();
	const Vec2& scale2 = collider1->GetScale();

	if (abs(position1.m_x - position2.m_x) < 0.5f * (scale1.m_x + scale2.m_x) &&
		abs(position1.m_y - position2.m_y) < 0.5f * (scale1.m_y + scale2.m_y))
	{
		return true;
	}

	return false;
}
