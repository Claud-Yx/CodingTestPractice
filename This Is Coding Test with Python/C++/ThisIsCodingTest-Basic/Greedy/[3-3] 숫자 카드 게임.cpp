#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	int k{};
	vector<vector<int>> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.k;

		int elm{};
		for ( int n{}; n < self.n; ++n ) {
			self.v.push_back( {} );
			for ( int m{}; m < self.k; ++m ) {
				is >> elm;
				self.v[n].emplace_back(elm);
			}
		}

		return is;
	}
};

struct TestSet {
	int num{};
	Param param{};
	int result{};

	TestSet() = default;
	TestSet( Param p, int r ) {
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

		out = format_to( out, "N:{}, M:{}\n", ts.param.n, ts.param.k );

		for ( int n{}; n < ts.param.n; ++n ) {
		out = format_to( out, "{:5} | ", "" );

			for ( int m{}; m < ts.param.k; ++m ) {
				out = format_to( out, "{} ", ts.param.v[n][m] );
			}
			out = format_to( out, "\n" );
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

int MySolution( Param param );
int BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/3-3.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, int, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, int, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

int MySolution( Param param )
{
	auto v = param.v;
	vector<int> mins{};

	for ( auto elm : v )
		mins.emplace_back( *min_element(elm.begin(), elm.end()) );
	
	return *max_element( mins.begin(), mins.end() );
}

int BookSolution( Param param )
{
	auto v = param.v;
	int result{};

	for ( auto elm : v )
		result = max( *min_element( elm.begin(), elm.end() ), result );

	return result;
}
