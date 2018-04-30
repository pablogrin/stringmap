#include <algorithm>
#include "stringmap.h"
#include <iostream>

template<typename T>
stringmap<T>::const_iterator::const_iterator() {
    map = nullptr;
    currentPair = nullptr;
}

template<typename T>
stringmap<T>::const_iterator::const_iterator(const stringmap& map) {
    string key = map.firstKey();
    if(key != ""){
        this->currentPair = map.findNode(map.firstKey())->value;
    }else{
        this->currentPair = nullptr;
    }
    this->map = &map;
}

template<typename T>
stringmap<T>::const_iterator::const_iterator(const const_iterator& other) {
    this->map = other.map;
    this->currentPair = other.currentPair;
}

template<typename T>
typename stringmap<T>::const_iterator::value_type stringmap<T>::const_iterator::operator*() {
    return *currentPair;
}

template<typename T>
typename stringmap<T>::const_iterator::value_type* stringmap<T>::const_iterator::operator->() {
    return currentPair;
}

template<typename T>
typename stringmap<T>::const_iterator& stringmap<T>::const_iterator::operator++() {
    string currentKey = map->nextKey(currentPair->first);
    if (currentKey == ""){
        this->currentPair = nullptr;
    } else {

        this->currentPair = (map->findNode(currentKey))->value;
    }
    return *this;
}

template<typename T>
typename stringmap<T>::const_iterator& stringmap<T>::const_iterator::operator--() {
    string currentKey = "";
    if (*this == map->cend()){
        currentKey = map->lastKey();
    } else {
        currentKey = map->previousKey(currentPair->first);
    }
    if (currentKey == ""){
        this->currentPair = nullptr;
    } else {

        this->currentPair = (map->findNode(currentKey))->value;
    }
    return *this;
}



