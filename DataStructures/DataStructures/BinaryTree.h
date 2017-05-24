#pragma once
#include <functional>
#include <stdexcept>
#include "ArrayQueue.h"
#include "ArrayStack.h"

template <typename T>
class BinaryTree {
public:

	// The node class, containing the data
	class Node {
	public:
		void setData(T elt) {
			this->data = elt;
		}

		T getData() {
			return this->data;
		}

	private:
		T data;
		Node* leftChild;
		Node* rightChild;
		Node* parent;

		Node(T data) : data(data), parent(NULL), leftChild(NULL), rightChild(NULL) { }

		void setParent(Node* parent) {
			this->parent = parent;
		}

		void setLeftChild(Node* child) {
			this->leftChild = child;
		}

		void setRightChild(Node* child) {
			this->rightChild = child;
		}
	};

	/////////////////////////////////

	enum INSERTION_TYPE { LEFT, RIGHT, ANY };

	/////////////////////////////////

	// Constructor
	BinaryTree();
	// Destructor
	~BinaryTree();


	// Know if the tree is empty
	bool empty() const;
	// Get the size of the tree
	int size() const;
	// Get the height of the tree
	int height() const;
	// Get the root of the tree
	Node* root() const;
	// Search a node in the tree
	Node* search(T elt) const;


	// Add a child to the parent node (or as the root if parent is null)
	Node* add(T childData, Node* parent, INSERTION_TYPE type = ANY) throw (std::logic_error);
	// Remove (and deallocate) a node (and all its descendants) from the tree
	void remove(Node* node);

	// Apply a function in each node, with the pre-order traversal
	void applyPreOrder(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the post-order traversal
	void applyPostOrder(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the in-order traversal
	void applyInOrder(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the depth-first traversal
	void applyDepthFirst(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the breadth-first traversal
	void applyBreadthFirst(std::function<void(Node* n)> f, Node* source);


	// Apply a recursive function on the tree
	template <typename U> U recursive(std::function<U(const Node, U, U)> f, Node* source, U terminal) const;

private:
	Node* _root;
};

/////////////////////////////////

// Constructor
template <typename T>
BinaryTree<T>::BinaryTree() {
	_root = NULL;
}

// Destructor
template <typename T>
BinaryTree<T>::~BinaryTree() {
	remove(_root);
}

/////////////////////////////////

// Know if the tree is empty
template <typename T>
bool BinaryTree<T>::empty() const {
	return (_root == NULL);
}

// Get the size of the tree
template <typename T>
int BinaryTree<T>::size() const {
	std::function<int(const Node, int, int)> _aux;
	_aux = [](const Node n, int gauche, int droite) {
		return gauche + droite + 1;
	};

	return recursif(_aux, _root, 0);
}

// Get the height of the tree
template <typename T>
int BinaryTree<T>::height() const {
	std::function<int(const Node, int, int)> _aux;
	_aux = [](const Node n, int gauche, int droite) {
		if (gauche >= droite) {
			return gauche + 1;
		} else {
			return droite + 1;
		}
	};

	return recursif(_aux, _root, 0);
}

// Get the root of the tree
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::root() const {
	return _root;
}

// Search a node in the tree
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::search(T elt) const {
	Node *result = NULL;
	auto _aux = [&result, elt](Node* n) {
		if (n->data == elt) {
			result = n;
		}
	};

	applyDepthFirst(_aux, _root);

	return result;
}

/////////////////////////////////

// Add a child to the parent node (or as the root if parent is null)
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::add(T childData, typename BinaryTree<T>::Node* parent, INSERTION_TYPE type) {
	if (parent == NULL) {
		// Setting the root
		if (_root != NULL) {
			throw std::logic_error("The root is already set !");
		}

		_root = new Node(childData);
		return _root;
	} else {
		// Adding a node
		if (type == LEFT && parent->leftChild != NULL) {
			throw std::logic_error("The parent already has a left child !");
		}
		if (type == RIGHT && parent->rightChild != NULL) {
			throw std::logic_error("The parent already has a right child !");
		}
		if (type == ANY && parent->leftChild != NULL && parent->rightChild != NULL) {
			throw std::logic_error("The parent already has two children !");
		}

		Node* n = new Node(childData);
		n->parent = parent;

		if (type == LEFT || (type == ANY && parent->leftChild == NULL)) {
			parent->leftChild = n;
		}
		else {
			parent->rightChild = n;
		}

		return n;
	}
}

// Remove (and deallocate) a node (and all its descendants) from the tree
template <typename T>
void BinaryTree<T>::remove(typename BinaryTree<T>::Node* node) {
	auto _aux = [](Node* n) {
		if (n->parent != NULL) {
			if (n->parent->leftChild == n) {
				n->parent->leftChild = NULL;
			} else {
				n->parent->rightChild = NULL;
			}
			delete n;
		}
	};

	applyPostOrder(_aux, node);
}

/////////////////////////////////

// Apply a function in each node, with the pre-order traversal
template <typename T>
void BinaryTree<T>::applyPreOrder(std::function<void(Node* n)> f, Node* source) {
	std::function<void(Node*)> _aux;
	_aux = [&_aux, f](Node* n) {
		if (n != NULL) {
			f(n);
			_aux(n->leftChild);
			_aux(n->rightChild);
		}
	};

	_aux(source);
}

// Apply a function in each node, with the post-order traversal
template <typename T>
void BinaryTree<T>::applyPostOrder(std::function<void(Node* n)> f, Node* source) {
	std::function<void(Node*)> _aux;
	_aux = [&_aux, f](Node* n) {
		if (n != NULL) {
			_aux(n->leftChild);
			_aux(n->rightChild);
			f(n);
		}
	};

	_aux(source);
}

// Apply a function in each node, with the in-order traversal
template <typename T>
void BinaryTree<T>::applyInOrder(std::function<void(Node* n)> f, Node* source) {
	std::function<void(Node*)> _aux;
	_aux = [&_aux, f](Node* n) {
		if (n != NULL) {
			_aux(n->leftChild);
			f(n);
			_aux(n->rightChild);
		}
	};

	_aux(source);
}

// Apply a function in each node, with the depth-first traversal
template <typename T>
void BinaryTree<T>::applyDepthFirst(std::function<void(Node* n)> f, Node* source) {
	Stack<Node*> stack = new ArrayStack<Node*>();
	stack->push(source);
	while (!stack->empty()) {
		Node *n = stack.pop();
		if (n != NULL) {
			f(n);
			stack->push(n->leftChild);
			stack->push(n->rightChild);
		}
	}
}

// Apply a function in each node, with the breadth-first traversal
template <typename T>
void BinaryTree<T>::applyBreadthFirst(std::function<void(Node* n)> f, Node* source) {
	Queue<Node*> queue = new ArrayQueue<Node*>();
	queue->add(source);
	while (!queue->empty()) {
		Node *n = queue.remove();
		if (n != NULL) {
			f(n);
			queue->add(n->leftChild);
			queue->add(n->rightChild);
		}
	}
}

/////////////////////////////////

// Apply a recursive function on the tree
template <typename T>
template <typename U>
U BinaryTree<T>::recursive(std::function<U(const Node, U, U)> f, Node* source, U terminal) const {
	if (source == NULL) {
		return terminal;
	}

	U leftValue = recursive(f, source->leftChild, terminal);
	U rightValue = recursive(f, source->rightChild, terminal);
	return f(*source, leftValue, rightValue);
}