#include <iostream>
#include <vector>
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
			p.v.push_back( elm );
		}

		return is;
	}
};

using Result = vector<int>;

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

		int elm{};
		for ( int i{}; i < t.param.n; ++i ) {
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

		auto out = format_to( ctx.out(), "");
		for ( const auto i : ts )
			out = format_to( out, "{} ", i );

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

		out = format_to( out, "n: {}\n", ts.param.n );
		
		out = format_to( out, "{:5} | ", "" );

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/6-1.txt" ) };

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
	Result v{ param.v };

	sort( v.begin(), v.end(), greater() );

	return v;
}

Result BookSolution( Param param )
{
	return Result{};
}
