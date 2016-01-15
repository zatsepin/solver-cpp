#include <engine/cell.hpp>
#include <engine/defs.hpp>
#include <stdexcept>

namespace solver
{

namespace engine
{

namespace
{
	const Cell::ValueType defaultPossibleValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
}

Cell::Cell()
	: value_( constants::DEFAULT_CELL_VALUE )
	, possibleValues_( std::begin( defaultPossibleValues ), std::end( defaultPossibleValues ) )
{
}

void fillPossibleValue()
{

}

Cell::ValueType Cell::getValue() const
{
	return value_;
}

void Cell::set( ValueType value )
{
	/// @todo: check value is placed in possible values for cell
	if( value == constants::DEFAULT_CELL_VALUE || ( value >= constants::MIN_CELL_VALUE && value <= constants::MAX_CELL_VALUE ) )
		value_ = value;
	else
		throw std::out_of_range( "cell value is out of range" );
}

} // namespace engine

} // namespace solver