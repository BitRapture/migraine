#pragma once
#include <string>
#include <unordered_map>

namespace br
{

	class cetamol
	{
	public:
		size_t FixedDigitSize{ 16 };
		bool AutoDocumentation{ true };

	private:
		static const int generatorVersionMajor = 1;
		static const int generatorVersionMinor = 0;

	private:
		static const char placeHolder{ 'x' };
		static const char labelDefineTag{ '^' }, labelTag{ '_' }, numberTag{ '-' }, fixedTag{ 'f' }, fillTag{ '$' }, gotoTag{ '*' }, stackPushTag{ '>' }, stackPopTag{ '<' }, branchReturnTag{ '^' }, callStackPop{ '~' };
		static const char indexIncrement{ 'e' }, passZeroFunction{ '!' }, pipeFunction{ '.' }, swapRegister{ 'E' };
		static constexpr char resetFunctionIndex[2]{ indexIncrement, passZeroFunction };
		static constexpr int fullNumberLength = 2 + (9 * 2) + 1; // e![number][! or .]
		
		std::string gotoBoilerPlate, stackPushBoilerPlate, stackPopBoilerPlate, branchReturnBoilerPlate, callStackPopBoilerPlate;
		int fixedNumberLength = FixedDigitSize * fullNumberLength;
		int fixedNumberMaximum;

		struct address_information
		{
			long* labelAddress;
			long programAddress;
			std::string gotoProgram;
		};

		typedef std::unordered_map<std::string, long> labeltable;
		labeltable labelTable;
		std::vector<address_information> addressInfo;

		std::string holdString;
		bool labelModeActive;
		bool numberModeActive;

	private:
		bool assert(bool condition, const std::string errorMessage, std::string& content);
		
		std::vector<int> getDigits(int number);
		int resolveNumberDigits(int initialNumber, int resolver);
		std::string fillChar(int amount, const char& character);
		std::string generateNumber(int number);
		std::string generateFullNumber(int number, int padding = 0);
		std::string generateFixedNumber(int number);
		std::string convertFilePath(const std::string& filePath);
		std::string generateJump(long& programCounter);

	public:
		std::string generateMigraine(const std::string& cetamolProgramData);
		std::string parseFile(const std::string& filePath);

		cetamol();
	};
}