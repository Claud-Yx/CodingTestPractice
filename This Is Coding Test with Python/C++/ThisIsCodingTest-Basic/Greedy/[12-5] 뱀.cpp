#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{}, l{};
	vector<pair<int, int>> apple;
	vector<pair<int, char>> dir;

	friend istream& operator>>( istream& is, Param& p ) {
		is >> p.n >> p.k;

		for ( int i{}; i < p.k; ++i ) {
			int num1{}, num2{};
			is >> num1 >> num2;
			p.apple.emplace_back( num1, num2 );
		}

		is >> p.l;

		for ( int i{}; i < p.l; ++i ) {
			int num{};
			char ch{};
			is >> num >> ch;
			p.dir.emplace_back( num, ch );
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
		out = format_to( out, "N: {} M: {} L: {} ", ts.param.n, ts.param.k, ts.param.l );

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );

		string tmp{ "apple" };
		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", tmp );
		tmp.clear();

		for ( int i{}; i < ts.param.k; ++i ) {
			out = format_to( out, "({} {}) ", ts.param.apple[i].first, ts.param.apple[i].second );
		}

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );

		tmp = "dir";
		out = format_to( out, "\n" );
		out = format_to( out, " {:4} | ", tmp );
		tmp.clear();

		for ( int i{}; i < ts.param.l; ++i ) {
			out = format_to( out, "({} {}) ", ts.param.dir[i].first, ts.param.dir[i].second );
		}

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-5.txt" ) };

	cout << "My Solution ==================\n";
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
Snake 클래스를 만들어 게임에서 사용될 속성과 메소드를 정의하여 풀어보았다.
아래는 Snake 클래스의 속성, 메소드 설명이다.

dir: 뱀이 현재 바라보는 방향, 4 방향이 있다.
pos: 뱀의 몸의 위치, 모든 마디가 list로 연결되어 있다.
lifespan: 뱀의 수명, 풀이의 답이다.
prev_tail_pos: 움직이기 이전의 꼬리 위치, 사과를 먹어 연장하거나 머리가 닿는지 여부를 확인한다.

MoveForward(): 현재 방향으로 무조건 나아간다. 나아가며 수명을 1초 증가시킨다.
Rotate(): 'D' 또는 'L' 에 의해 머리를 회전시킨다.
IsDead(): 뱀의 사망 여부를 체크한다. 맵을 벗어나거나 몸에 부딪치면 사망한다.
EatApple(): 사과를 먹는다. prev_tail_pos를 pos리스트에 append 한다. (=몸이 길어진다.)

0 0 0 0
0 1 1 0
0 2 1 0
0 0 0 0

*/

enum class DIR { N, E, S, W };

DIR& operator++( DIR& dir )
{
	if ( dir == DIR::W )
		dir = DIR::N;
	else
		dir = static_cast<DIR>( static_cast<int>( dir ) + 1 );
	return dir;
}

DIR& operator--( DIR& dir )
{
	if ( dir == DIR::N )
		dir = DIR::W;
	else
		dir = static_cast<DIR>( static_cast<int>( dir ) - 1 );
	return dir;
}

struct Coord { 
	int y{}, x{}; 

	bool operator==( const Coord& rhs )
	{
		return x == rhs.x and y == rhs.y;
	}
};

constexpr Coord kDirVec[4] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

class Snake {
public:
	DIR dir{ DIR::E };		// 바라보는 방향
	list<Coord> pos{};		// 몸 전체의 위치, front = 머리 -> queue로 바꿔보기
	int lifespan{};			// 뱀의 수명, 0초부터 시작
	Coord prev_tail_pos{};	// 뱀 꼬리의 이전 위치
	
	Snake()
	{
		pos.emplace_back( 0, 0 );
	}

	void MoveForward()
	{
		++lifespan;
		Coord prev = pos.front();

		for ( auto& i : pos ) {
			Coord tmp = i;
			i = prev;
			prev = tmp;
		}

		prev_tail_pos = prev;

		pos.front().x += kDirVec[(int)dir].x;
		pos.front().y += kDirVec[(int)dir].y;
	}

	void Rotate( char ch )
	{
		switch ( ch ) {
		case 'L':
			--dir;
			break;
		case 'D':
			++dir;
			break;
		}
	}

	bool IsDead( int map_max_size )
	{
		Coord head = pos.front();
		
		// 맵 밖으로 나가면 사망
		if ( head.x < 0 or head.x >= map_max_size or head.y < 0 or head.y >= map_max_size )
			return true;

		// 몸 길이 3 이하라면 무조건 생존
		if ( pos.size() <= 3 )
			return false;

		// 몸 길이 3 초과라면 몸과 부딪치면 사망
		auto begin = pos.begin();
		advance( begin, 1 );
		auto i = find( begin, pos.end(), head );

		// 주의:
		// 이 Snake 게임은 머리와 꼬리가 동시에 움직이는게 아니라
		// 머리가 먼저 움직이기 때문에
		// 움직이기 직전의 꼬리에 머리가 닿을 수 있다.
		if ( i != pos.end() or head == prev_tail_pos )
			return true;
		return false;
	}

	void EatApple()
	{
		pos.push_back( prev_tail_pos );
	}
};

Result MySolution( Param param )
{
	int n{ param.n }, k{ param.k }, l{ param.l };
	list<Coord> apple{};

	struct LessPair {
		bool operator()( const pair<int, char>& lhs, const pair<int, char>& rhs )
		{
			return lhs.first < rhs.first;
		}
	};

	deque<pair<int, char>> order_q;

	for ( int i{}; i < param.k; ++i )
		apple.emplace_back( param.apple[i].first - 1, param.apple[i].second - 1 );

	for ( int i{}; i < param.l; ++i )
		order_q.push_back( param.dir[i] );
	sort( order_q.begin(), order_q.end(), LessPair() );

	Snake snake{};

	// 뱀이 죽을 때 까지 반복
	while ( not snake.IsDead( n ) ) {
		// 뱀을 앞으로 움직인다.
		snake.MoveForward();

		// 회전 명령이 남아있다면
		if ( not order_q.empty() ) {
			// 회전 명령 타이머가 완료되면 회전시킨다. 후에 해당 명령을 제거한다.
			if ( order_q.front().first == snake.lifespan ) {
				snake.Rotate( order_q.front().second );
				order_q.pop_front();
			}
		}

		// 사과가 있다면 몸 길이를 늘리고 사과를 지운다.
		auto i = find( apple.begin(), apple.end(), snake.pos.front() );
		if ( i != apple.end() ) {
			snake.EatApple();
			apple.erase( i );
		}
	}

	// 뱀 수명 == 게임 시간
	return snake.lifespan;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}