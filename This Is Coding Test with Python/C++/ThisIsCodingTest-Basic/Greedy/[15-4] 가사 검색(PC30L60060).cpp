// https://programmers.co.kr/learn/courses/30/lessons/60060

#include "core.h"

#define CP_NUM "15-4"

#ifdef P15_4
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <string>
#include "CodingTester.h"

using namespace std;

struct Param {
	int wn{}, qn{};
	vector<string> words{}, queries{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.wn;

		string str{};
		for ( int i{}; i < self.wn; ++i )
		{
			is >> str;
			self.words.push_back( str );
		}

		is >> self.qn;

		for ( int i{}; i < self.qn; ++i )
		{
			is >> str;
			self.queries.push_back( str );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<int> v{};

	bool operator==( const Result& other )
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
		auto out = format_to( ctx.out(), "" );

		for ( int i{}; i < ts.n; ++i )
			out = format_to( out, "{} ", ts.v[i] );

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

		// Parameter Line
		string title{"word"};
		out = format_to( out, "\n{:^6}| ", title );
		for ( int i{}; i < ts.param.wn; ++i )
		{
			out = format_to( out, "{} ", ts.param.words[i] );
		}

		title = "query";
		out = format_to( out, "\n{:^6}| ", title );
		for ( int i{}; i < ts.param.qn; ++i )
		{
			out = format_to( out, "{} ", ts.param.queries[i] );
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
	// Start coding here


	return 0;
}

#endif SUBMIT
#endif