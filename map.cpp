#include "map.hpp"



MAP_TEMPLATE_DECLARE
DSA::Map<Key_T, Value_T>::Node::Node(const Key_T& k, const Value_T& v) :
key(k), value(v), itHelper({k, v}),
parent(nullptr), left(nullptr), right(nullptr), color(Red) {}

MAP_TEMPLATE_DECLARE
bool DSA::Map<Key_T, Value_T>::Node::isBlack() const noexcept {
    return this->color == Black;
}

MAP_TEMPLATE_DECLARE
bool DSA::Map<Key_T, Value_T>::Node::isRed() const noexcept {
    return this->color == Red;
}

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Node* DSA::Map<Key_T, Value_T>::Node::getGrandparent() {
    return (this->parent != nullptr) ? this->parent->parent : nullptr;
}

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Node* DSA::Map<Key_T, Value_T>::Node::getUncle() {
    Node* grandparent = this->getGrandparent();

    if (grandparent == nullptr)
        return nullptr;

    if (grandparent->left == this->parent)
        return grandparent->right;
    else
        return grandparent->left;
}

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::DestructorHelper(typename DSA::Map<Key_T, Value_T>::Node* node) {
    if (node == nullptr)
        return;
    DestructorHelper(node->left);
    DestructorHelper(node->right);
    delete node;
}

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Node*
DSA::Map<Key_T, Value_T>::FindHelper(typename DSA::Map<Key_T, Value_T>::Node* node, const Key_T& key) const {
    if (node == nullptr)
        return nullptr;
    if (node->key == key)
        return node;
    else if (key < node->key)
        return FindHelper(node->left, key);
    else
        return FindHelper(node->right, key);
}

MAP_TEMPLATE_DECLARE
bool DSA::Map<Key_T, Value_T>::InsertHelper(
        typename DSA::Map<Key_T, Value_T>::Node*& nodeRoot, typename DSA::Map<Key_T, Value_T>::Node*& node,
        typename DSA::Map<Key_T, Value_T>::Node* parent) {
    if (nodeRoot == nullptr) {
        nodeRoot = node;
        node->parent = parent;
        return true;
    }
    if (node->key < nodeRoot->key) {
        return InsertHelper(nodeRoot->left, node, nodeRoot);
    } else if (node->key > nodeRoot->key) {
        return InsertHelper(nodeRoot->right, node, nodeRoot);
    } else {
        nodeRoot->value = node->value;
        nodeRoot->itHelper = node->itHelper;
        delete node;
        return false;
    }
}

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::RotateLeft(typename DSA::Map<Key_T, Value_T>::Node *node) {
    if (node == nullptr || node->right == nullptr)
        return;

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

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::RotateRight(typename DSA::Map<Key_T, Value_T>::Node *node) {
    if (node == nullptr || node->left == nullptr)
        return;

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

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::Balance(typename DSA::Map<Key_T, Value_T>::Node* node) {
    if (node == nullptr) {
        return;
    }
    if (node->parent == nullptr) {
        node->color = Node::Black;
        return;
    }
    if (node->parent->isBlack()) {
        return;
    }
    Node* parent = node->parent;
    Node* grandparent = node->getGrandparent();
    if (grandparent == nullptr) {
        return;
    }
    Node* uncle = node->getUncle();
    if (uncle != BLACK && uncle->isRed()) {
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

MAP_TEMPLATE_DECLARE
DSA::Map<Key_T, Value_T>::Map() : root(nullptr), nodeCount(0) {}

MAP_TEMPLATE_DECLARE
DSA::Map<Key_T, Value_T>::~Map() { DestructorHelper(root); }

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::clear() {
    DestructorHelper(root);
    root = nullptr;
    nodeCount = 0;
}

MAP_TEMPLATE_DECLARE
bool DSA::Map<Key_T, Value_T>::isEmpty() const noexcept { return this->nodeCount == 0; }

MAP_TEMPLATE_DECLARE
size_t DSA::Map<Key_T, Value_T>::size() const noexcept { return this->nodeCount; }

MAP_TEMPLATE_DECLARE
size_t DSA::Map<Key_T, Value_T>::count(const Key_T& key)
{ return (FindHelper(root, key) != nullptr) ? 1 : 0; }

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::insert(const Key_T& key, const Value_T& value) {
    Node* node = new Node(key, value);
    if (InsertHelper(root, node, nullptr)) {
        nodeCount++;
        Balance(node);
    }
}

MAP_TEMPLATE_DECLARE
Value_T& DSA::Map<Key_T, Value_T>::at(const Key_T& key) {
    Node* node = FindHelper(root, key);
    if (node == nullptr)
        throw std::out_of_range("Key Does Not Exist In Map");
    return node->value;
}

MAP_TEMPLATE_DECLARE
void DSA::Map<Key_T, Value_T>::Iterator::getLeftNode(typename DSA::Map<Key_T, Value_T>::Node* node) {
    if (node == nullptr)
        return;
    nodes.push(node);
    getLeftNode(node->left);
}

MAP_TEMPLATE_DECLARE
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

MAP_TEMPLATE_DECLARE
DSA::Map<Key_T, Value_T>::Iterator::Iterator() : currentNode(nullptr) {}

MAP_TEMPLATE_DECLARE
DSA::Map<Key_T, Value_T>::Iterator::Iterator(typename DSA::Map<Key_T, Value_T>::Node* node) : currentNode(nullptr) {
    getLeftNode(node);
    getRightNode();
}

MAP_TEMPLATE_DECLARE
std::pair<Key_T, Value_T>& DSA::Map<Key_T, Value_T>::Iterator::operator*() const { return currentNode->itHelper; }

MAP_TEMPLATE_DECLARE
std::pair<Key_T, Value_T>* DSA::Map<Key_T, Value_T>::Iterator::operator->() const { return &(currentNode->itHelper); }

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Iterator& DSA::Map<Key_T, Value_T>::Iterator::operator++() {
    getRightNode();
    return *this;
}

MAP_TEMPLATE_DECLARE
bool DSA::Map<Key_T, Value_T>::Iterator::operator==(const Iterator& other) const
{ return this->currentNode == other.currentNode; }

MAP_TEMPLATE_DECLARE
bool DSA::Map<Key_T, Value_T>::Iterator::operator!=(const Iterator& other) const
{ return this->currentNode != other.currentNode; }

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Iterator DSA::Map<Key_T, Value_T>::find(const Key_T& key) {
    Node* node = FindHelper(root, key);
    return Iterator(node);
}

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Iterator DSA::Map<Key_T, Value_T>::begin() { return Iterator(root); }

MAP_TEMPLATE_DECLARE
typename DSA::Map<Key_T, Value_T>::Iterator DSA::Map<Key_T, Value_T>::end() { return Iterator(); }

template class DSA::Map<int, int>;
template class DSA::Map<int, Car>;
template class DSA::Map<std::string, Car>;
