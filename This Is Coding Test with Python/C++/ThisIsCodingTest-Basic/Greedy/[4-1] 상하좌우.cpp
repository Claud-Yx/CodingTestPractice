#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<char> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		char elm{};
		is >> elm;

		while ( elm != '\n' and elm != '\0' ) {
			if ( elm == ' ' ) {
				elm = static_cast<char>( is.get() );
				continue;
			}

			self.v.push_back( elm );

			elm = static_cast<char>( is.get() );
		}

		return is;
	}
};

struct Result {
	int x{}, y{};

	bool operator==( const Result& other ) const
	{
		return ( x == other.x ) && ( y == other.y );
	}

	friend istream& operator>>( istream& is, Result& self )
	{
		is >> self.y >> self.x;

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
		auto out = format_to( ctx.out(), "{} {}", ts.y, ts.x );
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

		out = format_to( out, "n:{}\n", ts.param.n );

		out = format_to( out, "{:5} | ", "" );
		for ( const auto& elm : ts.param.v ) {
			out = format_to( out, "{} ", elm );
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/4-1.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

Result MySolution( Param param )
{
	const int x_max{ param.n }, y_max{ param.n };
	Result pos{ 1, 1 };

	for ( const auto& dir : param.v ) {
		switch ( dir ) {
		case 'R':
			pos.x += 1;
			break;
		case 'L':
			pos.x -= 1;
			break;
		case 'U':
			pos.y -= 1;
			break;
		case 'D':
			pos.y += 1;
			break;
		}

		pos.x = clamp( pos.x, 1, x_max );
		pos.y = clamp( pos.y, 1, y_max );
	}

	return pos;
}

Result BookSolution( Param param )
{
	return Result{};
}
