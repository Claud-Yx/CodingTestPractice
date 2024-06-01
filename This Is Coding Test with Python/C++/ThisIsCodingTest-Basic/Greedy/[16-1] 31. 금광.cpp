#include "core.h"

#define CP_NUM "16-1"

#ifdef P16_1
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

struct Param {
	int x, y;
	vector<vector<int>> mine;

	friend istream& operator>>( istream& is, Param& self )
	{
		int tmp{};
		is >> self.y;

		is >> self.x;

		for ( int y{}; y < self.y; ++y )
		{
			self.mine.push_back( {} );
			for ( int x{}; x < self.x; ++x )
			{
				is >> tmp;
				self.mine.back().push_back( tmp );
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
		for ( int y{}; y < ts.param.y; ++y ) {
			out = format_to( out, "\n{:^6}| ", "" );

			for ( int x{}; x < ts.param.x; ++x )
				out = format_to( out, "{} ", ts.param.mine[y][x] );
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
	int y = param.y;
	int x = param.x;
	auto mine = param.mine;

	// Vars
	auto table = mine;	// 오른쪽으로 갈 수록 작아질 수는 없기 때문에 가능

	// Logic
	for ( int X{}; X < x - 1; ++X )
	{
		for ( int Y{}; Y < y; ++Y )
		{
			// 이동한 후 캔 금의 양 구하기
			int cur_amount = table[Y][X];

			// 전방
			table[Y][X + 1] = max( table[Y][X + 1], cur_amount + mine[Y][X + 1] );

			// 위
			if ( Y > 0 )
			{
				table[Y - 1][X + 1] = max( table[Y - 1][X + 1], cur_amount + mine[Y - 1][X + 1] );
			}

			// 아래
			if ( Y < y - 1 )
			{
				table[Y + 1][X + 1] = max( table[Y + 1][X + 1], cur_amount + mine[Y + 1][X + 1] );
			}
		}
	}

	auto max_elm = max_element( table.begin(), table.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.back() < rhs.back();
		}
	);

	result = max_elm->back();

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