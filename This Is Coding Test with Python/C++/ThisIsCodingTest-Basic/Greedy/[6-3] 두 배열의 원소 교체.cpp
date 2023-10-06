#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{};
	vector<int> v1{};
	vector<int> v2{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.k;

		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v1.push_back( elm );
		}

		elm = {};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v2.push_back( elm );
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

		out = format_to( out, "n: {} | k: {}\n", ts.param.n, ts.param.k );

		out = format_to( out, "{:5} | ", "" );
		for ( const auto i : ts.param.v1 )
			out = format_to( out, "{} ", i );
		out = format_to( out, "\n" );

		out = format_to( out, "{:5} | ", "" );
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/6-3.txt" ) };

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
	Result cnt{};


	for ( int i{}; i < param.k; ++i )
		swap( *min_element( param.v1.begin(), param.v1.end() ), *max_element( param.v2.begin(), param.v2.end() ) );

	cnt = accumulate( param.v1.begin(), param.v1.end(), 0 );

	return cnt;
}

Result BookSolution( Param param )
{
	return Result{};
}
