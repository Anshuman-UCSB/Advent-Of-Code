#include "../aoc.h"

struct Node{
	char val;
	Node* next;
	Node* prev;
	Node(char v = ' ', Node* next = 0, Node* prev = 0):val(v), next(next), prev(prev){}
};

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

	void remove(Node* n){
		size--;
		if(n == head && n == tail){
			head = tail = 0;
			delete n;
			return;
		}
		if(n == head){
			head = n->next;
			head->prev = 0;
			delete n;
			return;
		}
		if(n == tail){
			tail = n->prev;
			tail->next = 0;
			delete n;
			return;
		}
		n->prev->next=n->next;
		n->next->prev=n->prev;
		delete n;
	}

	void print(){
		string delim;
		for(Node* p = head;p;p=p->next){
			cout<<p->val;
		}cout<<endl;
	}
};

static inline bool reactants(const char& a, const char& b){
	return abs(a-b)==32;
}

int eval(string line, char ignore){
	linkedList l;
	l.size = line.size();
	for(auto& c: line){
		if(tolower(c) == ignore){
			l.size--;
			continue;
		}
		l.push(c);
	}
	for(auto p = l.head; p->next;){
		if(reactants(p->val, p->next->val)){
			if(p == l.head){
				l.remove(p->next);
				p=p->next;
				l.remove(p->prev);
			}else if(p->next == l.tail){
				l.remove(p->next);
				l.remove(p);
			}else{
				p = p->prev;
				l.remove(p->next);
				l.remove(p->next);
			}
		}else{
			p=p->next;
		}
	}

	return l.size;
}
char maxChar='a';

void p1(string line){
	linkedList l;
	l.size = line.size();
	for(auto& c: line){
		l.push(c);
		maxChar = max(maxChar, char(tolower(c)));
	}
	for(auto p = l.head; p->next;){
		if(reactants(p->val, p->next->val)){
			if(p == l.head){
				l.remove(p->next);
				p=p->next;
				l.remove(p->prev);
			}else if(p->next == l.tail){
				l.remove(p->next);
				l.remove(p);
			}else{
				p = p->prev;
				l.remove(p->next);
				l.remove(p->next);
			}
		}else{
			p=p->next;
		}
	}

	cout<<"[P1] "<<l.size<<endl;
}

void p2(string& line){
	int smallestPolymer = 500000;
	for(char ign = 'a';ign<=maxChar;ign++){
		smallestPolymer=min(smallestPolymer, eval(line, ign));
	}
	cout<<"[P2] "<<smallestPolymer<<endl;
}

int main(){
	fstream file("Day 5/input");
	string line;
	getline(file, line);
	p1(line);
	p2(line);
}