// https://school.programmers.co.kr/learn/courses/30/lessons/60058+//

#include "core.h"

#ifdef P13_4
#ifdef VSTOOL

#include <iostream>
#include <string>
#include "CodingTester.h"

using namespace std;

using Param = string;
using Result = string;

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
		out = format_to( out, "{}", ts.param );

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | ", "" );

		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice 13-4 =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/13-4.txt" ) };

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
 DFS를 사용하여 푼다.
 DFS 함수는 책에 나와있는 대로 조건문을 짜주면 된다.
 v를 DFS 재귀 함수에 인자로 넘기는 것을 기본으로 하여 의사코드를 작성해본다.

 1. if v == "": return "";				// v가 빈 문자열이라면 그대로 반환
 
 2. u = string(), v = string()			// u와 v를 string으로 선언
	u = w.substr(0, min_balanced)		// u는 균형 잡힌 부분까지 잘라서 할당
	v = w.substr(min_balanced)			// v는 나머지 부분 할당

 3. v = DFS( v )						// v에 대하여 DFS 수행, 3~4번 과정 모두 v를 DFS 하기 때문에 미리해도 상관 없다.

 4. if IsValid( u ):					// u가 올바르다면?
		u + v							// u 뒤에 DFS를 수행한 v를 이어붙이고 반환
		return u

 5. if not IsValid( u ):				// u가 올바르지 않다면?
		tmp = "(" + v + ")"				// 빈 문자열(tmp)에 '(' + v + ')' 를 할당
		u = u.substr(1, u.len() - 2)	// u의 처음, 끝 글자를 뺀 나머지를 대입한다.
		Reverse( u )					// 나머지를 뒤집어준다.
		tmp += u						// tmp 뒤에 u를 이어붙이고 반환
		return tmp
*/

string DFS( string w )
{
	// v(w)가 빈 문자열이면 그대로 반환
	if ( w.empty() )
		return w;

	// u에 들어갈 균형잡힌 문자열의 크기를 구함
	bool is_valid{ true };	// 동시에 u의 올바름(유효성)까지 검사하기 위한 bool
	int check_close{};		// 괄호가 잘 여닫히는지 체크할 int변수
	int cnt_open{}, cnt_close{};
	size_t blanced{};
	for ( const auto c : w )
	{
		++blanced;
		switch ( c )
		{
		case '(':
			++cnt_open;
			++check_close;
			break;
		case ')':
			++cnt_close;
			--check_close;
			break;
		}
		
		// check_close 가 0보다 작다면 -> 괄호가 열리지 않았는데 닫힌 것!
		if ( check_close < 0 )
			is_valid = false;

		if ( cnt_open == cnt_close )
			break;
	}

	// u 와 v를 분리
	string u{}, v{};
	u = w.substr( 0, blanced );
	v = w.substr( blanced );

	// v는 따로 DFS를 수행
	v = DFS( v );

	// u 가 올바르다면 u 뒤에 DFS를 실시한 v를 이어붙이고 반환
	if ( is_valid )
	{
		u += v;
		return u;
	}
	
	// u가 올바르지 않다면
	else
	{
		u = u.substr( 1, u.length() - 2 );	// 처음 끝 자르기

		// 모두 뒤집기
		for ( char& c : u )
		{
			switch ( c )
			{
			case '(':
				c = ')';
				break;
			case ')':
				c = '(';
				break;
			}
		}

		// 빈 문자열에 4-1 ~ 4-4 과정 수행
		string tmp{ "(" + v + ")" + u };
		return tmp;
	}

}

Result MySolution( Param param )
{
	string input = param;
	string result{};

	result = DFS( input );

	return result;
}

Result BookSolution( Param param )
{
	Result answer{};
	return answer;
}
#endif VSTOOL

// 제출용

#ifdef SUBMIT

#include <iostream>
#include <string>
#include "CodingTester.h"

using namespace std;

string DFS( string w )
{
	// v(w)가 빈 문자열이면 그대로 반환
	if ( w.empty() )
		return w;

	// u에 들어갈 균형잡힌 문자열의 크기를 구함
	bool is_valid{ true };	// 동시에 u의 올바름(유효성)까지 검사하기 위한 bool
	int check_close{};		// 괄호가 잘 여닫히는지 체크할 int변수
	int cnt_open{}, cnt_close{};
	size_t blanced{};
	for ( const auto c : w )
	{
		++blanced;
		switch ( c )
		{
		case '(':
			++cnt_open;
			++check_close;
			break;
		case ')':
			++cnt_close;
			--check_close;
			break;
		}

		// check_close 가 0보다 작다면 -> 괄호가 열리지 않았는데 닫힌 것!
		if ( check_close < 0 )
			is_valid = false;

		if ( cnt_open == cnt_close )
			break;
	}

	// u 와 v를 분리
	string u{}, v{};
	u = w.substr( 0, blanced );
	v = w.substr( blanced );

	// v는 따로 DFS를 수행
	v = DFS( v );

	// u 가 올바르다면 u 뒤에 DFS를 실시한 v를 이어붙이고 반환
	if ( is_valid )
	{
		u += v;
		return u;
	}

	// u가 올바르지 않다면
	else
	{
		u = u.substr( 1, u.length() - 2 );	// 처음 끝 자르기

		// 모두 뒤집기
		for ( char& c : u )
		{
			switch ( c )
			{
			case '(':
				c = ')';
				break;
			case ')':
				c = '(';
				break;
			}
		}

		// 빈 문자열에 4-1 ~ 4-4 과정 수행
		string tmp{ "(" + v + ")" + u };
		return tmp;
	}

}

int main()
{
	string p;
	cin >> p;

	string input = p;
	string answer{};

	answer = DFS( input );
	cout << answer;

	//return answer;
}

#endif SUBMIT
#endif P13_4