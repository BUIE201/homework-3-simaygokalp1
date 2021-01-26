#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;
	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

//Creation of the Tree
void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;

		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}


int findingMax(Node* root) {
	if (root == NULL)
		return 0;

	int left = findingMax(root->pLeft);
	int right = findingMax(root->pRight);

	int returnMax = max(max(left, right) + root->i, root->i);

	return returnMax;
}

void maxarray(Node* pRoot, vector<int>& maxbranch) {

	if (pRoot->pLeft && findingMax(pRoot->pLeft) > findingMax(pRoot->pRight)) {
		pRoot = pRoot->pLeft;
		maxbranch.push_back(pRoot->i);
		maxarray(pRoot, maxbranch);
	}
	else if (pRoot->pRight && findingMax(pRoot->pLeft) < findingMax(pRoot->pRight)) {
		pRoot = pRoot->pRight;
		maxbranch.push_back(pRoot->i);
		maxarray(pRoot, maxbranch);
	}

}


void main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}
	vector<int> maxbranch;
	maxarray(pRoot, maxbranch);
	
	cout << "Branch with the largest sum is: " << pRoot->i << " ";
	
	for (int i : maxbranch) {
		cout << i << " ";
	}
	cout << " -> SUM = " << findingMax(pRoot) << endl;
}