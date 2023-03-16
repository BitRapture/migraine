#pragma once
#include <string>
#include <vector>

namespace br
{

	class migraine
	{
		typedef int(migraine::*migraineFunction)(const int&);

	public:
		char IndexIncrement{ 'e' }, PassZeroFunction{ '!' }, PipeFunction{ '.' }, SwapRegister{ 'E' };

	private:
		size_t programCounter;
		std::vector<migraineFunction> functionList;
		std::vector<int> integerStack;
		unsigned int functionIndex;
		bool currentRegister;
		int integerRegisters[2];

	private:
		void gotoIndex(const int&);
		int number(const int&);
		int add(const int&);
		int subtract(const int&);
		int multiply(const int&);
		int divide(const int&);
		int input(const int&);
		int outputInt(const int&);
		int outputChar(const int&);
		int compareEquals(const int&);
		int compareGreater(const int&);
		int branch(const int&);
		int stackPush(const int&);
		int stackPop(const int&);
		int stackRead(const int&);
		int stackWrite(const int&);


		void buildFunctionList();
		unsigned int getRealFunctionIndex() { return functionIndex / 2; }
		void runFunction(const int&);
		void setFunctionIndex(const unsigned int&);

	public:
		void run(std::string program);
		migraine();
	};
}