// https://www.acmicpc.net/problem/14501

#include "core.h"

#define CP_NUM "16-3"

#ifdef P16_3
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<pair<int, int>> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		int tmp1{}, tmp2{};

		for ( int i{}; i < self.n; ++i )
		{
			is >> tmp1 >> tmp2;
			self.v.push_back( {tmp1, tmp2} );
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
		out = format_to( out, "n: {}", ts.param.n );
		out = format_to( out, "\n{:^6}| ", "" );

		for ( int day{}; const auto& elm : ts.param.v )
		{
			out = format_to( out, "\n{:>3}일 | {}일 - {}만원", ++day, elm.first, elm.second);
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

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/"+ string( CP_NUM ) + ".txt" ) };

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

	int resignation_date = param.n;
	vector<int> dt( resignation_date, 0);

	for ( int day{}; day < resignation_date; ++day )
	{
		int duration = param.v[day].first;
		int pay = param.v[day].second;

		int end_date = duration + day;
		if ( end_date <= resignation_date )		// 퇴사 기간을 넘기지 않아야 금액 추가가 가능
		{
			dt[day] += pay;	// 상담 시작일에 금액 추가 d[1] : 10

			if ( end_date < resignation_date )
			{
				for ( int i{ end_date }; i < resignation_date; ++i )
				{
					dt[i] = max( dt[i], dt[day] );	// 상담 끝나는 날에 시작일의 금액과 비교하여 추가
				}
			}
		}
	}

	result = *max_element( dt.begin(), dt.end() );

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

//#include <bits/stdc++.h>

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

	int resignation_date{};
	cin >> resignation_date;

	vector<pair<int, int>> v{};

	for ( int i{}; i < resignation_date; ++i )
	{
		int tmp1{}, tmp2{};
		cin >> tmp1 >> tmp2;
		v.push_back( { tmp1, tmp2 } );
	}

	vector<int> dt( resignation_date, 0 );

	for ( int day{}; day < resignation_date; ++day )
	{
		int duration = v[day].first;
		int pay = v[day].second;

		int end_date = duration + day;
		if ( end_date <= resignation_date )		// 퇴사 기간을 넘기지 않아야 금액 추가가 가능
		{
			dt[day] += pay;	// 상담 시작일에 금액 추가

			if ( end_date < resignation_date )
			{
				for ( int i{ end_date }; i < resignation_date; ++i )
				{
					dt[i] = max( dt[i], dt[day] );	// 상담 끝나는 날에 시작일의 금액과 비교하여 추가
				}
			}
		}
	}

	int result = *max_element( dt.begin(), dt.end() );

	cout << result;

	return 0;
}

#endif SUBMIT
#endif