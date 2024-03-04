// https://www.acmicpc.net/problem/18310

#include "core.h"

#define CP_NUM "14-2"

#ifdef P14_2
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

using int64 = __int64;

struct Param {
	int n{};
	vector<int64> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;
		unsigned int num{};
		for ( int i{}; i < self.n; ++i )
		{
			is >> num;
			self.v.push_back( num );
		}

		return is;
	}
};

using Result = int64;
;

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

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );

		// Parameter Line
		out = format_to( out, "n: {}", ts.param.n );
		for ( int i{}; i < ts.param.n; )
		{
			out = format_to( out, "\n{:^6}| ", "" );
			for ( int j{}; j < 8; ++j )
			{
				out = format_to( out, "{} ", ts.param.v[i++]);
				if ( i >= ts.param.n )
					break;
			}
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
 각 집에서의 안테나 설치 시뮬레이션을 돌린다.
 그 중 안테나 거리 합이 가장 짧으며 집의 위치가 가장 작은 값을 도출해낸다.

 -> 결국 중앙값을 구하는 것이므로, 정렬 후 중앙값을, 짝수라면 더 작은 수를 도출한다.

*/

#undef max
#undef min

Result MySolution( Param param )
{
	Result result{};

	int n{ param.n };
	vector<int64> v{ param.v };

	sort( v.begin(), v.end() );
	return v[(n-1)/2];

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
#include <limits>
#include <algorithm>

using namespace std;

using int64 = __int64;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG
	int n{};
	vector<int64> v{};

	cin >> n;

	int64 num{};
	for ( int i{}; i < n; ++i )
	{
		cin >> num;
		v.push_back( num );
	}

	sort( v.begin(), v.end() );
	cout << v[( n - 1 ) / 2];

	return 0;
}

#endif SUBMIT
#endif