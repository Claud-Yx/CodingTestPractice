// https://www.acmicpc.net/problem/16234

#include "core.h"

#define CP_NUM "13-7"

#ifdef P13_7
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <queue>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, l{}, r{};
	vector<vector<int>> map{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.l >> self.r;

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
		out = format_to( out, "N: {} | L: {} | R: {}", ts.param.n, ts.param.l, ts.param.r );

		// Parameter Line
		out = format_to( out, "\n{:^6}| ", "" );

		// Map
		string title{ "pop" };
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
 모든 국가들의 방문 여부를 저장할 table을 생성한다.
 한 번 방문 테이블을 생성 후 다시 초기화하지 않기 위해 int를 저장하고,
 방문 횟수 = 지난 날짜 이기 때문에 지난 날짜를 비교하여 방문 여부를 확인한다.

 방문 table: vector<vector<int> -> VisitTable visit_table

 모든 국가들은 반복문을 통해 방문을 확인한다. 방문한 적이 없으면 bfs를 실시하여
 국경이 열린 국가끼리 묶어 레퍼런스(&) 형태로 2차원의 연합 배열에 추가하며 동시에 합을 구한다.
 여기서 미리 연합의 인구수 합을 구해서 같이 넣기 위해 int, vector<int&>를 pair 형식으로 구현한다.

 연합 배열: vector<pair<int, vector<int&>>> -> vector<Union> unions
 연합 인구수 합: int pop_sum

 bfs는 국가의 상하좌우를 확인하며, bfs queue에는 국가의 위치가 들어간다.

 bfs queue: queue<Pos> bfs_q

*/

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

const Pos kDirVec[]{ Pos{0, -1}, {1, 0}, {0, 1}, {-1, 0} };

using Map = vector<vector<int>>;
using VisitTable = vector<vector<int>>;
using Union = pair<int, vector<int*>>;

Result MySolution( Param param )
{
	Result result{};

	// Input
	int n{ param.n }, l{ param.l }, r{ param.r };
	Map map{ param.map };

	// Vars
	int map_size{ n * n };
	int day{};	// 지난 날짜 확인용 = 정답
	VisitTable visit_table;	// 방문 확인 테이블
	vector<Union> unions;	// 연합 레퍼런스
	queue<Pos> bfs_q;

	// Init visit table
	for ( int y{}; y < n; ++y )
	{
		visit_table.push_back( {} );
		for ( int x{}; x < n; ++x )
			visit_table.back().push_back( 0 );
	}

	while ( true )
	{
		for ( int y{}; y < n; ++y )
		{
			for ( int x{}; x < n; ++x )
			{
				// 방문 한 적이 없다? = 지난 날의 수 ( 초기 visit_table[y][x] == 0, 초기 day == 0 )
				if ( visit_table[y][x] > day )
					continue;

				// 방문한 적이 없으면 방문 표시 후 현 위치를 시작으로 bfs 실시
				bfs_q.push( { x, y } );

				// 방문을 표시함
				++visit_table[y][x];
				
				// 새로운 연합 생성
				unions.push_back( {} );

				auto& cur_union = unions.back();

				while ( not bfs_q.empty() )
				{
					// pop
					Pos pos = bfs_q.front();
					bfs_q.pop();

					// 연합에 포함 후 연합의 총 인구수를 증가시킴
					cur_union.second.push_back( &map[pos.y][pos.x] );
					cur_union.first += map[pos.y][pos.x];

					// 4 뱡향을 확인
					for ( int i{}; i < 4; ++i )
					{
						Pos new_pos = pos + kDirVec[i];

						// border check
						if ( new_pos.x < 0 or new_pos.y < 0 or new_pos.x >= n or new_pos.y >= n )
							continue;

						// visit check
						if ( visit_table[new_pos.y][new_pos.x] > day )
							continue;

						// population check
						int pop_diff = abs( map[new_pos.y][new_pos.x] - map[pos.y][pos.x] );
						if ( pop_diff < l or r < pop_diff )
							continue;

						// 방문을 표시함
						++visit_table[new_pos.y][new_pos.x];

						// 모두 bfs_q에 push
						bfs_q.push( new_pos );

					}
				}
			}
		}

		// 만들어진 연합이 존재하지 않는다면? == 연합 수가 국가 수와 같다면?
		if ( unions.size() == n * n )
			break;

		// 인구 이동 처리
		for ( auto& u : unions )
		{
			int i = u.first / u.second.size();	// 평균 구해주기

			// 평균 인구를 각 나라에 넣어줌
			for ( auto& n : u.second )
			{
				*n = i;
			}
		}

		// 연합 초기화
		unions.clear();

		// 연합이 존재하고 이동이 끝났으면 하루가 지나감
		++day;
	}

	result = day;

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
#include <vector>
#include <queue>

using namespace std;

/*
 풀이
 모든 국가들의 방문 여부를 저장할 table을 생성한다.
 한 번 방문 테이블을 생성 후 다시 초기화하지 않기 위해 int를 저장하고,
 방문 횟수 = 지난 날짜 이기 때문에 지난 날짜를 비교하여 방문 여부를 확인한다.

 방문 table: vector<vector<int> -> VisitTable visit_table

 모든 국가들은 반복문을 통해 방문을 확인한다. 방문한 적이 없으면 bfs를 실시하여
 국경이 열린 국가끼리 묶어 레퍼런스(&) 형태로 2차원의 연합 배열에 추가하며 동시에 합을 구한다.
 여기서 미리 연합의 인구수 합을 구해서 같이 넣기 위해 int, vector<int&>를 pair 형식으로 구현한다.

 연합 배열: vector<pair<int, vector<int*>>> -> vector<Union> unions
 연합 인구수 합: int pop_sum

 bfs는 국가의 상하좌우를 확인하며, bfs queue에는 국가의 위치가 들어간다.

 bfs queue: queue<Pos> bfs_q
*/

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

const Pos kDirVec[]{ Pos{0, -1}, {1, 0}, {0, 1}, {-1, 0} };

using Map = vector<vector<int>>;
using VisitTable = vector<vector<int>>;
using Union = pair<int, vector<int*>>;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG

	// Input
	int n{}, l{}, r{};
	cin >> n >> l >> r;

	int num{};
	Map map{};
	for ( int y{}; y < n; ++y )
	{
		map.push_back( {} );
		for ( int x{}; x < n; ++x )
		{
			cin >> num;
			map.back().push_back( num );
		}

	}


	// Vars
	int day{};	// 지난 날짜 확인용 = 정답
	VisitTable visit_table;	// 방문 확인 테이블
	vector<Union> unions;	// 연합 레퍼런스
	queue<Pos> bfs_q;

	// Init visit table
	for ( int y{}; y < n; ++y )
	{
		visit_table.push_back( {} );
		for ( int x{}; x < n; ++x )
			visit_table.back().push_back( 0 );
	}

	while ( true )
	{
		for ( int y{}; y < n; ++y )
		{
			for ( int x{}; x < n; ++x )
			{
				// 방문 한 적이 없다? = 지난 날의 수 ( 초기 visit_table[y][x] == 0, 초기 day == 0 )
				if ( visit_table[y][x] > day )
					continue;

				// 방문한 적이 없으면 방문 표시 후 현 위치를 시작으로 bfs 실시
				bfs_q.push( { x, y } );

				// 방문을 표시함
				++visit_table[y][x];

				// 새로운 연합 생성
				unions.push_back( {} );

				auto& cur_union = unions.back();

				while ( not bfs_q.empty() )
				{
					// pop
					Pos pos = bfs_q.front();
					bfs_q.pop();

					// 연합에 포함 후 연합의 총 인구수를 증가시킴
					cur_union.second.push_back( &map[pos.y][pos.x] );
					cur_union.first += map[pos.y][pos.x];

					// 4 뱡향을 확인
					for ( int i{}; i < 4; ++i )
					{
						Pos new_pos = pos + kDirVec[i];

						// border check
						if ( new_pos.x < 0 or new_pos.y < 0 or new_pos.x >= n or new_pos.y >= n )
							continue;

						// visit check
						if ( visit_table[new_pos.y][new_pos.x] > day )
							continue;

						// population check
						int pop_diff = abs( map[new_pos.y][new_pos.x] - map[pos.y][pos.x] );
						if ( pop_diff < l or r < pop_diff )
							continue;

						// 방문을 표시함
						++visit_table[new_pos.y][new_pos.x];

						// 모두 bfs_q에 push
						bfs_q.push( new_pos );

					}
				}
			}
		}

		// 만들어진 연합이 존재하지 않는다면? == 연합 수가 국가 수와 같다면?
		if ( unions.size() == n * n )
			break;

		// 인구 이동 처리
		for ( auto& u : unions )
		{
			int i = u.first / u.second.size();	// 평균 구해주기

			// 평균 인구를 각 나라에 넣어줌
			for ( auto& n : u.second )
			{
				*n = i;
			}
		}

		// 연합 초기화
		unions.clear();

		// 연합이 존재하고 이동이 끝났으면 하루가 지나감
		++day;
	}

	cout << day;

	return 0;
}

#endif SUBMIT
#endif