#include "cetamol.h"
#include <fstream>
#include <vector>

namespace br
{

	bool cetamol::assert(bool condition, const char* errorMessage, std::string& content)
	{
		if (!condition)
		{
			content = "Error! ";
			content += errorMessage;
		}
		return condition;
	}

	std::vector<int> cetamol::getDigits(int number)
	{
		std::vector<int> digits;
		digits.push_back(number % 10);
		while (number >= 10)
		{
			number /= 10;
			digits.push_back(number % 10);
		}
		return digits;
	}

	int cetamol::resolveNumberDigits(int initialNumber, int resolver)
	{
		std::vector<int> digits = getDigits(initialNumber);
		int place = digits.size() * resolver;
		int newNumber = initialNumber + place;
		if (getDigits(newNumber).size() > digits.size())
		{
			newNumber = resolveNumberDigits(newNumber, resolver);
		}
		return newNumber;
	}

	std::string cetamol::fillChar(int amount, const char& character)
	{
		std::string fill = "";
		while (amount > 0)
		{
			fill += character;
			--amount;
		}
		return fill;
	}

	std::string cetamol::generateNumber(int number)
	{
		std::string numberProgram = resetFunctionIndex;
		if (number == 0)
		{
			numberProgram += passZeroFunction;
		}
		else if (number > 0)
		{
			std::vector<int> digits = getDigits(number);

			int previousDigit = 0;
			bool isFirstDigit = true;
			for (long i = digits.size() - 1; i > -1; --i)
			{
				int currentDigit = digits.at(i);
				if (currentDigit > previousDigit)
				{
					int increment = currentDigit - previousDigit;
					numberProgram += fillChar(increment * 2, indexIncrement);
				}
				else if (currentDigit < previousDigit)
				{
					numberProgram += resetFunctionIndex;
					numberProgram += fillChar(currentDigit * 2, indexIncrement);
				}
				if (isFirstDigit)
				{
					numberProgram += passZeroFunction;
					isFirstDigit = false;
				}
				else
				{
					numberProgram += pipeFunction;
				}
				previousDigit = currentDigit;
			}
			if (previousDigit != 0)
			{
				numberProgram += resetFunctionIndex;
			}
		}
		return numberProgram;
	}

	std::string cetamol::generateFullNumber(int number)
	{
		std::string numberProgram;
		std::vector<int> digits = getDigits(number);

		bool isFirstDigit = true;
		for (long i = digits.size() - 1; i > -1; --i)
		{
			numberProgram += resetFunctionIndex;
			int currentDigit = digits.at(i);
			int digitsRemaining = 9 - currentDigit;
			numberProgram += fillChar(currentDigit * 2, indexIncrement);
			if (isFirstDigit)
			{
				numberProgram += passZeroFunction;
				isFirstDigit = false;
			}
			else
			{
				numberProgram += pipeFunction;
			}
			numberProgram += fillChar(digitsRemaining * 2, indexIncrement);
		}

		return numberProgram;
	}

	std::string cetamol::convertFilePath(const std::string& filePath)
	{
		size_t lastSlashIndex = filePath.find_last_of("/\\");
		std::string directory = "";
		std::string fileName = filePath;
		if (lastSlashIndex != std::string::npos)
		{
			directory = filePath.substr(0, lastSlashIndex);
			fileName = filePath.substr(lastSlashIndex);
		}
		size_t fileExtensionIndex = fileName.rfind(".mol");

		if (fileExtensionIndex == std::string::npos)
		{
			return "";
		}
		fileName = fileName.substr(0, fileExtensionIndex + 2) + "grn";

		return directory + fileName;
	}

	std::string cetamol::generateMainJump(size_t& programCounter)
	{
		std::string mainJump;
		int resolvedMainJumpIndex = resolveNumberDigits(programCounter + gotoBoilerPlate.length(), fullNumberLength);
		mainJump = generateFullNumber(resolvedMainJumpIndex) + gotoBoilerPlate + '\n';
		return mainJump;
	}

