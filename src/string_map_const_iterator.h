#ifndef string_map_const_iterators_h
#define string_map_const_iterators_h

#include "string_map.h"
#include <iostream>

template<class T>
class string_map<T>::const_iterator{

public:

    /**
    * @brief Default constructor
    *
    * \complexity{\O(1)}
    */
    const_iterator();

    /**
    * @brief Constructor from a string_map
    *
    * \complexity{\O(1)}
    */
    const_iterator(const string_map& map);

    /**
    * @brief Copy constructor
    *
    *
    * \complexity{\O(1)}
    */
    const_iterator(const const_iterator&);

    using value_type = const string_map::value_type;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;

    /**
    * @brief Dereference operator
    *
    * \complexity{\O(L)}
    */
    value_type operator*();

    /**
    * @brief Reference operator
    *
    * \complexity{\O(L)}
    */
    value_type* operator->();

    /**
    * @brief Foward operator.
    *
    * \complexity{\O(L)}
    */
    const_iterator& operator++();

    /**
    * @brief Equality operator
    *
    * \complexity{\O(1)}
    */
    bool operator==(const const_iterator& other) const{
        return (other.map == this->map) &&
               (other.currentPair == this->currentPair);
    };

    /**
    * @brief Difference operator.
    *
    * \complexity{\O(1)}
    */
    bool operator!=(const const_iterator& other) const{
        return !(other == *this);
    }


private:
    friend class string_map;
    const string_map* map;
    pointer currentPair;
};


#include "string_map_const_iterator.hpp"
#endif // string_map_const_iterator_h