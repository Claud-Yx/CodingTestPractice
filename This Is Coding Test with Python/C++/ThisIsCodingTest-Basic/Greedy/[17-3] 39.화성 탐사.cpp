// --Coding Test Address Here--

#include "core.h"

#define CP_NUM "17-3"

#ifdef P17_3
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<vector<int>> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		int tmp{};

		for ( int i{}; i < self.n; ++i )
		{
			self.v.push_back( {} );
			for ( int j{}; j < self.n; ++j )
			{
				is >> tmp;

				self.v.back().push_back( tmp );
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
		auto out = format_to( ctx.out(), "{}", ts );
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

		// Parameter Line
		out = format_to( out, "n: {}", ts.param.n );

		for ( int i{}; i < ts.param.n; ++i )
		{
			out = format_to( out, "\n{:^6}| ", "" );
			for ( int j{}; j < ts.param.n; ++j )
			{
				out = format_to( out, "{} ", ts.param.v[i][j] );
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
 ????
*/

#include <queue>
#include <array>
#undef max

struct Spot {
	int x{}, y{};
	int cost{};
	Spot* prev{};

	bool operator<( const Spot& other ) const
	{
		return cost > other.cost;
	}

	bool operator==( const Spot& other ) const
	{
		return ( y == other.y && x == other.x );
	}
};

bool IsValidSpot( const Spot& spot, const Spot& prev_dir, int n )
{
	if ( spot.y == prev_dir.y && spot.x == prev_dir.x ) return false;
	else if ( spot.y < 0 ) return false;
	else if ( spot.y >= n ) return false;
	else if ( spot.x < 0 ) return false;
	else if ( spot.x >= n ) return false;
	return true;
}

Result MySolution( Param param )
{
	Result result{};

	int n = param.n;
	vector<vector<int>> v = param.v;
	vector<vector<int>> dt = v;

	for ( auto& y : dt )
	{
		for ( auto& x : y )
		{
			x = numeric_limits<int>::max();	// data table 理쒕?媛믪쑝濡?珥덇린??
		}
	}

	priority_queue<Spot> q{};
	q.emplace( 0, 0, v[0][0], new Spot{-1, -1, -1, nullptr});

	while ( !q.empty() )
	{
		auto spot = q.top();
		auto& dt_elm = dt[spot.y][spot.x];
		q.pop();

		dt_elm = min<int>( spot.cost, dt_elm );

		// ?ㅼ쓬 ??諛⑺뼢
		Spot dirs[]{
			{ spot.x, spot.y - 1, 0, new Spot{spot} },
			{ spot.x + 1, spot.y, 0, new Spot{spot} },
			{ spot.x, spot.y + 1, 0, new Spot{spot} },
			{ spot.x - 1, spot.y, 0, new Spot{spot} }
		};

		for ( auto& dir : dirs )
		{
			if ( IsValidSpot( dir, *spot.prev, n ) )
			{
				dir.cost = v[dir.y][dir.x] + spot.cost;	// ?ㅼ쓬 媛??μ냼???뚮え?됯낵 ?꾩옱源뚯????꾩쟻 ?뚮え?됱쓣 ?뷀븿

				if ( dt[dir.y][dir.x] > dir.cost )	// ?ㅼ쓬 媛??μ냼???덉쓣 ?뚮え?됰낫???묐떎硫?
				{
					q.emplace( dir );				// queue???깅줉
				}
			}
			else
			{
				delete dir.prev;
			}
		}

		delete spot.prev;
	}

	result = dt[n - 1][n - 1];

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
	// Start coding here


	return 0;
}

#endif SUBMIT
#endif