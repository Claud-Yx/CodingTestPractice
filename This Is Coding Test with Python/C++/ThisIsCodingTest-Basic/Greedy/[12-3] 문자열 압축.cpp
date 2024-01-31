#include <iostream>
#include <string>
#include <vector>
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-3.txt" ) };

	cout << "My Solution ==================\n";
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
/*
aabbaccc
-> 2a2ba3c

rep_str = [ [a, 2], [b, 2], [a, 1], [c, 3] ]

2a2ba3c

result = min(result, len(2a2ba3c))

*/


Result MySolution( Param param )
{
	Result result = param.length();

	for ( int size{ 1 }; size <= param.length(); ++size ) {
		vector<pair<string, int>> rep_str{};
		
		for ( int i{}; i < param.length(); i += size ) {
			string cur_str{ param.substr(i, size)};

			if ( rep_str.empty() or rep_str.back().first != cur_str )
				rep_str.emplace_back( cur_str, 0 );
			
			// aabbaccc
			// rep_str = [ [a, 2], [b, 2], [a, 1] ]

			++rep_str.back().second;
		}

		string new_str{};
		for ( const auto& elm : rep_str ) {
			if ( elm.second > 1 )
				new_str += to_string(elm.second);
			new_str += elm.first;
		}
		// 2a2ba3c

		int sum = new_str.length();
		result = min( result, sum );
	}

	return result;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}