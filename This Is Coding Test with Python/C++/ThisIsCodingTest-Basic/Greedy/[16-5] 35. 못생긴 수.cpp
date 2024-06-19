// --Coding Test Address Here--

#include "core.h"

#define CP_NUM "16-5"

#ifdef P16_5
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

using Param = int;
using Result = int;

struct TestSet {
	int num{};
	Param param{};
	Result result{};

	TestSet() = default;
	TestSet( Param p, Result r ) {
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

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );

		// Parameter Line
		out = format_to( out, "n: {}", ts.param );
		out = format_to( out, "\n{:^6}| ", "" );

		// Result Line
		out = format_to( out, "\n{:^6}| ", "" );
		out = format_to( out, "\n{:^6}| Result: {}", "", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice " << CP_NUM << " =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/" + string( CP_NUM ) + ".txt" ) };

	cout << "My Solution =========================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << "\nBook's Solution =========================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

/*
 ???
*/


Result MySolution( Param param )
{
	Result result{};

	vector<bool> ugly_nums{ false, true };	// 0怨?1??紐살깮湲????щ?

	int order{ 1 };
	for ( int num{ 2 }; order < param; ++num )
	{
		int div = num;

		if ( div % 5 == 0 )
		{
			div /= 5;
		}
		else if ( div % 3 == 0 )
		{
			div /= 3;
		}
		else if ( div % 2 == 0 )
		{
			div /= 2;
		}
		else
		{
			div -= div;
		}

		/*
			2 -> loop

			2 / 2 = 1
			1 = ugly
			== 2 = ugly
		*/

		if ( ugly_nums[div] )
		{
			ugly_nums.push_back( true );
			++order;
		}
		else
		{
			ugly_nums.push_back( false );
		}
	}

	result = ugly_nums.size() - 1;

	return result;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}
#endif VSTOOL

// For submit

#ifdef SUBMIT

#include <iostream>

using namespace std;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG
	// Start coding here


	return 0;
}

#endif SUBMIT
#endif