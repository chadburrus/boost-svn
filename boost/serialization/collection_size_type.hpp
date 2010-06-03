#ifndef BOOST_SERIALIZATION_COLLECTION_SIZE_TYPE_HPP
#define BOOST_SERIALIZATION_COLLECTION_SIZE_TYPE_HPP

// (C) Copyright 2005 Matthias Troyer
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cstddef> // size_t
#include <boost/serialization/strong_typedef.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost { 
namespace serialization {

BOOST_STRONG_TYPEDEF(std::size_t, collection_size_type)

} } // end namespace boost::serialization

BOOST_SERIALIZATION_SPLIT_FREE(collection_size_type)

BOOST_CLASS_IMPLEMENTATION(collection_size_type, primitive_type)

#endif //BOOST_SERIALIZATION_COLLECTION_SIZE_TYPE_HPP