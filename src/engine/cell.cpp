#include <engine/cell.hpp>
#include <engine/defs.hpp>
#include <stdexcept>

namespace solver
{

namespace engine
{

namespace
{
	const Cell::ValueType DEFAULT_CELL_VALUE = 0;
}

Cell::Cell()
	: value_( DEFAULT_CELL_VALUE )
{}

Cell::Cell( Cell::ValueType value )
	: value_( value )
{}

void fillPossibleValue()
{

}

Cell::ValueType Cell::get() const
{
	return value_;
}

void Cell::set( ValueType value )
{
	/// @todo: check value is placed in possible values for cell
	if( value >= constants::MIN_CELL_VALUE && value <= constants::MAX_CELL_VALUE )
		value_ = value;
	else
		throw std::out_of_range( "cell value is out of range" );
}

} // namespace engine

} // namespace solver