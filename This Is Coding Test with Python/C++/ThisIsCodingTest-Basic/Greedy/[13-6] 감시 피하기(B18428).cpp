// https://www.acmicpc.net/problem/18428

#include "core.h"

#define CP_NUM "13-6"

#ifdef P13_6
#ifdef VSTOOL

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include "CodingTester.h"

using namespace std;

enum class ElementType {
	None,
	Blank = 'X',
	Teacher = 'T',
	Student = 'S',
	Obstacle = 'O'
};

using Map = vector<vector<ElementType>>;

struct Param {
	int n{};
	Map map{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		char c{};
		for ( int i{}; i < self.n; ++i )
		{
			self.map.push_back( {} );
			for ( int j{}; j < self.n; ++j )
			{
				is >> c;
				self.map.back().push_back( static_cast<ElementType>( c ) );
			}
		}

		return is;
	}
};

using Result = string;

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
		out = format_to( out, "n: {}", ts.param.n );

		// Map
		string title{ "map" };
		out = format_to( out, "\n{:^6}| ", "" );
		for ( const auto& rows : ts.param.map )
		{
			out = format_to( out, "\n{:^6}| ", title );
			title.clear();

			for ( const auto& c : rows )
			{
				out = format_to( out, "{} ", static_cast<char>( c ) );
			}
		}

		// Parameter Line
		out = format_to( out, "\n{:^6}| ", "" );
		out = format_to( out, "\n{:^6}| ", "" );

		// Result Line
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice " << CP_NUM << " =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/" + string(CP_NUM) + ".txt" ) };

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
 각 요소들을 관리하기 용이하도록 클래스로 설계해본다.
*/

struct Pos { 
	int x{}, y{}; 
	Pos() = default;
	Pos( int x, int y ) : x{ x }, y{ y } {}

	Pos&& operator+( Pos other )
	{
		Pos tmp{ x + other.x, y + other.y };
		return move( tmp );
	}

	bool IsOut( size_t map_size )
	{
		return 0 > x or map_size <= x or 0 > y or map_size <= y;
	}
};

const array<Pos, 4> kDirVec{ Pos{0, -1}, {1, 0}, {0, 1}, {-1, 0} };

class Teacher {
public:
	Teacher() = default;
	Teacher( Pos pos ) : pos{ pos } {}

	Pos pos{};

	bool WatchStudent( const Map& map )
	{
		for ( const Pos& dir : kDirVec )
		{
			ElementType elm{};
			Pos next_pos{ pos };
			while ( elm != ElementType::Obstacle )
			{
				next_pos = next_pos + dir;

				// 범위 유효성 검사
				if ( next_pos.IsOut( map.size() ) )
					break;

				elm = map[next_pos.y][next_pos.x];

				// 학생을 찾으면 true를 리턴
				if ( elm == ElementType::Student )
					return true;
			}
		}

		// 반복문을 모두 통과하면 학생 발견 실패
		return false;
	}
};

Result MySolution( Param param )
{
	Result result{};
	int n = param.n;
	auto map = param.map;
	
	const int kMapSize = n * n;
	vector<shared_ptr<Teacher>> teachers{};

	for ( int i{}; i < kMapSize; ++i )
	{
		Pos pos{ i % n, i / n };

		if ( map[pos.y][pos.x] == ElementType::Teacher )
			teachers.emplace_back( make_shared<Teacher>( pos ) );
	}

	for ( int n1{}; n1 < kMapSize ; ++n1 )
	{
		// 첫 번째 장애물 설치, 이후 동일
		Pos pos1{ n1 % n, n1 / n };
		auto& map_pos1{ map[pos1.y][pos1.x] };

		if ( map_pos1 != ElementType::Blank )
			continue;
		map_pos1 = ElementType::Obstacle;

		for ( int n2{ n1 + 1 }; n2 < kMapSize; ++n2 )
		{
			Pos pos2{ n2 % n, n2 / n };
			auto& map_pos2{ map[pos2.y][pos2.x] };

			if ( map_pos2 != ElementType::Blank )
				continue;
			map_pos2 = ElementType::Obstacle;

			for ( int n3{ n2 + 1 }; n3 < kMapSize; ++n3 )
			{
				Pos pos3{ n3 % n, n3 / n };
				auto& map_pos3{ map[pos3.y][pos3.x] };

				if ( map_pos3 != ElementType::Blank )
					continue;
				map_pos3 = ElementType::Obstacle;

				// 장애물 설치가 끝난 후, 선생님들의 감시가 시작된다.
				bool detected{};
				for ( auto& teacher : teachers )
				{
					detected = teacher->WatchStudent( map );
					// 한 명이라도 발견되었다면 스킵 (장애물 위치를 옮김)
					if ( detected )
						break;
				}

				// 모든 선생님들이 발견하지 못했다면 그대로 YES 리턴
				if ( not detected )
				{
					return "YES";
				}

				// 장애물을 다시 치워준다.
				map_pos3 = ElementType::Blank;
			}
			map_pos2 = ElementType::Blank;
		}
		map_pos1 = ElementType::Blank;
	}

	// 모든 반복문을 통과했다면? 학생은 벗어날 수 없음
	return "NO";
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}
#endif VSTOOL

