// https://www.acmicpc.net/problem/1715

#include "core.h"

#define CP_NUM "14-4"

#ifdef P14_4
#ifdef VSTOOL

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		int num{};
		for ( int i{}; i < self.n; ++i )
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
		out = format_to( out, "n: {}", ts.param.n );
		for ( int i{}; i < ts.param.n;)
		{
			out = format_to( out, "\n{:^6}| ", "" );
			for ( int j{}; i < ts.param.n and j < 10; ++j, ++i )
				out = format_to( out, "{} ", ts.param.v[i] );
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

	cout << "\nBook's Solution =========================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

/*
 풀이
 오름차순 정렬 후 가장 작은 묶음끼리 카드를 합친다.
 카드를 합친 후 다시 정렬하여 가장 작은 묶음끼리 카드를 합쳐나간다.

 처음에는 vector에 넣고 계속 sort해서 풀어봤으나 시간초과가 났다.
 다음은 multiset을 이용했는데, 나쁘지 않았고 풀긴 풀었다.
 이후 더 짧은 시간이 나온 코드들을 살펴보니 priority_queue를 사용하더라. -> book's solution
 왜 이생각을 못했지?

 + for ( int i{}; i < n; ++i ) -> while ( n-- )
   대신, 사용한 n은 다시 사용하지 말아야 함

 * 나올 수 있는 최대값 -> int
*/

Result MySolution( Param param )
{
	ios_base::sync_with_stdio( false ), cin.tie( 0 );

	Result result{};

	// Input
	int n{ param.n };
	multiset<int> s( param.v.begin(), param.v.end() );

	auto begin{ s.begin() };
	auto next{ begin };
	++next;

	while ( next != s.end() )
	{
		result += *s.insert( *begin + *next );
		s.erase( begin );
		s.erase( next );

		begin = s.begin();
		next = begin;
		++next;
	}

	return result;
}

#include <queue>

Result BookSolution( Param param )
{
	ios_base::sync_with_stdio( false ), cin.tie( 0 );

	Result result{};

	// Input
	int n{ param.n };
	priority_queue<int, vector<int>, greater<int>> q(param.v.begin(), param.v.end());

	while ( q.size() > 1 )
	{
		int a{}, b{};
		
		a = q.top();
		q.pop();

		b = q.top();
		q.pop();

		int c = a + b;
		result += c;
		q.push( c );
	}

	return result;
}
#endif VSTOOL

// For submit

#ifdef SUBMIT

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

using ll = long long;

int main()
{
#ifdef DEBUG
	cout << "Practice " << CP_NUM << " =======================" << endl;
#endif DEBUG
	ios_base::sync_with_stdio( false ), cin.tie( 0 );

	// Start coding here
	ll result{};

	// Input
	int n{};
	multiset<ll> s{};

	// Init
	cin >> n;

	int num{};
	for ( int i{}; i < n; ++i )
	{
		cin >> num;
		s.insert( num );
	}

	auto begin{ s.begin() };
	auto next{ begin };
	++next;

	while ( next != s.end() )
	{
		result += *s.insert( *begin + *next );
		s.erase( begin );
		s.erase( next );

		begin = s.begin();
		next = begin;
		++next;
	}

	cout << result;

	return 0;
}

#endif SUBMIT
#endif