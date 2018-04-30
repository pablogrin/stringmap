#ifndef stringmap_const_iterators_h
#define stringmap_const_iterators_h

#include "stringmap.h"
#include <iostream>

template<class T>
class stringmap<T>::const_iterator{

public:

    /**
    * @brief Default constructor
    *
    * \complexity{\O(1)}
    */
    const_iterator();

    /**
    * @brief Constructor from a stringmap
    *
    * \complexity{\O(1)}
    */
    const_iterator(const stringmap& map);

    /**
    * @brief Copy constructor
    *
    *
    * \complexity{\O(1)}
    */
    const_iterator(const const_iterator&);

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
    const_iterator& operator++();

    /**
    * @brief Backward operator.
    *
    * \complexity{\O(L)}
    */
    const_iterator& operator--();

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
    friend class stringmap;
    const stringmap* map;
    pointer currentPair;
};


#include "stringmap_const_iterator.hpp"
#endif // stringmap_const_iterator_h