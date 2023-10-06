#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<int> v1{};
	vector<int> v2{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n;

		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v1.push_back( elm );
		}

		is >> p.m;

		elm = {};
		for ( int i{}; i < p.m; ++i ) {
			is >> elm;
			p.v2.push_back( elm );
		}

		return is;
	}
};

using Result = vector<string>;

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

		string elm{};
		for ( int i{}; i < t.param.m; ++i ) {
			is >> elm;
			t.result.push_back( elm );
		}

		return is;
	}
};

template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {

		auto out = format_to( ctx.out(), "" );
		for ( const auto& s : ts )
			out = format_to( out, "{} ", s );

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

		out = format_to( out, "n: {} | m: {}\n", ts.param.n, ts.param.m );

		out = format_to( out, " {:4} | ", "N" );
		for ( const auto i : ts.param.v1 )
			out = format_to( out, "{} ", i );
		out = format_to( out, "\n" );

		out = format_to( out, " {:4} | ", "M" );
		for ( const auto i : ts.param.v2 )
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/7-1.txt" ) };

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
	Result answers{};

	sort( param.v1.begin(), param.v1.end() );

	for ( auto i : param.v2 )
		if ( binary_search( param.v1.begin(), param.v1.end(), i ) )
			answers.push_back( "yes" );
		else
			answers.push_back( "no" );



	return answers;
}

Result BookSolution( Param param )
{
	return Result{};
}
