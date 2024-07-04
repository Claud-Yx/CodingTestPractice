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
 ????
 ??곕뼊 ???얜챷???regex???????롢늺 筌띲끉????꾩쓺 ?? ????됱뱽 野?揶쏆늿釉????뺣즲????? (Case 1)
 -> ??μ몛???얜챷??5 餓?3 揶쎛 ??쎈솭!

 ??곸춭 ?癒?퉳????곸뒠??륁쁽. (Case 2)

 - ??곸춭 ?癒?퉳?? ?類ｌ졊????λ선 ????癒?퐣 query?????퉸 ??묐뻬 ([frodo front frost...] ????癒?퐣 fro?? 嚥? -> upper/lower bound ????
 - ??λ선??疫뀀챷?졿에???쇰뻻 ??甕??닌됲뀋??곷튊 ??-> unordered_map ????
 - '?'??揶쏄낫而?'a'?? 'z'嚥?燁살꼹???뤿연 ?癒?퉳??????덈즲嚥???
   
   ?? 3疫꼲????λ선??[abc, cde, fgh, bbc, fag] 餓?'f??'嚥?筌욌뜆???뺣뼄筌?
	   1. ??λ선??쇱뱽 ?類ｌ졊 -> [abc, bbc, cde, fag, fgh]
       2. 'faa'?? 'fzz' 嚥?野껋럡????밴쉐
	   3. 域????????λ선 ??== 野꺜??野껉퀗????-> faa <= [fag, fgh] <= fzz, 2揶?
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

// ??곸춭 ?癒?퉳??????????쉘??筌띿쉶????λ선 ??? ?④쑴沅?
int CountMatches( const vector<string>& sorted_words, const string& query ) {
	string lower = query, upper = query;
	replace( lower.begin(), lower.end(), '?', 'a');  // '?'??'a'嚥?燁살꼹??
	replace( upper.begin(), upper.end(), '?', 'z');  // '?'??'z'嚥?燁살꼹??

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

	// ??쇱춿????λ선 ?귐딅뮞??(odorf)
	vector<string> reversed_words = words;
	for ( string& word : reversed_words ) {
		reverse( word.begin(), word.end() );
	}

	auto words_by_length = GenerateWordsByLength(words);
	auto reversed_words_by_length = GenerateWordsByLength(reversed_words);

	for ( const string& query : queries ) {
		if ( query[0] == '?' ) {
			// ?臾먮あ??'?' 筌ｌ꼶?? ??λ선????쇱춿??곴퐣 野꺜??
			string reversed_query = query;
			reverse( reversed_query.begin(), reversed_query.end() ); // ????o -> o????
			answer.v.push_back( CountMatches( reversed_words_by_length[query.size()], reversed_query));
		}
		else {
			// ?臾???'?' 筌ｌ꼶?? ?類ｊ컩?關?앮에?野꺜??
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