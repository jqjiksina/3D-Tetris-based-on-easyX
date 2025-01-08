#include "ChildrenList.h"
#include <iostream>
#include "ObjectBase.h"

ChildrenListNode::ChildrenListNode()
{
	this->ele = NULL;
	this->next = NULL;
}

ChildrenListNode::ChildrenListNode(const ObjectBase* obj)
{
	this->ele = (ObjectBase*)obj;
	this->next = NULL;
}

ChildrenListNode* createList()
{
	ChildrenListNode* chead = new ChildrenListNode();
	return chead;
}

void deleteList(ChildrenListNode* &node)//�Ӻ���ǰɾ������
{
	if (node == NULL) return;
	if(node ->next != NULL)//��ֹ��Ұָ��
	{
		deleteList(node->next);
	}
	if (node != NULL)
	{
		//node->ele->~ObjectBase();//��ִ�����������
		delete node;
		node = NULL;
	}
}

ChildrenList::ChildrenList()
{
	this->cptr = this->chead = createList();
	this->cend = this->chead->next;
}

ChildrenList::ChildrenList(const ChildrenList& list)//�������
{
	this->chead = createList();
	this->cptr = this->chead;
	ChildrenListNode* lptr = list.chead;
	for (ChildrenListNode*lptr = list.chead; lptr != NULL; this->cptr = this->cptr->next = new ChildrenListNode(), lptr = lptr->next)
	{
		this->cptr->ele = lptr->ele;//Ԫ�ؽ��и�ֵ����,�����Ǽ򵥵�ֵ����
	}
	this->cend = new ChildrenListNode();
}

ChildrenList::~ChildrenList()
{
	deleteList(this->chead);
	this->cend = NULL;
	this->chead = NULL;
	this->cptr = NULL;
}

ChildrenListNode* ChildrenList::findNode(const ObjectBase* obj)
{
	this->cptr = this->chead;
	for (; *(this->cptr->ele) != *obj; this->cptr = this->cptr->next);
	return this->cptr;
}

ChildrenList& ChildrenList::addNode(const ObjectBase* obj)
{
	this->cend = new ChildrenListNode(obj);
	this->cend = NULL;
	return *this;
}