#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	char c{};
	int n{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.c >> p.n;
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

		out = format_to( out, "n: {}\n", ts.param );

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/4-2.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

Result MySolution( Param param )
{
	int x{ param.c - 'a' + 1 };
	int y{ param.n };

	int cnt{};

	enum DIR { U, D, L, R };
	int x_dir[] = {0, 0, -1, 1};
	int y_dir[] = {-1, 1, 0, 0};

	for ( DIR dir{}; dir <= DIR::R; dir = DIR(dir + 1) ) {

	}

	return Result{};
}

Result BookSolution( Param param )
{
	return Result{};
}
