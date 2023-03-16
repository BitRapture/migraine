#include "migraine.h"

#include <iostream>

namespace br
{
	void migraine::gotoIndex(const int& intRegister)
	{
		setFunctionIndex(intRegister);
	}

	int migraine::number(const int& intRegister)
	{
		return (intRegister * 10) + (getRealFunctionIndex() % 10);
	}

	int migraine::add(const int& intRegister)
	{
		return intRegister + integerRegisters[!currentRegister];
	}

	int migraine::subtract(const int& intRegister)
	{
		return intRegister - integerRegisters[!currentRegister];
	}

	int migraine::multiply(const int& intRegister)
	{
		return intRegister * integerRegisters[!currentRegister];
	}

	int migraine::divide(const int& intRegister)
	{
		int value = integerRegisters[!currentRegister];
		return value != 0 ? intRegister / value : 0;
	}

	int migraine::input(const int& intRegister)
	{
		int readValue;
		std::cin >> readValue;
		return readValue;
	}

	int migraine::outputInt(const int& intRegister)
	{
		std::cout << intRegister;
		return intRegister;
	}

	int migraine::outputChar(const int& intRegister)
	{
		std::cout << (char)intRegister;
		return intRegister;
	}

	int migraine::compareEquals(const int& intRegister)
	{
		return intRegister == integerRegisters[!currentRegister];
	}

	int migraine::compareGreater(const int& intRegister)
	{
		return intRegister > integerRegisters[!currentRegister];
	}

	int migraine::branch(const int& intRegister)
	{
		int isBranching = (unsigned)intRegister > 0;
		if (isBranching)
		{
			int newProgramCounter = integerRegisters[!currentRegister];
			programCounter = newProgramCounter;
		}
		return intRegister;
	}

	int migraine::stackPush(const int& intRegister)
	{
		integerStack.push_back(intRegister);
		return intRegister;
	}

	int migraine::stackPop(const int& intRegister)
	{
		int value = 0;
		if (integerStack.size() > 0)
		{
			value = integerStack.back();
			integerStack.pop_back();
		}
		return value;
	}

	int migraine::stackRead(const int& intRegister)
	{
		int value = 0;
		if (intRegister < integerStack.size())
		{
			value = integerStack[intRegister];
		}
		return value;
	}

	int migraine::stackWrite(const int& intRegister)
	{
		if (intRegister < integerStack.size())
		{
			integerStack[intRegister] = integerRegisters[!currentRegister];
		}
		return intRegister;
	}

	void migraine::buildFunctionList()
	{
		for (int i = 0; i < 10; ++i)
		{
			functionList.push_back(&migraine::number);
		}

		functionList.push_back(&migraine::add);				// 10
		functionList.push_back(&migraine::subtract);		
		functionList.push_back(&migraine::multiply);		
		functionList.push_back(&migraine::divide);			

		functionList.push_back(&migraine::input);			// 14
		functionList.push_back(&migraine::outputInt);
		functionList.push_back(&migraine::outputChar);

		functionList.push_back(&migraine::compareEquals);	// 17
		functionList.push_back(&migraine::compareGreater);
		functionList.push_back(&migraine::branch);

		functionList.push_back(&migraine::stackPush);		// 20
		functionList.push_back(&migraine::stackPop);
		functionList.push_back(&migraine::stackRead);
		functionList.push_back(&migraine::stackWrite);

		functionList.shrink_to_fit();
	}

	void migraine::setFunctionIndex(const unsigned int& newIndex)
	{
		functionIndex = newIndex;
		if (getRealFunctionIndex() >= functionList.size())
		{
			functionIndex = 0;
		}
	}

	void migraine::runFunction(const int& intRegister)
	{
		bool isGotoFunction = ((functionIndex + 1) % 2) == 0;

		if (isGotoFunction)
		{
			gotoIndex(intRegister);
		}
		else
		{
			integerRegisters[currentRegister] = (this->*functionList[getRealFunctionIndex()])(intRegister);
		}
	}

	void migraine::run(std::string program)
	{
		size_t programLength = program.length();
		for (programCounter = 0; programCounter < programLength; programCounter++)
		{
			char currentChar = program.at(programCounter);
			
			if (currentChar == IndexIncrement)
			{
				setFunctionIndex(functionIndex + 1);
				continue;
			}

			if (currentChar == SwapRegister)
			{
				currentRegister = !currentRegister;
				continue;
			}

			if (currentChar == PassZeroFunction)
			{
				runFunction(0);
				continue;
			}

			if (currentChar == PipeFunction)
			{
				runFunction(integerRegisters[currentRegister]);
				continue;
			}
		}
	}

	migraine::migraine() : integerRegisters{ 0, 0 }, functionIndex{ 0 }, currentRegister{ 0 }
	{
		buildFunctionList();
		integerStack.reserve(65535);
	}
}