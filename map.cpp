#include "map.hpp"


template<typename Key_T, typename Value_T>
DSA::Map<Key_T, Value_T>::Node::Node(Key_T k, Value_T v) :
key(k), value(v), itHelper({k, v}),
parent(nullptr), left(nullptr), right(nullptr), color(Red) {}

template<typename Key_T, typename Value_T>
bool DSA::Map<Key_T, Value_T>::Node::isBlack() const noexcept {
    return this->color == Black;
}

template<typename Key_T, typename Value_T>
bool DSA::Map<Key_T, Value_T>::Node::isRed() const noexcept {
    return this->color == Red;
}

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Node* DSA::Map<Key_T, Value_T>::Node::getGrandparent() {
    return (this->parent != nullptr) ? this->parent->parent : nullptr;
}

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Node* DSA::Map<Key_T, Value_T>::Node::getUncle() {
    Node* grandparent = this->getGrandparent();

    if (grandparent == nullptr)
        return nullptr;

    if (grandparent->left == this->parent)
        return grandparent->right;
    else
        return grandparent->left;
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::DestructorHelper(typename DSA::Map<Key_T, Value_T>::Node* node) {
    if (node == nullptr)
        return;
    DestructorHelper(node->left);
    DestructorHelper(node->right);
    delete node;
}

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Node*
DSA::Map<Key_T, Value_T>::FindHelper(typename DSA::Map<Key_T, Value_T>::Node*& node, const Key_T& key) {
    if (node == nullptr)
        return nullptr;
    if (node->key == key)
        return node;
    else if (node->key < key)
        return FindHelper(node->left, key);
    else
        return FindHelper(node->right, key);
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::InsertHelper(
        typename DSA::Map<Key_T, Value_T>::Node*& nodeRoot, typename DSA::Map<Key_T, Value_T>::Node*& node,
        typename DSA::Map<Key_T, Value_T>::Node* parent) {
    if (nodeRoot == nullptr) {
        nodeRoot = node;
        node->parent = parent;
        return;
    }
    if (node->key < nodeRoot->key) {
        InsertHelper(nodeRoot->left, node, nodeRoot);
    } else if (node->key > nodeRoot->key) {
        InsertHelper(nodeRoot->right, node, nodeRoot);
    } else {
        nodeRoot->value = node->value;
        nodeRoot->itHelper = node->itHelper;
        delete node;
        nodeCount--;
        return;
    }
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::RotateLeft(typename DSA::Map<Key_T, Value_T>::Node *node) {
    Node* rightNode = node->right;
    Node* rightNodeChild = rightNode->left;

    if (rightNodeChild != nullptr)
        rightNodeChild->parent = node;

    rightNode->parent = node->parent;

    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = rightNode;
        else
            node->parent->right = rightNode;
    }
    else {
        root = rightNode;
    }

    node->right = rightNodeChild;
    rightNode->left = node;
    node->parent = rightNode;
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::RotateRight(typename DSA::Map<Key_T, Value_T>::Node *node) {
    Node* leftNode = node->left;
    Node* leftNodeChild = leftNode->right;

    if (leftNodeChild != nullptr)
        leftNodeChild->parent = node;

    leftNode->parent = node->parent;

    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = leftNode;
        else
            node->parent->right = leftNode;
    }
    else {
        root = leftNode;
    }

    node->left = leftNodeChild;
    leftNode->right = node;
    node->parent = leftNode;
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::Balance(typename DSA::Map<Key_T, Value_T>::Node *node) {
    if (node->parent == nullptr) {
        node->color = Node::Black;
        return;
    }
    if (node->parent->isBlack())
        return;
    Node* parent = node->parent;
    Node* grandparent = node->getGrandparent();
    if (grandparent == nullptr)
        return;
    Node* uncle = node->getUncle();
    if (uncle != nullptr && uncle->isRed()) {
        parent->color = Node::Black;
        uncle->color = Node::Black;
        grandparent->color = Node::Red;
        Balance(grandparent);
        return;
    }
    if (node == parent->right && parent == grandparent->left) {
        RotateLeft(parent);
        node = parent;
        parent = node->parent;
    } else if (node == parent->left && parent == grandparent->right) {
        RotateRight(parent);
        node = parent;
        parent = node->parent;
    }
    parent->color = Node::Black;
    grandparent->color = Node::Red;
    if (node == parent->left) {
        RotateRight(grandparent);
    } else {
        RotateLeft(grandparent);
    }
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::PrintHelper(typename DSA::Map<Key_T, Value_T>::Node* node) const {
    if (node == nullptr)
        return;
    PrintHelper(node->left);
    std::cout << node->key << ": " << node->value << ", ";
    PrintHelper(node->right);
}

template<typename Key_T, typename Value_T>
DSA::Map<Key_T, Value_T>::Map() : root(nullptr), nodeCount(0) {}

template<typename Key_T, typename Value_T>
DSA::Map<Key_T, Value_T>::~Map() { DestructorHelper(root); }

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::clear() {
    DestructorHelper(root);
    root = nullptr;
    nodeCount = 0;
}

template<typename Key_T, typename Value_T>
bool DSA::Map<Key_T, Value_T>::isEmpty() const noexcept { return this->nodeCount == 0; }

template<typename Key_T, typename Value_T>
size_t DSA::Map<Key_T, Value_T>::size() const noexcept { return this->nodeCount; }

template<typename Key_T, typename Value_T>
size_t DSA::Map<Key_T, Value_T>::count(const Key_T& key) const
{ return (FindHelper(root, key) != nullptr) ? 1 : 0; }

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::insert(const Key_T& key, const Value_T& value) {
    Node* node = new Node(key, value);
    InsertHelper(root, node, nullptr);
    Balance(node);
    nodeCount++;
}

template<typename Key_T, typename Value_T>
Value_T& DSA::Map<Key_T, Value_T>::at(const Key_T& key) {
    Node* node = FindHelper(node, key);
    if (node == nullptr)
        throw std::out_of_range("Key Does Not Exist In Map");
    return node->value;
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::printInOrder() const {
    PrintHelper(root);
    std::cout << std::endl;
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::Iterator::getLeftNode(typename DSA::Map<Key_T, Value_T>::Node* node) {
    if (node == nullptr)
        return;
    nodes.push(node);
    getLeftNode(node->left);
}

template<typename Key_T, typename Value_T>
void DSA::Map<Key_T, Value_T>::Iterator::getRightNode() {
    if (!nodes.empty()) {
        currentNode = nodes.top();
        nodes.pop();
        if (currentNode->right != nullptr)
            getLeftNode(currentNode->right);
    }
    else {
        currentNode = nullptr;
    }
}

template<typename Key_T, typename Value_T>
DSA::Map<Key_T, Value_T>::Iterator::Iterator() : currentNode(nullptr) {}

template<typename Key_T, typename Value_T>
DSA::Map<Key_T, Value_T>::Iterator::Iterator(typename DSA::Map<Key_T, Value_T>::Node* node) : currentNode(nullptr) {
    getLeftNode(node);
    getRightNode();
}

template<typename Key_T, typename Value_T>
std::pair<Key_T, Value_T>& DSA::Map<Key_T, Value_T>::Iterator::operator*() const { return currentNode->itHelper; }

template<typename Key_T, typename Value_T>
std::pair<Key_T, Value_T>* DSA::Map<Key_T, Value_T>::Iterator::operator->() const { return &(currentNode->itHelper); }

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Iterator& DSA::Map<Key_T, Value_T>::Iterator::operator++() {
    getRightNode();
    return *this;
}

template<typename Key_T, typename Value_T>
bool DSA::Map<Key_T, Value_T>::Iterator::operator==(const Iterator& other) const
{ return this->currentNode == other.currentNode; }

template<typename Key_T, typename Value_T>
bool DSA::Map<Key_T, Value_T>::Iterator::operator!=(const Iterator& other) const
{ return this->currentNode != other.currentNode; }

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Iterator DSA::Map<Key_T, Value_T>::find(const Key_T& key) {
    Node* node = FindHelper(root, key);
    return Iterator(node);
}

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Iterator DSA::Map<Key_T, Value_T>::begin() { return Iterator(root); }

template<typename Key_T, typename Value_T>
typename DSA::Map<Key_T, Value_T>::Iterator DSA::Map<Key_T, Value_T>::end() { return Iterator(); }
