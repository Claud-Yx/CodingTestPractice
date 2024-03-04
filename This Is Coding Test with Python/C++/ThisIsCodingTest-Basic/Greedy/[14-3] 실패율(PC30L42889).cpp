// https://school.programmers.co.kr/learn/courses/30/lessons/42889

#include "core.h"

#define CP_NUM "14-3"

#ifdef P14_3
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	int p{};
	vector<int> stages{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.p;

		int num{};
		for ( int i{}; i < self.p; ++i )
		{
			is >> num;
			self.stages.push_back( num );
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

// Only Result Formmater
template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "{}", "" );

		for ( int i{}; i < ts.n; ++i )
		{
			out = format_to( out, "{} ", ts.v[i] );
		}

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
		out = format_to( out, "n: {} | s: {}", ts.param.n, ts.param.p );

		// Parameter Line
		out = format_to( out, "\n{:^6}| ", "" );
		for ( int i{}; i < ts.param.p; ++i )
		{
			out = format_to( out, "{} ", ts.param.stages[i] );
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
 오름차순 정렬 후 equal_range를 사용해 각 스테이지 실패자의 수를 구한다.
*/

#define VER 2
#if (VER == 1)
Result MySolution( Param param )
{
	Result result{};

	// Input
	int n{ param.n }, p{ param.p };
	vector<int> stages{ param.stages };

	// Var
	vector<pair<int, double>> failure_rates{};

	// Init
	for ( int i{}; i < n + 1; ++i )
	{
		failure_rates.emplace_back( i + 1, 0.0 );
	}

	// Solution 
	ranges::sort( stages );

	auto begin = stages.begin();
	while ( begin != stages.end() )
	{
		auto [first, last] = equal_range( begin, stages.end(), *begin );
		
		auto failure_num = static_cast<double>( distance( first, last ) );
		auto passerby_num = static_cast<double>( distance( first, stages.end() ) );

		failure_rates[(*begin) - 1].second = failure_num / passerby_num;

		begin = last;
	}

	// 모든 스테이지 클리어율을 제외
	failure_rates.pop_back();

	ranges::sort( failure_rates,
		[]( const auto& lhs, const auto& rhs )
		{
			if ( lhs.second == rhs.second )
				return lhs.first < rhs.first;
			return lhs.second > rhs.second;
		}
	);

	// End
	for ( const auto& failure_rate : failure_rates )
	{
		result.v.push_back( failure_rate.first );
	}

	result.n = result.v.size();

	return result;
}

#elif (VER == 2)
Result MySolution( Param param )
{

	// Input
	int n{ param.n }, p{ param.p };
	vector<int> stages{ param.stages };

	// Var
	Result result{};
	vector<double> failure_rates(n, 0.0);

	// Init
	result.v = vector<int>( n );
	ranges::iota( result.v, 1 );

	// Solution 
	ranges::sort( stages );

	auto begin = stages.begin();
	while ( begin != stages.end() and *begin <= n )
	{
		auto [first, last] = equal_range( begin, stages.end(), *begin );

		auto failure_num = static_cast<double>( distance( first, last ) );
		auto passerby_num = static_cast<double>( distance( first, stages.end() ) );

		failure_rates[( *begin ) - 1] = failure_num / passerby_num;

		begin = last;
	}

	ranges::sort( result.v,
		[&]( const auto& lhs, const auto& rhs )
		{
			auto f1{ failure_rates[lhs - 1] }, f2{ failure_rates[rhs - 1] };
			return f1 == f2 ? lhs < rhs : f1 > f2;
		}
	);

	result.n = result.v.size();

	return result;
}
#endif

Result BookSolution( Param param )
{
	Result result{};
	return result;
}
#endif VSTOOL

// For submit

#ifdef SUBMIT

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG

	// Start coding here
	vector<int> answer{};


	// Input
	int n{};
	cin >> n;

	// programmers param
	int p{};
	cin >> p;

	vector<int> param{};
	int num{};
	for ( int i{}; i < p; ++i )
	{
		cin >> num;
		param.push_back( num );
	}

	vector<int> stages{ param };

	// Var
	vector<pair<int, double>> failure_rates{};

	// Init
	for ( int i{}; i < n + 1; ++i )
	{
		failure_rates.emplace_back( i + 1, 0.0 );
	}

	// Solution 
	ranges::sort( stages );

	auto begin = stages.begin();
	while ( begin != stages.end() )
	{
		auto [first, last] = equal_range( begin, stages.end(), *begin );

		auto failure_num = static_cast<double>( distance( first, last ) );
		auto passerby_num = static_cast<double>( distance( first, stages.end() ) );

		failure_rates[( *begin ) - 1].second = failure_num / passerby_num;

		begin = last;
	}

	// 모든 스테이지 클리어율을 제외
	failure_rates.pop_back();

	ranges::sort( failure_rates,
		[]( const auto& lhs, const auto& rhs )
		{
			if ( lhs.second == rhs.second )
				return lhs.first < rhs.first;
			return lhs.second > rhs.second;
		}
	);

	// End
	for ( const auto& failure_rate : failure_rates )
	{
		cout << failure_rate.first << " "; // must erase
		answer.push_back( failure_rate.first );
	}

	// must execute
	//return answer;

	return 0;
}

#endif SUBMIT
#endif