// --Coding Test Address Here--

#include "core.h"

#define CP_NUM "17-2"

#ifdef P17_2
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <array>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<array<int, 2>> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.m;

		int tmp1{}, tmp2{};

		for ( int i{}; i < self.m; ++i )
		{
			is >> tmp1 >> tmp2;
			self.v.push_back( {tmp1, tmp2} );
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
		auto out = format_to( ctx.out(), "{}", ts );
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
		out = format_to( out, "n: {} | m: {}", ts.param.n, ts.param.m );
		out = format_to( out, "\n{:^6}| ", "" );

		for ( int i{}; i < ts.param.m; ++i )
		{
			out = format_to( out, "\n{:^6}| {} -> {}", "", ts.param.v[i][0], ts.param.v[i][1]);
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
 ????
*/

#undef max

Result MySolution( Param param )
{
	Result result{};

	vector<vector<int>> dt{};

	int n = param.n, m = param.m;
	auto v = param.v;

	for ( int i{}; i < m; ++i )
	{
		dt.push_back( {} );
		for ( int j{}; j < m; ++j )
		{
			if ( i == j )
				dt.back().push_back( 0 );
			else
				dt.back().push_back( n );
		}
	}

	for ( const auto& elm : v )
	{
		dt[elm[0] - 1][elm[1] - 1] = 1;
	}

	// 플로이드 워셜로 위아래 학생 수 찾기
	for ( int k{}; k < n; ++k )
	{
		for ( int i{}; i < n; ++i )
		{
			for ( int j{}; j < n; ++j )
			{
				dt[i][j] = min<int>( { dt[i][j], dt[i][k] + dt[k][j] } );
			}
		}
	}

	for ( int i{}; i < n; ++i )
	{
		int cnt{};	// 자신을 기준으로 순위를 알 수 있는 학생 수

		for ( int j{}; j < n; ++j )
		{
			if ( dt[i][j] < n || dt[j][i] < n )	// 도달 가능 하다면
				cnt += 1;
		}

		if ( cnt == n )		// 학생수와 내 위아래 학생 수가 같다면
			result += 1;	// 결과에 추가
	}

	/*
	   1   2   3   4   5   6
	1  0               1	 
	2      0 	  -1 	 
	3          0   1 	 	 
	4      1  -1   0	 	 
	5 -1               0	 
	6                      0
	
	*/



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