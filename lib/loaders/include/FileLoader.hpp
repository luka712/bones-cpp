#pragma once

#ifndef BNS_FILE_LOADER_H

#define BNS_FILE_LOADER_H

#include <string>
#include <map>

namespace bns
{
    /**
     * @brief The file loader class.
     *
     */
    class FileLoader final
    {
    public:
        /**
         * @brief Open the file from path into string. If the file is not found, empty string is returned.
         *
         * @param std::string - file path
         * @param std::map<std::string, std::string> - the defines to be replaced in the file.
         * For example, if the file contains #define WIDTH ##WIDTH##, then we can replace ##WIDTH## with 100 for key value <##WIDTH##, 100>.
         * @return std::string
         */
        std::string LoadFile(std::string path, std::map<std::string, std::string> defines = {});

        /**
         * @brief Creates or open the file from path into string. If file is newly created one or empty, empty string is returned.
         *
         * @param path - the file path.
         * @return - file contents or empty string if file is newly created.
         */
        std::string CreateOrOpenFile(std::string path);

        /**
         * @brief Save contents into file. If file exists, contents of file will be overriden.
         *
         * @param path - the file path.
         * @param contents - the current contents of a file.
         */
        void SaveFile(std::string path, std::string contents);
    };
}

#endif // ! BONES_FILE_LOADER_H
