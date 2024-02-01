#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, weak_n, dist_n{};
	vector<int> weak{};
	vector<int> dist{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.weak_n;

		int num{};
		for ( int i{}; i < self.weak_n; ++i ) {
			is >> num;
			self.weak.emplace_back( num );
		}

		is >> self.dist_n;

		for ( int i{}; i < self.dist_n; ++i ) {
			is >> num;
			self.dist.emplace_back( num );
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

		out = format_to( out, "n: {}", ts.param.n );

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | [ ", "Weak" );
		for ( int i{}; const auto & elm : ts.param.weak ) {
			out = format_to( out, "{} ", elm );
		}

		out = format_to( out, "]\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | [ ", "Dist" );
		for ( int i{}; const auto & elm : ts.param.dist ) {
			out = format_to( out, "{} ", elm );
		}

		out = format_to( out, "]\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-8.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

/*
풀이
친구들은 항상 약한 지점부터 시작하여 돌아야 최대 효율을 낼 것이다.
그러므로 약한 지점부터 점검을 시작하며, 모든 약한 지점을 기준으로
시계/반시계 방향으로 점검하며 투입 수가 가장 적은 경우를 찾는다.

*/

void CheckWall( int n, vector<int>& weak, int dist, int start_weak, bool clockwise )
{
	if ( clockwise ) {
		reverse( weak.begin(), weak.end() );
	}

	// 순환 회전
	for ( int i{}; i < weak.size(); ++i ) {
		if ( weak.back() == start_weak )
			break;
		rotate( weak.rbegin(), weak.rbegin() + 1, weak.rend() );
	}

	for ( int i{}; i < dist; ++i ) {
		if ( weak.empty() )
			break;

		if ( weak.back() == start_weak )
			weak.pop_back();
		
		if ( clockwise ) {
			++start_weak;
			if ( start_weak == n )
				start_weak = 0;
		}
		else {
			--start_weak;
			if ( start_weak < 0 )
				start_weak = n - 1;
		}
	}
}

int dfs( int n, vector<int>& weak, vector<int> dist, int dist_idx )
{
	int result{};
	for ( int i{}; i < weak.size(); ++i ) {
		vector<int> weak_tmp( weak );
		CheckWall( n, weak_tmp, dist[dist_idx], weak[i], true );

		if ( weak_tmp.empty() )
			return 1;

		else if ( not weak_tmp.empty() and dist_idx + 1 == (int)dist.size() )
			return -1;

		else if ( not weak_tmp.empty() and dist_idx + 1 < (int)dist.size() )
			result = dfs( n, weak_tmp, dist, ++dist_idx );
	}
}

Result MySolution( Param param )
{
	Result result{};

	int n{ param.n };
	vector<int> weak( param.weak );
	vector<int> dist( param.dist );

	sort( dist.begin(), dist.end(), greater() );

	for ( int i{}; i < dist.size(); ++i ) {
		vector<int> weak_tmp( weak );


	}

	return result;
}

Result BookSolution( Param param )
{
	return Result{};
}
