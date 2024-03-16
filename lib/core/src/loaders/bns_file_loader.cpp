#include "bns_types.hpp"
#include "loaders/bns_file_loader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace bns
{
	std::string FileLoader::LoadFile(std::string path, std::map<std::string, std::string> defines)
	{
		std::ifstream input_file(path);
		if (!input_file.is_open())
		{
			std::string msg = "FileLoader::LoadFile: File not found: " + path;
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}
		std::string text = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

		input_file.close();

		// replace defines
		// define can be for example ##WIDTH## and we can replace it with 100, if key is ##WIDTH## and value is 100.
		for (auto kvp : defines)
		{
			auto key = kvp.first;
			auto value = kvp.second;

			// Replace all occurances in text
			do
			{
				text = text.replace(text.find(key), key.length(), value);
			} while (text.find(key) != std::string::npos);
		}

		return text;
	}

	std::vector<char> FileLoader::LoadFileAsBinary(std::string path)
	{
		std::ifstream file(path, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			std::string msg = "FileLoader::LoadFileAsBinary: File not found: " + path;
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
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