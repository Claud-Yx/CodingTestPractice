// https://www.acmicpc.net/problem/18405

#include "core.h"

#ifdef P13_3
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <deque>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{}, s{}, x{}, y{};
	vector<vector<int>> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.k;

		int num{};
		for ( int i : views::iota( 0 ) | views::take( self.n ) ) {
			self.v.push_back( {} );
			for ( int j : views::iota( 0 ) | views::take( self.n ) ) {
				is >> num;
				self.v.back().emplace_back( num );
			}
		}

		is >> self.s >> self.y >> self.x;

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

		out = format_to( out, "n: {} | k: {}", ts.param.n, ts.param.k );

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:^5} | ", "Map" );

		for ( int i{}; i < ts.param.n; ++i )
		{
			for ( int j{}; j < ts.param.n; ++j )
				out = format_to( out, "{} ", ts.param.v[i][j] );
			out = format_to( out, "\n{:5} | ", "" );
		}

		out = format_to( out, "\n{:5} | ", "" );

		out = format_to( out, "s: {} | y: {} | x: {}", ts.param.s, ts.param.y, ts.param.x );

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
	cout << "Practice 13-3 =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/13-3.txt" ) };

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
 앞선 연구실 문제와 비슷하면서 더 쉽다.
 마찬가지로 확산될 바이러스를 queue에 push하여 BFS를 진행하는데, 1초가 지날 때 마다 확산을 멈추고
 조건의 S초에 도달하면 멈춘 뒤 시험관의 상태를 확인하면 된다.
*/

constexpr int BLANK{ 0 };
constexpr array<pair<int, int>, 4> DIR_VEC{ pair<int,int>{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

Result MySolution( Param param )
{
	int n{ param.n }, k{ param.k }, s{ param.s }, y{ param.y }, x{ param.x };
	vector<vector<int>> v( param.v );

	// virus를 구조체로 선언: 번호, 좌표를 가짐
	struct Virus {
		Virus() {};
		Virus(int order, int x, int y) : 
			order{order}, x{x}, y{y} {}

		int order{};
		int x{}, y{};

		bool operator<( const Virus& other )
		{
			return order < other.order;
		}
	};

	// BFS를 수행할 deque (queue는 정렬이 안되고 priority_queue는 항상 정렬하기 때문에 불가능, 이하 queue로 대체하여 명명)
	deque<Virus> virus_q{};

	// deque virus_q를 초기화
	for ( int y{}; y < n; ++y )
		for ( int x{}; x < n; ++x )
			if ( v[y][x] > BLANK )
				virus_q.emplace_back( v[y][x], x, y );

	// 초당 확산될 바이러스의 수
	int virus_count{(int)virus_q.size()};

	// 시험관의 sec초 후의 sec을 나타내는 변수
	int sec{ s };

	sort(virus_q.begin(), virus_q.end());
	while ( not virus_q.empty() and sec > 0 )
	{
		// 제일 앞의 바이러스를 꺼낸다.
		auto virus = virus_q.front();
		virus_q.pop_front();

		// 바이러스의 4 방향을 모두 확인
		for ( int dir{}; dir < 4; ++dir )
		{
			// 시험관(맵) 밖을 나가지 않도록 체크, 어차피 빈칸이 아닌 곳만 확인하기 때문에 원래 위치를 확인해도 무관
			int Y = clamp( virus.y + DIR_VEC[dir].first, 0, n - 1 );
			int X = clamp( virus.x + DIR_VEC[dir].second, 0, n - 1 );
			
			// 확산될 위치가 아무것도 없는 빈칸이라면 확산 후 queue에 push
			if ( BLANK == v[Y][X] )
			{
				v[Y][X] = virus.order;
				virus_q.emplace_back( v[Y][X], X, Y );
			}
		}

		// 현재 시간의 바이러스가 모두 확산되었다면
		if ( --virus_count == 0 )
		{
			// 1초 경과
			--sec;

			// 다음 시간에 확산될 바이러스의 수를 지정
			virus_count = virus_q.size();

			// 바이러스들을 번호순에 맞게 정렬
			sort( virus_q.begin(), virus_q.end() );
		}
	}

	// 입력 받은 좌표는 1부터 시작하므로 1빼줌
	return v[y-1][x-1];
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
#include <deque>
#include <algorithm>

using namespace std;

using Result = int;

constexpr int BLANK{ 0 };
constexpr array<pair<int, int>, 4> DIR_VEC{ pair<int,int>{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int main()
{
#ifdef DEBUG
	cout << "Practice 13-1 =======================" << endl;
#endif DEBUG

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP
		int n{}, k{}, s{}, y{}, x{};
		vector<vector<int>> v{};

		cin >> n >> k;

		for ( int i{}; i < n; ++i )
		{
			v.push_back( {} );
			for ( int j{}; j < n; ++j )
			{
				int num{};
				cin >> num;
				v.back().emplace_back( num );
			}

		}

		cin >> s >> y >> x;

		// virus를 구조체로 선언: 번호, 좌표를 가짐
		struct Virus {
			Virus() {};
			Virus( int order, int x, int y ) :
				order{ order }, x{ x }, y{ y } {}

			int order{};
			int x{}, y{};

			bool operator<( const Virus& other )
			{
				return order < other.order;
			}
		};

		// BFS를 수행할 deque (queue는 정렬이 안되고 priority_queue는 항상 정렬하기 때문에 불가능, 이하 queue로 대체하여 명명)
		deque<Virus> virus_q{};

		// deque virus_q를 초기화
		for ( int y{}; y < n; ++y )
			for ( int x{}; x < n; ++x )
				if ( v[y][x] > BLANK )
					virus_q.emplace_back( v[y][x], x, y );

		// 초당 확산될 바이러스의 수
		int virus_count{ (int)virus_q.size() };

		// 시험관의 sec초 후의 sec을 나타내는 변수
		int sec{ s };

		sort( virus_q.begin(), virus_q.end() );
		while ( not virus_q.empty() and sec > 0 )
		{
			// 제일 앞의 바이러스를 꺼낸다.
			auto virus = virus_q.front();
			virus_q.pop_front();

			// 바이러스의 4 방향을 모두 확인
			for ( int dir{}; dir < 4; ++dir )
			{
				// 시험관(맵) 밖을 나가지 않도록 체크, 어차피 빈칸이 아닌 곳만 확인하기 때문에 원래 위치를 확인해도 무관
				int Y = clamp( virus.y + DIR_VEC[dir].first, 0, n - 1 );
				int X = clamp( virus.x + DIR_VEC[dir].second, 0, n - 1 );

				// 확산될 위치가 아무것도 없는 빈칸이라면 확산 후 queue에 push
				if ( BLANK == v[Y][X] )
				{
					v[Y][X] = virus.order;
					virus_q.emplace_back( v[Y][X], X, Y );
				}
			}

			// 현재 시간의 바이러스가 모두 확산되었다면
			if ( --virus_count == 0 )
			{
				// 1초 경과
				--sec;

				// 다음 시간에 확산될 바이러스의 수를 지정
				virus_count = virus_q.size();

				// 바이러스들을 번호순에 맞게 정렬
				sort( virus_q.begin(), virus_q.end() );
			}
		}

		// 입력 받은 좌표는 1부터 시작하므로 1빼줌
		cout << v[y - 1][x - 1];

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif P13_3