// 제출용

#ifdef SUBMIT

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include "CodingTester.h"

using namespace std;

enum class ElementType {
	None,
	Blank = 'X',
	Teacher = 'T',
	Student = 'S',
	Obstacle = 'O'
};

using Map = vector<vector<ElementType>>;

struct Pos {
	int x{}, y{};
	Pos() = default;
	Pos( int x, int y ) : x{ x }, y{ y } {}

	Pos&& operator+( Pos other )
	{
		return { x + other.x, y + other.y };
	}

	bool IsOut( size_t map_size )
	{
		return 0 > x or map_size <= x or 0 > y or map_size <= y;
	}
};

const array<Pos, 4> kDirVec{ Pos{0, -1}, {1, 0}, {0, 1}, {-1, 0} };

class Teacher {
public:
	Teacher() = default;
	Teacher( Pos pos ) : pos{ pos } {}

	Pos pos{};

	bool WatchStudent( const Map& map )
	{
		for ( const Pos& dir : kDirVec )
		{
			ElementType elm{};
			Pos next_pos{ pos };
			while ( elm != ElementType::Obstacle )
			{
				next_pos = next_pos + dir;

				// 범위 유효성 검사
				if ( next_pos.IsOut( map.size() ) )
					break;

				elm = map[next_pos.y][next_pos.x];

				// 학생을 찾으면 true를 리턴
				if ( elm == ElementType::Student )
					return true;
			}
		}

		// 반복문을 모두 통과하면 학생 발견 실패
		return false;
	}
};

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP
		int n{};
		Map map{};

		cin >> n;

		for ( int i{}; i < n; ++i )
		{
			map.push_back( {} );

			for ( int j{}; j < n; ++j )
			{
				char c{};
				cin >> c;
				map.back().push_back( static_cast<ElementType>( c ) );
			}
		}

		const int kMapSize = n * n;
		vector<shared_ptr<Teacher>> teachers{};

		for ( int i{}; i < kMapSize; ++i )
		{
			Pos pos{ i % n, i / n };

			if ( map[pos.y][pos.x] == ElementType::Teacher )
				teachers.emplace_back( make_shared<Teacher>( pos ) );
		}

		for ( int n1{}; n1 < kMapSize; ++n1 )
		{
			// 첫 번째 장애물 설치, 이후 동일
			Pos pos1{ n1 % n, n1 / n };
			auto& map_pos1{ map[pos1.y][pos1.x] };

			if ( map_pos1 != ElementType::Blank )
				continue;
			map_pos1 = ElementType::Obstacle;

			for ( int n2{}; n2 < kMapSize; ++n2 )
			{
				Pos pos2{ n2 % n, n2 / n };
				auto& map_pos2{ map[pos2.y][pos2.x] };

				if ( map_pos2 != ElementType::Blank )
					continue;
				map_pos2 = ElementType::Obstacle;

				for ( int n3{}; n3 < kMapSize; ++n3 )
				{
					Pos pos3{ n3 % n, n3 / n };
					auto& map_pos3{ map[pos3.y][pos3.x] };

					if ( map_pos3 != ElementType::Blank )
						continue;
					map_pos3 = ElementType::Obstacle;

					// 장애물 설치가 끝난 후, 선생님들의 감시가 시작된다.
					bool detected{};
					for ( auto& teacher : teachers )
					{
						detected = teacher->WatchStudent( map );
						// 한 명이라도 발견되었다면 스킵 (장애물 위치를 옮김)
						if ( detected )
							break;
					}

					// 모든 선생님들이 발견하지 못했다면 그대로 YES 리턴
					if ( not detected )
					{
						cout << "YES";
						return 0;
					}

					// 장애물을 다시 치워준다.
					map_pos3 = ElementType::Blank;
				}
				map_pos2 = ElementType::Blank;
			}
			map_pos1 = ElementType::Blank;
		}

		// 모든 반복문을 통과했다면? 학생은 벗어날 수 없음
		cout << "NO";
#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif