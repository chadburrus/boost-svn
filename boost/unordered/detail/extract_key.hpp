
// Copyright (C) 2005-2011 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_EXTRACT_KEY_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_EXTRACT_KEY_HPP_INCLUDED

#include <boost/unordered/detail/table.hpp>

namespace boost {
namespace unordered {
namespace detail {

    // key extractors
    //
    // no throw
    //
    // 'extract_key' is called with the emplace parameters to return a
    // key if available or 'no_key' is one isn't and will need to be
    // constructed. This could be done by overloading the emplace implementation
    // for the different cases, but that's a bit tricky on compilers without
    // variadic templates.

    struct no_key {
        no_key() {}
        template <class T> no_key(T const&) {}
    };

    template <typename Key, typename T>
    struct is_key {
        template <typename T2>
        static choice1::type test(T2 const&);
        static choice2::type test(Key const&);
        
        enum { value = sizeof(test(make<T>())) == sizeof(choice2::type) };
        
        typedef BOOST_DEDUCED_TYPENAME
            boost::detail::if_true<value>::
            BOOST_NESTED_TEMPLATE then<Key const&, no_key>::type type;
    };

    template <class ValueType>
    struct set_extractor
    {
        typedef ValueType value_type;
        typedef ValueType key_type;

        static key_type const& extract(key_type const& v)
        {
            return v;
        }

#if BOOST_UNORDERED_USE_RV_REF
        static key_type const& extract(BOOST_RV_REF(key_type) v)
        {
            return v;
        }
#endif

        static no_key extract()
        {
            return no_key();
        }
        
#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)
        template <class... Args>
        static no_key extract(Args const&...)
        {
            return no_key();
        }

#else
        template <class Arg>
        static no_key extract(Arg const&)
        {
            return no_key();
        }

        template <class Arg1, class Arg2>
        static no_key extract(Arg1 const&, Arg2 const&)
        {
            return no_key();
        }
#endif

        static bool compare_mapped(value_type const&, value_type const&)
        {
            return true;
        }
    };

    template <class Key, class ValueType>
    struct map_extractor
    {
        typedef ValueType value_type;
        typedef BOOST_DEDUCED_TYPENAME ::boost::remove_const<Key>::type key_type;

        static key_type const& extract(value_type const& v)
        {
            return v.first;
        }
            
        static key_type const& extract(key_type const& v)
        {
            return v;
        }

        // TODO: Why does this cause errors?
        //
        //static key_type const& extract(BOOST_RV_REF(key_type) v)
        //{
        //    return v;
        //}

        template <class Second>
        static key_type const& extract(std::pair<key_type, Second> const& v)
        {
            return v.first;
        }

        template <class Second>
        static key_type const& extract(
            std::pair<key_type const, Second> const& v)
        {
            return v.first;
        }

#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)
        template <class Arg1, class... Args>
        static key_type const& extract(key_type const& k,
            Arg1 const&, Args const&...)
        {
            return k;
        }

        template <class... Args>
        static no_key extract(Args const&...)
        {
            return no_key();
        }
#else

        template <class Arg1>
        static key_type const& extract(key_type const& k, Arg1 const&)
        {
            return k;
        }

        static no_key extract()
        {
            return no_key();
        }

        template <class Arg>
        static no_key extract(Arg const&)
        {
            return no_key();
        }

        template <class Arg, class Arg1>
        static no_key extract(Arg const&, Arg1 const&)
        {
            return no_key();
        }
#endif

#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)

#define BOOST_UNORDERED_KEY_FROM_TUPLE(namespace_)                          \
        template <typename T2>                                              \
        static no_key extract(boost::unordered::piecewise_construct_t,      \
                namespace_::tuple<> const&, T2&&)                           \
        {                                                                   \
            return no_key();                                                \
        }                                                                   \
                                                                            \
        template <typename T, typename T2>                                  \
        static BOOST_DEDUCED_TYPENAME is_key<key_type, T>::type             \
            extract(boost::unordered::piecewise_construct_t,                \
                namespace_::tuple<T> const& k, T2&&)                        \
        {                                                                   \
            return BOOST_DEDUCED_TYPENAME is_key<key_type, T>::type(        \
                namespace_::get<0>(k));                                     \
        }

#else

#define BOOST_UNORDERED_KEY_FROM_TUPLE(namespace_)                          \
        static no_key extract(boost::unordered::piecewise_construct_t,      \
                namespace_::tuple<> const&)                                 \
        {                                                                   \
            return no_key();                                                \
        }                                                                   \
                                                                            \
        template <typename T>                                               \
        static BOOST_DEDUCED_TYPENAME is_key<key_type, T>::type             \
            extract(boost::unordered::piecewise_construct_t,                \
                namespace_::tuple<T> const& k)                              \
        {                                                                   \
            return BOOST_DEDUCED_TYPENAME is_key<key_type, T>::type(        \
                namespace_::get<0>(k));                                     \
        }

#endif

BOOST_UNORDERED_KEY_FROM_TUPLE(boost)

#if !defined(BOOST_NO_0X_HDR_TUPLE)
BOOST_UNORDERED_KEY_FROM_TUPLE(std)
#elif defined(BOOST_HAS_TR1_TUPLE)
BOOST_UNORDERED_KEY_FROM_TUPLE(std::tr1)
#endif


        static bool compare_mapped(value_type const& x, value_type const& y)
        {
            return x.second == y.second;
        }
    };
}}}

#endif
