// ============================================================================================
// λ¬Έμ )
// Nκ°μ ?μλ₯??¬ν¨?κ³  ?λ ?μ΄???€λ¦μ°¨μ?Όλ‘ ?λ ¬?μ΄ ?μ΅?λ€. ?΄λ ???μ΄?μ xκ° ?±μ₯
// ?λ ?μλ₯?κ³μ°?μΈ?? ?λ? ?€μ΄ ?μ΄ {1, 1, 2, 2, 2, 2, 3}???μ ??x = 2?Όλ©΄, ?μ¬ ?μ΄?μ
// κ°μ΄ 2???μκ° 4κ°μ΄λ―λ‘?4λ₯?μΆλ ₯?©λ??
// 
// ?? ??λ¬Έμ ???κ° λ³΅μ‘??O(logN)?Όλ‘ ?κ³ λ¦¬μ¦???€κ³?μ? ?μΌλ©?'?κ° μ΄κ³Ό' ?μ ??λ°μ΅?λ€.
// 
// ?λ ₯ μ‘°κ±΄: μ²«μ§Έ μ€μ Nκ³?xκ° ?μ ?νλ‘?κ³΅λ°±?Όλ‘ κ΅¬λΆ?μ΄ ?λ ₯?©λ??
//           (1 <= N <= 1,000,000), (-10^9 <= x <= 10^9)
//			 ?μ§Έ μ€μ Nκ°μ ?μκ° ?μ ?νλ‘?κ³΅λ°±?Όλ‘ κ΅¬λΆ?μ΄ ?λ ₯?©λ??
//			 (-10^9 <= κ°??μ??κ°?<= 10^9)
// 
// μΆλ ₯ μ‘°κ±΄: ?μ΄???μ μ€γ??κ°μ΄ x???μ??κ°μλ₯?μΆλ ₯?©λ?? ?? κ°μ΄ x???μκ° ?λ???λ€λ©?
//           -1??μΆλ ₯?©λ??
//=============================================================================================

#include "core.h"

#define CP_NUM "15-1"

#ifdef P15_1
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int N{}, x{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.N >> self.x;

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

template <>
struct std::formatter<TestSet> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const TestSet& ts, FormatContext& ctx ) {

		// Example Number Line
		string strnum = "[" + to_string( ts.num ) + "]";
		auto out = format_to( ctx.out(), "{:^6}| ", strnum );

		// Parameter Line
		out = format_to( out, "N: {} | x: {}", ts.param.N, ts.param.x );
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
 ???
*/

Result MySolution( Param param )
{
	Result result{};

	int N{ param.N }, x{ param.x };
	vector<int> v{ param.v };

	auto first = lower_bound( v.begin(), v.end(), x );
	auto last = upper_bound( v.begin(), v.end(), x );

	result = distance( first, last );

	if ( result == 0 )
		result = -1;

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