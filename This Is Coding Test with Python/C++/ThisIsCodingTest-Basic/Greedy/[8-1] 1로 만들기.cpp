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

		out = format_to( out, "X: {}\n", ts.param );

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/8-1.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	cout << "Book's Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

Result MySolution( Param param )
{
	Result result{};

	while ( param > 1 ) {
		int i = param - 1;

		if ( param % 5 == 0 )
			param /= 5;
		else if ( i % 5 == 0 )
			param -= 1;
		else if ( param % 3 == 0 )
			param /= 3;
		else if ( i % 3 == 0 )
			param -= 1;
		else if ( param % 2 == 0 )
			param /= 2;
		else
			param -= 1;
		++result;
	}

	return result;
}

Result BookSolution( Param param )
{
	vector<int> v( param + 1 , 0 );

	int i{ 2 };
	while ( i <= param ) {
		// X - 1
		v[i] = v[i - 1] + 1;

		// X / 5
		if ( i % 5 == 0 )
			v[i] = min( v[i], v[i / 5] + 1 );

		// X / 3
		if ( i % 3 == 0 )
			v[i] = min( v[i], v[i / 3] + 1 );

		// X / 2
		if ( i % 2 == 0 )
			v[i] = min( v[i], v[i / 2] + 1 );

		++i;
	}

	return v[param];
}
