#include<iostream>
#include<stack>
#include<queue>
#include <vector>

using namespace std;
struct Node {
	int data;
	struct Node* pLeft;
	struct Node* pRight;
    int height;
};
typedef struct Node NODE;

//Create_tree
void treeInit(NODE*& t);
NODE* createNode(int);

//traversal
void NLR_traversal(NODE*);
void iterativePreorderTraversal(NODE*);

void LNR_traversal(NODE*);
void iterativeInorderTraversal(NODE*);

void LRN_traversal(NODE*);
void iterativePostOrderTraversal(NODE*);

//search
NODE* searchNode(NODE*, int);

//level traversal
vector<vector<int>> level_traversal(NODE*);

//height
int getHeight(NODE*);

//AVL Rotation
NODE* rightRotate(NODE*);
NODE* leftRotate(NODE*);

//Get Balance factor
int balanceFactor(NODE*);

//AVL Insertion
NODE* insertAVLNode(NODE*, int);

//AVL Check-out
bool isAVLTree(NODE*); 

//Leftmost leaf
NODE* minNode(NODE*);

//AVL Deletion
NODE* deleteAVLNode(NODE*, int);

int main() {
	int n; cin >> n;
    NODE* t; treeInit(t);
    while(n--){
        int x; cin >> x;
        t = insertAVLNode(t,x);
    }
    
    vector<vector<int>> m = level_traversal(t);
    for(int i =0 ; i < m.size(); i++){
        for(int j = 0; j < m[i].size(); j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << getHeight(t) << endl;
    cout << isAVLTree(t) << endl; 

    int x; cin >> x;
    t = deleteAVLNode(t,x);
    cout << "After Deletion" << endl;
    m = level_traversal(t);
    for(int i =0 ; i < m.size(); i++){
        for(int j = 0; j < m[i].size(); j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << getHeight(t) << endl;
    NLR_traversal(t);
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
    p->height = 1;
	return p;
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

int getHeight(NODE* t){
    if(t == NULL) 
        return 0;
    return 1 + max(getHeight(t->pLeft),getHeight(t->pRight));
}

NODE* rightRotate(NODE* t){
    NODE* x = t->pLeft;
    NODE* T2 = x->pRight;

    //Perform rotation
    x->pRight = t;
    t->pLeft = T2;
    //Update Height
    t->height = max(getHeight(t->pLeft),getHeight(t->pRight)) +1;
    x->height = max(getHeight(x->pLeft),getHeight(x->pRight)) +1;

    return x;
}

NODE* leftRotate(NODE* t){
    NODE* x = t->pRight;
    NODE* T1 = x->pLeft;

    //Perform Rotation
    x->pLeft = t;
    t->pRight = T1;

    //Update Height
    t->height = max(getHeight(t->pLeft),getHeight(t->pRight)) +1;
    x->height = max(getHeight(x->pLeft),getHeight(x->pRight)) +1;

    return x;
}

int balanceFactor(NODE* t){
    if(t == NULL)
        return 0;
    return (getHeight(t->pLeft) - getHeight(t->pRight));
}

NODE* insertAVLNode(NODE* t, int x){
    NODE* p = createNode(x);
    if( t == NULL){
        return p;
    }

    if(x < t->data){
        t->pLeft = insertAVLNode(t->pLeft,x);
    }
    else if(x > t->data){
        t->pRight = insertAVLNode(t->pRight,x);
    }
    else{
        return t;
    }
    t->height = max(getHeight(t->pLeft), getHeight(t->pRight)) + 1;

    int heightDiff = balanceFactor(t);

    //L-L Case
    if(heightDiff > 1 && x < t->pLeft->data){
        return rightRotate(t);
    }

    //R-R Case
    if(heightDiff < -1 && x > t->pRight->data){
        return leftRotate(t);
    }

    //L-R Case  
    if (heightDiff > 1 && x > t->pLeft->data)  
    {  
        t->pLeft = leftRotate(t->pLeft);  
        return rightRotate(t);  
    }  
    
    //R-L Case
    if(heightDiff < -1 && x < t->pRight->data){
        t->pRight = rightRotate(t->pRight);
        return leftRotate(t);
    }

    return t;
}

bool isAVLTree(NODE* node) {
        if (node == nullptr)
            return true;

        int isbalanceFactor = balanceFactor(node);

        if (isbalanceFactor > 1 || isbalanceFactor < -1)
            return false;

        return isAVLTree(node->pLeft) && isAVLTree(node->pRight);
}

NODE* minNode(NODE* t){
    NODE* tmp = t;
    while(tmp->pLeft != NULL){
        tmp = tmp->pLeft;
    }
    return tmp;
}

NODE* deleteAVLNode(NODE* t, int x){
    if(t == NULL)
        return t;
    
    if(x < t->data){
        t->pLeft = deleteAVLNode(t->pLeft,x);
    }
    else if(x > t->data){
        t->pRight = deleteAVLNode(t->pRight,x);
    }
    //Perform deletion
    else{
        //Node has one child or no child
        if(t->pLeft == NULL || t->pRight == NULL){
            NODE* tmp = t->pLeft?t->pLeft:t->pRight;

            //No child case
            if(tmp == NULL){
                tmp = t;
                t = NULL;
            }
            else{
                *t = *tmp; //Copy the component only
                free(tmp);
            }
        }
        else{
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            NODE* tmp = minNode(t->pRight);
            t->data = tmp->data;

            //Delete inorder successor
            t->pRight = deleteAVLNode(t->pRight,tmp->data);
        }
    }
    if(t == NULL) return t;
    t->height = max(getHeight(t->pLeft),getHeight(t->pRight)) +1;

    int balance = balanceFactor(t);
    // Left Left Case 
    if (balance > 1 && 
        balanceFactor(t->pLeft) >= 0) 
        return rightRotate(t); 
 
    // Left Right Case 
    if (balance > 1 && 
        balanceFactor(t->pLeft) < 0) 
    { 
        t->pLeft = leftRotate(t->pLeft); 
        return rightRotate(t); 
    } 
 
    // Right Right Case 
    if (balance < -1 && 
        balanceFactor(t->pRight) <= 0) 
        return leftRotate(t); 
 
    // Right Left Case 
    if (balance < -1 && 
        balanceFactor(t->pRight) > 0) 
    { 
        t->pRight = rightRotate(t->pRight); 
        return leftRotate(t); 
    } 
 
    return t; 
}