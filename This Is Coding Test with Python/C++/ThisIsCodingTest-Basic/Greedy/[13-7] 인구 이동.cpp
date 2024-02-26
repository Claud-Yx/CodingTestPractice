// https://www.acmicpc.net/problem/16234

#include "core.h"

#define CP_NUM "13-7"

#ifdef P13_7
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, l{}, r{};
	vector<vector<int>> pop{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.l >> self.r;

		int num{};
		for ( int i{}; i < self.n; ++i )
		{
			self.pop.push_back( {} );
			for ( int j{}; j < self.n; ++j )
			{
				is >> num;
				self.pop.back().push_back( num );
			}
		}

		return is;
	}
};

using Result = int;

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
		out = format_to( out, "N: {} | L: {} | R: {}", ts.param.n, ts.param.l, ts.param.r );

		// Parameter Line
		out = format_to( out, "\n{:^6}| ", "" );

		// Map
		string title{ "pop" };
		for ( const auto& rows : ts.param.pop )
		{
			out = format_to( out, "\n{:^6}| ", title );
			title.clear();

			for ( const auto& num : rows )
			{
				out = format_to( out, "{} ", num );
			}
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