#include <engine/desk.hpp>
#include <engine/cell.hpp>
#include <engine/defs.hpp>
#include <stdexcept>

namespace solver
{

namespace engine
{

using namespace constants;

Desk::Desk()
	: Desk( DEFAULT_DESK_SIZE )
{
}

Desk::Desk( SizeType size )
	: size_( size )
	, cells_( new Cell[ size_ * size_ ] )
{
}

Desk::~Desk()
{
	delete [] cells_;
}

void Desk::checkBoundaries( SizeType row, SizeType column ) const
{
	if( row >= size_ )
		throw std::out_of_range("row number is out of range");
	if( column >= size_ )
		throw std::out_of_range("column number is out of range");
}

Cell::ValueType Desk::getCellValue( SizeType row, SizeType column ) const
{
	checkBoundaries( row, column );
	return cells_[ row * size_ + column ].getValue();
}

const Cell::ValueArrayType& Desk::getCellPossibleValues( SizeType row, SizeType column ) const
{
	checkBoundaries( row, column );
	return cells_[ row * size_ + column ].getPossibleValues();
}

void Desk::setCellValue( SizeType row, SizeType column, Cell::ValueType value )
{
	checkBoundaries( row, column );
	cells_[ row * size_ + column ].setValue( value );
}

Desk::SizeType Desk::size() const
{
	return size_;
}

} // namespace engine

} // namespace solver