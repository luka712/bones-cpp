#include "loaders/FileLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace bns
{
    std::string FileLoader::LoadFile(std::string path, std::map<std::string, std::string> defines)
    {
        std::ifstream input_file(path);
        if (!input_file.is_open())
        {
            std::cerr << "Could not open the file - '" << path << "'" << std::endl;
            return "";
        }
        std::string text = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

        input_file.close();

        // replace defines
        // define can be for example ##WIDTH## and we can replace it with 100, if key is ##WIDTH## and value is 100.
        for(auto kvp : defines)
        {
            auto key = kvp.first;
            auto value = kvp.second;

            text.replace(text.find(key), key.length(), value);
        }

        return text;
    }

    std::string FileLoader::CreateOrOpenFile(std::string path)
    {
        std::ifstream input_file(path);

        std::string text = "";

        // if file found and open.
        if (input_file.is_open())
        {
            text = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
            input_file.close();
        }
        else
        {
            std::ofstream outfile(path);
            outfile.close();
        }

        return text;
    }

    void FileLoader::SaveFile(std::string path, std::string contents)
    {
        std::ofstream outfile(path);

        outfile << contents << std::endl;

        outfile.close();
    }

} // !namespace bns