#pragma once

// �Ʒ��� ���� ��ũ�θ� ����� ���� ������ �켱 ������ ��������!
// #define ADD(a, b) a + b
// �Ʒ� ���� ��� ���� 500�� �ƴ� 230�̴�.
// int n = 10 * ADD(20, 30);

#define SINGLETON(type) public:\
							static type* GetInstance()\
							{\
								 static type instance;\
								 return &instance;\
							}
