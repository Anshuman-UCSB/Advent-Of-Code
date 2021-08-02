#include "../aoc.h"

struct Node{
	char val;
	Node* next;
	Node* prev;
	Node(char v = ' ', Node* next = 0, Node* prev = 0):val(v), next(next), prev(prev){}
};

static void remove(Node* n){
	n->prev->next = n->next;
	n->next->prev = n->prev;
	delete n;
}

struct linkedList{
	Node* head;
	Node* tail;
	int size;

	linkedList():head(0), tail(0), size(0){}

	void push(const char& c){
		// cout<<head<< ", "<<tail<<endl;
		if(head == 0){
			head = new Node(c);
			tail = head;
		}else{
			tail->next = new Node(c, 0, tail);
			tail = tail->next;
		}
	}

	void print(){
		string delim;
		for(Node* p = head;p;p=p->next){
			cout<<delim<<"("<<p->val<<")";
			delim = "->";
		}cout<<endl;
	}
};

static inline bool reactants(const char& a, const char& b){
	return abs(a-b)==32;
}

void p1(string line){
	linkedList l;
	l.size = line.size();
	for(auto& c: line){
		l.push(c);
	}
	// l.print();
	cout<<"[P1] "<<l.size<<endl;
}

int main(){
	fstream file("Day 5/input");
	string line;
	getline(file, line);
	p1(line);
}