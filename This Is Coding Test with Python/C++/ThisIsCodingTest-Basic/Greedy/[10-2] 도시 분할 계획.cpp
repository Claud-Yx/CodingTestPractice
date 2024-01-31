#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{};
	vector<array<int, 3>> v;

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.k;
		p.v.reserve( p.k );

		int elm1{}, elm2{}, elm3{};
		for ( int i{}; i < p.k; ++i ) {
			is >> elm1 >> elm2 >> elm3;
			p.v.push_back( { elm1, elm2, elm3 } );
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

// result의 fomatter도 정의해야 함

template <>
struct std::formatter<TestSet> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx ) {

		string strnum = "[" + to_string( ts.num ) + "]";

		auto out = format_to( ctx.out(), " {:4} | ", strnum );

		out = format_to( out, "N: {} M: {}\n", ts.param.n, ts.param.k );

		for ( int n{}; const auto i : ts.param.v ) {
			out = format_to( out, "{:5} | ", "" );
			out = format_to( out, "{} {} {}\n", i[0], i[1], i[2] );
			++n;
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/10-2.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

int FindParent( const vector<int>& v, int a ) {
	if ( v[a] != a )
		return FindParent( v, v[a] );
	return v[a];
};

void UnionParent( vector<int>& v, int a, int b ) {
	int e1{ FindParent( v, a ) };
	int e2{ FindParent( v, b ) };

	if ( e1 < e2 )
		v[e2] = e1;
	else
		v[e1] = e2;
};

Result MySolution( Param param )
{
	Result result{};

	class Edge {
	public:
		Edge( int a, int b, int cost ) : a{ a }, b{ b }, cost{ cost } {}

		int a{}, b{};
		int cost{};

		bool operator<( const Edge& other ) {
			return cost < other.cost;
		}
	};

	vector<Edge> edges{};
	vector<int> graph{};

	// 유지비를 오름차순으로 정렬
	for ( int i{}; i < param.k; ++i )
		edges.push_back( { param.v[i][0], param.v[i][1], param.v[i][2] } );
	sort( edges.begin(), edges.end() );

	// 서로소 그래프 초기화
	for ( int i{}; i <= param.n; ++i )
		graph.push_back( i );

	int max_n{};
	for ( const auto& e : edges ) {
		if ( FindParent( graph, e.a ) != FindParent( graph, e.b ) ) {	// root가 같지 않다면
			UnionParent( graph, e.a, e.b );	// 합치기 연산
			result += e.cost;				// 간선값 축적
			max_n = max( e.cost, max_n );	// 가장 비싼 간선값 저장
		}
	}

	result -= max_n;	// 가장 비싼 간선 끊기

	return result;
}

Result BookSolution( Param param )
{
	return Result{};
}