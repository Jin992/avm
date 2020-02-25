//
// Created by jin on 2/25/20.
//

#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include <gmpxx.h>
#include <sstream>
#include "IOperand.h"
#include <iomanip>

#define IS_INTEGER(type_a, type_b) type_a < avm::Float && type_b < avm::Float

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
		T				_val;
		eOperandType	_type;
		std::string		_str;
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
	Operand<T>::Operand(std::string const &val, avm::eOperandType type): _type(type) {
		auto ld_val = std::stold(val);
		auto edge_val = std::numeric_limits<T>::max();
		if (ld_val > edge_val) throw std::string("Overflow");
		edge_val = type < Float ? std::numeric_limits<T>::min(): -edge_val;
		if (ld_val < edge_val) throw std::string("Underflow");
		if (type < Float) {
			_val = std::stoll(val);
			_str = std::to_string(_val);
		} else {
			_val = std::stod(val);
			std::ostringstream stream;
			stream << std::setprecision(type == Float ? 7 : 16) << _val;
			_str = stream.str();
		}
	}

	template <typename T>
	IOperand const * Operand<T>::operator+(const avm::IOperand &rhs) const {
		if (IS_INTEGER(_type, rhs.getType()))
			return create_type(std::to_string(_val +  std::stoll(rhs.toString())), rhs.getType());
		return create_type(std::to_string(_val + std::stod(rhs.toString())), rhs.getType()); // maybe static_cast<long double> needed but not sure
	}

	template <typename T>
	IOperand const * Operand<T>::operator-(const avm::IOperand &rhs) const {
		if (IS_INTEGER(_type, rhs.getType()))
			return create_type(std::to_string(_val - std::stoll(rhs.toString())), rhs.getType());
		return create_type(std::to_string(_val - std::stod(rhs.toString())), rhs.getType()); // maybe static_cast<long double> needed but not sure
	}

	template <typename T>
	IOperand const * Operand<T>::operator*(const avm::IOperand &rhs) const {
		if (IS_INTEGER(_type, rhs.getType()))
			return create_type(std::to_string(_type * std::stoll(rhs.toString())), rhs.getType());
	}

	template <typename T>
	IOperand const * Operand<T>::operator/(const avm::IOperand &rhs) const {
		//if (dynamic_cast<Operand>(rhs)._typeVal == 0) throw std::string("divByZero");
		if (IS_INTEGER(_type, rhs.getType())){}
	}

	template <typename T>
	IOperand const * Operand<T>::operator%(const avm::IOperand &rhs) const {
		//if (dynamic_cast<Operand>(rhs)._typeVal == 0) throw std::string("divByZero");
		if (IS_INTEGER(_type, rhs.getType())){}
	}

	template <typename T>
	int Operand<T>::getPrecision() const {
		if (_type < Float) return 0;
		return _type == Float ? 7 : 16;
	}

	template <typename T>
	eOperandType Operand<T>::getType() const {
		return _type;
	}

	template <typename T>
	std::string const & Operand<T>::toString() const {
		return _str;
	}
}
#endif //AVM_OPERAND_H
