#pragma once
extern class ObjectBase;

/// <summary>
/// by 光电2215 ##--##
/// 用于建立父类与子类间的树状关系，
/// 面向对象思想的集中应用
/// </summary>

class ChildrenListNode//存储子类的链表
{
public:
	ObjectBase* ele;//存储指向子类的指针
	ChildrenListNode* next;
	ChildrenListNode();
	ChildrenListNode(const ObjectBase*);
};

ChildrenListNode* createList();
void deleteList(ChildrenListNode*&);

class ChildrenList
{
public:
	ChildrenListNode* chead;//头节点
	ChildrenListNode* cptr;//临时节点
	ChildrenListNode* cend;//尾节点

	ChildrenList();
	~ChildrenList();
	ChildrenList(const ChildrenList&);

	ChildrenListNode* findNode(const ObjectBase*);
	ChildrenList& addNode(const ObjectBase*);
};