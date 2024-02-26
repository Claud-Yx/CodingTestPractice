// https://www.acmicpc.net/problem/18428

#include "core.h"

#define CP_NUM "13-6"

#ifdef P13_6
#ifdef VSTOOL

#include <iostream>
#include <string>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<vector<char>> map{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		char c{};
		for ( int i{}; i < self.n; ++i )
		{
			self.map.push_back( {} );
			for ( int j{}; j < self.n; ++j )
			{
				is >> c;
				self.map.back().push_back( c );
			}
		}

		return is;
	}
};

using Result = string;

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

template <>
struct std::formatter<TestSet> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx ) {

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );
		out = format_to( out, "n: {}", ts.param.n );

		// Map
		string title{ "map" };
		out = format_to( out, "\n{:^6}| ", "" );
		for ( const auto& rows : ts.param.map )
		{
			out = format_to( out, "\n{:^6}| ", title );
			title.clear();

			for ( const auto& c : rows )
			{
				out = format_to( out, "{} ", c );
			}
		}

		// Parameter Line
		out = format_to( out, "\n{:^6}| ", "" );
		out = format_to( out, "\n{:^6}| ", "" );

		// Result Line
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice " << CP_NUM << " =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/" + string(CP_NUM) + ".txt" ) };

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

// 제출용

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

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif