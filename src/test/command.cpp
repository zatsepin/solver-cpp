#include "command.hpp"
#include <engine/desk.hpp>
#include <engine/cell.hpp>
#include <engine/defs.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

namespace solver
{

namespace test
{

void PrintCommand::execute( std::ostream& os )
{
	engine::Desk::SizeType size = desk_.size();
	os << "-------------------------------" << std::endl;
	for( engine::Desk::SizeType row = 0; row < size; ++row )
	{
		os << "|";
		for( engine::Desk::SizeType column = 0; column < size; ++column )
		{
			engine::Cell::ValueType value = desk_.getCellValue( row, column );
			if(value == constants::DEFAULT_CELL_VALUE)
				os << " " << " " << " ";
			else
				os << " " << value << " ";
			if( (column + 1) % 3 == 0 )
				os << "|";
		}
		os << std::endl;
		if( (row + 1) % 3 == 0 )
			os << "-------------------------------" << std::endl;
	}
}

void HelpCommand::execute()
{
	std::cout << "Available commands:" << std::endl;
	std::cout << "  help - print this help" << std::endl;
	std::cout << "  print - print a whole desk" << std::endl;
	std::cout << "  set <row> <column> <value> - assign value to cell" << std::endl;
	std::cout << "  quit - close program" << std::endl;
}

SetValueCommand::SetValueCommand( engine::Desk& desk)
	: desk_( desk )
{
}

void SetValueCommand::execute( engine::Desk::SizeType row,
                               engine::Desk::SizeType column,
                               engine::Cell::ValueType value)
{
	desk_.set( row, column, value );
}


bool executeCommand( const std::string& str, const engine::Desk& desk )
{
	std::vector<std::string> tokens;
	boost::split(tokens, str, boost::is_any_of("\t "));

	if( !tokens.empty() && !tokens[0].empty() )
	{
		std::string& command = tokens[0];

		if( !command.compare( "quit" ) )
			return false;

		else
		if( !command.compare( "help" ) )
			HelpCommand().execute();

		else
		if( !command.compare( "print" ) )
			PrintCommand( desk ).execute( std::cout );

		else
		if( !command.compare( "set" ) )
		{
			if( tokens.size() - 1 < SetValueCommand::ArgumentCount )
				throw std::invalid_argument(" SET command needs 3 arguments ");

			using namespace engine;
			try
			{
				Desk::SizeType row = static_cast< Desk::SizeType >( stoi( tokens[1] ) );
				Desk::SizeType column = static_cast< Desk::SizeType >( stoi( tokens[2] ) );
				Cell::ValueType value = static_cast< Cell::ValueType >( stoi( tokens[3] ) );
				SetValueCommand( const_cast< Desk& >( desk ) ).execute( --row, --column, value );
			}
			catch( const std::invalid_argument& )
			{
				throw std::invalid_argument( "SET command parameter ill-formed" );
			}
		}

		else
			throw std::runtime_error( "unrecognized command" );
	}
	return true;
}

} // namespace test

} // namespace solver


