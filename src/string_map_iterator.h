#ifndef string_map_iterator_h
#define string_map_iterator_h

#include "string_map.h"
#include <iostream>

using namespace std;

class iterator{

public:

    /**
    * @brief Default constructor
    *
    * \complexity{\O(1)}
    */
    iterator();

    /**
    * @brief Constructor from a string_map
    *
    * \complexity{\O(1)}
    */
    iterator(const string_map& map);

    /**
    * @brief Copy constructor
    *
    *
    * \complexity{\O(1)}
    */
    iterator(const iterator&);

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
    iterator& operator++();

    /**
    * @brief Equality operator
    *
    * \complexity{\O(1)}
    */
    bool operator==(const iterator& other) const;

    /**
    * @brief Difference operator.
    *
    * \complexity{\O(1)}
    */
    bool operator!=(const iterator& other) const;


private:
    friend class string_map;
    const string_map* map;
    pointer currentPair;
};

#include "string_map_iterator.h"
#endif // string_map_iterator_h