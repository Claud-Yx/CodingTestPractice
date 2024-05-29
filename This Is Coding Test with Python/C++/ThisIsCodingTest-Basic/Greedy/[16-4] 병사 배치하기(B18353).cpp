// --Coding Test Address Here--

#include "core.h"

#define CP_NUM "16-4"

#ifdef P16_4
#ifdef VSTOOL

#include <iostream>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		int tmp{};
		for ( int i{}; i < self.n; ++i )
		{
			is >> tmp;
			self.v.push_back( tmp );
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

		for ( int i{}; i < ts.param.n; ++i )
		{
			out = format_to( out, "{} ", ts.param.v[i]);
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
 앞뒤 사람의 전투력을 비교하고, 뒷 사람의 전투력이 앞 사람보다 높거나 같다면 둘 중 한 명이 빠져야 한다.

*/


Result MySolution( Param param )
{
	Result result{};

	int pop = param.n;
	auto forces = param.v;

	vector<int> dt( pop, 1 );
	reverse( forces.begin(), forces.end() );

	for ( int i{ 1 }; i < pop; ++i )
	{
		for ( int j{}; j < i; ++j )
		{
			if ( forces[j] < forces[i] ) // 뒷 사람의 전투력이 같거나 크다면
			{
				dt[i] = max( dt[i], dt[j] - 1 );
			}
		}
	}

	result = pop - *max_element( dt.begin(), dt.end() );

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