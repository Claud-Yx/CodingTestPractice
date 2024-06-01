// https://www.acmicpc.net/problem/1932

#include "core.h"

#define CP_NUM "16-2"

#ifdef P16_2
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n;
	vector<vector<int>> triangle;

	friend istream& operator>>( istream& is, Param& self )
	{
		int tmp{};
		is >> self.n;

		for ( int y{}; y < self.n; ++y )
		{
			self.triangle.push_back( {} );
			for ( int x{}; x <= y; ++x )
			{
				is >> tmp;
				self.triangle.back().push_back( tmp );
			}
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
		out = format_to( out, "\n{:^6}| {}", "N", ts.param.n);
		out = format_to( out, "\n{:^6}| ", "" );

		for ( int y{}; y < ts.param.triangle.size(); ++y ) {
			out = format_to( out, "\n{:^6}| ", "" );

			for ( int x{}; x < ts.param.triangle[y].size(); ++x )
				out = format_to( out, "{} ", ts.param.triangle[y][x] );
		}

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
 풀이
*/


Result MySolution( Param param )
{
	Result result{};

	// Input
	auto n = param.n;
	auto triangle = param.triangle;

	// Vars
	auto table = triangle;

	for ( int y{}; y < n - 1; ++y )
	{
		for ( int x{}; x <= y; ++x )
		{
			int cur_amount = table[y][x];

			// Left
			table[y + 1][x] = max( table[y + 1][x], cur_amount + triangle[y + 1][x] );

			// Right
			table[y + 1][x + 1] = max( table[y + 1][x + 1], cur_amount + triangle[y + 1][x + 1] );
		}
	}

	result = *max_element( table.back().begin(), table.back().end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs < rhs;
		}
	);

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
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG
	// Start coding here
	int result{};

	// Input
	int n;
	vector<vector<int>> triangle;

	cin >> n;

	int tmp{};
	for ( int y{}; y < n; ++y )
	{
		triangle.push_back( {} );
		for ( int x{}; x <= y; ++x )
		{
			cin >> tmp;
			triangle.back().push_back( tmp );
		}
	}

	// Vars
	auto table = triangle;

	for ( int y{}; y < n - 1; ++y )
	{
		for ( int x{}; x <= y; ++x )
		{
			int cur_amount = table[y][x];

			// Left
			table[y + 1][x] = max( table[y + 1][x], cur_amount + triangle[y + 1][x] );

			// Right
			table[y + 1][x + 1] = max( table[y + 1][x + 1], cur_amount + triangle[y + 1][x + 1] );
		}
	}

	result = *max_element( table.back().begin(), table.back().end(), []( const auto& lhs, const auto& rhs )
		{
			return lhs < rhs;
		}
	);

	cout << result;

	return 0;
}

#endif SUBMIT
#endif