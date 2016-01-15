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

	/// @brief Ctor
	Cell();

	/// @brief Ctor
	/// @param value Cell value
	Cell( ValueType value );

	/// @brief Get cell value
	/// @returns Current cell value. 0 if cell value is undefined.
	ValueType get() const;

	/// @brief Set a new cell value
	/// @param value Value to be set. If cell value is needed to be unset then parameter must be 0.
	void set( ValueType value );

private:
	void fillPossibleValue();

	ValueType value_;

	std::set<ValueType> possibleValues_;
};

} // namespace engine

} // namespace solver

#endif // CELL_H