#include "cetamol.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		br::cetamol generator;
		if (argc > 2)
		{
			size_t arglen = strlen(argv[2]);
			if (arglen > 1 && argv[2][0] == '-')
			{
				switch (argv[2][1])
				{
				case 'd':
					generator.AutoDocumentation = false;
					break;
				}
			}
		}
		std::cout << generator.parseFile(argv[1]);
	}

#ifdef _DEBUG
	br::cetamol generator;
	std::cout << generator.parseFile("../cetamolProgram.mol");
#endif

	return 0;
}