#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<vector<int>> map{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.m;

		for ( int i{}; i < self.n; ++i ) {
			self.map.push_back( {} );
			for ( int j{}; j < self.n; ++j ) {
				int num{};
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

		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "n: {} m: {}\n", ts.param.n, ts.param.m );

		out = format_to( out, "{:5} | ", "Map" );
		for ( int i{}; const auto & elm : ts.param.map ) {
			for ( int j{}; j < ts.param.n; ++j )
				out = format_to( out, "{} ", elm[j] );

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-7.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

enum class MAP {
	ROAD,
	HOUSE,
	CHICKEN
};

#undef max
class Building {
public:
	Building() {}
	Building( int x, int y ) : x{ x }, y{ y } {}

	int x{}, y{};
	int min_dist{};

	inline int GetDistanceTo( const Building& to_building )
	{
		return abs( to_building.x - x ) + abs( to_building.y - y );
	}

	bool operator<( const Building& other )
	{
		return min_dist < other.min_dist;
	}
};

Result MySolution( Param param )
{
	Result result{};

	int n{ param.n }, m{ param.m };
	vector<vector<int>> map{};

	for ( int i{}; i < n; ++i ) {
		map.push_back( {} );
		for ( int j{}; j < n; ++j ) {
			map.back().push_back( param.map[i][j] );
		}
	}

	vector<Building> Houses{};
	vector<Building> Chickens{};

	for ( int i{}; i < n; ++i ) {
		for ( int j{}; j < n; ++j ) {
			if ( map[i][j] == (int)MAP::HOUSE )
				Houses.emplace_back( i + 1, j + 1 );
			else if ( map[i][j] == (int)MAP::CHICKEN )
				Chickens.emplace_back( i + 1, j + 1 );
		}
	}

	for ( auto& chicken : Chickens ) {
		for ( auto& house : Houses ) {
			chicken.min_dist += chicken.GetDistanceTo( house );
		}
	}

	sort( Chickens.begin(), Chickens.end() );

	for ( auto& house : Houses ) {
		int min_num{ numeric_limits<int>::max() };
		for ( int i{}; i < m; ++i ) {
			min_num = min( min_num, house.GetDistanceTo( Chickens[i] ) );
		}
		result += min_num;
	}

	return result;
}

Result BookSolution( Param param )
{
	return Result{};
}
