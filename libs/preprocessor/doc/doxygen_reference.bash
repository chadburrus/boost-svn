#!/bin/bash

# Copyright (C) 2001
# Housemarque Oy
# http://www.housemarque.com
#
# Permission to copy, use, modify, sell and distribute this software is
# granted provided this copyright notice appears in all copies. This
# software is provided "as is" without express or implied warranty, and
# with no claim as to its suitability for any purpose.

rm -f reference/*.html reference/*.htm
doxygen doxygen_reference.dox
rm reference/doxygen.css reference/doxygen.gif

cd reference

for html in *.html
do
  sed -e 's/enum__params__with__a__default_8hpp.html/enum_params_with_a_default.htm/g' -e 's/enum__params__with__defaults_8hpp.html/enum_params_with_defaults.htm/g' $html > $html.tmp
  mv $html.tmp $html
done

mv enum__params__with__a__default_8hpp.html enum_params_with_a_default.htm
mv enum__params__with__defaults_8hpp.html enum_params_with_defaults.htm
