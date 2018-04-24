#include <algorithm>
#include "stringmap.h"
#include <iostream>


// public functions //

template<typename T>
stringmap<T>::stringmap(){
    root = new Node(nullptr);
    _amountOfKeys = 0;
}

template<typename T>
stringmap<T>::~stringmap(){
    this->clear();
    delete root;
}

template<typename T>
stringmap<T>::stringmap(const stringmap& other){
    root = new Node(nullptr);
    _amountOfKeys = 0;
    auto it = other.cbegin();
    while (it != other.cend()){
        insert(*it);
        ++it;
    }
}


template<typename T>
stringmap<T>& stringmap<T>::operator=(const stringmap& other){
    this->clear();
    auto it = other.cbegin();
    while (it != other.cend()){
        auto toInsert = *it;
        this->insert(toInsert);
        ++it;
    }
    return *this;
}

template<typename T>
bool stringmap<T>::operator==(const stringmap<T>& other) const{
    if (this->size() != other.size()) {
        return false;
    } else {
        auto itThis = this->cbegin();
        auto itOther = other.cbegin();
        while (itOther != other.cend()) {
            auto pairThis = *itThis;
            auto pairOther = *itOther;
            if (pairThis.first != pairOther.first || pairThis.second != pairOther.second){
                return false;
            }
            ++itThis;
            ++itOther;
        }
    }
    return true;
}

template<typename T>
bool stringmap<T>::operator!= (const stringmap<T>& other) const{
    return !(*this==other);
}

template<typename T>
typename stringmap<T>::size_type stringmap<T>::count(const stringmap<T>::key_type& key) const{
    if (cfind(key) == cend()) {
        return 0;
    } else {
        return 1;
    }
}

template<typename T>
size_t stringmap<T>::size() const{
    return this->_amountOfKeys;
}

template<typename T>
bool stringmap<T>::empty() const{
    return this->root->children.empty();
}

template<typename T>
T& stringmap<T>::operator[](const stringmap<T>::key_type& key){
    if (find(key) == end()) {
        insert(value_type(key, T()));
    }
    return at(key);
}

template<typename T>
T& stringmap<T>::at(const stringmap<T>::key_type& key){
    int index = 0;
    Node* current = root;
    while (index != key.size() && current->children.count(key[index]) != 0) {
        current = current->children[key[index]];
        index++;
    }
    return current->value->second;
}

template<typename T>
const T& stringmap<T>::cat(const stringmap<T>::key_type& key) const{
    int index = 0;
    Node* current = root;
    while (index != key.size() && current->children.count(key[index]) != 0){
        current = current->children[key[index]];
        index++;
    }
    return current->value->second;
}

template<typename T>
void stringmap<T>::clear() {
    auto it = this->begin();
    while (it != end()){
        it = erase(it);
    }
}

template<typename T>
typename stringmap<T>::iterator stringmap<T>::begin(){
    if (this->empty()){
        return end();
    } else {
        return find(firstKey());
    }
}

template<typename T>
typename stringmap<T>::iterator stringmap<T>::end(){
    auto it = stringmap<T>::iterator(*this);
    it.currentPair = nullptr;
    return it;
}

template<typename T>
typename stringmap<T>::const_iterator stringmap<T>::cbegin() const{
    if (this->empty()){
        return cend();
    } else {
        return cfind(firstKey());
    }
}

template<typename T>
typename stringmap<T>::const_iterator stringmap<T>::cend() const{
    auto it = stringmap<T>::const_iterator(*this);
    it.currentPair = nullptr;
    return it;
}

template<typename T>
typename stringmap<T>::iterator stringmap<T>::find(const stringmap<T>::key_type& key){
    Node* nodeFound = findNode(key);
    if (nodeFound == nullptr) {
        return end();
    }
    else {
        auto it = iterator(*this);
        it.currentPair = nodeFound->value;
        return it;
    }
}

template<typename T>
typename stringmap<T>::const_iterator stringmap<T>::cfind(const stringmap<T>::key_type& key) const{
    Node* nodeFound = findNode(key);
    if (nodeFound == nullptr) {
        return cend();
    }
    else {
        auto it = stringmap<T>::const_iterator(*this);
        it.currentPair = nodeFound->value;
        return it;
    }
}

template<typename T>
pair<typename stringmap<T>::iterator, bool> stringmap<T>::insert(const stringmap<T>::value_type& val){
    bool inserted = false;
    string key = val.first;
    T valor = val.second;
    auto it = find(key);
    if (it != end()) {
        pair<stringmap<T>::iterator, bool> res = make_pair(this->end(), inserted);
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
        pair<stringmap<T>::iterator, bool> res;
        auto it = iterator(*this);
        it.currentPair = current->value;
        res = make_pair(it, inserted);
        return res;
    }
}

template<typename T>
typename stringmap<T>::size_type stringmap<T>::erase(const stringmap<T>::key_type& key) {
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
typename stringmap<T>::iterator stringmap<T>::erase(stringmap::iterator pos) {
    auto key = pos.currentPair->first;
    auto it = ++pos;
    erase(key);
    return it;
}

// private functions //

template<typename T>
string stringmap<T>::firstKey() const {
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
string stringmap<T>::nextKey(string currentKey) const {
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
                    key += (*currentNode->children.begin()).first;
                    currentNode = (*currentNode->children.begin()).second;
                }
            }
        }
        return key;
    }
}

template<typename T>
typename stringmap<T>::Node* stringmap<T>::findNode(string key) const {
    int index = 0;
    stringmap<T>::Node* current = root;
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
vector<typename stringmap<T>::Node*> stringmap<T>::getBranch(string key) const {
    vector<stringmap<T>::Node*> branch = vector<stringmap<T>::Node*>();
    int index = 0;
    stringmap<T>::Node* current = root;
    while (index != key.size() && current->children.count(key[index]) != 0) {
        branch.push_back(current);
        current = current->children[key[index]];
        index++;
    }
    return branch;
}







