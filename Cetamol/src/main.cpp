#include "cetamol.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		br::cetamol generator;
		if (argc > 2 && argv[2] == "-d")
		{
			generator.AutoDocumentation = false;
		}
		std::cout << generator.parseFile(argv[1]);
	}

#ifdef _DEBUG
	br::cetamol generator;
	std::cout << generator.parseFile("../cetamolProgram.mol");
#endif

	return 0;
}