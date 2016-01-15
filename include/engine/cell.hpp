#ifndef CELL_H
#define CELL_H

#include <set>

namespace solver
{

namespace engine
{

class Cell
{
public:
	typedef unsigned long ValueType;

	typedef std::set< ValueType > ValueArrayType;

	/// @brief Ctor
	Cell();

	/// @brief Get cell value
	/// @returns Current cell value. 0 if cell value is undefined.
	ValueType getValue() const;

	/// @brief Set a new cell value
	/// @param value Value to be set. If cell value is needed to be unset then parameter must be 0.
	void setValue( ValueType value );

	/// @brief Get cell possible values
	/// @returns Current cell possible values array.
	const ValueArrayType& getPossibleValues() const;

private:
	void fillPossibleValue();

	ValueType value_;

	ValueArrayType possibleValues_;
};

} // namespace engine

} // namespace solver

#endif // CELL_H