#ifndef STRING_MAP_STRING_MAP_H
#define STRING_MAP_STRING_MAP_H

#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>

using std::string;
using std::vector;
using std::pair;

using namespace std;

/**
 * map<string, T> on a retrieval tree structure.
 * T preconditions:
 * - Has a copy constructor (with copy(T) complexity)
 * - Has an operator== (with cmp(T) complexity)
 * - Operator[] is only allowed if T has a default constructor
 *
 * Map preconditions:
 * - Empty string ("") is not used as a key to store a value.
 */
template < typename T >
class string_map {
public:
    typedef string key_type;
    typedef T mapped_type;
    typedef std::pair<const key_type, mapped_type> value_type;
    typedef size_t size_type;

    class iterator;
    class const_iterator;
    

    /** @brief Constructs an empty map.
     *
     * \complexity{\O(1)}
     */
    string_map();

    /** @brief Destroys map.
     *
     * \complexity{\O(sn * S)}
     */
    ~string_map();

    /** @brief Constructs a map by copying another one.
     *
     * \complexity{\O(sn * S * copy(T))}
     */
    string_map(const string_map<T>& other);

    /** @brief Assignment operator
     *
     * \complexity{\O(sn * S * copy(T))}
     */
    string_map& operator=(const string_map& other);

    /** @brief Comparison operators
     *
     * \complexity{\O(sn * S * cmp(T))}
     */
    bool operator==(const string_map& other) const;
    bool operator!=(const string_map& other) const;

    /** @brief Amount of appearances for a given key (0 or 1)
     *  @param key
     *
     *  \complexity{\O(S)}
     */
    size_type count(const key_type& key) const;

    /** @brief Amount of defined keys */
    size_type size() const;

    /** @brief Whether the map is empty or not */
    bool empty() const;


    /** @brief Access and definition of key/value pairs
     *  @param key (if not defined, inserted)
     *  @returns reference to the value
     *
     *  \complexity{
     *    * \O(S) if key not defined
     *    * \O(S) + copy(T) if it is
     *  }
     */
    T& operator[](const key_type& key);

    /** @brief Access to a key/value pair
     *  @param key (must be previously defined)
     *  @returns reference to the value
     *
     *  \complexity{\O(S)}
     */
    T& at(const key_type& key);

    /** @brief Access to a key/value pair
     *  @param key (must be previously defined)
     *  @returns const reference to the value
     *
     *  \complexity{\O(S)}
     */ 
    const T& cat(const key_type& key) const;

    /** @brief Empties the map
     */
    void clear();

    // Access through iterators

    /** @brief iterator to the first key/value pair in lexical order
     *  @returns iterator to the element or end() if the map is empty
     *
     *  \complexity{\O(S)}
     */
   iterator begin();

    /**  @brief iterator to the end of the collection
     *
     *  \complexity{\O(S)}
     */
   iterator end();

   // const versions
   const_iterator cbegin() const;
   const_iterator cend() const;

    /** @brief finds a key/value pair through its key
     *  @param key
     *  @returns iterator to the key/value pair
     *
     *  \complexity{\O(S)}
     */
   iterator find(const key_type& key);

    /** @brief finds a key/pair value through its key
     *  @param key
     *  @returns iterator to the key/value pair
     *
     *  \complexity{\O(S)}
     */
   const_iterator cfind(const key_type &key) const;

    /** @brief inserts a key/value pair into the map
     *
     * @param key/value pair
     * @returns an iterator/bool pair, with its first element pointing to the key/value pair
     * and its second element indicating whether or not the key was inserted.
     *
     * 
     * \complexity{\O(S + copy(T))}
     */
    pair<iterator, bool> insert(const value_type &value);

    /** @brief erase a key and its value
     *  @param key
     *  @returns Amount of erased elements (0 or 1)
     *
     *  \complexity{\O(S)}
     */
    size_type erase(const key_type& key);

    /** @brief erase a key and its value through an iterator
     *  @param iterator pointing at the key/value pair
     *  @returns iterator pointing at the following pair (or end())
     *
     *  \complexity{\O(S)}
     */
    iterator erase(iterator pos);

private:

    friend class iterator;
    friend class const_iterator;
    struct Node {
        map<char, Node*> children;
        value_type* value;
        Node(value_type* v) : value(v) {};
    };

    Node* root;
    size_t _amountOfKeys;
    string firstKey() const;
    string nextKey(string currentKey) const;
    Node* findNode(string key) const;
    vector<Node*> getBranch(string key) const;

};

#include "string_map.hpp"
#include "string_map_iterator.h"
#include "string_map_const_iterator.h"
#endif //STRING_MAP_STRING_MAP_H
