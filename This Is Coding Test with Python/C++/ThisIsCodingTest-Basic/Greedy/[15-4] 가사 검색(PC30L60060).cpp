// https://programmers.co.kr/learn/courses/30/lessons/60060

#include "core.h"

#define CP_NUM "15-4"
#define CASE 2

#ifdef P15_4
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include "CodingTester.h"

using namespace std;

struct Param {
	int wn{}, qn{};
	vector<string> words{}, queries{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.wn;

		string str{};
		for ( int i{}; i < self.wn; ++i )
		{
			is >> str;
			self.words.push_back( str );
		}

		is >> self.qn;

		for ( int i{}; i < self.qn; ++i )
		{
			is >> str;
			self.queries.push_back( str );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<int> v{};

	bool operator==( const Result& other )
	{
		if ( n != other.n )
			return false;

		if ( v != other.v )
			return false;
		return true;
	}

	friend istream& operator>>( istream& is, Result& self )
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

// Only Result Formmater
template <>
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "" );

		for ( int i{}; i < ts.n; ++i )
			out = format_to( out, "{} ", ts.v[i] );

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
		string title{"word"};
		out = format_to( out, "\n{:^6}| ", title );
		for ( int i{}; i < ts.param.wn; ++i )
		{
			out = format_to( out, "{} ", ts.param.words[i] );
		}

		title = "query";
		out = format_to( out, "\n{:^6}| ", title );
		for ( int i{}; i < ts.param.qn; ++i )
		{
			out = format_to( out, "{} ", ts.param.queries[i] );
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
 일단 이 문제는 regex를 사용하면 매우 쉽게 풀 수 있을 것 같아서 시도해본다. (Case 1)
 -> 효율성 문제 5 중 3 가 실패!

 이진 탐색을 이용하자. (Case 2)

 - 이진 탐색은 정렬된 단어 사이에서 query를 통해 수행 ([frodo front frost...] 사이에서 fro?? 로) -> upper/lower bound 사용
 - 단어의 길이로 다시 한 번 구분해야 함 -> unordered_map 사용
 - '?'는 각각 'a'와 'z'로 치환하여 탐색할 수 있도록 함
   
   예) 3글자 단어들 [abc, cde, fgh, bbc, fag] 중 'f??'로 질의한다면?
	   1. 단어들을 정렬 -> [abc, bbc, cde, fag, fgh]
       2. 'faa'와 'fzz' 로 경계 생성
	   3. 그 사이의 단어 수 == 검색 결과 수 -> faa <= [fag, fgh] <= fzz, 2개
*/


#if (CASE == 1)
Result MySolution( Param param )
{
	Result result{};

	// Input
	auto words = param.words;
	auto queries = param.queries;

	for ( auto& query : queries )
	{
		string re_str = regex_replace( query, regex( R"(\?)" ), "." );
		regex re( re_str );

		int amount{};
		for ( const auto& word : words )
		{
			if ( regex_match( word, re ) )
				++amount;
		}

		result.v.push_back( amount );
	}
	
	result.n = result.v.size();
	return result;
}

#elif (CASE == 2)

unordered_map<int, vector<string>> GenerateWordsByLength(const vector<string>& words)
{
	unordered_map<int, vector<string>> m{};

	for ( const auto& word : words )
	{
		m[word.size()].push_back( word );
	}

	for ( auto& v : m )
	{
		sort( v.second.begin(), v.second.end() );
	}

	return m;
}

// 이진 탐색을 사용해 패턴에 맞는 단어 수를 계산
int CountMatches( const vector<string>& sorted_words, const string& query ) {
	string lower = query, upper = query;
	replace( lower.begin(), lower.end(), '?', 'a');  // '?'를 'a'로 치환
	replace( upper.begin(), upper.end(), '?', 'z');  // '?'를 'z'로 치환

	auto lower_bound_ = lower_bound( sorted_words.begin(), sorted_words.end(), lower );
	auto upper_bound_ = upper_bound( sorted_words.begin(), sorted_words.end(), upper );

	return distance( lower_bound_, upper_bound_ );
}

Result MySolution( Param param )
{
	Result answer{};

	// Input
	auto words = param.words;
	auto queries = param.queries;

	// 뒤집힌 단어 리스트 (odorf)
	vector<string> reversed_words = words;
	for ( string& word : reversed_words ) {
		reverse( word.begin(), word.end() );
	}

	auto words_by_length = GenerateWordsByLength(words);
	auto reversed_words_by_length = GenerateWordsByLength(reversed_words);

	for ( const string& query : queries ) {
		if ( query[0] == '?' ) {
			// 접두사 '?' 처리: 단어를 뒤집어서 검색
			string reversed_query = query;
			reverse( reversed_query.begin(), reversed_query.end() ); // ????o -> o????
			answer.v.push_back( CountMatches( reversed_words_by_length[query.size()], reversed_query));
		}
		else {
			// 접미사 '?' 처리: 정방향으로 검색
			answer.v.push_back( CountMatches( words_by_length[query.size()], query));
		}
	}

	answer.n = answer.v.size();
	return answer;
}
#endif

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