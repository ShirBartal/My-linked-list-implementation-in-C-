#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;
string s;
using ItemType = string;
struct Node {
	ItemType m_data;
	Node *next;
};

class LinkedList
{
private:
	Node * head;
public:
	LinkedList(); //constructor
	LinkedList(const LinkedList &rhs); // copy constructor
	LinkedList& operator=(const LinkedList& rhs); //equals overloading. assignment operator
	~LinkedList(); //destructor
	void insertToFront(const ItemType &val);
	void printList();
	bool get(int i, ItemType& item) const;
	void reverseList(); //Reverses the LinkedList
	void printReverse() const; //Prints the LinkedList in reverse order
	int size() const; //Returns the number of items in the Linked List.
	void append(const LinkedList &other); //Appends the values of other onto the end of this
	//LinkedList.
	void swap(LinkedList &other); // Exchange the contents of this LinkedList with the other one.

};
LinkedList::~LinkedList() { //destructor
	Node *node = head;
	while (node != nullptr)
	{
		Node *save = node->next;
		delete node; //(*head).m_data; 
		node = save;
	}
}
LinkedList::LinkedList() {//constructor
	head = nullptr;
}
LinkedList::LinkedList(const LinkedList &rhs) { //copy constructor, deep copy
	Node *node = rhs.head;
	Node **prevNodeNext = &head; // pointer to previous node's next pointer
	while (node != nullptr)
	{
		Node *copy = new Node;
		copy->m_data = node->m_data;
		*prevNodeNext = copy;
		prevNodeNext = &(copy->next);
		node = node->next;
	}
	*prevNodeNext = nullptr;
}
void LinkedList::insertToFront(const ItemType &val) {
	Node *newNode = new Node;
	newNode->m_data = val;
	//(*newNode).m_data;
	if (head == nullptr) {
		head = newNode;
		newNode->next = nullptr;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}
void LinkedList::printList()
{
	Node *node = head;
	while (node != nullptr)
	{
		cout << node->m_data << ", "; //(*head).m_data; 
		node = node->next;
	}
	cout << endl;
}

bool LinkedList::get(int i, ItemType& item) const {
	int m = 0;
	Node *node = head;
	while (node != nullptr)
	{
		if (i < 0)
			return false;
		if (i == m) {
			item = node->m_data;
			return true;
		}
		m++;
		node = node->next;
	}
	return false;
}

//Reverses the LinkedList
void LinkedList::reverseList() {
	LinkedList a;
	Node *node = head;
	while (node != nullptr)
	{
		a.insertToFront(node->m_data);
		node = node->next;
	}
	node = head;
	Node *newNode = a.head;
	while (node != nullptr)
	{
		node->m_data = newNode->m_data;
		node = node->next;
		newNode = newNode->next;
	}
}
//// Prints the LinkedList in reverse order
void LinkedList::printReverse() const {
	LinkedList a;
	Node *node = head;
	while (node != nullptr)
	{
		a.insertToFront(node->m_data);
		node = node->next;
	}
	a.printList();
}
// Exchange the contents of this LinkedList with the other one.
void LinkedList::swap(LinkedList &other) {
	Node *node = head;
	head = other.head;
	other.head = node;
}

//// Returns the number of items in the Linked List.
int LinkedList::size() const {
	Node *node = head;
	int i = 0;
	while (node != nullptr) {
		i++;
		node = node->next;
	}
	return i;
}

void LinkedList::append(const LinkedList &other) {
	LinkedList copy(other);
	if (head == nullptr) {
		head = copy.head;
	}
	else {
		Node *node = head;
		while (node->next != nullptr)
			node = node->next;
		node->next = copy.head;
	}
	copy.head = nullptr;
}

int main()
{
	LinkedList e1;
	e1.insertToFront("bell");
	e1.insertToFront("biv");
	e1.insertToFront("devoe");
	LinkedList e2;
	e2.insertToFront("Andre");
	e2.insertToFront("Big Boi");
	e1.append(e2);  // adds contents of e2 to the end of e1
	e1.printList();
	string s11 = "Big Boi";
	bool check = e1.get(3, s11);
	if (check)
		cout << "good" << endl;
	else
		cout << "bad" << endl;
	string s;
	cout << e1.size() << endl;
	cout << s11 << endl;
	cout << (e1.size() == 5 && e1.get(3, s) && s == "Big Boi") << endl;
	cout << "s" << s << endl;

	assert(e1.size() == 5 && e1.get(3, s) && s == "Big Boi");
	assert(e2.size() == 2 && e2.get(1, s) && s == "Andre");
	LinkedList e3;
	e3.insertToFront("Rare Essence");
	e3.insertToFront("JunkYard");
	e3.insertToFront("Chuck Brown");
	e3.printList();
	e3.append(e3);
	e3.printList();
	assert(e3.size() == 6 && e3.get(3, s) && s == "Chuck Brown");
	LinkedList e6;
	e6.insertToFront("Sam");
	e6.insertToFront("Carla");
	e6.insertToFront("Cliff");
	e6.insertToFront("Norm");

	e6.reverseList();  // reverses the contents of e1
	string d;
	assert(e6.size() == 4 && e6.get(0, d) && d == "Sam");


	LinkedList e7;
	e7.insertToFront("A");
	e7.insertToFront("B");
	e7.insertToFront("C");
	e7.insertToFront("D");
	LinkedList e8;
	e8.insertToFront("X");
	e8.insertToFront("Y");
	e8.insertToFront("Z");
	e8.swap(e7);  // exchange contents of e1 and e2
	string s1;
	assert(e7.size() == 3 && e7.get(0, s1) && s1 == "Z");
	assert(e8.size() == 4 && e8.get(2, s1) && s1 == "B");

}

LinkedList & LinkedList::operator=(const LinkedList& rhs)
{
	if (this == &rhs) //this - is the object that we're currently working on.
		return *this;
	if (this->head != nullptr) {
		Node *node = head;
		while (node != nullptr)
		{
			Node *save = node->next;
			delete node; //(*head).m_data; 
			node = save;
		}
	}
	Node *node = rhs.head;
	Node **prevNodeNext = &head; // pointer to previous node's next pointer
	while (node != nullptr)
	{
		Node *copy = new Node;
		copy->m_data = node->m_data;
		*prevNodeNext = copy;
		prevNodeNext = &(copy->next);
		node = node->next;
	}
	*prevNodeNext = nullptr;
	return *this;
}
