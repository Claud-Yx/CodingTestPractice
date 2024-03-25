// ============================================================================================
// 문제)
// N개의 원소를 포함하고 있는 수열이 오름차순으로 정렬되어 있습니다. 이때 이 수열에서 x가 등장
// 하는 횟수를 계산하세요. 예를 들어 수열 {1, 1, 2, 2, 2, 2, 3}이 있을 때 x = 2라면, 현재 수열에서
// 값이 2인 원소가 4개이므로 4를 출력합니다.
// 
// 단, 이 문제는 시간 복잡도 O(logN)으로 알고리즘을 설계하지 않으면 '시간 초과' 판정을 받습니다.
// 
// 입력 조건: 첫째 줄에 N과 x가 정수 형태로 공백으로 구분되어 입력됩니다.
//           (1 <= N <= 1,000,000), (-10^9 <= x <= 10^9)
//			 둘째 줄에 N개의 원소가 정수 형태로 공백으로 구분되어 입력됩니다.
//			 (-10^9 <= 각 원소의 값 <= 10^9)
// 
// 출력 조건: 수열의 원소 중ㅇ서 값이 x인 원소의 개수를 출력합니다. 단, 값이 x인 원소가 하나도 없다면
//           -1을 출력합니다.
//=============================================================================================

#include "core.h"

#define CP_NUM "15-1"

#ifdef P15_1
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int N{}, x{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.N >> self.x;

		int num{};
		for ( int i{}; i < self.N; ++i ) 
		{
			is >> num;
			self.v.push_back( num );
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
		out = format_to( out, "N: {} | x: {}", ts.param.N, ts.param.x );
		out = format_to( out, "\n{:^6}| ", "" );
		for ( int i{}; i < ts.param.N; ++i )
		{
			out = format_to( out, "{} ", ts.param.v[i] );
		}
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
 풀이
*/


Result MySolution( Param param )
{
	Result result{};
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