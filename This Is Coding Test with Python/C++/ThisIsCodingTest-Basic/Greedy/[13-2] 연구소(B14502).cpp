// https://www.acmicpc.net/problem/14502

#include "core.h"

#ifdef P13_2
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <queue>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<vector<int>> map{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.m;

		int num{};
		for ( int i : views::iota( 0 ) | views::take( self.n ) ) {
			self.map.push_back( {} );
			for ( int j : views::iota( 0 ) | views::take( self.m ) ) {
				is >> num;
				self.map.back().emplace_back( num );
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

		out = format_to( out, "n: {} | m: {}", ts.param.n, ts.param.m );

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:^5} | ", "Map" );

		for ( int i{}; i < ts.param.n; ++i )
		{
			for ( int j{}; j < ts.param.m; ++j )
				out = format_to( out, "{} ", ts.param.map[i][j] );
			out = format_to( out, "\n{:5} | ", "" );
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
	cout << "Practice 13-2 =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/13-2.txt" ) };

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
 연구실 전체를 세 개의 벽으로 막아보면서 바이러스 유출 상황을 시뮬레이션 한다.
 그 중에서 오염되지 않은 방의 크기가 가장 큰 경우를 구한다.
 상당히 비효율적이라고 생각되지만 일단 바로 생각난 김에 시도해본다.
 바이러스 유출은 BFS 알고리즘을 사용한다.
 좌표는 ( y, x ) 순서를 기준으로 한다.
*/

constexpr int BLANK{ 0 }, WALL{ 1 }, VIRUS{ 2 };
constexpr array<pair<int, int>, 4> DIR_VEC{ pair<int,int>{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int GenerateBiohazardAndCountBlank( queue<pair<int, int>> virus_q, vector<vector<int>> map, const pair<int, int>& max_map, array<pair<int, int>, 3> new_walls )
{
	// 새로운 벽을 설치
	for ( const auto& [Y, X] : new_walls )
	{
		map[Y][X] = WALL;
	}

	while ( not virus_q.empty() )
	{
		auto virus = virus_q.front();
		virus_q.pop();

		/*
		2 1 0 0 1 1 0
		1 0 1 0 1 2 0
		0 1 1 0 1 0 0
		0 1 0 0 0 1 0
		0 0 0 0 0 1 1
		0 1 0 0 0 0 0
		0 1 0 0 0 0 0
		*/

		// 4방향을 돌며 바이러스 전파를 확인
		for ( int i{}; i < 4; ++i )
		{
			// 연구소(맵) 밖을 나가지 않도록 체크, 어차피 빈칸이 아닌 곳만 확인하기 때문에 원래 위치를 확인해도 무관
			int Y = clamp( virus.first + DIR_VEC[i].first, 0, max_map.first );
			int X = clamp( virus.second + DIR_VEC[i].second, 0, max_map.second );

			// 빈칸 확인 후 바이러스 전파, 그리고 바이러스 queue에 push하여 전파를 기다림
			if ( map[Y][X] == BLANK )
			{
				map[Y][X] = VIRUS;
				virus_q.emplace( Y, X );
			}
		}
	}

	// 오염되지 않은 방의 수를 셈
	int count{};
	for ( const auto& Y : map )
		for ( const auto& X : Y )
			if ( X == BLANK )
				++count;

	return count;
}

Result MySolution( Param param )
{
	Result answer{};

	int n{ param.n }, m{ param.m };
	vector<vector<int>> map( param.map );

	queue<pair<int, int>> virus_q{};
	pair<int, int> max_map{ n - 1, m - 1 };

	// 초기 바이러스의 위치를 queue에 담는다.
	for ( int y{}; y < n; ++y )
		for ( int x{}; x < m; ++x )
			if ( map[y][x] == VIRUS )
				virus_q.emplace( y, x );

	const int map_size{ n * m };
	for ( int idx1{}; idx1 < map_size; ++idx1 )
	{
		// 벽을 세울 위치를 정하고 그 위치가 유효하지 않다면 반복문을 무시
		int Y1{ idx1 / m }, X1{ idx1 % m };
		if ( map[Y1][X1] != BLANK )
			continue;

		for ( int idx2{ idx1 + 1 }; idx2 < map_size; ++idx2 )
		{
			int Y2{ idx2 / m }, X2{ idx2 % m };
			if ( map[Y2][X2] != BLANK )
				continue;

			for ( int idx3{ idx2 + 1 }; idx3 < map_size; ++idx3 )
			{
				int Y3{ idx3 / m }, X3{ idx3 % m };
				if ( map[Y3][X3] != BLANK )
					continue;

				answer = max( answer, GenerateBiohazardAndCountBlank( virus_q, map, max_map, { pair<int,int>{Y1, X1}, {Y2, X2}, {Y3, X3} } ) );
			}
		}
	}

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
#include <array>
#include <ranges>
#include <queue>
#include <algorithm>

using namespace std;

using Result = int;

constexpr int BLANK{ 0 }, WALL{ 1 }, VIRUS{ 2 };
constexpr array<pair<int, int>, 4> DIR_VEC{ pair<int,int>{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int GenerateBiohazardAndCountBlank( queue<pair<int, int>> virus_q, vector<vector<int>> map, const pair<int, int>& max_map, array<pair<int, int>, 3> new_walls )
{
	// 새로운 벽을 설치
	for ( const auto& [Y, X] : new_walls )
	{
		map[Y][X] = WALL;
	}

	while ( not virus_q.empty() )
	{
		auto virus = virus_q.front();
		virus_q.pop();

		// 4방향을 돌며 바이러스 전파를 확인
		for ( int i{}; i < 4; ++i )
		{
			// 연구소(맵) 밖을 나가지 않도록 체크, 어차피 빈칸이 아닌 곳만 확인하기 때문에 원래 위치를 확인해도 무관
			int Y = clamp( virus.first + DIR_VEC[i].first, 0, max_map.first );
			int X = clamp( virus.second + DIR_VEC[i].second, 0, max_map.second );

			// 빈칸 확인 후 바이러스 전파, 그리고 바이러스 queue에 push하여 전파를 기다림
			if ( map[Y][X] == BLANK )
			{
				map[Y][X] = VIRUS;
				virus_q.emplace( Y, X );
			}
		}
	}

	// 오염되지 않은 방의 수를 셈
	int count{};
	for ( const auto& Y : map )
		for ( const auto& X : Y )
			if ( X == BLANK )
				++count;

	return count;
}

int main()
{
#ifdef DEBUG
	cout << "Practice 13-1 =======================" << endl;
#endif DEBUG

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP
		Result answer{};

		int n{}, m{};
		vector<vector<int>> map{};

		cin >> n >> m;

		for ( int i{}; i < n; ++i )
		{
			map.push_back( {} );
			for ( int j{}; j < m; ++j )
			{
				int num{};
				cin >> num;
				map.back().emplace_back( num );
			}

		}

		queue<pair<int, int>> virus_q{};
		pair<int, int> max_map{ n - 1, m - 1 };

		// 초기 바이러스의 위치를 queue에 담는다.
		for ( int y{}; y < n; ++y )
			for ( int x{}; x < m; ++x )
				if ( map[y][x] == VIRUS )
					virus_q.emplace( y, x );

		const int map_size{ n * m };
		for ( int idx1{}; idx1 < map_size; ++idx1 )
		{
			// 벽을 세울 위치를 정하고 그 위치가 유효하지 않다면 반복문을 무시
			int Y1{ idx1 / m }, X1{ idx1 % m };
			if ( map[Y1][X1] != BLANK )
				continue;

			for ( int idx2{ idx1 + 1 }; idx2 < map_size; ++idx2 )
			{
				int Y2{ idx2 / m }, X2{ idx2 % m };
				if ( map[Y2][X2] != BLANK )
					continue;

				for ( int idx3{ idx2 + 1 }; idx3 < map_size; ++idx3 )
				{
					int Y3{ idx3 / m }, X3{ idx3 % m };
					if ( map[Y3][X3] != BLANK )
						continue;

					answer = max( answer, GenerateBiohazardAndCountBlank( virus_q, map, max_map, { pair<int,int>{Y1, X1}, {Y2, X2}, {Y3, X3} } ) );
				}
			}
		}

		cout << answer;

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif P13_2