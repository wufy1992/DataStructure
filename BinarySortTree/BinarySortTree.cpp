#include <cstdio>
#include <cstring>
#include <vector>

template <typename T>
struct Node
{
	T data;
	Node* leftNode;
	Node* rightNode;
	Node(T d)
	{
		data = d;
		leftNode = nullptr;
		rightNode = nullptr;
	}
};

template <typename T>
class BinarySortTree
{
public:
	BinarySortTree(const std::vector<T>& vecData)
	{
		rootNode = nullptr;
		for (size_t i = 0; i < vecData.size(); i++)
		{
			Insert(vecData[i]);
		}
	}



	void Insert(T data)
	{
		InsertRecursion(rootNode, data);
	}

	void Delete(T data)
	{
		DeleteRecursion(rootNode, data, nullptr, true);
	}

	bool IsExist(T data)
	{
		IsExistRecursion(rootNode, data);
	}

	Node<T>* GetRoot()
	{
		return rootNode;
	}


	bool Compare(BinarySortTree cmpTree)
	{
		return CompareRecursion(rootNode, cmpTree.GetRoot());
	}

private:
	void InsertRecursion(Node<T>*& node, T data)
	{
		if (node == nullptr)
		{
			node = new Node<T>(data);
			node->data = data;
			node->leftNode = nullptr;
			node->rightNode = nullptr;
		}
		else if (data < node->data)
			InsertRecursion(node->leftNode, data);
		else
			InsertRecursion(node->rightNode, data);
	}

	void DeleteRecursion(Node<T>*& node, T data, Node<T>*& partentNode, bool isRight)
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

	bool IsExistRecursion(const Node<T>* node, T data)
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


	bool CompareRecursion(Node<T>* node, Node<T>* nodeCompared)
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
	Node<T>* rootNode;
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
		int len = strlen(strInput);
		std::vector<char> dataVec;
		for (int i = 0; i < len; i++)
		{
			dataVec.push_back(strInput[i]);
		}
		BinarySortTree<char> binarySortTree = BinarySortTree<char>(dataVec);

		while (count--)
		{
			scanf("%s", strInput);
			if (strlen(strInput) != len)
			{
				printf("NO\n");
				continue;
			}
			dataVec.clear();
			for (int i = 0; i < len; i++)
			{
				dataVec.push_back(strInput[i]);
			}
			BinarySortTree<char> comparedBinarySortTree = BinarySortTree<char>(dataVec);

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
