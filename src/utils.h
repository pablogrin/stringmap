#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <list>

template<class T>
bool pertenece(T x, vector<T> v) {
    for (int i = 0; i < v.size(); ++i) {
        if (x == v[i]) {
            return true;
        }
    }
    return false;
}

template<class T>
bool subset(vector<T> v1, vector<T> v2) {
    for (int i = 0; i < v1.size(); ++i) {
        if (not pertenece(v1[i], v2)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool seteq(vector<T> v1, vector<T> v2) {
    return subset(v1, v2) and subset(v2, v1);
}

template<class T>
std::ostream &operator<<(ostream &os, const list<T> &l) {
  os << "[";
  for (auto e : l) {
    os << e << ", ";
  }
  os << "]";
  return os;
}

template<class A, class B>
std::ostream &operator<<(ostream &os, const pair<A, B> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

#endif //UTILS_H
