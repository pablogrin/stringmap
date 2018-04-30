#ifndef stringmap_iterator_h
#define stringmap_iterator_h

#include "stringmap.h"
#include <iostream>


template<class T>
class stringmap<T>::iterator{

public:

    /**
    * @brief Default constructor
    *
    * \complexity{\O(1)}
    */
    iterator();

    /**
    * @brief Constructor from a stringmap
    *
    * \complexity{\O(1)}
    */
    iterator(stringmap& map);

    /**
    * @brief Copy constructor
    *
    *
    * \complexity{\O(1)}
    */
    iterator(const iterator&);

    using value_type = const stringmap::value_type;
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
    iterator& operator++();

    /**
    * @brief Backward operator.
    *
    * \complexity{\O(L)}
    */
    iterator& operator--();

    /**
    * @brief Equality operator
    *
    * \complexity{\O(1)}
    */
    bool operator==(const iterator& other) const{
        return (other.map == this->map) &&
               (other.currentPair == this->currentPair);
    };

    /**
    * @brief Difference operator.
    *
    * \complexity{\O(1)}
    */
    bool operator!=(const iterator& other) const{
        return !(other == *this);
    }


private:
    friend class stringmap;
    stringmap* map;
    pointer currentPair;
};

#include "stringmap_iterator.hpp"
#endif // stringmap_iterator_h