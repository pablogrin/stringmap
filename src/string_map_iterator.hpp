#include <algorithm>
#include "string_map.h"
#include <iostream>

template<typename T>
string_map<T>::iterator::iterator() {
    map = nullptr;
    currentPair = nullptr;
}

template<typename T>
string_map<T>::iterator::iterator(const string_map& map) {
    string key = map.firstKey();
    if(key != ""){
        this->currentPair = map.findNode(map.primeraClave())->value;
    }else{
        this->currentPair = nullptr;
    }
    this->map = &map;
}

template<typename T>
string_map<T>::iterator::iterator(const iterator& other) {
    this->map = other.mapa;
    this->currentPair = other.currentPair;
}

template<typename T>
typename string_map<T>::iterator::value_type string_map<T>::iterator::operator*() {
    return *currentPair;
}

template<typename T>
typename string_map<T>::iterator::value_type* string_map<T>::iterator::operator->() {
    return currentPair;
}

template<typename T>
typename string_map<T>::iterator& string_map<T>::iterator::operator++() {
    string currentKey = map->nextKey(currentPair->first);
    if (currentKey == ""){
        this->currentPair = nullptr;
    } else {

        this->currentPair = (map->findNode(currentKey))->value;
    }
    return *this;
}

template<typename T>
bool string_map<T>::iterator::operator==(const string_map<T>::iterator& other) const{
    return (other.map == this->map) &&
            (other.currentPair->first == this->currentPair->first) &&
            (other.currentPair->second == this->currentPair->second);
}


