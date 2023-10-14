#include "loaders/FileLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace bns
{
    std::string FileLoader::LoadFile(std::string path)
    {
        std::ifstream input_file(path);
        if (!input_file.is_open())
        {
            std::cerr << "Could not open the file - '" << path << "'" << std::endl;
            return "";
        }
        std::string text = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

        input_file.close();

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