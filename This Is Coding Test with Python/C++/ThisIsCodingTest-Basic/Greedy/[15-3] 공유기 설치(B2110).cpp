// https://www.acmicpc.net/problem/2110

#include "core.h"

#define CP_NUM "15-3"

#ifdef P15_3
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int N{}, C{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.N >> self.C;

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

// Only Result Formmater
template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "{}", ts );
		return out;
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
		out = format_to( out, "N: {} | C: {}", ts.param.N, ts.param.C );
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
 아마도 최소/최대값의 중앙값과 가장 유사한 값을 공유기 위치로 지정하는게 맞는 것 같다.

 다음은 예시 배열이다.
 
 1. 이진 탐색을 사용하기 위해 정렬해야 한다.
 
	[1 3 5 9 10]									|	[1 2 3 4 5 6 39 61 81]

 2. 공유기를 총 4개로 가정했을 때, 4개의 지점을 골라야 한다.
    여기서 항상 2개의 지점은 처음(min)과 끝(max)으로 지정한다.
 
	[1 3 5 9 10]									|	[1 2 3 4 5 6 39 61 81]
	 ^       ^										|	 ^				   ^

 3. 중앙값( min + (max-min) / 2 )을 구한다.

	median = 1 + ( 10 - 1 ) / 2 = 5.5				| median = 1 + ( 81 - 1 ) / 2 = 41

 4. 이진탐색을 진행하여 median와 가장 유사한 위치를 구한다. 그 위치가 다음 공유기의 위치가 된다.
 
	median: 5.5										|	median: 41
	[1 3 5 9 10]									|	[1 2 3 4 5 6 39 61 81]
	 ^   ^   ^										|	 ^           ^     ^	

 5. 왼쪽과 오른쪽을 mid를 포함한 두 배열로 나누어 동일하게 진행한다.
    동일하게 진행하되, 둘 중 각 중간값이 중앙값에 더 가까운 쪽을 고른다.

			left    right							|			left				right
			[1 3 5] [5 9 10]						|			[1 2 3 4 5 6 39]	[39 61 81]
	median   3	     7.5							|	median	 20					 60
	        [1 3 5] [5 9 10]						|			[1 2 3 4 5 6 39]	[39 61 81]
			   ^									|									^

 6. 결과

	[1 3 5 9 10]									|	[1 2 3 4 5 6 39 61 81]
	 ^ ^ ^   ^										|	 ^           ^  ^  ^	
	답: 2										    |	답: 20
*/

double GetMedian( int min, int max )
{
	return min + double( ( max - min ) / 2.0 );
}

Result MySolution( Param param )
{
	Result result{};

	int N{ param.N }, C{ param.C };
	auto v{ param.v };

	int min{ v.front() }, max{ v.back() }; // min과 max를 처음과 끝으로 지정한다.
	int wifi = C - 2;	// 동시에 공유기(대충 와이파이) 수를 2 줄인다.(2개를 배치했다는 의미)
	int min_distance = max - min;		// 최소 거리

	float median = 

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