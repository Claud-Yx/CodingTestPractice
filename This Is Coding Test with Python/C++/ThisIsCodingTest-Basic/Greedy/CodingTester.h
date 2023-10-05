#pragma once

#include <vector>
#include <fstream>
#include <filesystem>
#include <functional>
#include <iostream>
#include <format>
#include <string>
#include <Windows.h>

template<class Param, class Result>
bool TestSolution( std::function<Result( Param& )> solution, Param test, Result valid )
{
	return valid == solution( test );
}

template<class T>
inline std::vector<T> ReadTestFile( std::filesystem::path path )
{
	std::ifstream is( path );

	if ( not is ) {
		std::cerr << "Read Failed: " << path << std::endl;
		exit( -1 );
	}

	std::vector<T> elms{};

	while ( true ) {
		T elm{};

		if ( !( is >> elm ) )
			break;

		elms.emplace_back( std::move(elm) );
	}

	return elms;
}

template<class Param, class Result>
void OutputResult( Param test, Result expect, Result valid, bool result )
{
	static unsigned int num{ 0 };

	std::string numstr{ "[" + std::to_string( ++num ) +"]" };

		std::cout << std::format( " {:>4} | {:20} | {:10} | {:10} | {:5}\n", numstr, test, expect, valid, result );
}

template<class Param, class Result>
void OutputTestSolution( std::function<Result( Param& )> solution, Param test, Result valid )
{
	OutputResult<Param, Result>(
		test, solution( test ), valid,
		TestSolution<Param, Result>( solution, test, valid )
	);
}

template<class Param, class Result, class TestSet>
void OutputTestSolution( std::function<Result( Param& )> solution, int num, Param test, Result valid )
{
	TestSet test_set{ test, solution( test ) };
	test_set.num = num;

	bool result = TestSolution<Param, Result>( solution, test, valid );

	std::cout << std::format( "{}\n", test_set );
	std::cout << std::format( "{:=^80}\n", "");
	std::cout << std::format( " Valid Result: {} | ", valid );
	
	if ( result )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x2);
	else
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x4);
	
	std::cout << std::format( "{}\n", result );
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0xf);
}