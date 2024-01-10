#include<iostream>
#include<stack>
#include<queue>
#include <vector>
#include <random>
#include <fstream>
#include <String>
#include <sstream>
using namespace std;

string filename = "input.txt";
ifstream reader(filename, ios::in);

struct Node {
	int data;
	struct Node* pLeft;
	struct Node* pRight;
};
typedef struct Node NODE;

//Create_tree
void treeInit(NODE*& t);
NODE* createNode(int);
void insertNode(NODE*&, int);
void iterativeInsertNode(NODE*&, int);

//traversal
void NLR_traversal(NODE*);
void iterativePreorderTraversal(NODE*);

void LNR_traversal(NODE*);
void iterativeInorderTraversal(NODE*);

void LRN_traversal(NODE*);
void iterativePostOrderTraversal(NODE*);

//search
NODE* searchNode(NODE*, int);

//delete
NODE* deleteNode(NODE*, int);

vector<vector<int>> level_traversal(NODE*);


int main() {
	string s;
	while (getline(reader,s)) {
		NODE* t; treeInit(t);
		stringstream ss(s);
		string token;
		while (getline(ss, token, ' ')) {
			int x = stoi(token);
			insertNode(t, x);
		}
		cout << "NLR traversal:      "; 
		NLR_traversal(t);
		cout << endl;

		cout << "Preorder traversal: ";
		iterativePreorderTraversal(t);
		cout << endl ;

		cout << "LNR traversal: ";
		LNR_traversal(t);
		cout << endl;

		cout << "Inorder traversal: ";
		iterativeInorderTraversal(t);
		cout << endl;

		cout << "LRN traversal:       ";
		LRN_traversal(t);
		cout << endl;
		
		cout << "Postorder traversal: ";
		iterativePostOrderTraversal(t);
		cout << endl;

		cout << endl;
	}
	
	return 0;
}

void treeInit(NODE*& t) {
	t = NULL;
}

NODE* createNode(int x) {
	NODE* p = new NODE;
	if (!p) return nullptr;
	p->data = x;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
}

void insertNode(NODE*& t, int x) {
	NODE* newNODE = new NODE;
	newNODE = createNode(x);
	if (!newNODE) return;
	if (t == NULL) {
		t = newNODE;
		return;
	}
	else {
		if (t->data > x) {
			insertNode(t->pLeft, x);
		}
		else if (t->data < x) {
			insertNode(t->pRight, x);
		}
	}
	return;
}
void iterativeInsertNode(NODE*& t, int x) {
	NODE* newNode = new NODE;
	newNode = createNode(x);

	if (t == NULL) {
		t = newNode;
	}
	else {
		queue <NODE*> q;
		q.push(t);
		while (!q.empty()) {
			NODE* curr = q.front();
			q.pop();
			if (curr->data > x) {
				if (curr->pLeft != NULL) {
					q.push(curr->pLeft);
				}
				else {
					curr->pLeft = newNode;
					return;
				}
			}
			else if (curr->data < x) {
				if (curr->pRight != NULL) {
					q.push(curr->pRight);
				}
				else {
					curr->pRight = newNode;
					return;
				}
			}
		}
	}
}

void NLR_traversal(NODE* t) {
	if (t == NULL) return;
	cout << t->data << " ";
	NLR_traversal(t->pLeft);
	NLR_traversal(t->pRight);
}
void iterativePreorderTraversal(NODE* t) {
	if (t == NULL) return;
	stack<NODE*> q;
	q.push(t);
	while (!q.empty()) {
		NODE* curr = q.top();
		cout << curr->data << " ";
		q.pop();

		if (curr->pRight != NULL) {
			q.push(curr->pRight);
		}
		if (curr->pLeft != NULL) {
			q.push(curr->pLeft);
		}
	}
	return;
}

void LNR_traversal(NODE* t) {
	if (t == NULL) return;
	LNR_traversal(t->pLeft);
	cout << t->data << " ";
	LNR_traversal(t->pRight);
}
void iterativeInorderTraversal(NODE* t) {
	if (t == NULL) return;
	stack<NODE*> st;
	while (t != NULL || !st.empty()) {
		if (t != NULL ) {
			st.push(t);
			t = t->pLeft;
		}
		else {
			NODE* curr = st.top();
			st.pop();

			cout << curr->data << " ";
			if (curr->pRight != NULL) {
				t = curr->pRight;
			}
		}
	}
	return;
}

void LRN_traversal(NODE* t) {
	if (t == NULL) return;
	LRN_traversal(t->pLeft);
	LRN_traversal(t->pRight);
	cout << t->data << " ";
}
void iterativePostOrderTraversal(NODE* t) {
	if (t == NULL) return;
	stack<NODE*>st;
	st.push(t);
	NODE* prev = nullptr;
	while (!st.empty()) {
		NODE* curr = st.top();
		if (prev == nullptr || prev->pLeft == curr || prev->pRight == curr) {
			if (curr->pLeft != NULL) {
				st.push(curr->pLeft);
			}
			else if ( curr->pRight == nullptr) {
				cout << curr->data << " ";
				st.pop();
			}
			else {
				st.push(curr->pRight);
			}
		}
		else if (curr->pLeft == prev ) {
			if (curr->pRight != nullptr) {
				st.push(curr->pRight);
			}
			else {
				cout << curr->data << " ";
				st.pop();
			}
		}
		else {
			cout << curr->data << " ";
			st.pop();
		}
		prev = curr;
	}

	return;
}

NODE* searchNode(NODE* t, int x) {
	if (t == NULL || t->data == x) return t;
	if (t->data > x) {
		return searchNode(t->pLeft, x);	
	}
	return searchNode(t->pRight, x);
}

NODE* deleteNode(NODE* t, int x) {
	if (t == NULL) return t;

	if (t->data > x) {
		t->pLeft = deleteNode(t->pLeft, x);
		return t;
	}
	else if (t->data < x) {
		t->pRight = deleteNode(t->pRight, x);
		return t;
	}

	if (t->pLeft == NULL) {
		NODE* temp = t->pRight;
		delete t;
		return temp;
	}
	else if (t->pRight == NULL) {
		NODE* temp = t->pLeft;
		delete t;
		return temp;
	}
	else {
		NODE* succParent = t;
		NODE* succ = t->pRight;
		while (succ->pLeft != NULL) {
			succParent = succ;
			succ = succ->pLeft;
		}

		if (succParent != t) {
			succParent->pLeft = succ->pRight;
		}
		else {
			succParent->pRight = succParent->pRight;
		}
		t->data = succ->data;
		delete succ;
		return t;
	}
}

vector<vector<int>> level_traversal(NODE* t) {
	int lv = 0;
	queue<NODE*> q;
	q.push(t);
	q.push(nullptr);
	vector<vector<int>> res;
	if (t == nullptr) {
		return res;
	}
	vector<int> curr;
	while (!q.empty()) {
		NODE* temp = q.front();
		q.pop();
		if (temp != nullptr) {
			curr.push_back(temp->data);
			if (temp->pLeft != nullptr) {
				q.push(temp->pLeft);
			}
			if (temp->pRight != nullptr) {
				q.push(temp->pRight);
			}
		}
		else {
			vector<int> c_curr(curr);
			res.push_back(c_curr);
			curr.clear(); // C++ không tự động giải phóng bộ nhớ, cần phải xóa tay
			if (!q.empty()) {
				q.push(nullptr);
			}
		}
	}

	return res;
}