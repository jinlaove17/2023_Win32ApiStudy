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
	// �� ���� �׷� Ÿ���� ������, ū �׷� Ÿ���� ���� ����Ѵ�.
	UINT row = (UINT)group1;
	UINT col = (UINT)group2;

	if (row > col)
	{
		swap(row, col);
	}

	col = 1 << col;

	// �̹� üũ�Ǿ� �ִ� ���̾�ٸ�, üũ�� �����Ѵ�.
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
		
		// ������Ʈ1�� �浹ü�� �������� ���� ���
		if (collider1 == nullptr)
		{
			continue;
		}

		for (int j = 0; j < group2Objects.size(); ++j)
		{
			CCollider* collider2 = group2Objects[j]->GetCollider();

			// ������Ʈ2�� �浹ü�� �������� �ʰų�, ���� �浹ü�� ���
			if (collider2 == nullptr || collider1 == collider2)
			{
				continue;
			}

			// �� �浹ü�� ���� ������ �浹 ���� Ȯ��
			CollisionID collisionID = {};

			collisionID.m_lowPart = collider1->GetID();
			collisionID.m_highPart = collider2->GetID();

			// ���� �����ӿ� �� �浹ü�� �浹�� ���
			if (IsCollided(collider1, collider2))
			{
				// ���� �����ӿ��� �浹�� ���
				if (m_prevStates[collisionID.m_quadPart])
				{
					// �� ������Ʈ �� �� ������Ʈ�� ��Ȱ��ȭ �Ǿ��ų�, ���� ������ ������Ʈ�� ��� �� ������Ʈ�� �浹�� ������Ų��.
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
					// �� ������Ʈ �� �� ������Ʈ�� ��Ȱ��ȭ �Ǿ��ų�, ���� ������ ������Ʈ�� ��� �� ������Ʈ�� �浹�� ��ȿȭ�ȴ�.
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
				// ���� �����ӿ��� �浹�� ���
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
