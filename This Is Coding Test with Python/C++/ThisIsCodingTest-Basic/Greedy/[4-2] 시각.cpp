#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

using Param = int;
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

		out = format_to( out, "n: {}\n", ts.param );

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/4-2.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

Result MySolution( Param param )
{
	class Time {
	public:
		int h{}, m{}, s{};

		Time() = default;
		Time( int h, int m, int s ) : h{ h }, m{ m }, s{ s } {}

		void Tick()
		{
			++s;
			if ( s >= 60 ) {
				s = 0;
				++m;
				if ( m >= 60 ) {
					m = 0;
					++h;
				}
				if ( h >= 24 )
					h = 0;
			}
		}

		bool ContainThree()
		{
			string str{ to_string( h ) + to_string( m ) + to_string( s ) };
			return str.contains( "3" );
		}

		bool operator==( const Time& other ) const
		{
			return ( h == other.h ) and ( m == other.m ) and ( s == other.s );
		}
	};

	Time t;
	Time max{ param, 59, 59 };

	int cnt{};
	while ( not( t == max ) ) {
		if ( t.ContainThree() )
			++cnt;
		t.Tick();
	}

	return cnt;
}

Result BookSolution( Param param )
{
	int cnt{};

	for ( int h{}; h < param + 1; ++h ) {
		for ( int m{}; m < 60; ++m ) {
			for ( int s{}; s < 60; ++s ) {
				string str{ to_string( h ) + to_string( m ) + to_string( s ) };
				if ( str.contains( "3" ) )
					++cnt;
			}
		}
	}

	return cnt;
}
