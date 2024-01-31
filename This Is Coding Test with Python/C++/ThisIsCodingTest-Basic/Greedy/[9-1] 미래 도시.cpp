#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{};
	vector<pair<int, int>> v{};
	int x{}, k{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.k;

		int elm1{}, elm2{};
		for ( int i{}; i < p.k; ++i ) {
			is >> elm1 >> elm2;
			p.v.emplace_back( elm1, elm2 );
		}

		is >> p.x >> p.k;

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

		string strnum = "[" + to_string( ts.num ) + "]";

		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "N: {} K: {}\n", ts.param.n, ts.param.k );

		for ( const auto i : ts.param.v ) {
			out = format_to( out, "{:5} | ", "" );
			out = format_to( out, "W: {} V: {}\n", i.first, i.second );
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/9-1.txt" ) };

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
	const int INF{ int(1e9) };

	vector<vector<int>> v( param.n + 1, vector<int>( param.n + 1, INF ) );

	for ( int i{ 1 }; i <= param.n; ++i )
		v[i][i] = 0;

	for ( int i{}; i < param.k; ++i ) {
		v[param.v[i].first][param.v[i].second] = 1;
		v[param.v[i].second][param.v[i].first] = 1;
	}

	for ( int i{ 1 }; i <= param.n; ++i )
		for ( int j{ 1 }; j <= param.n; ++j )
			for ( int k{ 1 }; k <= param.n; ++k )
				v[i][j] = min( v[i][j], v[i][k] + v[k][j] );

	Result result = v[1][param.k] + v[param.k][param.x];

	return result >= INF ? -1 : result;
}

Result BookSolution( Param param )
{
	return 0;
}