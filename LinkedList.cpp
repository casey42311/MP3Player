#include <string>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList()
{
	first_ = last_ = nullptr;
	listLen_ = 0;
}

void LinkedList::AddLinkToBack(void* ptr)
{
	Node* newNode = new Node; //Create a pointer called newNode and point it to a new node object
	newNode->data_ = ptr; //Set the data of our new object to the Shell information
	if(listLen_ == 0) //If the linked list is empty
	{
		first_ = newNode;
		first_->next_ = last_;
	}
	else if(listLen_ == 1)
	{
		last_ = newNode;
		first_->next_ = last_;
		last_->prev_ = first_;
	}
	else
	{
		Node* prevNode = last_;
		last_->next_ = newNode; //Set the next_ address of current last node to newNode
		last_ = newNode; //Set last_ pointer equal to newNode pointer, this is now the end of the linked list
		last_->prev_ = prevNode; //Set the previous address of the new last node to the previous last node
	}

	listLen_++; //Increment list length
}

void* LinkedList::RemoveThisLink(Node* node)
{
	Node* previousNode = node->prev_;
	Node* nextNode = node->next_;

	if(previousNode != nullptr) //If this is not the first node
	{
		previousNode->next_ = nextNode; //point previousNode to nextNode
	}

	if(nextNode != nullptr) //If this is not the last node
	{
		nextNode->prev_ = previousNode; //point nextNode to previousNode
	}

	if(node == first_) //If the node to be deleted is the first node
	{
		first_ = node->next_; //point first_ to next_
	}

	if(node == last_) //If the node to be deleted is the last node
	{
		last_ = node->prev_; //point last_ to prev_
	}
	
	node->next_ = node->prev_ = nullptr;

	listLen_--; //Decrement list length

	return node;
}

void* LinkedList::RemoveLinkFromFront()
{
	Node* removeNode;
	if(first_ == nullptr) //If the linked list is empty, do nothing
	{
		return first_;
	}

	void* oldData = first_->data_; //Create a pointer to the Shell data of the first node

	if(first_ == last_) //If the linked list length is 1, set first and last to nullptr
	{
		removeNode = first_;
		delete removeNode;
		first_ = last_ = nullptr;
	}
	else //Set first equal to the second node
	{
		removeNode = first_;
		first_ = first_->next_;
		delete removeNode;
	}

	listLen_--; //Decrement list length

	return oldData; //Return pointer to Shell data we want to delete
}

Node* LinkedList::GetFirstNode()
{
	return first_;
}

long LinkedList::GetListLength()
{
	return listLen_;
}

LinkedList::~LinkedList()
{
	
}