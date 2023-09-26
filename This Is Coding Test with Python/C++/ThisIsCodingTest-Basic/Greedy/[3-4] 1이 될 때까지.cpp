#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	int k{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.k;

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

		out = format_to( out, "n:{}, k:{}\n", ts.param.n, ts.param.k );
		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

int MySolution( Param param );
int BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/3-4.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, int, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, int, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

int MySolution( Param param )
{
	int dividend = param.n;
	int divisor = param.k;
	int remainder{}, amount{};
	
	do {
		remainder = dividend % divisor;
		dividend /= divisor;
		amount += remainder + (dividend < 1 ? -1 : 1);
	} while ( dividend > 1 );

	return amount;
}

int BookSolution( Param param )
{
	return 0;
}
