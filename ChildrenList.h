#pragma once
extern class ObjectBase;

/// <summary>
/// by ���2215 ##--##
/// ���ڽ�����������������״��ϵ��
/// �������˼��ļ���Ӧ��
/// </summary>

class ChildrenListNode//�洢���������
{
public:
	ObjectBase* ele;//�洢ָ�������ָ��
	ChildrenListNode* next;
	ChildrenListNode();
	ChildrenListNode(const ObjectBase*);
};

ChildrenListNode* createList();
void deleteList(ChildrenListNode*&);

class ChildrenList
{
public:
	ChildrenListNode* chead;//ͷ�ڵ�
	ChildrenListNode* cptr;//��ʱ�ڵ�
	ChildrenListNode* cend;//β�ڵ�

	ChildrenList();
	~ChildrenList();
	ChildrenList(const ChildrenList&);

	ChildrenListNode* findNode(const ObjectBase*);
	ChildrenList& addNode(const ObjectBase*);
};