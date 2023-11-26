#ifndef BNS_CHAR_UTIL_HPP

#define BNS_CHAR_UTIL_HPP

#include "Types.hpp"
#include <vector>
#include <string>

namespace bns
{
   struct CharUtil
   {
        /// @brief Copy a list of strings to a char** array.
        /// @param listOfStrings The list of strings to copy.
        /// @return The char** array.
        static char** CreateCopy(const std::vector<std::string>& listOfStrings);
   };

} // namespace bns

#endif // BNS_CHAR_UTIL_HPP