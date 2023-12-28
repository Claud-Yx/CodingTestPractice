#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> v{};
	int k{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n;

		int elm{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm;
			p.v.emplace_back( elm );
		}

		is >> p.k;

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
		out = format_to( out, "K: {}", ts.param.k );

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
		for ( int i : ts.param.v )
			out = format_to( out, "{} ", i );

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/11-6.txt" ) };

	cout << "My Solution : Greedy ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << endl;
	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

/*
 풀이:
*/

Result MySolution( Param param )
{
	Result result{};

	// 비교 연산자 재정의, using문
	using Elm = pair<int, int>;

	struct LessKey {
		bool operator() ( const Elm& lhs, const Elm& rhs ) {
			return lhs.first < rhs.first;
		};
	};

	struct LessValue {
		bool operator() ( const Elm& lhs, const Elm& rhs ) {
			return lhs.second < rhs.second;
		};
	};

	// 각 음식의 번호와 섭취 시간을 pair(dict) 타입으로 저장
	vector<Elm> v{};
	for ( int i{}; i < param.n; ++i ) {
		v.emplace_back( i + 1, param.v[i] );
	}

	// 섭취 시간 기준 오름차순으로 정렬
	sort( v.begin(), v.end(), LessValue());

	// 편리한 delete를 위해 list로 복사
	list<Elm> l{ v.begin(), v.end() };
	int k{ param.k };

	// 섭취 시간이 빠른 음식부터 꺼내오기
	auto p{ l.begin() };

	while ( p != l.end() or l.empty() ) {
		int eat_time{ p->second };
		size_t eat_all_time{ eat_time * l.size() };

		// 현재 음식을 다 먹기 전에 네트워크 장애가 발생했을 때
		if ( 0 > k - eat_all_time ) {
			size_t idx{ k % eat_all_time };
			l.sort( LessKey() );	// 남은 음식의 번호를 오름차순으로 정렬

			auto iter{ l.begin() };
			for ( int j{}; j < idx; ++j ) {
				++iter;
			}

			result = ( *iter ).first;
			break;
		}

		// 넷장애 시간 초세기
		k -= eat_all_time;

		// 모든 음식 섭취 시간 빼기
		auto iter{ l.begin() };
		auto cur_l_size{ l.size() };
		for ( int j{}; j < cur_l_size; ++j ) {
			iter->second -= eat_time;

			if ( iter->second == 0 ) {	// 다 먹었다면
				auto tmp{ iter };
				++tmp;
				l.erase( iter );
				iter = tmp;
			}
			else
				++iter;
		}

		p = next;
	}

	if ( k >= 0 )
		result = -1;

	return result;
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}