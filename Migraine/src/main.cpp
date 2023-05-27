#include "file_handling.h"
#include "migraine.h"

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		br::migraine model;
		std::string programText = br::parseFile(argv[1]);
		model.run(programText);
	}

#ifdef _DEBUG
	br::migraine model;
	std::string programText = br::parseFile("../cetamolProgram.mgrn");
	model.run(programText);
#endif

	return 0;
}