#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{}, c{};
	vector<int> indices{};
	vector<vector<pair<int, int>>> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.m >> p.c;

		p.v.reserve( p.m );

		int elm1{}, elm2{}, elm3{};
		p.indices.emplace_back( elm1 );

		for ( int i{}; i < p.m; ++i ) {
			is >> elm2 >> elm3;
			p.v[elm1].emplace_back( pair<int, int>{ elm1, elm2 } );
		}

		return is;
	}
};

struct Result {
	int x{}, y{};

	friend istream& operator>>( istream& is, Result& p )
	{
		is >> p.x >> p.y;
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

template <>
struct std::formatter<TestSet> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx ) {

		string strnum = "[" + to_string( ts.num ) + "]";

		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "N: {} M: {} C: {}\n", ts.param.n, ts.param.m, ts.param.c );

		for ( int n{};  const auto i : ts.param.v ) {
			out = format_to( out, "{:5} | ", "" );
			out = format_to( out, "X: {} Y: {} Z: {}\n", ts.param.indices[n], i.first, i.second );
			++n;
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}, {}", ts.result.x, ts.result.y );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/9-2.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

Result MySolution( Param param )
{

}

Result BookSolution( Param param )
{
}