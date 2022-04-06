
/*
==========================================
  Copyright (c) YEAR dynamic_static
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/placeholder.hpp"

#include "catch2/catch.hpp"

namespace dst {
namespace tests {

TEST_CASE("Placeholder", "[placeholder]")
{
    SECTION("Placeholder")
    {
        CHECK(placeholder());
    }
}

} // namespace tests
} // namespace dst
