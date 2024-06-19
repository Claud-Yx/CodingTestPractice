// https://www.acmicpc.net/problem/11404

#include "core.h"

#define CP_NUM "17-1"

#ifdef P17_1
#ifdef VSTOOL

#include <iostream>
#include <array>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, m{};
	vector<array<int, 3>> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.m;

		int tmp1{}, tmp2{}, tmp3{};
		for ( int i{}; i < self.m; ++i )
		{
			is >> tmp1 >> tmp2 >> tmp3;
			self.v.push_back( { tmp1, tmp2, tmp3 } );
		}

		return is;
	}
};

using Result = vector<vector<int>>;

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

		int tmp{};

		for ( int i{}; i < t.param.n; ++i )
		{
			t.result.push_back( {} );
			for ( int j{}; j < t.param.n; ++j )
			{
				is >> tmp;
				t.result.back().push_back( tmp );
			}


		}

		return is;
	}
};

// Only Result Formmater
template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "" );

		for ( int i{}; i < ts.size(); ++i )
		{
			out = format_to( ctx.out(), "\n{:^6}| ", "" );
			for ( int j{}; j < ts.size(); ++j )
			{
				out = format_to( ctx.out(), "{:>2} ", ts[i][j] );
			}
		}

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
		out = format_to( out, "n: {} m: {}", ts.param.n, ts.param.m );
		out = format_to( out, "\n{:^6}| ", "" );

		for ( int i{}; i < ts.param.v.size(); ++i )
		{
			for ( int j{}; j < ts.param.v[i].size(); ++j )
			{
				out = format_to( out, "{:>2} ", ts.param.v[i][j] );
			}
			out = format_to( out, "\n{:^6}| ", "" );
		}

		// Result Line
		out = format_to( out, "\n{:^6}| ", "" );
		out = format_to( out, "\n{:^6}| Result: {}\n", "", ts.result );

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
 ????
*/

#undef max
#undef min
constexpr int A{ 0 }, B{ 1 }, FARE{ 2 };
constexpr int MAX_FARE{ 1'000'000 };

Result MySolution( Param param )
{
	Result result{};


	int n = param.n, m = param.m;
	auto v = param.v;

	for ( int i{}; i < n; ++i )
	{
		result.push_back( {} );
		for ( int j{}; j < n; ++j )
		{
			if ( i == j )
			{
				result.back().push_back( 0 );
			}
			else
			{
				result.back().push_back( MAX_FARE );
			}
		}
	}

	for ( const auto& path : v )
	{
		result[path[A] - 1][path[B] - 1] = min( result[path[A] - 1][path[B] - 1], path[FARE] );
	}


	for ( int offset{}; offset < n; ++offset )
	{
		for ( int i{}; i < n; ++i )
		{
			for ( int j{}; j < n; ++j )
			{
				result[i][j] = min( result[i][j], result[i][offset] + result[offset][j] );
			}
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