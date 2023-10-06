#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.m;

		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v.push_back( elm );
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

		out = format_to( out, "n: {} | m: {}\n", ts.param.n, ts.param.m );

		out = format_to( out, " {:4} | ", "" );
		for ( const auto i : ts.param.v )
			out = format_to( out, "{} ", i );
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/7-2.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

Result MySolution( Param param )
{
	int start{};
	int end = *max_element( param.v.begin(), param.v.end() );
	Result mid{};

	while ( true ) {
		mid = (start + end) / 2;
		int amount = accumulate( param.v.begin(), param.v.end(), 0, [&]( const int& a, const int& b ) {
			return a + max( b - mid, 0 );
			} );

		if ( amount == param.m )
			break;
		else if ( amount > param.m )
			start = mid + 1;
		else
			end = mid - 1;
	}

	return mid;
}

Result BookSolution( Param param )
{
	return Result{};
}
