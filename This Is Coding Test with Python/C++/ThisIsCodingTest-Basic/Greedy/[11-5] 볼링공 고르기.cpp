#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.m;
		int elm{};

		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v.emplace_back( elm );
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
		out = format_to( out, "N: {} M: {}", ts.param.n, ts.param.m );

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
		for ( int i : ts.param.v )
			out = format_to( out, "{} ", i );

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/11-5.txt" ) };

	cout << "My Solution : Greedy ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << endl;
	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

/*
 풀이:
 1. 중복되는 무게를 집합으로 모읍니다. 
	예) [1, 3, 2, 3, 2] -> [1], [2, 2], [3, 3]

 2. 모든 집합의 수 = k
	각 집합의 크기 =  n_1 ... n_k
	볼링공을 고르는 경우의 수 = x
	라고 했을 때,
	
	∑(1 <= i < j <= k)n_i * n_j = x

	라고 식을 세워볼 수 있습니다.

	예) ∑(1 <= i < j <= 3)n_i * n_j
		= n_1 * n_2 + n_1 * n_3 + n_2 * n_3
		= 1 * 2 + 1 * 2 + 2 * 2
		= 8
*/

Result MySolution( Param param )
{
	Result result{};
	vector<int> cons_nums{};

	sort( param.v.begin(), param.v.end() );	// 중복되는 번호의 집합을 구하기 위해 정렬

	int weight{};

	// 중복되는 무게들의 집합을 구한다. 
	// 예)[1, 3, 2, 3, 2] ->[1], [2, 2], [3, 3]
	for ( int w : param.v ) {
		if ( weight != w ) {
			weight = w;
			cons_nums.emplace_back( 0 );
		}
		++cons_nums.back();
	}

	// ∑(1 <= i < j <= k)n_i * n_j
	// 위 식을 코드로 풀어쓴다.
	for ( int i{}; i < cons_nums.size(); ++i ) {
		for ( int j{ i + 1 }; j < cons_nums.size(); ++j ) {
			result += cons_nums[i] * cons_nums[j];
		}
	}

	return result;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}