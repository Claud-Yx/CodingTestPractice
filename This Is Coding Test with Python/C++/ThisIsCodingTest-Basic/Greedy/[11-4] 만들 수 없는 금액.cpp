#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n;
		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v.emplace_back( elm );
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
		out = format_to( out, "N: {} ", ts.param.n );

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
		for ( int i : ts.param.v )
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/11-4.txt" ) };

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

	sort( param.v.begin(), param.v.end(), greater<>() );

	for ( int i{ 1 }; ; ++i ) {
		int num{ i };

		for ( int elm : param.v ) {
			num -= elm;

			if ( num == 0 )
				break;
			else if ( num < 0 ) {
				if ( elm == param.v.back() ) {
					result = i;
					break;
				}
				num += elm;
				continue;
			}
		}

		if ( num > 0 ) {
			result = i;
			break;
		}

		if ( result != 0 )
			break;
	}

	return result;
}

Result BookSolution( Param param )
{
	Result result{ 1 };

	sort( param.v.begin(), param.v.end() );

	for ( int i : param.v ) {
		if ( result < i )
			break;
		result += i;
	}

	return result;
}