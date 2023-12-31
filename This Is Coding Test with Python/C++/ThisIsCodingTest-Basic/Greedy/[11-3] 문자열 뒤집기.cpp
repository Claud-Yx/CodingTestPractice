#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

using Param = string;
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
		out = format_to( out, "{} ", ts.param );

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/11-3.txt" ) };

	cout << "My Solution : Greedy ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	cout << endl;
	cout << "Book's Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

// Greedy
Result MySolution( Param param )
{
	Result result{};

	int num_0{}, num_1{};

	char cur{};
	for ( auto c : param ) {
		if ( cur != c ) {
			cur = c;

			switch ( c ) {
			case '0':
				++num_0;
				break;
			case '1':
				++num_1;
				break;
			}
		}
	}

	result = min( num_0, num_1 );

	return result;
}

Result BookSolution( Param param )
{
	Result result{};

	int count0{}, count1{};

	if ( param[0] == '1' )
		count0 += 1;
	else
		count1 += 1;

	for ( int i{}; i < param.length(); ++i ) {
		if ( param[i] != param[i + 1] ) {
			if ( param[i + 1] == '1' )
				count0 += 1;
			else
				count1 += 1;
		}
	}

	result = min( count0, count1 );

	return result;
}