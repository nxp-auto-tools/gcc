// { dg-do run { target c++2a } }

// Copyright (C) 2018 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <string>
#include <testsuite_hooks.h>

void
test01()
{
  auto is_vowel = [](const char c)
  {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  };

  std::string str("cute fluffy kittens");
  std::erase_if(str, is_vowel);
  VERIFY( str == "ct flffy kttns" );
}

void
test02()
{
  std::string str = "cute fluffy kittens";
  std::erase(str, 'f');
  VERIFY( str == "cute luy kittens" );
  std::erase(str, 'z');
  VERIFY( str == "cute luy kittens" );
}

int
main()
{
  test01();
  test02();

  return 0;
}
