#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ranges>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{};
	vector<vector<int>> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.k;

		char elm{};
		for ( int i{}; i < p.n; ++i ) {
			p.v.push_back( {} );
			for ( int j{}; j < p.k; ++j ) {
				is >> elm;
				p.v[i].push_back( atoi( &elm ));
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

		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "n: {} | m: {}\n", ts.param.n, ts.param.k );

		out = format_to( out, " {:4} | {}\n", "", "Map");
		for ( const auto& v : ts.param.v ) {
		out = format_to( out, " {:4} | ", "" );
			for ( const auto i : v )
				out = format_to( out, "{}", i );
			out = format_to( out, "\n" );
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/5-1.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	cout << "Book's Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

Result MySolution( Param param )
{
	Result cnt{};

	constexpr int HOLE{ 0 }, BLOCK{ 1 };

	vector<vector<uint8_t>> frozen(param.n, vector<uint8_t>(param.k, false));

	// dfs 함수
	function<void(int y, int x)> dfs = [&]( int y, int x )
		{
			if ( y < 0 or y >= param.n or x < 0 or x >= param.k ) // y, x 가 범위를 벗어난다면
				return;

			if ( param.v[y][x] == BLOCK )	// 해당 위치가 막혔다면
				return;

			if ( frozen[y][x] == true )
				return;
			
			// 이 위치는 얼은 부분 -> frozen 벡터에 추가
			frozen[y][x] = true;

			// 탐색 시작
			dfs( y, x + 1 );
			dfs( y, x - 1 );
			dfs( y + 1, x );
			dfs( y - 1, x );
		};

	for ( int y : views::iota( 0, param.n ) ) 
		for ( int x : views::iota(0, param.k) )
			if ( frozen[y][x] == false and param.v[y][x] == HOLE ) {
				dfs( y, x );
				++cnt;
			}

	return cnt;
}

Result BookSolution( Param param )
{
	Result cnt{};

	constexpr int HOLE{ 0 }, BLOCK{ 1 };

	// dfs 함수
	function<bool( int y, int x )> dfs = [&]( int y, int x ) -> bool
		{
			if ( y < 0 or y >= param.n or x < 0 or x >= param.k ) // y, x 가 범위를 벗어난다면
				return false;

			if ( param.v[y][x] == HOLE ) {	// 해당 위치가 막혔다면
				param.v[y][x] = BLOCK;

				// 탐색 시작
				dfs( y, x + 1 );
				dfs( y, x - 1 );
				dfs( y + 1, x );
				dfs( y - 1, x );

				return true;
			}

			return false;
		};

	for ( int y : views::iota( 0, param.n ) )
		for ( int x : views::iota( 0, param.k ) )
			if ( dfs( y, x ) )
				++cnt;

	return cnt;
}
