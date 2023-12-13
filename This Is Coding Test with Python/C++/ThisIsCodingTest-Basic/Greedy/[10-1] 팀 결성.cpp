#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <ranges>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<array<int, 3>> v;

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.m;
		p.v.reserve( p.m );

		int elm1{}, elm2{}, elm3{};
		for ( int i{}; i < p.m; ++i ) {
			is >> elm1 >> elm2 >> elm3;
			p.v.push_back( { elm1, elm2, elm3 } );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<string> v{};

	friend istream& operator>>( istream& is, Result& r )
	{
		is >> r.n;
		int s{};

		for ( int i{}; i < r.n; ++i ) {
			is >> s;
			r.v.push_back( s == 1 ? "YES" : "NO" );
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

		out = format_to( out, "N: {} M: {}\n", ts.param.n, ts.param.m );

		for ( int n{}; const auto i : ts.param.v ) {
			out = format_to( out, "{:5} | ", "" );
			out = format_to( out, "{} {} {}\n", i[0], i[1], i[2] );
			++n;
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result);

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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/10-1.txt" ) };

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

int FindParent( vector<int> v, int a ) {
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
	vector<int> parents{};
	Result result{};

	for ( int i{}; i < param.v.size(); ++i )
		parents.push_back( i );

	for ( auto& e : param.v ) {
		if ( e[0] == 0 )
			UnionParent( parents, e[1], e[2] );
		if ( e[0] == 1 )
			result.v.push_back( ( FindParent( parents, e[1] ) == e[2] ) ? "YES" : "NO" );
	}

	return result;
}

Result BookSolution( Param param )
{
	return Result{};
}