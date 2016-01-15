#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <engine/desk.hpp>
#include <string>
#include <iostream>

namespace solver
{

namespace test
{

class PrintDeskCommand
{
public:
	explicit PrintDeskCommand( const engine::Desk& desk )
		: desk_( desk )
	{}

	void execute( std::ostream& os );

private:
	const engine::Desk& desk_;
};

class PrintCellCommand
{
public:
	explicit PrintCellCommand( const engine::Desk& desk )
		: desk_( desk )
	{}

	void execute( std::ostream& os,
	              engine::Desk::SizeType row,
	              engine::Desk::SizeType column );

private:
	const engine::Desk& desk_;
};

class HelpCommand
{
public:
	HelpCommand()
	{}

	void execute();
};

class SetValueCommand
{
public:
	static const ulong ArgumentCount = 3;

	SetValueCommand( engine::Desk& desk )
		: desk_( desk )
	{}

	void execute( engine::Desk::SizeType row,
	              engine::Desk::SizeType column,
	              engine::Cell::ValueType value);

private:
	engine::Desk& desk_;
};

bool executeCommand( const std::string& str, const engine::Desk& desk );

} // namespace test

} // namespace solver

#endif // COMMAND_HPP