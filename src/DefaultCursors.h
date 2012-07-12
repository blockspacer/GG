// -*- C++ -*-
/* GG is a GUI for SDL and OpenGL.
   Copyright (C) 2003-2008 T. Zachary Laine

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1
   of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
    
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA

   If you do not wish to comply with the terms of the LGPL please
   contact the author as other terms are available for a fee.
    
   Zach Laine
   whatwasthataddress@gmail.com

Copyright for cursors:
   Copyright © 2009-2011 Davorin Učakar <davorin.ucakar@gmail.com>

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice (including the next
   paragraph) shall be included in all copies or substantial portions of the
   Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "DecodeBase64.h"


namespace {

    const std::size_t CURSORS_SIZE = 6496;

    const char CURSORS[CURSORS_SIZE + 1] = {
         'i', 'V', 'B', 'O', 'R', 'w', '0', 'K', 'G', 'g', 'o', 'A', 'A', 'A', 'A', 'N', 'S', 'U', 'h', 'E', 'U', 'g', 'A', 'A', 'A', 'I', 'A', 'A', 'A', 'A', 'C', 'A', 'C', 'A', 'Y', 'A', 'A', 'A', 'D', 'D', 'P', 'm', 'H', 'L', 'A', 'A', 'A', 'A', 'A', 'X', 'N', 'S', 'R', '0', 'I', 'A', 'r', 's', '4', 'c',
         '6', 'Q', 'A', 'A', 'A', 'A', 'Z', 'i', 'S', '0', 'd', 'E', 'A', 'P', '8', 'A', '/', 'w', 'D', '/', 'o', 'L', '2', 'n', 'k', 'w', 'A', 'A', 'A', 'A', 'l', 'w', 'S', 'F', 'l', 'z', 'A', 'A', 'A', 'L', 'E', 'w', 'A', 'A', 'C', 'x', 'M', 'B', 'A', 'J', 'q', 'c', 'G', 'A', 'A', 'A', 'A', 'A', 'd', '0',
         'S', 'U', '1', 'F', 'B', '9', 'w', 'H', 'B', 'w', 'M', 'J', 'K', '/', 'n', 'n', 'b', 'g', '0', 'A', 'A', 'B', 'K', 'G', 'S', 'U', 'R', 'B', 'V', 'H', 'j', 'a', '7', 'V', '3', 'r', 'j', 'x', 'z', 'F', 'E', 'f', '/', '1', '3', 'N', 'z', 'b', 'z', '7', 's', 'D', '8', '4', 'w', 'l', 'w', 'L', 'F', 'l',
         'g', 'Q', 'R', 'y', 'H', 'k', 'h', 'A', 'I', 'B', '9', 'i', 'J', 'Y', 'p', 'k', '5', 'B', 'g', 'U', 'g', 'a', 'N', 'I', '/', 'G', 'V', '8', 'Q', 'v', 'k', 'H', 'k', 'E', 'J', 'E', 'R', 'I', 'R', 'E', 'p', 'H', 'z', 'L', 'h', 'x', 'B', 'i', '4', '4', 'g', 'I', 'D', 'M', 'a', 'H', '7', '8', '5', '3',
         'P', 't', '/', 'e', 'c', '7', 'f', 'z', 'o', 'a', 't', 'v', 'a', '/', 'u', '6', 'Z', '3', 'p', '6', 'e', 'm', 'b', '2', '9', 'q', 'a', 'k', '0', 'e', '3', 'N', 'z', 'k', '5', 'V', 'd', 'z', '2', '6', 'u', 'r', 'q', '6', 'G', 'm', 'i', 'h', 'h', 'R', 'a', 'O', 'L', 'o', 'y', 'x', 'z', 'w', 'J', 'A',
         'Q', 'v', 'd', 'E', 'A', '7', 'Q', '0', 'j', 'f', '9', 'I', 'Q', 'm', 'J', '8', '7', 'g', 'K', 'Y', 'A', 'T', 'A', 'N', 'Y', 'N', 'z', '4', 'v', 'g', '5', 'a', 'm', 's', 'R', '/', 'p', 'A', 'V', 'A', 'M', 'G', 'u', 'w', 'B', 'm', 'A', 'O', 'w', 'G', 'y', 'N', 'T', 'G', 'g', 'a', '/', '2', 'E', 'E',
         '3', 'W', 'd', 'p', 'G', 'a', 't', 'p', 'W', 'g', 'B', 'I', 'K', 'Q', 'H', 'g', 'a', 'w', 'C', 'P', 'A', 'D', 'h', 'W', 'I', 'x', 'O', 'a', 'x', 'u', '8', 'F', 'R', 'N', '8', 'w', 'K', 'O', '4', '4', 'g', 'D', '3', 'q', 'o', '2', 'C', 'L', 'm', 'R', 'j', 'j', 'L', '2', '/', 'k', 'T', 'Q', 'A', 'L',
         'N', 'T', 'G', 'h', 'a', 'f', 'z', '+', 'h', 'A', 'o', 'R', 'V', 'Q', 'N', 'L', 'M', 'H', '+', 'b', '+', 'u', 'l', '+', 'G', 'W', 'V', 'J', 'c', 'i', 'T', '9', 'R', 'l', 'N', 'M', 'a', 'B', 'q', '/', 'h', '8', 'C', 'm', 'h', 'g', 'a', 'm', 'N', 'Q', 'i', 'B', 'Z', 'v', '6', 'W', 't', 'k', 'T', '0',
         '9', '6', 'v', 'Q', 'f', 'k', 'q', 'G', 'm', 'Q', 'n', 'D', 'J', 'g', 'T', 'M', '/', 'I', '8', 'B', '2', 'G', 'E', 'a', 'O', 'E', 'd', 'C', 'M', 'F', 'Y', 'n', '8', '2', 'N', 'Y', 'z', 'G', 'T', 'Y', 'm', 'T', 'C', 'E', 'l', 'k', 'B', 'Y', 'G', 'L', '1', 'A', 's', '5', 'e', 'q', 'h', 'g', 'I', 'n',
         '8', '8', 'v', '2', 'U', '3', 'I', 'Y', 'm', 'D', 'C', 'E', 'Q', 'm', 'D', 'i', 'P', 'g', 'Z', 'g', 'k', 'u', '6', 'L', 'u', 'p', 'l', 'f', 'p', 'p', '+', 'S', 'w', '8', 'K', 'E', 'I', 'R', 'I', 'C', 'Y', 'W', 'H', 'y', 'W', 'B', '3', 'M', 'F', '0', 'L', 's', 'X', '6', 'Z', 'j', 'q', 'q', '+', 'i',
         '/', 'Z', 'Q', 'c', 'J', 'i', 'Y', '0', 'i', 'F', '8', 'A', 'S', 'I', 'Q', 'Q', 'L', 'i', 'Z', '3', 'A', 'U', 'h', 'j', 'R', 'l', 'N', 'W', 'I', 'F', 'y', 'a', 'f', '9', '3', 'x', '/', 'H', 's', 'h', '/', 'S', 'Q', 'Y', 's', 'i', 'k', 'A', 'G', 'z', '7', 'z', 'X', 'J', 'L', 'A', 'C', 'w', 'C', 'W',
         'A', 'D', 'w', 'E', 's', 'A', 'u', 'g', 'V', '7', 'K', 'x', 'T', 'e', 'L', 'P', 'G', '+', '9', 'N', 'D', 'U', '8', 'B', 'n', 'A', 'B', 'w', 'G', '8', 'A', 'b', 'R', 'M', 'M', 'i', 'g', 'A', 'c', '0', 'M', 'w', 'A', 'J', 'R', 'I', '+', 'E', 'g', 'w', 't', 'I', 'M', 'P', 'O', '5', '5', 'h', 'e', '4',
         'n', '9', 'l', 'P', 'Q', 'Q', 'L', 'A', 'X', 'n', '4', 'e', 'w', 'D', '0', 'A', 'G', '/', 'R', 'y', 'W', 'Y', 'c', 'A', 'V', 'I', 'A', '/', 'a', '6', 'q', '3', 'Y', '/', 'n', 'u', 'a', 'f', 'o', '7', 'R', 'Y', 'z', 'a', 'B', 'X', 'D', 'L', '8', 't', 'w', 'T', 'R', 'N', 's', 'm', 'C', 'Y', 'b', '0',
         'x', 'M', 'v', 'n', '+', 'T', 'H', 'i', 'F', 'u', 'c', 'N', 'I', 'Z', 'C', 'F', 'B', 'c', 'A', 'c', 'd', 'x', 'i', 'c', 'B', 'b', 'B', 'C', 'j', 'e', 'x', 'W', 'J', 'Q', 'A', 'e', '+', 'L', 'c', 'M', '6', 'Z', 'Y', 'h', 'A', 'q', 'H', 'x', 'C', 'y', 'H', 'G', 'A', 'O', 'z', 'Z', '6', 'C', 'F', 'a',
         'z', 'h', 'F', 'z', 'u', 'w', 'A', 'W', 'M', '5', '4', 'r', '2', 'j', '9', 'O', 'v', 'C', 'W', 'F', '4', 'B', 'l', 'S', 'l', 'g', 'E', '6', '0', 'r', 'w', 'f', 'G', 'o', 'T', '8', 'k', 'R', 'r', 'd', 'o', 'R', 'e', 't', 'R', 'x', 'r', 'v', 'y', 'u', 'I', 'f', 'Y', '2', '3', 'R', 'd', 'A', 'S', 'Z',
         'X', 'y', 'P', 'S', 'd', '1', 'o', 'I', 'c', 'd', '/', 'y', '2', 'B', 'u', 'k', 'p', 'V', '2', 'y', 'E', 'G', 'e', 'E', 'E', 'I', 'u', 'O', '5', '4', 'o', 'G', 'i', 'f', 'b', 'x', 'R', 'r', 'Q', 'A', 'l', '2', 'm', 'W', 'c', 'o', 'A', 'O', 'p', 'w', 'W', 'g', 'H', '1', '4', 'H', '8', 'I', 'F', 'x',
         '7', '1', 'c', 'A', 'l', 'q', 'n', 'z', 't', '4', 'g', 'R', 'H', 'Q', 'D', 'b', 'J', 'c', 'b', 'h', 'U', 'P', 'z', 'b', 'R', 'M', 'M', 'O', 'g', 'F', 'W', 'L', '+', 'e', '0', 'w', '8', '1', 'u', 'U', 't', 'j', 'F', 'i', '3', 'h', 'x', 'z', 'p', 's', 'a', 'I', '6', 'R', 't', 'Q', 'i', '1', 'a', '3',
         'A', 'J', 'y', 'h', '+', '7', 'M', 'A', 'T', 't', 'J', 'f', '/', 'd', 'x', 'D', 'M', 'r', '1', 'F', 'L', 'c', 'A', '0', 'V', 'H', 'j', '3', 'q', 'w', 'g', '+', 'w', 'D', 'X', 'y', 'T', '+', '5', '4', 'W', 'w', 'D', '6', '4', 'V', 'v', 'U', 'A', 'B', 'N', '6', '1', 'A', 'H', '3', 'W', 'e', 'd', '2',
         'E', 'X', 'H', '8', 'L', 'Y', 'B', '/', 'm', '4', 'T', '4', 'g', 'a', 'k', 't', 'Q', 'o', 'g', '7', 'Z', 'K', 'Z', 'X', '6', 'D', '1', 'F', 'h', 'a', 'B', 'H', '7', '1', '+', 'l', 'c', 'X', 'O', 'C', 'B', 'F', 'X', 'S', 'u', '2', '7', 'T', '1', 'G', 'y', 'R', '8', 'G', 'z', 'R', 'p', 'b', 'W', 's',
         'R', '4', 'K', '5', 'U', 'V', 'A', '5', '9', 'O', '/', 'W', 'A', 'J', 'w', 'X', 'Q', 't', 'w', '0', '2', 'v', 'Y', 'e', 'g', 'P', 'c', 'd', 's', '4', 'D', '3', 'L', 'X', '2', '4', 'T', 'I', 'x', 'f', 'o', '/', 'd', 'm', 'O', '4', 'H', '0', '/', '2', '+', 'p', '0', '1', 'b', 'p', 'B', '/', '8', 'y',
         't', 'P', 'A', 'F', 'k', 'q', 'i', 'H', 'g', 'd', 'r', 'l', 't', 'A', 'A', 'F', '8', 'H', '9', 'P', 'A', 'p', 'j', 'n', 'N', '5', 'x', 'j', 'j', 'u', 'J', 'e', 'x', 'F', 'n', 'A', 'm', 'p', '6', 'b', 'A', '/', 'i', 'J', 'z', 'y', 'z', 'A', 'a', 'I', 'P', 'P', 'L', 'O', 'A', 'Y', 'W', 'Z', '8', 'b',
         'D', 'F', 'e', 'u', 'B', 'W', 'D', 'M', 'X', 'w', 'J', 'w', '1', 'z', 'U', 'L', 'k', 'F', 'I', 'O', 'W', 'A', 'D', '9', 'x', 'k', 'v', 'U', '4', 'D', 'W', '6', 'b', 'N', 'R', 'O', 'k', 'U', 'Y', 'g', 'o', 'u', 'Y', 'X', 'x', 'T', '9', 'u', 'e', 'u', 'i', '6', 'I', 'w', 'y', 'B', 'm', 'C', 'P', 'm',
         'b', 'w', 'V', 'Y', 'K', 's', 'k', 's', 'n', 'D', 'C', 'U', 'h', 's', 'M', 's', '+', 'o', 't', 'D', '2', 'w', 'y', 'H', 'D', 'O', 'y', 'f', 'H', 'j', 'F', 'L', 'W', '8', 'A', 'L', 'Q', 'o', 'g', 'b', 'O', 'W', 'F', 'g', '3', 'g', 'e', '/', 'I', '8', 'u', 'X', 'y', 'X', 'w', '+', 'B', 'E', 'h', 'q',
         '5', 'A', 'K', 'A', '4', '/', 'T', 'g', 'Q', 'x', 'p', 'D', 'x', 'w', 'D', '8', 'S', 'A', 'j', 'x', 'D', 'T', '3', '7', 'G', '/', 'o', '+', '5', 'p', 'Q', 'r', 'B', 'D', '8', '8', 'H', 'a', 's', 'Z', 'Z', 'r', '5', 'F', 'I', 'N', '1', 'S', 'a', 'z', 'A', 'F', 'g', '2', 'z', 'j', 't', 'j', 'A', '0',
         'v', 'y', 'w', 'U', 'E', 'g', 'K', 'D', '+', 'c', 't', 'k', 'k', 'Z', 'z', 'M', '1', '8', 'p', 'i', 'C', 'k', 'C', 'H', 'P', 'b', 'x', 'D', 'E', 'p', '2', 'Q', 'a', 'X', 's', 'W', 'w', 'C', 'l', '6', 'd', 'p', 'X', 'M', 'b', 'y', 'x', 'B', 'C', 'M', 'X', 'f', 'B', 'f', 'A', 'E', 'j', 'f', 'c', '2',
         '7', 'a', '8', 'k', 'I', 'G', 'l', 'p', 'c', '9', 'f', 'V', 'F', 'z', 'Z', '6', 'X', 'O', 'a', '7', 'j', 'B', 'A', 'w', 's', '7', '+', 'S', 'x', '3', 'y', 'b', 'D', '8', 'B', 'j', '3', 'A', 'm', 'T', 'Y', 's', 'k', 'C', 'E', '1', 'N', '0', 'g', 'T', 'k', '8', 'M', 'Y', 'M', 'v', 'I', 'f', 'g', 'l',
         'a', 'f', 'i', 'j', 'A', 'L', '6', '0', 'd', 'O', 'x', 'V', '8', 'l', 'V', 'u', 'U', '8', 'f', 's', 'R', 'K', 'B', 'X', 'k', 'E', 'U', '5', 'T', 'X', '7', 'I', 'G', 'z', 'Q', 'j', 'u', 'U', 'O', 'O', '6', 'Q', 'C', 'O', 'P', 'I', 'H', '0', '8', 'A', 'e', 'c', 'P', 'o', 'G', 'F', '+', 'U', 's', '+',
         'Z', 't', '8', 'l', 'A', 'D', '7', 'O', 'U', 'G', 'L', 'M', 's', 'e', 'v', 'K', 'j', '7', 'L', 'h', '1', 'w', '0', 'b', 'p', '7', 'D', 's', 'D', '4', 'a', 'T', '9', 'T', 'Y', '5', 'f', '3', 'c', 'A', '/', 'B', 'D', 'o', 'B', 'L', 'o', 'g', 'J', 'c', 'E', '7', 'R', 'V', 'O', '2', 'T', 'b', 'J', 'K',
         'n', 'S', 'w', 'c', 'B', 'Z', 'z', 'A', 'o', 'o', '7', 'h', 'N', 'T', 'L', '7', 'd', '/', 'P', 'C', '4', 'y', 'Y', 'N', 'I', 'o', 'A', 'R', 'q', 'J', 'H', 'x', 'P', 'v', 'g', 'T', 'N', 'm', '/', '+', 'H', '9', '3', '7', 'P', 'W', 'n', '8', 'H', 'T', 'K', 'H', '6', '5', 'F', 'm', 'K', '2', 'a', 'Y',
         'e', 'N', 'J', 'w', '/', 'j', 'L', 'D', 'v', 'S', 'U', 'F', 'w', 'B', 'S', 'C', 'e', 'a', 'g', 'k', 'k', 'M', 's', 'k', 'e', 'P', 'd', 'I', 'C', 'H', 'L', 'X', 'R', 'r', 'g', 'P', 'M', 'A', 'r', '5', '9', '9', 'o', 'k', 'b', 'x', 'k', 'd', '/', 'A', 'q', 'Z', '/', 'm', 'V', 'L', 'm', 'D', 'g', 'W',
         'X', 'u', '5', 'Y', '5', 'v', 'p', 'D', 'E', 'Q', 'S', 'A', 'C', '4', 'E', 'O', 'P', 'E', '2', 'S', '8', 'K', '2', 'h', 'v', 'y', 'a', 'S', '2', '1', 'Z', 'z', 'F', 'j', 'C', 'K', '0', 'M', 't', 'y', 'z', 'i', 'I', '6', 'r', 'k', 'U', 'D', 'X', 'D', 'F', 'n', 'B', 'z', 'v', 'M', 'A', 'u', '0', 'U',
         's', 'X', 'I', '6', 'z', 'D', '4', 'q', 'A', 'i', 'A', 'B', 'P', 'C', 'a', 'E', 'u', 'E', 'v', '/', '/', '5', 'o', '6', 'p', 'I', 't', 'q', 'l', 'o', 'm', 'H', 'Q', 'b', 'h', '3', 'W', 'X', 'x', 'C', 'h', 'g', 'i', '6', 'E', 'G', 'I', 'k', 'B', 'E', 'A', '3', 'f', 'h', 'N', 'q', 'x', 'e', 's', 'U',
         '3', 'Y', '8', '9', 'V', 'R', '3', 'G', 'd', 'n', 'f', 'L', 'v', 'm', 'R', 'U', '9', 'u', 'D', 'V', 'N', 'V', 'U', 'd', 'O', 'R', 'A', 'j', '1', 'p', 'Y', 'm', 'p', '6', 'o', 't', 'D', 'J', 'E', 'g', 't', 'L', 'u', 'L', 'W', '2', 'i', 'h', 'h', 'R', 'a', 'O', 'l', 'A', '/', 'Q', 'D', 'n', 'M', 'B',
         'y', '8', '+', 'H', 'L', 'R', 'T', 's', 'Q', '7', 'M', 'c', 'c', 'c', 'Y', 'n', 'U', 'M', 'E', 'f', 'M', 'w', '9', 'T', 'T', '4', 'f', '3', 'i', 'k', 'x', '9', '0', 'w', 'K', 'I', 'm', '/', 'a', 'w', 'O', 'Q', '0', 'i', 'J', 'y', 'b', 'Q', 'Q', '3', 'g', 'y', 'x', 'j', 'B', 'D', 'g', 'u', 'w', 'F',
         'r', 'c', 'e', 'g', 'I', 'o', 'R', 'b', 'v', 'j', 'G', 'C', 'x', 'L', 'P', 'j', 'd', 'e', '7', '7', 'N', 'l', 'S', 'g', 'Z', 'Y', 'b', 'u', 'i', 'R', 'q', 'Z', 'z', '2', 'm', 'Y', 'Z', '/', 'N', '8', '/', 'n', 'k', 'O', 'a', 'm', 'V', 'w', 'B', 'o', '4', 's', '2', 'B', 'G', 'Y', '5', 'k', 'J', 'K',
         'e', 'e', 'A', 'i', 'e', 'A', 'T', '9', 'p', 'F', 'T', 'h', 'e', 'M', 'Y', 'f', '6', 'E', 'e', 'p', '+', 'q', 'i', 'A', 't', 'O', 'o', 'Z', 'q', 'I', 'W', 'I', 'y', 'i', 'O', 'J', 'L', 'h', 'p', 'c', 'n', '9', 'n', '1', 'B', 'N', 'E', '4', 'g', 'd', 'F', 'Z', '9', 'J', 'r', 'i', 'b', 'b', 'S', '0',
         '+', 'W', 'U', 'A', 'T', '9', 'F', 'z', 'g', 'v', 'V', 'f', 'm', 'A', 'U', 'Q', 'a', 'v', 'X', 'C', 't', 'u', 'd', '9', 'H', 't', 'V', 'u', 'h', '/', 'a', 'h', 'w', 'S', 'k', 'w', '1', 'O', 'j', 'v', 'i', 'M', '6', 'q', '9', '+', '3', 'X', 'C', 'T', '2', 'o', 'N', 'P', 'S', 'X', 'j', 'P', 'v', 'v',
         'Q', 'K', '1', '/', '6', 'M', 'i', 'n', '9', '/', 'q', 'H', 'j', 'w', 'b', 'b', 'h', 'G', 'S', 'W', 'T', 'O', 'x', 'Y', 'z', 'n', 'g', 'c', 'c', '+', 'w', 'L', 'g', 'Q', 'W', 'o', '9', 'Y', 'C', 'Q', 'h', 'N', 'C', 'y', 'T', 'n', 'N', 's', '/', '4', 'O', 'n', 'z', 'S', '0', 'b', '3', '3', 'W', 'g',
         '8', 'h', '+', 'W', 'o', 'Z', 'a', 'E', 'o', 'z', 'm', 'B', 'w', 't', 'H', '5', 'k', '2', 'R', 'm', 'J', 'p', 'm', '0', 'S', 'Y', 's', 'z', 'F', 'q', 'v', 'T', 'Q', 'w', 'V', 'A', '+', 'w', 'J', 'l', 'E', 'k', 'J', '9', 'H', 'V', 'B', 'U', '1', 'H', '7', 'T', 'A', 'm', 'x', 'D', 'J', 'b', 'h', 'w',
         '2', 'K', 'J', '7', 'e', 'r', 'N', 'M', 'N', '4', 'Z', 'm', '6', 'U', 'a', 'P', 'W', '7', '7', '7', 'C', 'M', 'B', '/', 'y', 'O', 'n', 'a', 'p', 'I', 's', '7', 'Y', '6', 'c', 'j', 'O', 'Y', 'p', 'Z', 'N', 'P', 'g', 'K', 'e', 'B', 'K', 'B', 'B', 'h', '8', 'H', 't', 'I', 'r', '2', 'u', '6', 'z', 'A',
         'r', 'n', 'F', 'f', '3', '9', 's', 't', 'K', 'n', 'R', 'J', 'T', 'q', 'N', '3', 'o', 'B', 'I', 'd', 'X', 'e', 'P', 's', 'f', '/', 'm', 'Y', 'y', 'z', '7', 'f', 'J', 'f', 'N', 'b', 'Z', 'v', 'z', 'N', 'p', 'K', 'F', 'G', 'x', 'y', 's', 'F', '7', 'd', 'S', '1', 't', 'P', 'M', '7', 'n', '/', 'Z', 'X',
         'k', 'K', 'k', 's', 'H', 'Q', 'G', 'g', 'w', 'o', 'g', 'S', 'h', '9', 'c', '9', 'Z', 'j', 'Q', '6', 'B', 'I', 'I', 'd', 'x', 'Y', 'g', '0', 'x', 'G', 'D', '+', 'V', 'N', 'n', '2', 'i', '0', 'i', 'p', 'Q', 'F', 'V', 'A', 'W', 't', 'b', 'r', 'z', 'o', 'D', 'Z', '0', 'P', 'E', '3', 'I', 'g', '1', 'l',
         'z', 'f', '5', '2', 'E', '+', '2', 'v', 'O', '7', 'J', 'U', 'y', 'D', 'f', 'g', '2', 'u', 'j', '6', 'H', 'G', 'n', '8', 'j', 'U', 'F', 'D', 'a', 'N', 'z', 'B', 'a', 'X', '1', 'q', 'b', 'H', '9', 'j', 'A', 'j', 'A', 'M', '6', '+', 'm', 'N', '0', 'V', 'C', 'n', '9', 'R', 'm', 'G', 's', 'r', 'P', 'J',
         'Y', 'S', 'G', '0', 'Z', 'h', 'q', 'S', 'Y', 'W', 't', '/', 'o', 'w', 'J', 'w', 'x', 'O', 'B', 'I', 'Z', 'R', 'S', '1', 'A', 'n', 'B', '4', 'h', 'd', 'Q', 'm', 't', 'C', 'K', 'G', 'A', 'A', 'z', 'D', 'M', 'm', 'o', 'l', 'N', 'H', 'i', 'a', '8', 'm', 'F', 'e', 'R', 'n', 'Y', 'F', 'x', 'v', 'S', '9',
         '8', 'S', 'L', 'T', 'b', 'i', 'm', 'l', '0', 'w', 'L', '0', 'o', 'L', 'Z', 'd', 'l', 'y', 'G', '2', 'U', 'G', 'L', 'C', 'k', 'N', 'E', 'w', 'D', 'O', '1', '3', 'K', 'a', 'w', 't', 'M', 'P', 'Y', 'X', 'q', 'M', 'j', 's', 'c', 'f', 'T', 'X', 'a', 'E', 'p', 'Z', 'A', 'L', '3', 'o', 'c', 'I', '6', 'X',
         'I', 'f', 'W', '9', 'A', 'L', 'y', 'J', 'w', 'c', 'J', 'R', 'M', 's', 'A', 'C', 'N', 'E', 'X', 'D', 'M', 'L', 'Q', '/', 'S', '/', 's', 'H', '1', 'v', 'e', 'N', 'q', 'e', 'o', '8', 'x', 'R', '8', 'S', 'U', 'D', '6', 'A', '5', 'R', 'k', '+', '4', '3', 'E', 'u', 'B', 'n', 'W', 'h', '4', 'v', 's', 'r',
         'U', 'D', 'V', '2', '5', 'q', 'C', 'i', 'W', 'q', 'm', 'n', '5', 'H', 'e', 'g', 't', 'i', 'l', '3', 'E', 'L', '4', 'g', 'E', 'p', 'U', 'G', 'W', 'c', 'y', 'V', 'r', '7', 'z', '9', 'g', 'T', 'O', 'L', 'R', 'D', 'P', 'O', 'A', 'b', 'p', '0', 'T', 't', '5', 'z', 'A', '8', 'E', 'K', 'l', 'x', 'b', 's',
         'Q', 'a', 'U', 'X', '6', 'b', 'J', 'o', 'k', '5', '5', 'O', 'o', '1', '6', 'x', '0', 'i', 'X', 'a', 'Q', 'r', 'c', 'v', 'N', 'U', 'n', 'D', 'M', 'L', 'T', 'f', '9', 'e', '4', 'z', 'U', 'A', 'U', 'x', 'T', 'q', 'F', 'f', '+', 'k', 'Z', 'X', 'V', 'N', 'E', 'b', 'R', 'n', 't', 'F', 'z', 'I', 'q', 'P',
         '2', 'Q', 'l', 'd', 'C', 'o', '2', '1', 'H', 'F', 'y', 'K', 'B', 'q', '7', '9', 'B', 'c', 'f', '1', 'S', 't', 'p', 'f', 'o', 'E', 'Q', 'M', 'L', 'M', '7', 'e', 'F', 'F', 'R', '9', 'g', 'C', 'l', 'j', 'r', 'O', '9', 'C', 'r', 'U', 'R', '6', '5', 'w', 'R', 'K', 'K', 'Q', 't', 'V', 'C', 'C', 'm', 'a',
         'D', 'B', 'H', 'b', 'k', 'y', '5', 'M', 'g', '8', '3', 's', 'V', '7', 'Q', 'u', 'E', '0', 'x', 'b', 'g', 'E', 'B', 'G', 'y', 'w', 'o', 'u', 'I', 'g', 'C', 'x', 'i', 'h', 'v', 'U', 'P', 'a', 'V', 'D', 'T', 'Q', 'J', 'Q', 'N', 'z', '2', 'l', '9', 'g', 'V', 'w', 'W', 't', 'O', 'm', 'O', '6', '6', 'F',
         'a', 'u', 'I', 'k', 'v', 'g', 'J', '5', 'a', 'C', 'O', 'B', 'w', 'y', 'a', 'Q', 'L', 'T', '0', 't', 't', 'N', 'B', 'C', 'C', 'y', '2', '0', '0', 'E', 'I', 'L', 'L', 'b', 'T', 'Q', 'Q', 'g', 's', 't', 't', 'N', 'B', 'C', 'C', 'y', '0', 'M', 'N', 'Y', 'g', 'R', 'o', 'L', '9', 'Q', 'w', 'e', 'Y', 'W',
         'R', 'k', 'c', 'A', '9', 'K', 'r', 'Y', 'N', 't', 'R', 'm', 'z', 'M', 'I', 'F', 'k', 'w', 'P', '7', 'y', '6', 'd', 'G', 'k', 'R', 'x', 'l', 'A', 'e', 'B', 'a', 'x', '2', 'v', 'x', 'u', 'E', '7', '8', 'q', 'I', 'r', '5', 'A', '6', 'd', 'q', 'Q', '1', 'U', 't', 'K', 'V', 'Q', 'y', 'P', 'a', 'D', 'N',
         'e', 'b', 't', '9', 'd', 'D', 'p', 'Z', 'F', '9', 'V', 'b', 'o', 'y', 'j', 'C', 'K', 'E', 'p', 'o', '3', 'U', 'n', 'q', 'a', 'J', '2', 'B', 'o', 'g', 's', 'Y', 'n', 'c', 'T', 'g', 'm', 'T', '+', '9', 'K', 'p', 'm', '/', '3', '5', 'D', '+', 'G', 'b', 'l', 'e', 'h', 'y', 'Y', 'U', 'h', 'D', 'H', '4',
         'n', 'z', 'a', 'y', 'g', 'P', 'I', 'H', 'a', 'f', 'o', 'I', 'o', '0', '5', 'U', 'y', 'S', 'u', 'Y', 'l', 'Z', 'k', 'f', 'k', 'I', 'Z', '0', 'P', 'P', '0', '/', 'B', '1', 'W', 'Q', 'Q', 'G', 'e', '9', '6', 'O', 'y', 'U', 'N', 'a', 'j', 'z', 'c', 't', 'c', 'x', 'e', 'A', 'h', 'U', 'Z', 'c', 'w', 'H',
         '9', 'k', '/', 'B', 'u', 'A', 'l', '1', 'W', 'j', 'Y', 'i', 'C', 's', 'F', 'A', 'M', 'q', 'b', 'z', 'I', 'S', 'W', 'A', 'l', '6', 'A', 'y', 'c', '3', 'd', 'R', '7', 'Y', 'n', 'm', 'v', 's', 'K', 'Y', 'W', 'z', 'U', 's', 'K', 'd', 'H', 'x', 'P', 'F', 'F', 'S', 'W', 'w', 'b', 'd', 'S', 'V', '9', 'D',
         'V', 'a', 'z', 'K', 'P', 'L', 's', '+', 'F', 'v', 'O', '5', 'E', 'A', 'C', '4', 'g', 'f', '5', 'R', 'r', '7', 'F', 'w', 'Z', '6', 'Z', 'Z', 'E', '/', 'N', '/', 'S', '3', '3', 'A', 'y', '9', 'R', 'V', '4', 'W', 'M', 'l', 'Z', 'G', 'W', 't', '1', 'c', 'K', 'M', 'D', 'O', 'B', 'H', 'q', 'R', '+', 'c',
         '1', 'd', 'K', 'S', 'E', 'h', '1', '/', 'k', 'g', 'R', 'g', 'm', 'l', '2', 'c', 'E', 'T', 'c', 'j', 'M', 'k', 'L', 'v', '1', 'd', '/', 'K', 'S', '3', 'R', 'g', 'Q', 'j', 'D', 'P', 'B', 'L', 'R', 's', 'h', 'R', 'C', 'R', 'w', '/', 'x', '3', 'a', 'M', 'h', 'b', 'J', 'x', '9', 'E', 'n', 'x', 'z', 'm',
         '4', 'z', 'c', 'U', 'p', 'U', 'W', 'b', '9', 'r', 'M', 'e', 'a', '/', '6', 'n', 'o', 'X', 'I', 'H', 'k', '1', 'A', 'B', 'y', 'N', 'K', '6', 'T', '6', 'i', 'j', 'l', '6', 'D', 'O', '9', 'V', 'u', 'q', 'U', 'B', 's', 'T', 'G', 'l', 'P', 'N', '/', 'P', 's', 'B', 'R', 'h', 'j', '3', 'b', '5', 'I', '5',
         'n', 'k', 'C', 'F', 'i', 'S', '/', 'U', 'z', 'j', '8', 'R', '0', '7', 'c', 'Y', '8', '/', 'V', 'R', 'L', 'r', 'x', 'O', 'U', 'Q', 'w', 'H', 'V', 'K', 'K', 'f', 'A', 'X', 'w', 'x', 'R', 'w', 'h', 'y', 'd', 'w', 'q', 'l', 'I', 'V', 'r', 'n', 'm', '2', '5', 'E', '4', '/', 'I', 'N', 'c', 's', '4', 'k',
         'G', '5', 'd', 'l', 'Q', 'C', 'e', 'c', 'p', 'G', 'F', 'H', 'F', '4', 'P', '8', 'm', '+', 'W', '5', '6', '4', 'R', 'j', 'n', 'X', 'y', 'R', 'y', 'o', '6', '2', 't', '7', 'T', 'z', 'U', 'w', 'D', 'P', 'M', '0', 'v', '4', 'w', 'O', 'I', 'r', 'h', 'c', 'w', 'M', 'b', 'M', '6', '1', 'p', 'H', '7', '8',
         'I', 'o', 'c', 'X', 'X', 'o', 'c', 'U', 'Z', '2', 'p', 'd', '2', 'a', '3', 'R', 'b', 'D', 'g', '4', 'W', 'U', 'I', 'b', '9', 'R', 'k', '5', '6', '1', 'D', 'H', 'o', '3', '3', 'v', 'e', 'G', '4', 'D', '6', 'o', 'x', 'A', 'f', 'V', 'T', '6', 'e', 'h', 'X', 'O', 'm', 'E', '3', 'r', 'q', 'J', '2', 'f',
         'k', '+', '/', 'z', 'w', 'P', 'C', 'V', 'p', 'h', 'F', 'W', 'U', '1', 'E', 'Y', 'z', 'v', 'U', 'c', 'W', 'b', 'U', 'p', 'W', 'E', '5', 'M', 'D', 'z', 'W', 't', 'W', 'c', 'h', 'P', 'l', '8', '0', 't', 'o', '9', '9', 'f', 'R', 'r', 'n', 'S', 'r', 'Z', 'K', 'N', 's', 'c', 'v', 'm', 'c', 'M', 'N', 'A',
         'H', '5', '+', '2', 'R', 'M', '+', 't', 'I', '8', '5', 'p', 'o', 'Q', 'f', 'G', '/', 'C', 'w', 'h', 'M', 'B', 'g', 'z', 'W', '9', 'I', 'P', 'S', 'Q', 'z', 'n', '+', 'l', 'E', 'X', '8', '0', 'N', '4', 'l', 'e', 'R', '0', '+', 'h', '6', 'A', 'Z', '7', 'L', 'G', 'W', '8', 'u', '+', 'O', 'J', 'O', 'g',
         'a', '2', 'x', 'e', 'v', 'I', 'f', 'w', 'w', '5', 't', '7', 'L', 'N', 'q', '3', '4', '3', 'i', 'u', 'y', '2', 'I', 'T', 'O', '4', 'i', '8', 'Q', 'Z', 'N', '5', '+', '0', 's', 'A', 'X', 's', '8', 'Q', 'A', 'n', 'M', 'c', 'L', 'j', 'v', '+', '8', '3', 'd', '/', 'k', 'c', 'H', '8', 'd', 'w', '2', 'a',
         'c', 'i', '1', 'f', 'm', 'm', 'N', '2', 'd', '0', 'i', 'j', 'z', 'g', 's', 'h', 'b', 'h', 'q', 'I', 'r', '6', 'N', '/', 'L', 'L', 's', 'O', 'B', 'H', '1', 'k', 'E', 'P', 'Q', 'W', 'a', 'e', 'I', '9', 'e', 's', '9', 'O', 'o', 'D', 'n', 'm', 'w', 'Y', '8', 'U', '/', 'a', 'P', 'r', 'b', 'd', 'O', '1',
         'c', 'f', 'q', '+', 'i', '/', '7', 'R', '7', '2', 'W', 'E', 'g', 'J', '8', 'G', 'f', 'o', 'n', 'w', 'r', '1', 'O', '7', 'n', 'x', 'd', 'C', 'f', 'J', '5', 'j', 'i', 'q', 'M', '6', 'o', 'B', 'n', 'M', 'f', '5', 'v', '6', '+', 'H', 'X', 'y', 'R', '+', 'A', 'z', '/', 'K', 'U', 'e', 'F', 'm', 'C', 'D',
         'G', 'G', 'C', 'e', 'X', 'P', '2', 'Q', 'x', 't', 's', '1', 'Q', 'j', 'R', 'u', '0', 'X', 'x', '9', 'n', 'q', '0', 'u', 'Y', 'R', 'p', 'q', 'A', 'X', 'y', 'D', 'H', '3', '/', 'O', 'i', 'M', 'q', 'V', 's', 'Q', 'I', '9', 'D', 'B', '5', 't', 'r', '6', 'd', '6', '0', '5', '5', 'C', 'U', 'F', '0', '8',
         'u', 'M', '/', '8', 'J', 'V', 'K', '0', 'D', 'o', 'C', 'L', 'A', 'L', '7', 'w', '6', 'f', 'P', 'U', 'o', '+', 'E', 'H', 'j', 'i', '+', 'n', 'z', '+', 't', 'Q', '+', '9', 'S', 'X', 'q', 'D', 'M', 'm', 'D', 'D', 'P', '5', 'E', 'B', 'n', 'H', 'm', 'A', 'c', 'G', 'P', '9', 'Z', 'y', 'g', 'k', 'B', 'V',
         'R', 'O', 'V', 'c', 'R', '9', 't', 'r', 'h', 'E', '0', 'z', '/', 'z', 'o', 'p', '4', 'T', '2', '6', 'N', 'o', 'k', 'X', 'Z', '6', 'n', 'f', 'N', 'p', 'G', 'x', 'R', '9', 'N', '3', 't', '6', 's', 'W', 'g', 'i', 'W', 'a', '0', 'm', 'm', 'v', 'V', 'O', '+', 'A', '1', 'Z', 'f', 'u', '+', 'H', 'v', 'w',
         'O', 'M', 'k', '6', 'w', 'A', 'z', 'n', 'B', 'j', '+', 'Y', 'A', 'I', '4', 'Z', 'U', 'T', 'm', 'U', 't', 'A', 'B', '8', 'x', '+', '8', 'e', 'W', 'S', 'U', 'f', 'T', '7', 'w', 'y', '6', 'S', 'D', 'c', 'H', 'x', 'B', 't', 'm', 'g', 'e', '6', 'b', 'v', 'A', 'K', 'X', 'Z', 'l', 'b', '9', 'N', 'M', 'C',
         'H', 'a', 'C', 'F', 'o', 'M', 'e', 'k', 'q', '8', 'M', 'c', 'r', 'T', '3', 'D', 'T', 'M', 'Z', 'c', 'C', '+', 'i', 'x', 'W', 'c', 'C', 'P', 'h', 'R', 'B', 'f', 'Z', 'o', 'y', 'F', '1', '4', 'j', 'O', 'N', 'T', 'Y', 'L', 'K', 'I', 't', 'f', 'M', 'i', 'E', 'U', 'Z', 'm', 'A', 'q', 'B', 'w', 'r', 'X',
         '7', 'w', '2', 'M', 'Q', 'V', 'w', 'k', 'z', 'd', '9', 'm', 'v', 'o', '/', 'I', 'U', '4', 'D', 'Q', '1', 'U', 'A', '9', 'n', 'z', 'd', 'X', 'A', 'y', 'f', 'I', 'F', '9', 'h', 'f', 'D', 'Z', 'R', 'S', '9', 'i', 'J', 't', 'U', '+', 'J', 'H', 'p', 'y', '8', 'A', 'u', 'G', 'E', 'x', '+', '2', '+', 'R',
         '1', 'Y', 'l', 'p', 'f', 'V', 'y', 'K', 'M', '8', 'M', 'C', 'U', '7', 'M', 'W', 'b', '1', '8', 'H', 'a', '+', '6', 'T', 'r', '7', 'Q', 'a', 'M', 'C', 'X', 'V', 'h', '0', 'R', '0', 'P', 'J', '8', '/', 'S', '1', 'q', '/', 'C', 'a', 'A', 'n', 'p', 'Z', 'R', '5', 'f', 'Z', '8', 'W', 'l', 'L', 'a', 'e',
         'E', 'G', 'L', 'X', 'l', 'C', '5', 'C', 'p', 'M', '2', 'k', 'j', 'v', 'T', '1', '9', 'B', 'Z', 'o', 'f', 'l', '5', '9', 'S', 'S', 't', 'w', 'w', 'B', '9', 'h', '7', '+', 'Z', 'O', 'Z', '5', 'X', 'M', 'N', 'w', 'N', 'T', 'e', 'y', 'x', 'M', 'a', '5', 'u', 'W', '6', 'j', '3', '7', 'o', 'Q', '5', 'w',
         'F', '2', 'p', 'V', 'j', 'x', 'e', 'F', 'E', 'A', 'Y', 't', 'u', 'p', 'j', 'F', 'f', 'u', 'T', 'T', 't', 'y', 'J', 'K', '4', 'e', '3', 'h', 's', 'S', 'N', 'o', 'J', 'S', '3', 'B', 'P', 'E', 'U', 'Z', 'L', '5', 'O', 'W', '3', 'E', 'M', '1', '+', 'Q', 'B', 'Z', '0', '9', 'L', 'S', 'a', '/', 'I', '5',
         'k', 'F', 'U', 'U', 'w', 'h', 'S', 'C', 'T', 'T', '3', 'r', 'k', 'V', 'L', '2', 'f', 'P', 'o', '8', 'p', 'I', 'p', '3', 'k', '8', 'w', '3', 'h', 'W', 'C', 'W', 'Z', 'g', 'e', 'T', 'L', 'A', 'q', '4', 'U', 'T', 'H', 'z', 'u', 'U', 'W', 'r', 'I', '0', 'U', 's', 'K', 'B', 'v', 'J', 't', 'w', 'C', 'F',
         'C', 'G', 'm', '8', 'D', '1', 'N', 'L', 'l', 'E', 'E', 'J', '8', 'U', 'f', '0', 'y', 't', 's', 'u', 'B', 't', 'P', 'U', 'a', 'k', 's', 'S', '9', 'U', 'g', 'W', 'i', 'W', 'F', '1', 'C', 'g', 'm', 'b', 'z', '9', 'A', 'r', 'y', 'j', 'T', 'W', 'R', 'w', 'D', 'q', '2', 'K', 'd', 'e', 'g', '7', 'C', 'V',
         'E', 'o', 'K', 'Y', 'N', 'M', 'U', 'W', 't', 'K', 'A', 'w', 'p', 'S', '+', 'i', 'o', '1', 'a', 'k', 'o', 'M', 'n', '2', 'h', 'u', 'I', '+', 't', 'B', 'z', 'y', '8', 'U', 'f', 'q', 'Z', 'k', 'h', 'T', 'F', 'q', 'D', 'M', '+', '0', 'e', '2', 'R', 'M', 'y', 'w', 'M', 'H', '/', 'Y', 'c', 'R', '9', '6',
         'G', 'x', '1', 'b', 'I', 'w', '6', 'z', '5', 'Q', 't', 'p', 't', 'x', 'i', '1', 'T', 'm', 'm', 'L', 'I', 'x', '1', 'R', 'G', 'O', 'V', 'T', 'P', 'V', 'p', 'o', 'o', 'T', 'p', 'f', 'K', 'l', 'J', 'A', 'o', 's', '4', 'N', 'k', 'U', '3', 'j', 'P', '5', 'I', 'C', 'w', 'D', 'd', '+', 'm', 'o', 'W', 'T',
         'e', 'X', 'H', 'k', 'H', 'q', 'q', 't', 'E', '9', 'w', 'U', '/', 'i', 'M', 't', 'A', 'P', 'y', 'Y', 'E', 't', 'e', 'y', '5', 'J', 'N', 'Q', 'C', 'x', 'H', 'b', 'U', 'E', 'u', 'e', 'M', 'd', 'e', '/', 'm', '8', 'Y', '/', 'r', 'P', 'y', 'S', 'E', 'Z', '7', 'L', 'F', 'Q', 'C', '+', 'G', '9', 'g', 'n',
         '0', 'P', 'E', '0', '1', 'E', 'o', 'c', 'T', 'x', 'Q', 'p', 'A', '0', '3', 'j', 'H', 'y', 'b', 'G', '8', '5', 'V', 'H', 'v', 'v', 'A', 'j', 'A', '5', '7', 'z', 'R', 'j', 'o', 'B', 'W', 'u', '+', 'n', '1', 'S', 'X', 'r', 'Z', 'X', 'z', '/', 'H', 'F', 'S', 'S', 'R', 'N', 'k', 't', 'W', 'U', '3', 'j',
         '9', '6', 'W', 'x', '6', 't', '1', 'H', '+', '/', '3', 'A', 'r', 's', 'd', 'x', 'c', 'K', 'N', 'N', 'k', 'v', 'O', 'c', 'K', 'G', 'I', 'B', 't', 'C', 'T', 't', 'G', 'o', 's', '6', 'b', '6', 'K', '/', 'z', 'Z', 'i', 'P', 'w', 'R', '8', 'a', 'z', '5', '1', 'D', 'P', 'y', 'k', 'j', 'R', 'P', 'p', 'c',
         '+', 'K', '9', 'A', 'r', 'f', 'j', 'x', '5', 'A', 'o', 'B', '4', 'O', 'P', 'I', '+', 'H', '0', 'Z', 'z', 'x', 'N', 'B', 'y', 'q', '7', '7', 'u', 'y', 'D', 'l', '/', 'W', 'C', '0', 'c', 'Q', 'V', 'q', '+', 'b', 't', 'L', '/', 'W', 'W', 'r', 'm', 'f', 'A', 's', 'B', 'r', 'O', 'y', 'D', '7', 'z', 'c',
         '1', 'U', 'A', 'z', 'z', 'V', 's', 'f', 'h', 'P', 'S', 'x', '8', 'e', 'x', 'r', 'A', 'F', '4', 'V', 'Q', 'n', 'x', 'm', 'H', 'F', '6', 'k', 'N', '0', 'p', 'u', 'B', 'Q', 'q', 'A', 'i', 'f', '8', 'K', 'V', 'A', 'b', 'O', 'K', 'g', 'a', 'P', 'Y', 'h', 'k', 'D', '8', 'J', 'I', 'Q', '4', 'p', '8', 'R',
         '8', 'f', 's', 'M', 'T', 'W', 'Z', 'n', '5', 'u', '7', 'F', 'L', '2', 'H', '6', 'D', '8', 'Q', '8', 'h', 'B', 'C', '3', 'o', 'G', 'o', 'h', '6', 'P', 'x', 'E', 'V', '4', 'L', 'q', 'P', 'P', 'r', 'J', 'o', 'g', 'e', 'U', 'I', 'c', 'm', 'Q', '7', 'g', '5', 'b', 'T', '9', 'b', 'M', 'X', '9', 'U', 'E',
         'M', 'G', 'Q', '6', '9', 'f', 'i', 'n', 'Q', 'g', 'h', '9', '/', 'x', '9', 'Q', 'G', 'z', 'g', 'n', 'A', '8', 'x', 'j', 'F', 'v', '7', '7', 'd', 'K', '0', 'a', '1', '3', '0', 'A', 'L', '0', 'b', 'C', '7', '0', 'P', 'b', 'u', 'K', 'U', 'f', 'z', 'k', 'A', 'l', 'x', 'I', '5', 'X', 'g', 'N', 'M', 'V',
         '+', 'L', 'p', 'B', 'e', 'L', 'O', 'y', 'k', 'z', 'O', '3', '5', 'L', 'k', 's', 'g', 'C', 'l', '1', 'P', 'Y', 'v', 'm', 'a', '9', 'C', '7', 'U', 'C', '4', 'Z', '9', '4', '8', 'T', 'c', 'z', 'o', 'B', 'G', 'm', 'H', 'D', '/', '9', 'e', 'c', '3', '7', 'w', 'Q', 'E', 'X', '+', 'W', 'N', 'q', 'Z', 'g',
         't', 'R', 'A', 's', 'm', 'q', 'a', 'P', 'n', 'N', '+', 'L', 'N', 'P', 'x', 'I', 'q', 'D', 'M', 'M', '7', 'z', 'i', 'q', 'o', 'n', 'y', 'e', 's', 'R', '5', 'y', 'F', 'f', '0', 't', 'c', 't', '5', 'p', '4', 'c', 'J', 'i', 'G', 'a', 'T', 'N', 'C', 'z', 'f', 'G', '3', 'W', 'P', 'G', 'b', '6', 'a', 'Y',
         'k', 'y', 'I', 'K', 'd', 'I', 'Q', '3', 'f', 'q', 'O', 'x', 'J', 'y', 'L', 'h', 'z', 'z', 'L', '7', 'u', 'x', 'n', 'f', 'f', '8', 'I', '+', 'P', '0', '7', 'D', 'Q', 'd', 'l', 'T', 'w', '8', 'w', 'z', 'D', 'G', '/', '5', 'b', 'N', 'V', 'n', 'G', 'd', 'K', '5', 'e', 'w', 'M', 'S', 'T', '7', 'P', 'j',
         'Y', '8', '5', 'm', 'L', 'F', 'o', 'c', 'a', 'g', 'p', 'D', '8', 'B', '+', 'P', 'i', 'N', '9', 'G', 'T', '8', 'r', 'N', 'P', 'u', '9', '4', 'R', '2', 'm', 'W', 's', 'r', 'u', 'C', 'u', 'f', 'X', 'T', 'Z', 'x', 'h', 'e', '8', 'F', 'w', 'G', 'f', '5', 's', 'c', 'v', '0', 'W', 'w', 'N', 'H', 'G', 'X',
         'V', 'P', 'v', '3', 'g', 'r', 'E', 'D', '2', 'L', 'Y', 'j', 'u', 'N', 'I', '5', 'l', '8', 'e', 'O', '5', 'I', 'q', 'n', 'e', '7', '4', 'Q', '0', '/', '/', 'Q', 's', '4', 's', 'N', 'Y', 'u', 'r', 'z', 'r', 'j', 'Z', 'b', 't', 'o', 'p', 'x', '7', '7', '9', 'X', 'x', 'A', 'e', 'Q', 'l', 'v', '9', '/',
         'Q', 'Y', '3', '5', '1', 'P', 'j', 'u', 'X', 'a', 'h', 'q', 'G', 'B', '0', 'L', '4', 'a', 'F', 'T', 'I', 'h', 'v', '+', '1', '+', 'h', '9', 'E', 'x', 'a', '6', '9', 'b', 'b', 'x', 'W', 'P', 'j', 'z', 'N', 'M', 'w', '2', 'B', 'F', 'Y', 'J', 'e', 'i', 'j', 'Y', 'R', 's', 'Z', 'e', 'R', 'P', 'I', 'J',
         'P', 'g', 'D', 'w', 'O', 'v', 'N', 'H', 'M', 'v', '2', 'Q', '1', 'I', 'G', 's', 'B', '+', 'B', 'J', 'I', 'c', 'R', '3', '9', 'N', 'I', 'P', 'i', 'Q', 'E', 'b', 'l', 'g', 'Y', '/', 'I', 'C', '/', '8', '7', '8', 'x', 'r', 'v', '2', 'o', '4', 'Q', 'b', 'J', 'g', 'Y', '2', '3', '4', 'X', 'y', 'F', 'c',
         't', 'q', '1', 'e', 'C', 'Y', 'C', 'b', 'k', 'f', 'B', 'n', '0', 'f', 'Q', 'Y', 'e', 'd', '3', 'z', 'x', 'p', 'g', 'P', 'A', 'H', '+', 'g', 'a', 'e', 'o', '6', '0', 'V', 'n', 'F', 'u', 'c', 'E', 'P', 'f', 'I', 'p', 'k', 's', 'X', 'I', '1', 'k', '6', 'y', '/', 'p', 'O', '8', 'U', 'Q', 'y', 'M', '7',
         'D', 'm', 'D', 'F', 'k', 'P', 'K', 'f', 'U', 'a', 'c', 'e', 'Y', '2', 'N', '+', 'B', '8', 'C', 'n', 'F', 'm', '1', '4', 'F', 'c', 'B', 't', 'C', 's', 'h', 's', 'F', 'Q', 'j', 'L', 'Z', 'u', 'F', '/', 'k', 'T', 'z', '7', 'L', 'S', 'M', 'O', 'c', 'D', 'c', 'i', '/', 'q', 'y', 'Z', 'y', 'T', 'S', '1',
         '/', 'T', 'i', 'A', 'L', 'y', '1', 'B', 's', 'h', '/', 'Q', 'r', '0', 'w', 'S', 'w', 'w', 'k', 'c', 'C', 'I', 'e', '7', 'H', 'L', '4', 'M', 'R', '/', 'A', 'C', 'D', 'Q', 'U', 'P', 'i', '4', 'b', 'G', 'E', '2', 'L', 'w', 'U', '0', 'V', 'D', 's', 'c', 'a', 'z', 'F', '6', 'H', '2', '8', 'R', 'W', 't',
         'k', 't', 'U', '0', '/', 'i', 'x', 'H', 'c', 'A', 'q', 'q', '/', 'J', 'p', 'J', 'x', 'y', '8', 'p', 'O', 'q', 'd', 'L', 's', '8', 'V', 'w', 'A', 'L', 'W', 'V', 'l', 'j', 'Y', 'g', 'v', 'O', '/', 'm', 'f', 'P', '8', 'c', 'h', 'Y', 'P', 'T', 'k', 'F', 'C', 'w', '3', 'o', 'h', '5', 'y', '2', 'M', 'a',
         'd', 'u', 'B', '7', 'J', 'o', 'V', 'F', '9', '+', 'o', '1', 'j', 'T', '+', 'L', 'L', 'h', '2', 'b', 'P', '0', 'X', 'e', '/', 'g', 'k', '2', 'F', 'J', 'q', 'b', 'Q', 'G', 'O', 'c', 'm', 'z', 'w', 'B', 'S', '6', 'U', '2', 'o', 'y', 'r', 'I', 'N', 'r', 'f', 'C', 'x', 'j', 'M', '/', 'J', '0', 'u', '4',
         'A', 's', 'v', 'm', '1', 'C', 'R', 'n', 'z', 'O', 'u', 'g', 'f', '4', 'T', '6', 'y', 'x', 'l', 'e', '+', 'N', 'W', 'c', 'a', 'F', 'X', 'R', 'W', 'o', 'F', 'N', '4', '8', '+', 'j', 'S', '2', '8', 'M', 'X', 'Q', 'T', 'w', 'D', 'V', '2', 'L', 'G', 'K', 'x', 'K', 'F', 'n', 'M', '5', '3', 'D', 'X', 'P',
         'X', '4', 'K', 'q', 'i', 'P', 'Z', 't', 'x', 'u', 'x', 'g', 'I', 's', 's', 'a', '+', 'S', '4', 'H', 'z', '1', 'A', 'H', 'n', 'q', 'D', 'x', 'b', 'x', 'o', 'H', 'F', '0', 'E', 'k', 'g', 'M', '8', 'i', 'j', '0', 'c', 'u', '/', 'H', 'y', 'T', 'p', 'G', 'a', 'I', '1', 'I', '5', 'o', '7', 'P', 'E', 'w',
         'Y', '1', 'q', 'Y', 'u', 'R', 'g', 'U', 'Y', 'Z', '+', 'A', 't', 'g', 'B', 'z', 'x', 'G', 'g', 'N', 'V', '0', 'k', 'x', 'F', 's', 'n', 'n', '2', 'K', 'Z', 'h', 'b', 'p', '4', 'E', 'X', 's', 'M', 'V', 'q', 'N', '3', 'S', '3', '2', 'o', 'L', 'Y', 'G', '4', 'Z', 'L', '5', 'o', 'Q', 'M', 'k', 'X', 'M',
         'n', 'z', 'A', 'a', 'r', 'r', 'e', 'L', 'H', 'w', 'P', 'w', '7', 'w', 'w', 'm', 'n', 'C', 'M', 'm', 'W', 'F', 'e', 'm', 'h', 'h', 'S', '/', 'z', '5', 'A', 'A', 'b', 'v', 'L', 'z', 'p', 'o', 'c', 'F', 'p', '4', '9', 'a', 'A', 'R', 'a', 'I', 'w', 'd', 'q', 'z', '1', '1', 'E', '+', 'v', 'h', 'o', '4',
         'i', '3', '7', 'N', 'A', 'l', '0', 's', 'Y', 't', 'm', 'I', 'B', 'w', 'z', 'g', 'T', 'z', '3', 'N', 'X', 'p', 'd', 'p', 'W', 'g', 'c', 'H', 'U', '7', 'J', '0', 'X', 'd', 'w', 'O', 'D', 'h', 'a', 'T', 'M', 'g', 'M', 'k', '6', '+', 'Q', 'd', '+', '4', 'Z', 'n', 'm', '8', 'a', 'f', 'R', '5', 's', 's',
         'y', 'l', 'z', 't', 'u', 'X', 'v', 'W', 'T', 'd', 'A', '1', 'B', 'p', 'a', 'J', 'b', 'r', '0', 'R', 'l', 'p', 'e', 'r', '0', 'T', 'E', 'P', 'v', 'f', 'y', '9', 'Y', 'X', 'm', 'u', 'a', '8', 'O', 'f', 'F', 'm', 'w', 'o', '1', 'z', 'b', 'z', 'e', '8', 'H', 'm', '3', 'Q', 'N', 'M', 'Y', 'M', 'u', '5',
         'Z', 'T', 'u', '6', 'K', 'f', 'z', 'B', 'w', 'a', 'I', '8', 'I', 'f', 'B', 's', 'u', '/', 'Y', 'r', 't', 'u', 'D', 'O', '9', 'O', 'l', '5', 'P', 'j', 'e', 'A', 'P', '4', '0', 'h', '9', 'Q', 'a', 'h', 't', 'o', 'p', 'i', 'V', '8', 'g', '7', 'f', 's', 'D', 'm', '5', 'D', 'K', 'W', '1', 't', 'W', 'M',
         'P', 'y', '8', 'I', '4', '2', '3', 'y', 'N', 'R', 'M', '8', 'B', 'E', 'a', 'y', 'w', 'J', 'Y', 'r', 'W', 'g', 'o', 'a', '3', '3', 'O', 'f', 'G', 'w', 'i', 't', 'x', '2', 'w', '8', 'v', 'Z', 'Q', 'X', 'b', '5', 'g', 'z', 'p', 'k', 'k', 'r', 'k', 'Z', 'y', 'w', 'P', 'M', 'e', 'x', 'E', 'f', 'x', 'F',
         'B', 'S', 'D', 'r', 'N', 'z', 'H', 'x', 'F', '5', 'p', 'i', 'l', 'G', 'E', '+', 'k', 'y', 'z', 't', 'I', 'U', '+', 'T', '4', 'w', 'b', 'S', 'v', 'E', '3', 'U', 'k', '6', 'z', 'Z', 'C', 'H', '6', 'T', 'A', 'T', '6', 'z', 'g', 'C', 'o', 'F', 'w', 'A', 'd', '/', 'G', 'p', 'v', '5', 'l', 'v', 'F', 'o',
         '0', '/', 'D', 'W', 'K', '0', '/', 'X', 'Z', 's', 'W', 's', 'G', 's', 'F', '/', 'm', 'E', 'D', 'E', 'Z', 'r', '5', 'F', 'm', 'k', 'X', 'e', 'W', 'B', 'R', 'b', 'C', 'w', '1', 'a', 'a', 's', 'N', '/', 'G', 'I', 'e', 'A', '/', 'w', 'M', 'F', 'g', 'q', 'L', 'F', '4', '1', 'u', 'y', 'w', 'g', 'A', 'A',
         'A', 'A', 'B', 'J', 'R', 'U', '5', 'E', 'r', 'k', 'J', 'g', 'g', 'g', '=', '=', 0
    };

    std::string CursorsFilename()
    {
        namespace fs = boost::filesystem;
        fs::path temp_directory = fs::temp_directory_path();
        fs::path cursors_path = temp_directory / "gigi_cursors.png";
        boost::system::error_code error;
        if (!fs::exists(cursors_path, error) || error) {
            assert(std::strlen(CURSORS) == CURSORS_SIZE);
            std::vector<unsigned char> buffer;
            detail::DecodeBase64(buffer, CURSORS, CURSORS_SIZE);
            fs::path tmp_cursors_path =
                temp_directory /
                ("gigi_cursors_" + fs::unique_path().string() + ".png");
            {
                fs::ofstream ofs(tmp_cursors_path);
                ofs.write(static_cast<char*>(static_cast<void*>(&buffer[0])),
                          buffer.size());
            }
            fs::rename(tmp_cursors_path, cursors_path);
        }
        return cursors_path.string();
    }

}