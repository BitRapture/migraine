#include "cetamol.h"
#include <algorithm>
#include <fstream>
#include <vector>

namespace br
{

	bool cetamol::assert(bool condition, const std::string errorMessage, std::string& content)
	{
		if (!condition)
		{
			content += "# Error! ";
			content += errorMessage + '\n';
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

	std::string cetamol::generateFullNumber(int number, int padding)
	{
		std::string numberProgram;
		std::vector<int> digits = getDigits(number);
		long digitsLength = digits.size();
		long digitsLeft = digitsLength - 1;

		if (digitsLength < padding)
		{
			digitsLeft = padding - digitsLength;
			for (long i = 0; i < digitsLeft; ++i)
			{
				digits.push_back(0);
			}
			digitsLength = padding;
		}

		std::string lastProgram;
		for (long i = digitsLength - 1; i > -1; --i)
		{
			numberProgram += resetFunctionIndex;
			int currentDigit = digits.at(i);
			int digitsRemaining = 9 - currentDigit;
			numberProgram += fillChar(currentDigit * 2, indexIncrement);
			if (i >= digitsLength - digitsLeft)
			{
				numberProgram += passZeroFunction;
			}
			else
			{
				numberProgram += pipeFunction;
			}
			lastProgram = fillChar(digitsRemaining * 2, indexIncrement);
			numberProgram += lastProgram;
		}

		return numberProgram;
	}

	std::string cetamol::generateFixedNumber(int number)
	{
		return generateFullNumber(number, FixedDigitSize);
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

	std::string cetamol::generateJump(long& address)
	{
		std::string jumpProgram;
		jumpProgram = generateFixedNumber(address) + gotoBoilerPlate + '\n';
		return jumpProgram;
	}

	std::string cetamol::generateMigraine(const std::string& cetamolProgramData)
	{
		std::vector<std::string> migraineProgram;
		migraineProgram.push_back("");
		std::string blurb = "# This migraine program was generated from a .mol file!\n# https://github.com/bitrapture/migraine\n";
		blurb += "# Cetamol v" + std::to_string(generatorVersionMajor) + "." + std::to_string(generatorVersionMinor) + "\n\n";

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
					migraineProgram.back() += resetFunctionIndex;
					migraineProgram.back() += gotoBoilerPlate;
					migraineProgramCounter += gotoBoilerPlate.length() + 2;
					break;
				case stackPushTag:
					migraineProgram.back() += stackPushBoilerPlate;
					migraineProgramCounter += stackPushBoilerPlate.length();
					break;
				case stackPopTag:
					migraineProgram.back() += stackPopBoilerPlate;
					migraineProgramCounter += stackPopBoilerPlate.length();
					break;
				case branchReturnTag:
					migraineProgram.back() += branchReturnBoilerPlate;
					migraineProgramCounter += branchReturnBoilerPlate.length();
					break;
				case callStackPop:
					migraineProgram.back() += callStackPopBoilerPlate;
					migraineProgramCounter += callStackPopBoilerPlate.length();
					break;
				case indexIncrement:
				case passZeroFunction:
				case pipeFunction:
				case swapRegister:
					++migraineProgramCounter;
				case '\n':
					migraineProgram.back() += currentChar;
					break;
				}
			}
			else
			{
				switch (currentChar)
				{
				case labelTag:
					if (labelModeActive)
					{
						bool labelDefined = holdString.at(0) == labelDefineTag;
						holdString = labelDefined ? holdString.substr(1) : holdString;

						bool labelExists = labelTable.find(holdString) != labelTable.end();
						if (!labelExists) { labelTable[holdString] = -1; }

						if (labelDefined)
						{
							migraineProgram.back() += AutoDocumentation ? "\n# " + holdString + " define" : "\n";
							labelTable[holdString] = migraineProgramCounter + 1;
						}
						else
						{
							size_t fixedSize = fixedNumberLength + gotoBoilerPlate.length();

							address_information entry;
							entry.labelAddress = &labelTable[holdString];
							entry.programAddress = migraineProgramCounter;
							entry.gotoProgram = labelTable[holdString] > -1 ? generateJump(labelTable[holdString]) : fillChar(fixedSize, placeHolder);
							addressInfo.push_back(entry);

							migraineProgramCounter += fixedSize;
							migraineProgram.push_back("");
						}

						labelModeActive = false;
						holdString = "";
					}
				case fillTag:
				case numberTag:
					if (numberModeActive)
					{
						bool isFixed = holdString.at(0) == fixedTag;
						holdString = isFixed ? holdString.substr(1) : holdString;

						errno = 0;
						char* additionalChars = nullptr;
						int number = strtol(holdString.c_str(), &additionalChars, 10);
						if (errno == 0 && !*additionalChars)
						{
							std::string numberProgram = currentChar == fillTag ? fillChar(number, indexIncrement) : isFixed ? generateFixedNumber(number) : generateNumber(number);
							migraineProgram.back() += numberProgram;
							migraineProgramCounter += numberProgram.length();
						}
						numberModeActive = false;
						holdString = "";
					}
					break;
				}

				if (numberModeActive || labelModeActive)
				{
					holdString += currentChar;
				}
			}
		}

		std::sort(addressInfo.begin(), addressInfo.end(), [](address_information& a, address_information& b) {
			return a.programAddress < b.programAddress;
		});

		size_t programIt = 0;
		std::string finalProgram;
		for (auto info : addressInfo)
		{
			if (info.gotoProgram.at(0) == placeHolder && *info.labelAddress > -1)
			{
				info.gotoProgram = generateJump(*info.labelAddress);
			}
			finalProgram += migraineProgram.at(programIt) + info.gotoProgram;
			programIt++;
		}
		finalProgram += migraineProgram.back();

		std::string errorLogging;
		assert(!labelModeActive, "Label define never closed", errorLogging);
		assert(!numberModeActive, "Number define never closed", errorLogging);


		return errorLogging + blurb + finalProgram;
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
		stackPushBoilerPlate += fillChar(44, indexIncrement) + pipeFunction;
		stackPushBoilerPlate += resetFunctionIndex;

		stackPopBoilerPlate = resetFunctionIndex;
		stackPopBoilerPlate += fillChar(46, indexIncrement) + passZeroFunction;
		stackPopBoilerPlate += resetFunctionIndex;

		branchReturnBoilerPlate = resetFunctionIndex;
		branchReturnBoilerPlate += fillChar(40, indexIncrement) + passZeroFunction;
		branchReturnBoilerPlate += resetFunctionIndex;

		callStackPopBoilerPlate = resetFunctionIndex;
		callStackPopBoilerPlate += fillChar(42, indexIncrement) + passZeroFunction;
		callStackPopBoilerPlate += resetFunctionIndex;

		fixedNumberMaximum = (int)pow(10, FixedDigitSize);
	}
}