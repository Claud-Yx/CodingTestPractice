// https://school.programmers.co.kr/learn/courses/30/lessons/42889

#include "core.h"

#define CP_NUM "14-3"

#ifdef P14_3
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	int s{};
	vector<int> stages{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.s;

		int num{};
		for ( int i{}; i < self.s; ++i )
		{
			is >> num;
			self.stages.push_back( num );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<int> v{};

	bool operator==(const Result& other)
	{
		if ( n != other.n )
			return false;

		if ( v != other.v )
			return false;
		return true;
	}

	friend istream& operator>>( istream& is, Result& self )
	{
		is >> self.n;

		int num{};
		for ( int i{}; i < self.n; ++i )
		{
			is >> num;
			self.v.push_back( num );
		}

		return is;
	}
};

struct TestSet {
	int num{};
	Param param{};
	Result result{};

	TestSet() = default;
	TestSet( Param p, Result r ) {
		TestSet();
		param = p;
		result = r;
	}
	friend istream& operator>>( istream& is, TestSet& t )
	{
		is >> t.param;
		is >> t.result;

		return is;
	}
};

// Only Result Formmater
template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "{}", "");

		for ( int i{}; i < ts.n; ++i )
		{
			out = format_to( out, "{} ", ts.v[i] );
		}

		return out;
	}
};

template <>
struct std::formatter<TestSet> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx ) {

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );
		out = format_to( out, "n: {} | s: {}", ts.param.n, ts.param.s );

		// Parameter Line
		out = format_to( out, "\n{:^6}| ", "" );
		for ( int i{}; i < ts.param.s; ++i )
		{
			out = format_to( out, "{} ", ts.param.stages[i] );
		}

		// Result Line
		out = format_to( out, "\n{:^6}| ", "" );
		out = format_to( out, "\n{:^6}| Result: {}", "", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice " << CP_NUM << " =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/" + string( CP_NUM ) + ".txt" ) };

	cout << "My Solution =========================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << "\nBook's Solution =========================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

/*
 풀이
*/


Result MySolution( Param param )
{
	Result result{};
	return result;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}
#endif VSTOOL

// For submit

#ifdef SUBMIT

#include <iostream>

using namespace std;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP
		// Start coding here

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif