// https://school.programmers.co.kr/learn/courses/30/lessons/60063

#include "core.h"

#define CP_NUM "13-8"

#ifdef P13_8
#ifdef VSTOOL

#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<vector<int>> map{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		int num{};
		for ( int i{}; i < self.n; ++i )
		{
			self.map.push_back( {} );
			for ( int j{}; j < self.n; ++j )
			{
				is >> num;
				self.map.back().push_back( num );
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

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );

		// Parameter Line
		// Map
		string title{ "map" };
		for ( const auto& rows : ts.param.map )
		{
			out = format_to( out, "\n{:^6}| ", title );
			title.clear();

			for ( const auto& num : rows )
			{
				out = format_to( out, "{} ", num );
			}
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
 이전의 '미로 탈출'과 비슷하게 BFS 알고리즘으로 해결한다.
 이를 위해 최단거리 테이블이 필요한데, 방향에 따라 두 개가 필요하다.

 최단거리 테이블: vector<vector<unsigned int>> x_min_dist, y_min_dist

 로봇의 북동남서 뿐만 아니라 회전도 하나의 이동으로 구분해본다.
 즉 회전을 북서, 북동, 남서, 남동 으로의 이동으로 생각하여 총 8방향으로 움직이는 것이다.
 BFS알고리즘을 이용하는데, queue에 담을 정보는 로봇의 위치 배열, 현재 위치까지의 거리이다.

 queue: queue<Robot>
 로봇 위치 배열: Robot::array<Pos, 2> pos
 현재 위치 거리: unsigned int cur_dist

 BFS 반복문에서는 queue에서 로봇 위치를 꺼내와 다음 위치로 이동시키는데, 
 로봇이 새로 닿는 칸(아래의 N)이 현재 위치와 같거나 짧은 거리가 등록되어있다면 진행을 멈춘다.

 예) 최단거리 테이블( R = 로봇 | N = 가보지 않은 곳(INT MAX) | X = 벽 )

      R = 1         R = 2         R = 3        R = 4
    R R N X X     1 1 N X X     1 1 2 X X
	N N N X N     R R N X N	BLK 2 R R X N
	N X N X X -S> N X N X X -E>	N X N X X
	X X N N X	  X X N N X		X X N N X
	N N N N N	  N N N N N		N N N N N
			   |
	              1 R R X X     1 1 2 X X
			 	  2 2 N X N	OVR 2 R R X N
			  -E> N X N X X -N>	N X N X X
			 	  X X N N X	    X X N N X
			 	  N N N N N		N N N N N
			   |			 |
						        2 2 R X X     2 2 3 X X
						        2 2 R X N	  2 2 R X N
			   |		    SE>	N X N X X -S> N X R X X -> ...
						   	    X X N N X	  X X N N X
						   	    N N N N N	  N N N N N
			   |             |
				  N R N X X	    2 2 R X X
				  N R N X N	OVR 2 2 R X N
			  SE> N X N X X	-E>	N X N X X
			      X X N N X	    X X N N X
				  N N N N N	    N N N N N
			   |             |
			                    1 1 2 X X
							OVR 2 R R X N
			   |			SE>	N X N X X
							    X X N N X
								N N N N N
			   |
				  R 2 N X X     2 2 3 X X
				  R 2 N X N	BLK R 2 3 X N
			  SW> N X N X X -N>	R X N X X
				  X X N N X		X X N N X
				  N N N N N		N N N N N
*/

enum class DIR { N, E, S, W, NW, NE, SE, SW, LAST };
enum class ROT { X, Y };

struct Pos {
	int x{}, y{};

	Pos operator+( const Pos& other )
	{
		return { x + other.x, y + other.y };
	}

	void operator+=( const Pos& other )
	{
		*this = *this + other;
	}
};

const Pos kDirVec[]{ {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1} };

using Map = vector<vector<int>>;
using RobotPos = array<Pos, 2>;
using DistTable = array<vector<vector<unsigned int>>, 2>;
constexpr int ROAD{ 0 }, WALL{ 1 };

class Robot {
public:
	RobotPos pos{ Pos{ 0, 0 }, { 1, 0 } };	// default: 로봇의 초기 위치, index는 0: 왼쪽 or 위
	ROT rotation{ ROT::X };	// 로봇의 긴 부분의 방향(X: 가로 | Y: 세로)

	// 이동이 가능한가? -> 벽이나 맵 외부에 의해 갈 수 없으면 false, 가능하면 이동 후 true
	bool TryMove( DIR dir, const Map& map )
	{
		size_t map_size = map.size();

		RobotPos new_pos{ pos };
		size_t int_dir{ size_t( dir ) };

		// new_pos 정하기
		switch ( dir ) 
		{
		case DIR::N:
		case DIR::E:
		case DIR::S:
		case DIR::W:
			for ( int i{}; i < pos.size(); ++i )
			{
				new_pos[i] += kDirVec[int_dir];
			}
			break;
		case DIR::NW:
			new_pos[1] += kDirVec[int_dir];
			break;
		case DIR::NE:
			if ( rotation == ROT::X )
				new_pos[0] += kDirVec[int_dir];
			else
				new_pos[1] += kDirVec[int_dir];
			break;
		case DIR::SE:
			new_pos[0] += kDirVec[int_dir];
			break;
		case DIR::SW:
			if ( rotation == ROT::X )
				new_pos[0] += kDirVec[int_dir];
			else
				new_pos[1] += kDirVec[int_dir];
			break;
		}

		// border check
		for ( const auto& p : new_pos )
		{
			if ( p.x < 0 or p.y < 0 or p.x >= map_size or p.y >= map_size )
				return false;
			if ( WALL == map[p.y][p.x] )
				return false;
		}

		// 방향 전환을 알림
		switch ( dir )
		{
		case DIR::NW:
		case DIR::NE:
		case DIR::SE:
		case DIR::SW:
			rotation = ( rotation == ROT::X ? ROT::Y : ROT::X );
			break;
		}

		pos = new_pos;
		return true;
	}
};

Result MySolution( Param param )
{
	Result result{};

	int n{ param.n };
	Map map{ param.map };

	DistTable dist_tables{};
	size_t X{ size_t( ROT::X ) }, Y{ size_t( ROT::Y ) };
	queue<pair<Robot, unsigned int>> bfs_q{};

	for ( auto& dist_table : dist_tables )
	{
		for ( int y{}; y < n; ++y )
		{
			dist_table.push_back( {} );
			for ( int x{}; x < n; ++x )
			{
				dist_table[y].push_back( -1 );
			}
		}
	}

	bfs_q.push( { Robot{}, 1 } );

	while ( not bfs_q.empty() )
	{
		// queue pop
		auto robot = bfs_q.front().first;
		auto dist = bfs_q.front().second;
		bfs_q.pop();

		// 현 위치로 움직여도 되는지? -> 최단거리 테이블 확인 후 업데이트
		auto& dist_table = dist_tables[(size_t)robot.rotation];
		auto& pos1{ dist_table[robot.pos[0].y][robot.pos[0].x] };
		auto& pos2{ dist_table[robot.pos[1].y][robot.pos[1].x] };

		// 양쪽 모두 현 거리보다 낮다면 불가능
		if ( pos1 < dist and pos2 < dist )
			continue;

		pos1 = min( pos1, dist );
		pos2 = min( pos2, dist );

		// 모든 방향 이동 가능 여부 확인
		for ( DIR dir{}; dir != DIR::LAST; dir = DIR( int(dir) + 1 ) )
		{
			Robot next_robot = robot;

			if ( next_robot.TryMove( dir, map ) )
			{
				bfs_q.push( { next_robot, dist + 1 } );
			}
		}
	}

	result = min( dist_tables[X][n - 1][n - 1], dist_tables[Y][n - 1][n - 1] );
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

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP
		// Start coding here

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif