#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> v{};
	int k{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n;

		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v.emplace_back( elm );
		}

		is >> p.k;

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
		out = format_to( out, "K: {}", ts.param.k );

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/11-6.txt" ) };

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
  1  2  3
 [3, 1, 2]
 k = 5

  2  3  1
 [1, 2, 3]
 k = 5

  3  1
 [2, 3]
 k = 2

 idx = 0

  1, 3
 [3, 2]

 v[idx] == 1

*/

template<typename T>
struct LessPair2nd {
	bool operator()( const pair<T, T>& lhs, const pair<T, T>& rhs ) {
		return lhs.second < rhs.second;
	}
};

template<typename T>
struct LessPair1st {
	bool operator()( const pair<T, T>& lhs, const pair<T, T>& rhs ) {
		return lhs.first < rhs.first;
	}
};

Result MySolution( Param param )
{
	Result result{};

	vector<pair<int, int>> v;

	for ( int num{ 1 }; auto & i : param.v ) {
		v.emplace_back( num, i );
		++num;
	}

	sort( v.begin(), v.end(), LessPair2nd<int>() );

	int eat_time{};
	for ( int i{}; i < v.size(); ++i ) {
		eat_time = v[i].second;

		if ( eat_time == 0 )
			continue;

		int new_k = param.k - eat_time * ( v.size() - i );
		if ( new_k <= 0 )
			break;

		param.k = new_k;

		for ( int j{ i }; j < v.size(); ++j )
			v[j].second -= eat_time;
	}

	vector<pair<int, int>> last_v{};
	for ( auto& i : v )
		if ( i.second > 0 )
			last_v.emplace_back( i );

	int sum = accumulate( last_v.begin(), last_v.end(), 0, [](int lhs, auto& rhs) {
		return lhs += rhs.second;
	} );

	if ( param.k > 0 and last_v.empty() or sum == param.k )
		result = -1;
	else {

		sort( last_v.begin(), last_v.end(), LessPair1st<int>() );

		auto idx{ param.k % last_v.size() };

		result = last_v[idx].first;
	}

	return result;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}