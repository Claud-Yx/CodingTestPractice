// https://www.acmicpc.net/problem/14888

#include "core.h"

#ifdef P13_5
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <limits>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> nums{};
	array<int, 4> opers{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		int num{};
		for ( int i : views::iota( 0 ) | views::take( self.n ) )
		{
			is >> num;
			self.nums.emplace_back( num );
		}

		for ( auto& elm : self.opers )
		{
			is >> elm;
		}

		return is;
	}
};

using Result = array<int, 2>;

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
		is >> t.result[0] >> t.result[1];

		return is;
	}
};

template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "{} {}", ts[0], ts[1]);
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
		out = format_to( out, "n: {}", ts.param.n );
		out = format_to( out, "\n{:^5} | ", "nums" );

		for ( int i{}; i < ts.param.n; ++i )
		{
			out = format_to( out, "{} ", ts.param.nums[i] );
		}

		out = format_to( out, "\n{:^5} | ", "opers" );

		for ( int i{}; i < 4; ++i )
		{
			out = format_to( out, "{} ", ts.param.opers[i] );
		}

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | ", "" );

		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice 13-5 =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/13-5.txt" ) };

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

#undef max
#undef min

/*
 풀이
 단순하게 생각해서 모든 연산자들의 순열을 구하여 대입 및 계산 후 최소/최대 값을 구해본다.
 DFS를 사용한다면 끝까지 탐색하여 얻은 최종 결과를 비교해가며 풀 수 있을 것이다.
*/

enum OPERATOR { PLUS, MINUS, MULTIPLY, DIVISION };

Result MySolution( Param param )
{
	Result result{};
	int n{ param.n };
	vector<int> nums( param.nums );
	vector<OPERATOR> opers{};

	// 입력 받은 연산자를 각각 하나씩 넣어준다.
	for ( int i{}; i < 4; ++i )
		for ( int j{}; j < param.opers[i]; ++j )
			opers.emplace_back( (OPERATOR)i );

	ranges::sort( opers );

	int min{ numeric_limits<int>::max() };
	int max{ numeric_limits<int>::min() };

	do {
		// 맨 앞의 숫자로 연산 시작
		int result{ nums.front() };

		for ( int i{}; i < opers.size(); ++i )
		{
			int r_operand = nums[i + 1];
			switch ( opers[i] )
			{
			case PLUS:
				result += r_operand;
				break;
			case MINUS:
				result -= r_operand;
				break;
			case MULTIPLY:
				result *= r_operand;
				break;
			case DIVISION:
				result /= r_operand;
				break;
			}
		}

		max = result > max ? result : max;
		min = result < min ? result : min;
	} while ( ranges::next_permutation( opers ).found );

	result = { max, min };

	return result;
}

Result BookSolution( Param param )
{
	Result answer{};
	return answer;
}
#endif VSTOOL

// 제출용

#ifdef SUBMIT

#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <limits>

using namespace std;

using Result = array<int, 2>;
enum OPERATOR { PLUS, MINUS, MULTIPLY, DIVISION };

int main()
{
#ifdef DEBUG
	cout << "Practice 13-5 =======================" << endl;
#endif DEBUG

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP

		Result result{};
		int n{};
		vector<int> nums{};
		vector<OPERATOR> opers{};

		int tmp{};
		cin >> n;

		for ( int i{}; i < n; ++i )
		{
			cin >> tmp;
			nums.emplace_back( tmp );
		}


		// 입력 받은 연산자를 각각 하나씩 넣어준다.
		for ( int i{}; i < 4; ++i ) {
			cin >> tmp;

			for ( int j{}; j < tmp; ++j )
				opers.emplace_back( (OPERATOR)i );
		}

		ranges::sort( opers );

		int min{ numeric_limits<int>::max() };
		int max{ numeric_limits<int>::min() };

		do {
			// 맨 앞의 숫자로 연산 시작
			int result{ nums.front() };

			for ( int i{}; i < opers.size(); ++i )
			{
				int r_operand = nums[i + 1];
				switch ( opers[i] )
				{
				case PLUS:
					result += r_operand;
					break;
				case MINUS:
					result -= r_operand;
					break;
				case MULTIPLY:
					result *= r_operand;
					break;
				case DIVISION:
					result /= r_operand;
					break;
				}
			}

			max = result > max ? result : max;
			min = result < min ? result : min;
		} while ( ranges::next_permutation( opers ).found );

		result = { max, min };

		cout << max << '\n' << min;

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif P13_5