// =================================================================================
// 문제)
// 고정점(Fixed Point)이란, 수열의 원소 중에서 그 값이 인덱스와 동일한 원소를 의미합니다.
// 예를 들어 수열 a = {-15, -4, 2, 8, 13}이 있을 때 a[2] = 2이므로, 고정점은 2가 됩니다.
// 
// 하나의 수열이 N개의 서로 다른 원소를 포함하고 있으며, 모든 원소가 오름차순으로 정렬되어
// 있습니다. 이때 이 수열에서 고정점이 있다면, 고정점을 출력하는 프로그램을 작성하세요.
// 고정점은 최대 1개만 존재합니다. 만약 고정점이 없다면 -1을 출력합니다.
// 
// 단, 이 문제는 시간 복잡도 O(logN)으로 알고리즘을 설계하지 않으면 '시간 초과' 판정을 받습니다.
// 
// 입력 조건: 첫째 줄에 N이 입력됩니다. (1 <= N <= 1,000,000)
//			 둘째 줄에 N개의 원소가 정수 형태로 공백으로 구분되어 입력됩니다.
//			 (-10^9 <= 각 원소의 값 <= 10^9)
// 
// 출력 조건: 고정점을 출력합니다. 고정점이 없다면 -1을 출력합니다.
// =================================================================================

#include "core.h"

#define CP_NUM "15-2"

#ifdef P15_2
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param
{
	int N{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.N;

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

struct TestSet
{
	int num{};
	Param param{};
	Result result{};

	TestSet() = default;
	TestSet( Param p, Result r )
	{
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

// Only Result Formmater
template <>
struct std::formatter<Result>
{
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx )
	{
		auto out = format_to( ctx.out(), "{}", ts );
		return out;
	}
};

template <>
struct std::formatter<TestSet>
{
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx )
	{

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );

		// Parameter Line
		out = format_to( out, "N: {}", ts.param.N );
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
	for ( int i{}; const auto & test_set : test_sets )
	{
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
 다음 두 개의 배열이 존재한다고 가정해보자.
 [  0,  1, 2, 3,  4]
 [-15, -4, 1, 3, 13]

 위 두 배열은 인덱스와 원소를 배열화 한 것이다.

 여기서 이진탐색을 진행하는데, 중앙값과 인덱스를 비교하는 것이다.
 만약 위 처럼 중앙값(1)이 인덱스(2)보다 작다면 우측에서 이진탐색을 진행한다.

 우측 배열
 [3,  4]
 [3, 13]

 여기서는 중앙값(3)과 인덱스(3)이 동일하게 나오므로, 답은 3이 된다.
*/

Result MySolution( Param param )
{
	Result result{};
	auto v{ param.v };

	int min{};
	int max = v.size() - 1;
	int mid{};

	while ( true )
	{
		mid = min + ( max - min ) / 2;
		if ( mid == v[mid] ) // 중앙값과 인덱스가 같다면 == 답
		{
			result = mid;
			break;
		}
		else if ( mid < v[mid] ) // 인덱스 < 중앙값
			max = mid - 1;
		else					// 인덱스 > 중앙값
			min = mid + 1;

		if ( max == min )		// 이진탐색의 마지막 원소를 발견했을 때
		{
			if ( max == v[max] )
				result = max;
			else				// 중앙값과 인덱스(min==max==mid)가 다르다면 == 결과 없음
				result = -1;
			break;
		}
	}


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