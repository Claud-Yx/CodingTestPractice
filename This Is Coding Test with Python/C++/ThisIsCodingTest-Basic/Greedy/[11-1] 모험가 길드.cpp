#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> v;

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n;
		p.v.reserve( p.n );

		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v.emplace_back( elm );
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

		string strnum = "[" + to_string( ts.num ) + "]";

		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "N: {}\n", ts.param.n );

		out = format_to( out, "{:5} | ", "" );
		for ( int n{}; const auto i : ts.param.v ) {
			out = format_to( out, "{} ", i );
			++n;
		}

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/11-1.txt" ) };

	cout << "My Solution : Greedy ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	cout << endl;
	cout << "Book's Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

// Greedy
Result MySolution( Param param )
{
	Result result{};

	sort( param.v.begin(), param.v.end(), greater<>() );

	int max_num{}, group_num{};

	for ( int i{}; i < param.n; ++i ) {
		int cur_group_num{};

		for ( int j{ i }; j < param.n; ++j ) {
			if ( max_num <= 0 ) {
				max_num = param.v[j];
				++cur_group_num;
			}

			--max_num;
		}

		group_num = max( group_num, cur_group_num );
	}

	result = group_num;

	return result;
}

Result BookSolution( Param param )
{
	Result result{};

	sort( param.v.begin(), param.v.end() );

	int cnt{};				// 현재 그룹에 포함된 모험가 수

	for ( int i : param.v ) {	// 공포도를 낮은 것부터 하나씩 확인
		++cnt;				// 현재 그룹에 해당 모험가 포함

		if ( cnt >= i ) {	// 현재 그룹에 포함된 모험가 수가 현재 공포도 이상이라면 그룹 결성
			++result;		// 총 그룹 수 증가
			cnt = 0;		// 현재 그룹에 포함된 모험가 수 초기화
		}
	}

	return result;
}