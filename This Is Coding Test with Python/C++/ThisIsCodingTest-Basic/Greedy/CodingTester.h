#pragma once

#include <vector>
#include <fstream>
#include <filesystem>
#include <functional>
#include <iostream>
#include <format>
#include <string>

template<class Param, class Result>
bool TestSolution( std::function<Result( Param& )> solution, Param test, Result valid )
{
	return valid == solution( test );
}

template<class T>
inline std::vector<T> ReadTestFile( std::filesystem::path path )
{
	std::ifstream is( path );

	//int c;
	//while ( is >> c )
	//	std::cout << c << " ";
	//is.seekg( 0, std::ios::beg );

	std::vector<T> elms{};
	T elm{};

	while ( is >> elm )
		elms.emplace_back( elm );

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