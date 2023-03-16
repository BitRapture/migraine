#pragma once
#include <fstream>
#include <string>

namespace br
{
	std::string parseFile(const char* filePath, const char discard = '#')
	{
		std::ifstream inputFile(filePath);

		std::string out, line;
		out += discard;
		if (inputFile.is_open())
		{
			while (std::getline(inputFile, line))
			{
				size_t lineLength = line.size();
				for (size_t i = 0; i < lineLength; ++i)
				{
					char currentChar = line.at(i);
					if (currentChar == discard) { break; }
					if (currentChar > 32) { out += currentChar; }
				}
			}
		}

		inputFile.close();
		return out;
	}

}