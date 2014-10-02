//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <vector>

#include "detail/base_type.hpp"
#include "expression_def.ipp"


namespace rill
{
    namespace ast
    {
        typedef std::vector<expression_ptr> expression_list;

    } // namespace ast
} // namespace rill
