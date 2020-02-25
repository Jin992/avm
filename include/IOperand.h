//
// Created by jin on 2/25/20.
//

#ifndef AVM_IOPERAND_H
#define AVM_IOPERAND_H

#include <string>

namespace avm {

	enum	eOperandType {
		Int8,
		Int16,
		Int32,
		Float,
		Double,
		Size_Op
	};

	class IOperand {
	public:
		virtual int					getPrecision( void ) const = 0; //Precision of the type of the instance
		virtual eOperandType		getType(void) const = 0;

		virtual IOperand const *	operator+(IOperand const & rhs) const = 0; // Sum
		virtual IOperand const *	operator-(IOperand const & rhs) const = 0; // Difference
		virtual IOperand const *	operator*(IOperand const & rhs) const = 0; // Product
		virtual IOperand const *	operator/(IOperand const & rhs) const = 0; // Quotient
		virtual IOperand const *	operator%(IOperand const & rhs) const = 0; // Modulo

		virtual std::string const &	toString( void ) const = 0; // string representation of the instance

		virtual ~IOperand( void ){}
	};
}
#endif //AVM_IOPERAND_H
