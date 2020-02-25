//
// Created by jin on 2/25/20.
//

#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include <gmpxx.h>
#include <sstream>
#include "IOperand.h"
#include <iomanip>

namespace avm {
	template<typename T>
	class Operand : public IOperand {
	public:
		Operand(std::string const &val, eOperandType type);
		Operand(Operand const &rhs) = default;
		~Operand() override  = default;

		Operand &operator=(Operand const &rhs) = default;

		IOperand const *operator+(IOperand const & rhs ) const override;
		IOperand const *operator-(IOperand const & rhs ) const override;
		IOperand const *operator*(IOperand const & rhs ) const override;
		IOperand const *operator/(IOperand const & rhs ) const override;
		IOperand const *operator%(IOperand const & rhs ) const override;

		int getPrecision() const override;
		eOperandType getType() const override;
		std::string const & toString() const override;

	private:
		IOperand const * create_type(std::string const &s, eOperandType type) const;

	private:
		T				_typeVal;
		eOperandType	_opType;
		std::string		_strVal;
	};

	template <typename T>
	IOperand const * Operand<T>::create_type(std::string const &s, avm::eOperandType type) const {
		IOperand *result = nullptr;
		switch (type) {
			case Int8:
				result = new Operand<int8_t>(s, type);
				break;
			case Int16:
				result = new Operand<int16_t>(s, type);
				break;
			case Int32:
				result = new Operand<int32_t>(s, type);
				break;
			case Float:
				result = new Operand<float>(s, type);
				break;
			default:
				result = new Operand<double>(s, type);
				break;
		}
		return result;
	}

	template <typename T>
	Operand<T>::Operand(std::string const &val, avm::eOperandType type): _opType(type) {
		auto ld_val = std::stold(val);
		auto edge_val = std::numeric_limits<T>::max();
		if (ld_val > edge_val) throw std::string("Overflow");
		edge_val = type < Float ? std::numeric_limits<T>::min(): -edge_val;
		if (ld_val < edge_val) throw std::string("Underflow");
		if (type < Float) {
			_typeVal = std::stoll(val);
			_strVal = std::to_string(_typeVal);
		} else {
			_typeVal = std::stod(val);
			std::ostringstream stream;
			stream << std::setprecision(type == Float ? 7 : 16) << _typeVal;
			_strVal = stream.str();
		}
	}

	template <typename T>
	IOperand const * Operand<T>::operator+(const avm::IOperand &rhs) const {

	}

	template <typename T>
	IOperand const * Operand<T>::operator-(const avm::IOperand &rhs) const {

	}

	template <typename T>
	IOperand const * Operand<T>::operator*(const avm::IOperand &rhs) const {

	}

	template <typename T>
	IOperand const * Operand<T>::operator/(const avm::IOperand &rhs) const {

	}

	template <typename T>
	IOperand const * Operand<T>::operator%(const avm::IOperand &rhs) const {

	}

	template <typename T>
	int Operand<T>::getPrecision() const {
		if (_opType < Float) return 0;
		return _opType == Float ? 7 : 16;
	}

	template <typename T>
	eOperandType Operand<T>::getType() const {
		return _opType;
	}

	template <typename T>
	std::string const & Operand<T>::toString() const {
		return _strVal;
	}
}
#endif //AVM_OPERAND_H
