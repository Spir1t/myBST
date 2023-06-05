#include "BST.h"
#include <vector>
#include <iostream>


BinarySearchTree::Node::Node(Key key, Value value, Node* parent, Node* left, Node* right)
    :keyValuePair(key, value), parent(parent), left(left), right(right) {}


BinarySearchTree::Node::Node(const BinarySearchTree::Node &other) {
    keyValuePair = other.keyValuePair;
    parent = other.parent;
    if (other.left == nullptr) {
        left = nullptr;
    } else {
        left = new Node(*other.left);
    }
    if (other.right == nullptr) {
        right = nullptr;
    } else {
        right = new Node(*other.right);
    }
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
{
    if(other._root == nullptr)
    {
        _root == nullptr;
    }
    else
    {
        _root == new Node(*other._root);
    }
    _size = other._size;
}


BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
    if(this == &other)
    {
        return *this;
    }
    this->~BinarySearchTree();
    if(other._root == nullptr)
    {
        _root == nullptr;
    }
    else
    {
        _root == new Node(*other._root);
    }
    _size = other._size;
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept 
{
    _root = other._root;
    other._root = nullptr;
    _size = other._size;
    other._size = 0;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->~BinarySearchTree();
    _root = other._root;
    other._root = nullptr;
    _size = other._size;
    other._size = 0;
    return *this;
}


BinarySearchTree::~BinarySearchTree() {
    if (_root != nullptr) {
        std::vector<Node *> nodes;
        nodes.push_back(_root);
        while (!nodes.empty()) {
            Node *node = nodes.back();
            nodes.pop_back();
            if (node->left != nullptr) {
                nodes.push_back(node->left);
            }
            if (node->right != nullptr) {
                nodes.push_back(node->right);
            }
            delete node;
        }
    }
}


BinarySearchTree::Iterator::Iterator(BinarySearchTree::Node *node) 
{
    _node = node;
}


std::pair<Key, Value> &BinarySearchTree::Iterator::operator*()
{
    return _node->keyValuePair;
}


const std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() const {
    return _node->keyValuePair;
}


std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() 
{
    return &_node->keyValuePair;
}


const std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() const 
{
    return &_node->keyValuePair;
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() 
{
    if(_node->right != nullptr){
        _node = _node->right;
        while(_node->left != nullptr){
            _node = _node->left;
        }
        return *this;
    }
    while(_node->parent != nullptr && _node->parent->right == _node){
        _node = _node->parent;
    }
    _node = _node->parent;
    return *this;
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) 
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() 
{
    if(_node->left != nullptr){
        _node = _node->left;
        while(_node->right != nullptr){
            _node = _node->right;
        }
        return *this;
    }
    while(_node->parent != nullptr && _node->parent->left == _node){
        _node = _node->parent;
    }
    _node = _node->parent;
    return *this;
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) 
{
    Iterator tmp = *this;
    --(*this);
    return tmp;
}


bool BinarySearchTree::Iterator::operator==(const BinarySearchTree::Iterator &other) const 
{
    return _node == other._node;
}


bool BinarySearchTree::Iterator::operator!=(const BinarySearchTree::Iterator &other) const 
{
    return _node != other._node;
}

//const iterator

BinarySearchTree::ConstIterator::ConstIterator(const BinarySearchTree::Node *node) 
{
    _node = node;
}

const std::pair<Key, Value> &BinarySearchTree::ConstIterator::operator*() const 
{
    return _node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::ConstIterator::operator->() const 
{
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() 
{
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    } else {
        while (_node->parent != nullptr && _node->parent->right == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) 
{
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() 
{
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    } else {
        while (_node->parent != nullptr && _node->parent->left == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) 
{
    ConstIterator tmp = *this;
    --(*this);
    return tmp;
}

bool BinarySearchTree::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const {
    return _node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const {
    return !(*this == other);
}


void BinarySearchTree::insert(const Key &key, const Value &value, Node *node) 
{
    if (node == nullptr) {
        _root = new Node(key, value);
        _size++;
        return;
    }
    if (key < node->keyValuePair.first) {
        if (node->left == nullptr) {
            node->left = new Node(key, value);
            node->left->parent = node;
            _size++;
            return;
        }
        insert(key, value, node->left);
    } else if (key > node->keyValuePair.first) {
        if (node->right == nullptr) {
            node->right = new Node(key, value);
            node->right->parent = node;
            _size++;
            return;
        }
        insert(key, value, node->right);
    } else {
        node->keyValuePair.second = value;
    }
}


void BinarySearchTree::insert(const Key &key, const Value &value) 
{
    insert(key, value, _root);
}


void BinarySearchTree::erase(const Key &key, BinarySearchTree::Node *node) 
{
    if (node == nullptr) {
        return;
    }
    if (key < node->keyValuePair.first) {
        erase(key, node->left);
    } else if (key > node->keyValuePair.first) {
        erase(key, node->right);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent == nullptr) {
                _root = nullptr;
            } else if (node->parent->left == node) {
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
            delete node;
            _size--;
        } else if (node->left == nullptr) {
            if (node->parent == nullptr) {
                _root = node->right;
                _root->parent = nullptr;
            } else if (node->parent->left == node) {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            } else {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            delete node;
            _size--;
        } else if (node->right == nullptr) {
            if (node->parent == nullptr) {
                _root = node->left;
                _root->parent = nullptr;
            } else if (node->parent->left == node) {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            } else {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            delete node;
            _size--;
        } else {
            Node *tmp = node->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            node->keyValuePair = tmp->keyValuePair;
            erase(tmp->keyValuePair.first, tmp);
        }
    }
}


void BinarySearchTree::erase(const Key &key) 
{
    erase(key, _root);
}


BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) 
{
    Node *node = _root;
    while (node != nullptr) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else if (key > node->keyValuePair.first) {
            node = node->right;
        } else {
            break;
        }
    }
    if (node == nullptr) {
        return end();
    }
    return Iterator(node);
}


BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const 
{
    Node *node = _root;
    while (node != nullptr) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else if (key > node->keyValuePair.first) {
            node = node->right;
        } else {
            break;
        }
    }
    if (node == nullptr) {
        return cend();
    }
    return ConstIterator(node);
}


std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) 
{
    Iterator it_start = find(key);
    if (it_start == end()) {
        return std::make_pair(it_start, it_start);
    }
    Iterator it_tmp = it_start;
    Iterator it_end = it_start;
    it_tmp--;
    Iterator begin_it = begin();
    while (it_tmp->first == key && it_tmp != begin_it) {
        it_start--;
        it_tmp--;
    }
    it_tmp = it_end;
    it_tmp++;
    Iterator end_it = end();
    while (it_tmp->first == key && it_tmp != end_it) {
        it_end++;
        it_tmp++;
    }
    it_end++;
    return std::make_pair(it_start, it_end);
}


std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator>
BinarySearchTree::equalRange(const Key &key) const {
    ConstIterator it_start = find(key);
    if (it_start == cend()) {
        return std::make_pair(it_start, it_start);
    }
    ConstIterator it_tmp = it_start;
    ConstIterator it_end = it_start;
    it_tmp--;
    ConstIterator begin_it = cbegin();
    while (it_tmp->first == key && it_tmp != begin_it) {
        it_start--;
        it_tmp--;
    }
    it_tmp = it_end;
    it_tmp++;
    ConstIterator end_it = cend();
    while (it_tmp->first == key && it_tmp != end_it) {
        it_end++;
        it_tmp++;
    }
    it_end++;
    return std::make_pair(it_start, it_end);
}


BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const 
{
    Node *node = _root;
    while (node != nullptr) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else if (key > node->keyValuePair.first) {
            node = node->right;
        } else {
            break;
        }
    }
    while (node->left != nullptr) {
        node = node->left;
    }

    return ConstIterator(node);
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const 
{
    Node *node = _root;
    while (node != nullptr) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else if (key > node->keyValuePair.first) {
            node = node->right;
        } else {
            break;
        }
    }
    while (node->right != nullptr) {
        node = node->right;
    }

    return ConstIterator(node);
}


BinarySearchTree::Iterator BinarySearchTree::begin() 
{
    Node *node = _root;
    if (node == nullptr) {
        return Iterator(node);
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return Iterator(node);
}


BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const 
{
    Node *node = _root;
    if (node == nullptr) {
        return ConstIterator(node);
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return ConstIterator(node);
}


BinarySearchTree::Iterator BinarySearchTree::end() 
{
    Node *node = _root;
    if (node == nullptr) {
        return Iterator(node);
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return Iterator(node);
}


BinarySearchTree::ConstIterator BinarySearchTree::cend() const 
{
    Node *node = _root;
    if (node == nullptr) {
        return ConstIterator(node);
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return ConstIterator(node);
}

size_t BinarySearchTree::size() const 
{
    return _size;
}