// BinarySortTree.cpp : Defines the entry point for the console application.
//
#include <cstdio>
#include <cstring>

struct Node
{
	char data;
	Node* leftNode;
	Node* rightNode;
	Node(char d)
	{
		data = d;
		leftNode = nullptr;
		rightNode = nullptr;
	}
};

class BinarySortTree
{
public:
	BinarySortTree(char* strData)
	{
		rootNode = nullptr;
		int len = strlen(strData);
		for (int i = 0; i < len; i++)
		{
			Insert(strData[i]);
		}
	}



	void Insert(char data)
	{
		InsertRecursion(rootNode, data);
	}

	void Delete(char data)
	{
		DeleteRecursion(rootNode, data, nullptr, true);
	}

	bool IsExist(char data)
	{
		IsExistRecursion(rootNode, data);
	}

	Node* GetRoot()
	{
		return rootNode;
	}


	bool Compare(BinarySortTree cmpTree)
	{
		return CompareRecursion(rootNode, cmpTree.GetRoot());
	}

private:
	void InsertRecursion(Node*& node, char data)
	{
		if (node == nullptr)
		{
			node = new Node(data);
		}

		else if (data < node->data)
			InsertRecursion(node->leftNode, data);
		else
			InsertRecursion(node->rightNode, data);
	}

	void DeleteRecursion(Node* node, char data, Node* partentNode, bool isRight)
	{
		if (node->data == data)
		{
			if (node->leftNode == nullptr && node->rightNode == nullptr)
			{
				if (!partentNode)
					rootNode = nullptr;
				if (isRight)
					partentNode->rightNode = nullptr;
				else
					partentNode->leftNode = nullptr;
			}
			else if (node->rightNode == nullptr)
			{
				// 只有左子树
				if (!partentNode)
					rootNode = node->leftNode;
				if (isRight)
					partentNode->rightNode = node->leftNode;
				else
					partentNode->leftNode = node->leftNode;
			}
			else if (node->leftNode == nullptr)
			{
				// 只有右子树
				if (!partentNode)
					rootNode = node->rightNode;
				if (isRight)
					partentNode->rightNode = node->rightNode;
				else
					partentNode->leftNode = node->rightNode;
			}
			else
			{
				Node* tempNode = node->leftNode;
				Node* tempParentNode = node;

				while (tempNode->rightNode)
				{
					// 找到按大小排序正好是其后面的节点
					tempParentNode = tempNode;
					tempNode = tempNode->rightNode;
				}

				tempParentNode->rightNode = nullptr;

				if (!partentNode)
					rootNode = tempNode;
				if (isRight)
					partentNode->rightNode = tempNode;
				else
					partentNode->leftNode = tempNode;

			}

			delete node;
		}
		else
		{

		}
	}

	bool IsExistRecursion(const Node* node, char data)
	{
		if (node->data == data)
		{
			return true;
		}
		if (node->data < data)
			return IsExistRecursion(node->rightNode, data);
		else
			return IsExistRecursion(node->leftNode, data);
	}


	bool CompareRecursion(Node* node, Node* nodeCompared)
	{
		if (node == nullptr && nodeCompared == nullptr)
			return true;

		if (node == nullptr || nodeCompared == nullptr)
		{
			return false;
		}

		if (node->data != nodeCompared->data)
		{
			return false;
		}
		else
		{
			if (!CompareRecursion(node->leftNode, nodeCompared->leftNode))
				return false;
			if (!CompareRecursion(node->rightNode, nodeCompared->rightNode))
				return false;

			return true;
		}
	}

	// data
	Node* rootNode;
};

void testTree()
{
	// HDU 3791
	// freopen("in.txt", "r", stdin);
	int count;
	while (scanf("%d", &count) && count != 0)
	{
		char strInput[15];
		scanf("%s", strInput);

		BinarySortTree binarySortTree = BinarySortTree(strInput);

		while (count--)
		{
			scanf("%s", strInput);
			BinarySortTree comparedBinarySortTree = BinarySortTree(strInput);

			if (binarySortTree.Compare(comparedBinarySortTree)) printf("YES\n");
			else printf("NO\n");
		}
	}
}

int main()
{
	testTree();
	return 0;
}
