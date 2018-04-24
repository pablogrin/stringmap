#include <algorithm>
#include "string_map.h"
#include <iostream>


// public functions //

template<typename T>
string_map<T>::string_map(){
    root = new Node(nullptr);
    _amountOfKeys = 0;
}

template<typename T>
string_map<T>::~string_map(){
    this->clear();
    delete root;
}

template<typename T>
string_map<T>::string_map(const string_map& other){
    root = new Node(nullptr);
    _amountOfKeys = 0;
    auto it = other.cbegin();
    while (!it.isEnd()){
        insert(*it);
        ++it;
    }
}


template<typename T>
string_map<T>& string_map<T>::operator=(const string_map& other){
    this->clear();
    auto it = other.cbegin();
    while (!it.isEnd()){
        auto toInsert = *it;
        this->insert(toInsert);
        ++it;
    }
    return *this;
}

template<typename T>
bool string_map<T>::operator==(const string_map<T>& other) const{
    if (this->size() != other.size()) {
        return false;
    } else {
        auto itOther = other.cbegin();
        while(!itOther.isEnd()) {
            auto pairOther = *itOther;
            if (this->count(pairOther.first) == 0) {
                return false;
            }
            if (other.at(pairOther.first) != this->at(pairOther.first)){
                return false;
            }
            ++itOther;
        }
    }
    return true;
}

template<typename T>
bool string_map<T>::operator!= (const string_map<T>& other) const{
    return !(*this==other);
}

template<typename T>
typename string_map<T>::size_type string_map<T>::count(const string_map<T>::key_type& key) const{
    if (find(key).isEnd()) {
        return 0;
    } else {
        return 1;
    }
}

template<typename T>
size_t string_map<T>::size() const{
    return this->_amountOfKeys;
}

template<typename T>
bool string_map<T>::empty() const{
    return this->root->children.empty();
}

template<typename T>
T& string_map<T>::operator[](const string_map<T>::key_type& key){
    if (find(key).isEnd()) {
        insert(value_type(key, T()));
    }
    return at(key);
}

template<typename T>
T& string_map<T>::at(const string_map<T>::key_type& key){
    int index = 0;
    Node* current = root;
    while (index != key.size() && current->children.count(key[index]) != 0) {
        current = current->children[key[index]];
        index++;
    }
    return current->value->second;
}

template<typename T>
const T& string_map<T>::at(const string_map<T>::key_type& key) const{
    int index = 0;
    Node* current = root;
    while (index != key.size() && current->children.count(key[index]) != 0){
        current = current->children[key[index]];
        index++;
    }
    return current->value->second;
}

template<typename T>
void string_map<T>::clear() {
    auto it = this->begin();
    while (it != end()){
        it = erase(it);
    }
}

template<typename T>
typename string_map<T>::iterator string_map<T>::begin(){
    auto it = string_map<T>::iterator(*this);
    return it;
}

template<typename T>
typename string_map<T>::iterator string_map<T>::end(){
    auto it = string_map<T>::iterator(*this);
    it.currentPair = nullptr;
    return it;
}

template<typename T>
typename string_map<T>::const_iterator string_map<T>::cbegin() const{
    auto it = string_map<T>::iterator(*this);
    return it;
}

template<typename T>
typename string_map<T>::const_iterator string_map<T>::cend() const{
    auto it = string_map<T>::iterator(*this);
    it.currentPair = nullptr;
    return it;
}

template<typename T>
typename string_map<T>::iterator string_map<T>::find(const string_map<T>::key_type& key){
    Node* nodeFound = findNode(key);
    if (nodeFound == nullptr) {
        return end();
    }
    else {
        auto it = string_map<T>::iterator(this);
        it.currentPair = nodeFound->value;
        return it;
    }
}

template<typename T>
typename string_map<T>::const_iterator string_map<T>::find(const string_map<T>::key_type& key) const{
    Node* nodeFound = findNode(key);
    if (nodeFound == nullptr) {
        return end();
    }
    else {
        auto it = string_map<T>::iterator(this);
        it.currentPair = nodeFound->value;
        return it;
    }
}

template<typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map<T>::value_type& val){
    bool inserted = false;
    string key = val.first;
    T valor = val.second;
    iterator it = find(key);
    if (!it.isEnd()) {
        pair<string_map<T>::iterator, bool> res = make_pair(this->end(), inserted);
        return res;
    } else {
        int index = 0;
        Node* current = root;
        while (index < key.size()) {
            if (current->children.count(key[index]) == 0) {
                Node* nextNode = new Node(nullptr);
                current->children.insert(pair<char, Node*>(key[index], nextNode));
            }
            current = current->children[key[index]];
            index++;
        }
        current->value = new value_type(val);
        inserted = true;
        this->_amountOfKeys++;
        pair<string_map<T>::iterator, bool> res;
        auto it = iterator(*this);
        it.currentPair = current->value;
        res = make_pair(it, inserted);
        return res;
    }
}

