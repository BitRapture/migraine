#pragma once
#include <string>
#include <unordered_map>

namespace br
{

	class cetamol
	{
	public:
		bool AutoDocumentation{ true };

	private:
		static const char labelTag{ '_' }, numberTag{ '-' }, fillTag{ '$' }, gotoTag{'*'}, stackPushTag{'>'}, stackPopTag{'<'};
		static const char indexIncrement{ 'e' }, passZeroFunction{ '!' }, pipeFunction{ '.' }, swapRegister{ 'E' };
		static constexpr char resetFunctionIndex[2]{ indexIncrement, passZeroFunction };
		static constexpr int fullNumberLength = 2 + (9 * 2) + 1; // e![number][! or .]
		std::string gotoBoilerPlate, stackPushBoilerPlate, stackPopBoilerPlate;

		std::unordered_map<std::string, int> labelTable;
		std::vector<size_t> labelPlacement;
		std::string holdString;
		bool labelModeActive;
		bool numberModeActive;

	private:
		bool assert(bool condition, const char* errorMessage, std::string& content);
		
		std::vector<int> getDigits(int number);
		int resolveNumberDigits(int initialNumber, int resolver);
		std::string fillChar(int amount, const char& character);
		std::string generateNumber(int number);
		std::string generateFullNumber(int number);
		std::string convertFilePath(const std::string& filePath);
		std::string generateMainJump(size_t& programCounter);

	public:
		std::string generateMigraine(const std::string& cetamolProgramData);
		std::string parseFile(const std::string& filePath);

		cetamol();
	};
}