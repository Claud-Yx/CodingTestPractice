#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<vector<int>> v;

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n;
		p.v.reserve( p.n );

		int elm1{};
		for ( int i{}; i < p.n; ++i ) {
			p.v.push_back( {} );
		
			while ( true ) {
				is >> elm1;
				if ( elm1 == -1 )
					break;
				p.v[i].push_back( elm1 );
			}

		}

		return is;
	}
};

struct Result {
	int n{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Result& r )
	{
		int s{};

		is >> r.n;
		for ( int i{}; i < r.n; ++i ) {
			is >> s;
			r.v.push_back( s );
		}

		return is;
	}

	bool operator==( const Result& other )
	{
		if ( v.size() != other.v.size() )
			return false;

		for ( int i{}; i < v.size(); ++i ) {
			if ( v[i] != other.v[i] )
				return false;
		}

		return true;
	}
};

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

		out = format_to( out, "N: {}\n", ts.param.n );

		for ( int n{}; const auto i : ts.param.v ) {
			out = format_to( out, "{:5} | ", "" );
			for ( const auto j : i )
				out = format_to( out, "{} ", j );
			out = format_to( out, "\n" );
			++n;
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

template<>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {

		auto out = format_to( ctx.out(), "" );
		for ( int i{}; i < ts.v.size(); ++i )
			out = format_to( out, "{} ", ts.v[i] );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/10-3.txt" ) };

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

Result MySolution( Param param )
{
	Result result{};
	result.v = vector<int>( param.n + 1, {} );

	vector<int> ts( param.n + 1, 0 );								// indegree 수
	vector<vector<int>> outdegree( param.n + 1, vector<int>{} );	// outdegree 배열
	queue<int> q{};

	ts[0] == 9999;
	for ( int i{1};  const auto & e : param.v ) {
		ts[i] = e.size() - 1;

		for ( int j{ 1 }; j < e.size(); ++j )
			outdegree[e[j]].push_back(i);

		++i;
	}

	// 최초 indegree가 0인 edge를 queue에 삽입
	for ( int i{1}; i < ts.size(); ++i  )
		if ( ts[i] == 0 )
			q.push( i );

	// queue가 빌 때 까지 반복
	while ( not q.empty() ) {
		int cur = q.front();
		q.pop();

		result.v[cur] = param.v[cur - 1][0];
		for ( int i{ 1 }; i < param.v[cur - 1].size(); ++i ) {
			result.v[cur] = max( result.v[param.v[cur - 1][i]] + param.v[cur - 1][0], result.v[cur]);
		}

		for ( int i{}; i < outdegree[cur].size(); ++i ) {
			--ts[outdegree[cur][i]];

			if ( ts[outdegree[cur][i]] == 0 )
				q.push( outdegree[cur][i] );
		}
	}
	
	result.v.erase( result.v.begin() );
	return result;
}

Result BookSolution( Param param )
{
	return Result{};
}