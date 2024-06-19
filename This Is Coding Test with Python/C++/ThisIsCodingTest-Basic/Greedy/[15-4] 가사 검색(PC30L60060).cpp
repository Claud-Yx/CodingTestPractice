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
 ???
 ?쇰떒 ??臾몄젣??regex瑜??ъ슜?섎㈃ 留ㅼ슦 ?쎄쾶 ? ???덉쓣 寃?媛숈븘???쒕룄?대낯?? (Case 1)
 -> ?⑥쑉??臾몄젣 5 以?3 媛 ?ㅽ뙣!

 ?댁쭊 ?먯깋???댁슜?섏옄. (Case 2)

 - ?댁쭊 ?먯깋? ?뺣젹???⑥뼱 ?ъ씠?먯꽌 query瑜??듯빐 ?섑뻾 ([frodo front frost...] ?ъ씠?먯꽌 fro?? 濡? -> upper/lower bound ?ъ슜
 - ?⑥뼱??湲몄씠濡??ㅼ떆 ??踰?援щ텇?댁빞 ??-> unordered_map ?ъ슜
 - '?'??媛곴컖 'a'? 'z'濡?移섑솚?섏뿬 ?먯깋?????덈룄濡???
   
   ?? 3湲???⑥뼱??[abc, cde, fgh, bbc, fag] 以?'f??'濡?吏덉쓽?쒕떎硫?
	   1. ?⑥뼱?ㅼ쓣 ?뺣젹 -> [abc, bbc, cde, fag, fgh]
       2. 'faa'? 'fzz' 濡?寃쎄퀎 ?앹꽦
	   3. 洹??ъ씠???⑥뼱 ??== 寃??寃곌낵 ??-> faa <= [fag, fgh] <= fzz, 2媛?
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

// ?댁쭊 ?먯깋???ъ슜???⑦꽩??留욌뒗 ?⑥뼱 ?섎? 怨꾩궛
int CountMatches( const vector<string>& sorted_words, const string& query ) {
	string lower = query, upper = query;
	replace( lower.begin(), lower.end(), '?', 'a');  // '?'瑜?'a'濡?移섑솚
	replace( upper.begin(), upper.end(), '?', 'z');  // '?'瑜?'z'濡?移섑솚

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

	// ?ㅼ쭛???⑥뼱 由ъ뒪??(odorf)
	vector<string> reversed_words = words;
	for ( string& word : reversed_words ) {
		reverse( word.begin(), word.end() );
	}

	auto words_by_length = GenerateWordsByLength(words);
	auto reversed_words_by_length = GenerateWordsByLength(reversed_words);

	for ( const string& query : queries ) {
		if ( query[0] == '?' ) {
			// ?묐몢??'?' 泥섎━: ?⑥뼱瑜??ㅼ쭛?댁꽌 寃??
			string reversed_query = query;
			reverse( reversed_query.begin(), reversed_query.end() ); // ????o -> o????
			answer.v.push_back( CountMatches( reversed_words_by_length[query.size()], reversed_query));
		}
		else {
			// ?묐???'?' 泥섎━: ?뺣갑?μ쑝濡?寃??
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