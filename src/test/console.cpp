#include <engine/desk.hpp>
#include "command.hpp"
#include <iostream>
#include <string>

using namespace solver;
using namespace solver::engine;

int main()
{
	Desk desk;

	std::string input;

	while( true )
	{
		try
		{
			std::cout << "> ";
			getline( std::cin,  input );
			if( !test::executeCommand( input, desk ) )
				break;
		}
		catch( const std::exception& ex )
		{
			std::cout << "error: " << ex.what() << std::endl;
		}
	}

	return 0;
}