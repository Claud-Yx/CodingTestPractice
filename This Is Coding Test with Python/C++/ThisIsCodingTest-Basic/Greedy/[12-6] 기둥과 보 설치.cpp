#include <iostream>
#include <vector>
#include <array>
#include "CodingTester.h"

using namespace std;

using ABuildFrame = array<int, 4>;
constexpr int COLUMN{ 0 }, BEAM{ 1 };
constexpr int REMOVE{ 0 }, INSTALL{ 1 };
constexpr int X{ 0 }, Y{ 1 }, A{ 2 }, B{ 3 };

struct Param {
	int n{}, k{};
	vector<ABuildFrame> build_frame{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.k;

		for ( int i{}; i < self.k; ++i ) {
			int n1{}, n2{}, n3{}, n4{};

			is >> n1 >> n2 >> n3 >> n4;

			self.build_frame.push_back( { n1, n2, n3, n4 } );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<array<int, 3>> v{};

	bool operator==( const Result& other ) const
	{
		if ( v.size() != other.v.size() )
			return false;

		for ( int i{}; i < v.size(); ++i ) {
			for ( int j{}; j < 3; ++j ) {
				if ( v[i][j] != other.v[i][j] )
					return false;
			}
		}

		return true;
	}

	friend istream& operator>>( istream& is, Result& self )
	{
		is >> self.n;

		int n1{}, n2{}, n3{};
		for ( int i{}; i < self.n; ++i ) {
			is >> n1 >> n2 >> n3;
			self.v.push_back( { n1, n2, n3 } );
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
		auto out = format_to( ctx.out(), "");
		
		for ( int i{}; i < ts.n; ++i )
			out = format_to( out, "[{} {} {}] ", ts.v[i][0], ts.v[i][1], ts.v[i][2] );
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

		out = format_to( out, "n: {}\n", ts.param.n );

		out = format_to( out, "{:5} | ", "" );
		for ( int i{}; const auto & elm : ts.param.build_frame ) {
			out = format_to( out, "[{} {} {} {}] ", elm[0], elm[1], elm[2], elm[3] );

			++i;
			if ( i % 3 == 0 )
				out = format_to( out, "\n{:5} | ", "" );

		}

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-6.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

bool CanBuild( const vector<vector<array<bool, 2>>>& map, int x, int y, int category )
{
	switch ( category ) {
	case COLUMN:
		// 바닥에는 항상 설치 가능
		if ( y == 0 )
			return true;

		// 바로 아래가 기둥이면 설치 가능
		if ( map[x][y - 1][COLUMN] )
			return true;

		// 보의 한 쪽 끝이라면 설치 가능
		if ( map[x][y][BEAM] )
			return true;

		if ( x > 0 and map[x - 1][y][BEAM] )
			return true;
		return false;
	case BEAM:
		if ( y > 0 ) {
			// 한 쪽 끝부분이 기둥 위라면 설치 가능
			if ( map[x][y - 1][COLUMN] or map[x + 1][y - 1][COLUMN] )
				return true;

			// 양쪽 끝 부분이 다른 보와 연결되는 경우 설치 가능
			if ( ( x > 0 and map[x - 1][y][BEAM] ) and ( x < (int)map.size() and map[x + 1][y][BEAM] ) )
				return true;
		}

		return false;
	}

	return false;
}

bool CanRemove( vector<vector<array<bool, 2>>> map, int x, int y, int category )
{
	// 일단 삭제해 봄
	map[x][y][category] = false;

	switch ( category ) {
	case COLUMN:
		// 위에 기둥이 있다면 가능할까?
		// |
		// 
		if ( map[x][y + 1][COLUMN] and not CanBuild(map, x, y + 1, COLUMN) )
			return false;

		// 위쪽 양 옆에 있는 보들은 괜찮을까?
		// 왼쪽
		if ( ( x > 0 and map[x - 1][y + 1][BEAM] and not CanBuild( map, x - 1, y + 1, BEAM ) ) )
			return false;

		// 오른쪽
		if ( map[x][y + 1][BEAM] and not CanBuild( map, x, y + 1, BEAM ) )
			return false;

		return true;
	case BEAM:
		// 보 위에 있는 기둥들은 괜찮을까?
		// 왼쪽
		if ( map[x][y][COLUMN] and not CanBuild( map, x, y, COLUMN ) )
			return false;

		// 오른쪽
		if ( map[x + 1][y][COLUMN] and not CanBuild( map, x + 1, y, COLUMN ) )
			return false;

		// 양 옆의 보들은 괜찮을까?
		// 왼쪽
		if ( ( x > 0 and map[x - 1][y][BEAM] and not CanBuild( map, x - 1, y, BEAM ) ) )
			return false;

		// 오른쪽
		if ( map[x + 1][y][BEAM] and not CanBuild( map, x + 1, y, BEAM ) )
			return false;

		return true;
	}

	return false;
}

Result MySolution( Param param )
{
	Result result{};

	int n = param.n;
	vector<ABuildFrame> build_frame{};

	for ( int i{}; i < param.k; ++i )
		build_frame.push_back( param.build_frame[i] );

	vector<vector<array<bool, 2>>> build_map( n + 1, vector<array<bool, 2>>( n + 1, { false, false } ) );

	for ( const auto& elm : build_frame ) {
		switch ( elm[B] ) {
		case INSTALL:
			// 설치 가능하면 바로 설치
			if ( CanBuild( build_map, elm[X], elm[Y], elm[A] ) )
				build_map[elm[X]][elm[Y]][elm[A]] = true;

			break;
		case REMOVE:
			// 삭제하려면 연결 부위들의 조건이 충족하는지 확인해야 함
			if ( CanRemove( build_map, elm[X], elm[Y], elm[A] ) )
				build_map[elm[X]][elm[Y]][elm[A]] = false;

			break;
		}
	}

	for ( int x{}; x <= n; ++x ) {
		for ( int y{}; y <= n; ++y ) {
			if ( build_map[x][y][COLUMN] )
				result.v.push_back( { x, y, COLUMN } );
			if ( build_map[x][y][BEAM] )
				result.v.push_back( { x, y, BEAM } );
		}
	}

	sort( result.v.begin(), result.v.end(), 
		[](const auto& lhs, const auto& rhs)
		{
			if ( lhs[X] < rhs[X] )
				return true;
			else if ( lhs[X] == rhs[X] ) {
				if ( lhs[Y] < rhs[Y] )
					return true;
				else if ( lhs[Y] == rhs[Y] )
					return lhs[A] < rhs[A];
				else
					return false;
			}
			else
				return false;

		}
	);

	// debug
	result.n = result.v.size();
	return result;
}

Result BookSolution( Param param )
{
	return Result{};
}