template<typename T>
typename string_map<T>::size_type string_map<T>::erase(const string_map<T>::key_type& key) {
    string editedKey = key;
    Node* current = findNode(key);
    auto branch = getBranch(key);
    if(count(key) == 0){
        return 0;
    }
    delete current->value;
    current->value = nullptr;
    this->_amountOfKeys--;
    if (!current->children.empty()) {
        return 1;
    }
    delete current;
    current = branch.back();
    branch.pop_back();
    while (!branch.empty() && current->children.size() <= 1 && current->value == nullptr) {
        current->children.erase(editedKey.back());
        if (current->children.empty()){
            delete current;
        }
        current = branch.back();
        branch.pop_back();
        editedKey.pop_back();
    }
    current->children.erase(editedKey.back());
    return 1;
}

template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map::iterator pos) {
    auto key = pos.currentPair->first;
    auto it = ++pos;
    erase(key);
    return it;
}

// private functions //

template<typename T>
string string_map<T>::firstKey() const {
    Node* currentNode = root;
    string key = "";

    while (currentNode->children.size() != 0 && currentNode->value == nullptr) {
        auto firstPair = currentNode->children.begin();
        char firstChar = (*firstPair).first;
        key += firstChar;
        currentNode = currentNode->children[firstChar];
    }
    return key;
}

template<typename T>
string string_map<T>::nextKey(string currentKey) const {
    Node* currentNode = findNode(currentKey);
    if(currentNode == nullptr){
        return "";
    }
    std::string key = currentKey;
    if (currentNode->children.size() > 0) { //current key is substring of nexy key
        bool noMeMovi = true;
        while ((currentNode->children.size() != 0 && currentNode->value == nullptr) || noMeMovi) {
            noMeMovi = false;
            auto firstPair = currentNode->children.begin();
            char firstChar = (*firstPair).first;
            key += firstChar;
            currentNode = currentNode->children[firstChar];
        }
        return key;
    } else { //current key is not substring of nexy key
        vector<Node*> branch = getBranch(currentKey);
        unsigned long index = branch.size() - 1;
        currentNode = branch[index];
        bool sideSteps = false;
        while (index > 0 && !(sideSteps)) {
            auto it = currentNode->children.begin();
            while (it->first < key.back() && it != currentNode->children.end()) {
                it++;
            }
            if (it != currentNode->children.end()) {
                it++;
            }
            key.pop_back();
            if (it == currentNode->children.end()) {
                currentNode = branch[index - 1];
                index--;
            } else {
                char c = it->first;
                key.push_back(c);
                sideSteps = true;
                currentNode = currentNode->children[it++->first];
            }
        }

        if (currentNode == nullptr) {
            return "";
        } else {
            if (index != 0) { //longest common substring not empty
                while (currentNode->value == nullptr) {
                    key += (*currentNode->children.begin()).first;
                    currentNode = (*currentNode->children.begin()).second;
                }
            } else { //longest common substring is ""
                auto it = root->children.begin();
                while (it->first <= key[0] && it != root->children.end()) {
                    it++;
                }
                if(it == root->children.end()){
                    return "";
                }
                key = "";
                key += it->first;
                currentNode = root->children[it->first];
                while (currentNode->value == nullptr) {
                    key += (*currentNode->hijos.begin()).first;
                    currentNode = (*currentNode->hijos.begin()).second;
                }
            }
        }
        return key;
    }
}

template<typename T>
typename string_map<T>::Node* string_map<T>::findNode(string key) const {
    int index = 0;
    string_map<T>::Node* current = root;
    while (index < key.size() && current->children.count(key[index]) != 0) {
        current = current->children[key[index]];
        index++;
    }
    if (index == key.size() && current->value != nullptr) {
        return current;
    } else {
        return nullptr;
    }
}

template<typename T>
vector<typename string_map<T>::Node*> string_map<T>::getBranch(string key) const {
    vector<string_map<T>::Node*> branch = vector<string_map<T>::Node*>();
    int index = 0;
    string_map<T>::Node* current = root;
    while (index != key.size() && current->children.count(key[index]) != 0) {
        branch.push_back(current);
        current = current->children[key[index]];
        index++;
    }
    return branch;
}







