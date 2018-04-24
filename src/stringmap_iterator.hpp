#include <algorithm>
#include "stringmap.h"
#include <iostream>

template<typename T>
stringmap<T>::iterator::iterator() {
    map = nullptr;
    currentPair = nullptr;
}

template<typename T>
stringmap<T>::iterator::iterator(const stringmap& map) {
    string key = map.firstKey();
    if(key != ""){
        this->currentPair = map.findNode(map.firstKey())->value;
    }else{
        this->currentPair = nullptr;
    }
    this->map = &map;
}

template<typename T>
stringmap<T>::iterator::iterator(const iterator& other) {
    this->map = other.map;
    this->currentPair = other.currentPair;
}

template<typename T>
typename stringmap<T>::iterator::value_type stringmap<T>::iterator::operator*() {
    return *currentPair;
}

template<typename T>
typename stringmap<T>::iterator::value_type* stringmap<T>::iterator::operator->() {
    return currentPair;
}

template<typename T>
typename stringmap<T>::iterator& stringmap<T>::iterator::operator++() {
    string currentKey = map->nextKey(currentPair->first);
    if (currentKey == ""){
        this->currentPair = nullptr;
    } else {

        this->currentPair = (map->findNode(currentKey))->value;
    }
    return *this;
}

