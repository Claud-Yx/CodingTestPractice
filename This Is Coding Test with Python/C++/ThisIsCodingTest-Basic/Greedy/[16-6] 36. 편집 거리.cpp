// --Coding Test Address Here--

#include "core.h"

#define CP_NUM "16-6"

#ifdef P16_6
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

struct Param {
	string A{}, B{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.A >> self.B;

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
		out = format_to( out, "A: {}", ts.param.A );
		out = format_to( out, "\n{:^6}| ", "" );
		out = format_to( out, "B: {}", ts.param.B );

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

#undef max
#undef min

Result MySolution( Param param )
{
	Result result{};

	string A = param.A, B = param.B;
	vector<vector<int>> dp{};

	for ( int i{}; i <= A.size(); ++i )
	{
		dp.push_back( {} );

		for ( int j{}; j <= B.size(); ++j )
		{
			if ( i == 0 )
			{
				dp.back().push_back( j );
			}
			else if ( j > 0 )
			{
				dp.back().push_back( numeric_limits<int>::max() );
			}
			else
			{
				dp.back().push_back( i );
			} 
		}
	}

	for ( int i{}; i < A.size(); ++i )
	{
		for ( int j{}; j < B.size(); ++j )
		{
			if ( A[i] == B[j] )	// 같은 위치의 단어가 같으면 넘어감
			{
				dp[i + 1][j + 1] = dp[i][j];
			}
			else
			{
				dp[i + 1][j + 1] = 1 + min( min(dp[i + 1][j], dp[i][j + 1]), dp[i][j] );
			}
		}
	}

	result = dp[A.size()][B.size()];

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