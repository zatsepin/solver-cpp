#ifndef DESK_H
#define DESK_H

#include <engine/cell.hpp>
#include <engine/defs.hpp>
#include <vector>

namespace solver
{

namespace engine
{

class Desk
{
public:
	typedef ulong SizeType;

	Desk();

	Desk( SizeType size );

	~Desk();

	Cell::ValueType getCellValue( SizeType row, SizeType column ) const;

	const Cell::ValueArrayType& getCellPossibleValues( SizeType row, SizeType column ) const;

	void setCellValue( SizeType row, SizeType column, Cell::ValueType value );

	SizeType size() const;

private:
	void checkBoundaries( SizeType row, SizeType column ) const;

	SizeType size_;

	Cell* cells_;
};

} // namespace engine

} // namespace solver

#endif // DESK_H