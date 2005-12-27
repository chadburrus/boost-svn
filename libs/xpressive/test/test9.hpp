///////////////////////////////////////////////////////////////////////////////
// test9.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./test.hpp"

///////////////////////////////////////////////////////////////////////////////
// get_test_cases
//
template<typename BidiIterT>
boost::iterator_range<test_case<BidiIterT> const *> get_test_cases()
{
    typedef typename boost::iterator_value<BidiIterT>::type char_type;
    typedef test_case<BidiIterT> test_case;
    typedef basic_regex<BidiIterT> regex_type;

    static char_type const *nilbr = 0;
    static test_case const test_cases[] =
    {
        test_case // test151
        (
            L("bbbc")
          , L("^(b?\?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbbc"), L("b"), nilbr)
        )
      , test_case // test152
        (
            L("bbbbc")
          , L("^(b?\?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , no_match
        )
      , test_case // test153
        (
            L("bbbbc")
          , L("^(b?\?)*d$")
          , regex_type(bos >> *(s1= -optional(L('b'))) >> L('d') >> eos)
          , L("")
          , no_match
        )
      , test_case // test154
        (
            L("bc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bc"), L(""), nilbr)
        )
      , test_case // test155
        (
            L("bbc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L("b"), nilbr)
        )
      , test_case // test156
        (
            L("bbbc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbbc"), L("b"), nilbr)
        )
      , test_case // test157
        (
            L("bbbbc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , no_match
        )
      , test_case // test158
        (
            L("bbbbc")
          , L("^(b?\?)*?d$")
          , regex_type(bos >> -*(s1= -optional(L('b'))) >> L('d') >> eos)
          , L("")
          , no_match
        )
      , test_case // test159
        (
            L("bbc")
          , L("^(|||b)*bc$")
          , regex_type(bos >> *(s1= nil | nil | nil | L('b')) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L(""), nilbr)
        )
      , test_case // test160
        (
            L("bbc")
          , L("^(|||b)*?bc$")
          , regex_type(bos >> -*(s1= nil | nil | nil | L('b')) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L("b"), nilbr)
        )
      , test_case // test164
        (
            L("1yzZ^aAc2")
          , L("[Z-a]+")
          , regex_type(icase(+range(L('Z'),L('a'))))
          , L("i")
          , backrefs(L("zZ^aA"), nilbr)
        )
      , test_case // test165
        (
            L("1yzZ^aAc2")
          , L("[Z-a]+")
          , regex_type(+range(L('Z'),L('a')))
          , L("")
          , backrefs(L("Z^a"), nilbr)
        )
    };

    return boost::make_iterator_range(test_cases);
}
