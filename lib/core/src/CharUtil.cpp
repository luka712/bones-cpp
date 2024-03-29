#include "CharUtil.hpp"

namespace bns
{
    char** CharUtil::CreateCopy(const std::vector<std::string>& listOfStrings)
    {
        char** result = new char*[listOfStrings.size()];

        for (size_t i = 0; i < listOfStrings.size(); i++)
        {
            result[i] = new char[listOfStrings[i].size() + 1];
            strcpy(result[i], listOfStrings[i].c_str());
        }

        return result;
    }

    void CharUtil::FreeCopy(char** copy, u32 size)
    {
        for (size_t i = 0; i < size; i++)
        {
            delete[] copy[i];
        }

        delete[] copy;
    }
} // namespace bns