	std::string cetamol::generateMigraine(const std::string& cetamolProgramData)
	{
		std::string migraineProgram = "";
		std::string blurb = "# This migraine program was generated from a .mol file!\n# https://github.com/bitrapture/migraine\n\n";

		std::string mainJump = "";
		size_t programLength = cetamolProgramData.length();
		size_t migraineProgramCounter = 0;
		for (size_t i = 0; i < programLength; ++i)
		{
			char currentChar = cetamolProgramData.at(i);

			if (!labelModeActive && !numberModeActive)
			{
				switch (currentChar)
				{
				case labelTag:
					labelModeActive = true;
					break;
				case fillTag:
				case numberTag:
					numberModeActive = true;
					break;
				case gotoTag:
					migraineProgram += resetFunctionIndex;
					migraineProgram += gotoBoilerPlate;
					migraineProgramCounter += gotoBoilerPlate.length() + 2;
					break;
				case stackPushTag:
					migraineProgram += stackPushBoilerPlate;
					migraineProgramCounter += stackPushBoilerPlate.length();
					break;
				case stackPopTag:
					migraineProgram += stackPopBoilerPlate;
					migraineProgramCounter += stackPopBoilerPlate.length();
					break;
				case indexIncrement:
				case passZeroFunction:
				case pipeFunction:
				case swapRegister:
					++migraineProgramCounter;
				case '\n':
					migraineProgram += currentChar;
					break;
				}
			}
			else
			{
				switch (currentChar)
				{
				case labelTag:
				case fillTag:
				case numberTag:
				{
					if (labelModeActive)
					{
						auto labelTableQuery = labelTable.find(holdString);
						if (labelTableQuery == labelTable.end())
						{
							migraineProgram += AutoDocumentation ? "\n# " + holdString + " define" : "";
							if (holdString == "MAIN")
							{
								if (migraineProgramCounter > 0)
								{
									std::string jump = generateMainJump(migraineProgramCounter);
									mainJump = AutoDocumentation ? "\n# MAIN jump boilerplate\n" : "";
									mainJump += jump;
									size_t programCounterShift = jump.length() - 1;
									for (auto it = labelTable.begin(); it != labelTable.end(); it++)
									{
										it->second += (int)programCounterShift;
									}
									std::string mainReset = "\n";
									mainReset += stackPopBoilerPlate += { passZeroFunction, swapRegister, passZeroFunction };
									migraineProgram += mainReset;
									migraineProgramCounter += programCounterShift + mainReset.length();
								}
							}
							labelTable[holdString] = (int)migraineProgramCounter;
						}
						else
						{
							labelPlacement.push_back(migraineProgramCounter);
							//std::string numberProgram = generateNumber(labelTable[holdString]);
							//migraineProgram += numberProgram;
							//migraineProgramCounter += numberProgram.length();
							// 
							// Needs to be placed after since we're shifting
							// UNFORTUNATELY
							// we need to rework this all :(
							// Needs to be redone so that the label positions get sorted after main code has been plonked down
							// On the upside, this will mean any label can be branched forward as well as backwards
							// On the downside, the whole resolver code is kinda frickin pointless :/

						}
						labelModeActive = false;
						holdString = "";
					}
					else if (numberModeActive)
					{
						errno = 0;
						char* additionalChars = nullptr;
						int number = strtol(holdString.c_str(), &additionalChars, 10);
						if (errno == 0 && !*additionalChars)
						{
							std::string numberProgram = currentChar == fillTag ? fillChar(number, indexIncrement) : generateNumber(number);
							migraineProgram += numberProgram;
							migraineProgramCounter += numberProgram.length();
						}
						numberModeActive = false;
						holdString = "";
					}
					else
					{
						holdString += currentChar;
					}
					break;
				}
				default:
					holdString += currentChar;
					break;
				}
			}
		}

		return blurb + mainJump + migraineProgram;
	}

	std::string cetamol::parseFile(const std::string& filePath)
	{
		std::string migraineFilePath = convertFilePath(filePath);

		std::ifstream programFile(filePath);
		std::ofstream migraineFile(migraineFilePath);
		if (!programFile.is_open() || !migraineFile.is_open())
		{
			return "";
		}

		std::string programData, line;
		while (std::getline(programFile, line))
		{
			size_t lineLength = line.length();
			size_t usableChars = 0;
			for (size_t i = 0; i < lineLength; ++i)
			{
				char currentChar = line.at(i);
				if (currentChar == '#') { break; }
				programData += currentChar;
				++usableChars;
			}
			if (AutoDocumentation && usableChars > 0)
			{
				programData += '\n';
			}
		}
		programFile.close();

		std::string migraineProgram = generateMigraine(programData);
		migraineFile.write(migraineProgram.c_str(), migraineProgram.length());
		migraineFile.close();

		return migraineFilePath;
	}

	cetamol::cetamol() : labelModeActive{ false }, numberModeActive{ false }
	{
		gotoBoilerPlate = resetFunctionIndex;
		gotoBoilerPlate += { swapRegister, indexIncrement, indexIncrement, passZeroFunction, indexIncrement, passZeroFunction };
		gotoBoilerPlate += fillChar(38, indexIncrement) + pipeFunction;

		stackPushBoilerPlate = resetFunctionIndex;
		stackPushBoilerPlate += fillChar(40, indexIncrement) + pipeFunction;
		stackPushBoilerPlate += resetFunctionIndex;

		stackPopBoilerPlate = resetFunctionIndex;
		stackPopBoilerPlate += fillChar(42, indexIncrement) + passZeroFunction;
		stackPopBoilerPlate += resetFunctionIndex;
	}
}