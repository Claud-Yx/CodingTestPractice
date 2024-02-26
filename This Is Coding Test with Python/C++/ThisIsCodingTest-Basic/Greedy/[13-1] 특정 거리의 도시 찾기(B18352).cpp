// https://www.acmicpc.net/problem/18352 -> 시간 초과!

#include "core.h"

#ifdef P13_1
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <map>
#include <ranges>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{}, k{}, x{};
	vector<pair<int, int>> road{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.m >> self.k >> self.x;

		int num1{}, num2{};
		for ( int i{}; i < self.m; ++i ) {
			is >> num1 >> num2;
			self.road.emplace_back( num1, num2 );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<int> v{};

	bool operator==( const Result& other ) const
	{
		if ( v.size() != other.v.size() )
			return false;

		for ( int i{}; i < v.size(); ++i ) {
			if ( v[i] != other.v[i] )
				return false;
		}

		return true;
	}

	friend istream& operator>>( istream& is, Result& self )
	{
		is >> self.n;

		int n{};
		for ( int i{}; i < self.n; ++i ) {
			is >> n;
			self.v.push_back( n );
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

template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "" );

		out = format_to( out, "[ " );
		for ( int i{}; i < ts.n; ++i )
			out = format_to( out, "{} ", ts.v[i] );
		out = format_to( out, "]" );
		return out;
	}
};

template <>
struct std::formatter<TestSet> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx ) {

		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "n: {} | m: {} | k: {} | x: {}", ts.param.n, ts.param.m, ts.param.k, ts.param.x );

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | ", "Road" );
		for ( int i{}; const auto & elm : ts.param.road ) {
			out = format_to( out, "[{} {}] ", elm.first, elm.second );

			if ( ++i % 5 == 0 )
				out = format_to( out, "\n{:5} | ", ""  );
		}

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice 13-1 =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/13-1.txt" ) };

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

void DFS( const vector<vector<int>>& road_table, map<int, int>& result, const int count, const int x, const int k )
{
	// 맵에 없다면? 최소 거리가 되는 것
	if ( not result.contains( x ) )
		result.try_emplace( x, count );

	// 맵에 있다면 최소 거리를 비교 후 삽입
	else
		result[x] = min( result[x], count );
		
	// k번째 도시라면 더 이상 갈 필요가 없음
	if ( k == count )
		return;

	// 아직 k번째 도시가 아니라면 이어진 도로를 확인 (X == 1 -> 2, 3)
	for ( int new_x : road_table[x] )
		DFS( road_table, result, count + 1, new_x, k );
}

Result MySolution( Param param )
{
	Result answer{};

	int n{ param.n }, m{ param.m }, k{ param.k }, x{ param.x };
	vector<pair<int, int>> road( param.road.begin(), param.road.end() );

	vector<vector<int>> road_table{};
	for ( auto i : views::iota( 0 ) | views::take( n + 1 ) )
		road_table.push_back( {} );

	for ( const auto& i : road )
		road_table[i.first].push_back( i.second );

	// 1 2
	// 1 3
	// 2 3
	// 2 4
	//---------
	// 0: 
	// 1: 2, 3
	// 2: 3, 4
	// 3:
	// 4:

	map<int, int> map_result{};
	DFS( road_table, map_result, 0, x, k );

	// map | x = 1
	// {1: 0}
	// {2: 1}
	// {3: 1}
	// {4: 2}

	// map 루프를 돌며 최소 거리가 k 인 도시를 결과에 추가
	for ( const auto [first, second] : map_result )
		if ( second == k )
			answer.v.push_back( first );

	if ( answer.v.empty() )
		answer.v.push_back( -1 );
	ranges::sort( answer.v );

	// output
	answer.n = answer.v.size();

	return answer;
}

Result BookSolution( Param param )
{
	Result answer{};
	return answer;
}

#endif VSTOOL

// 제출용

#ifdef SUBMIT

#include <iostream>
#include <vector>
#include <map>
#include <ranges>
#include <algorithm>

using namespace std;

void DFS( const vector<vector<int>>& road_table, map<int, int>& result, const int count, const int x, const int k )
{
	// 맵에 없다면? 최소 거리가 되는 것
	if ( not result.contains( x ) )
		result.try_emplace( x, count );

	// 맵에 있다면 최소 거리를 비교 후 삽입
	else
		result[x] = min( result[x], count );

	// k번째 도시라면 더 이상 갈 필요가 없음
	if ( k == count )
		return;

	// 아직 k번째 도시가 아니라면 이어진 도로를 확인
	for ( int new_x : road_table[x] )
		DFS( road_table, result, count + 1, new_x, k );
}

int main()
{
#ifdef DEBUG
	cout << "Practice 13-1 =======================" << endl;
#endif DEBUG
#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP

		vector<int> answer{};

		int n{}, m{}, k{}, x{};
		vector<pair<int, int>> road{};

		cin >> n >> m >> k >> x;
		for ( int i{}; i < m; ++i )
		{
			int n1{}, n2{};
			cin >> n1 >> n2;
			road.emplace_back( n1, n2 );
		}

		vector<vector<int>> road_table{};
		for ( auto i : views::iota( 0 ) | views::take( n + 1 ) )
			road_table.push_back( {} );

		for ( const auto& i : road )
			road_table[i.first].push_back( i.second );

		map<int, int> map_result{};
		DFS( road_table, map_result, 0, x, k );

		// map 루프를 돌며 최소 거리가 k 인 도시를 결과에 추가
		for ( const auto [first, second] : map_result )
			if ( second == k )
				answer.push_back( first );

		if ( answer.empty() )
			answer.push_back( -1 );
		ranges::sort( answer );

		for ( auto i : answer )
			cout << i << " ";

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif P13_1