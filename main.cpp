#include <iostream>
#include "include/Operand.h"

int main() {
	avm::Operand<int8_t> a("45", avm::Int8);
	avm::Operand<float > b("4.5", avm::Float);
	const avm::IOperand *c = a+b;


	std::cout << c->toString() << std::endl;
	return 0;
}