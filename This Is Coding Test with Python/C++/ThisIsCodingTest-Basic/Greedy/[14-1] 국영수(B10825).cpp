// https://www.acmicpc.net/problem/10825

#include "core.h"

#define CP_NUM "14-1"

#ifdef P14_1
#ifdef VSTOOL

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	vector<string> name{};
	vector<int> kor{}, eng{}, math{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n;

		string name{};
		int k{}, e{}, m{};
		for ( int i{}; i < self.n; ++i )
		{
			is >> name >> k >> e >> m;

			self.name.push_back( name );
			self.kor.push_back( k );
			self.eng.push_back( e );
			self.math.push_back( m );
		}

		return is;
	}
};

struct Result {
	int n{};
	vector<string> v{};

	bool operator==( const Result& other )
	{
		if ( n != other.n )
			return false;

		if ( v != other.v )
			return false;

		//for ( int i{}; i < n; ++i )
		//	if ( v[i] != other.v[i] )
		//		return false;

		return true;
	}

	friend istream& operator>>( istream& is, Result& self )
	{
		string name{};

		is >> self.n;

		for ( int i{}; i < self.n; ++i )
		{
			is >> name;

			self.v.push_back( name );
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
struct std::formatter<Result> {
	constexpr auto parse( format_parse_context& ctx ) { return ctx.begin(); }

	template <typename FormatContext>
	auto format( const Result& ts, FormatContext& ctx ) {
		auto out = format_to( ctx.out(), "{}", "" );

		for ( int i{}; i < ts.v.size(); ++i )
		{
			out = format_to( out, "{} ", ts.v[i] );
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
		out = format_to( out, "n: {}", ts.param.n );
		for ( int i{}; i < ts.param.n; ++i )
			out = format_to( out, "\n{:^6}| {} {} {} {}", "", ts.param.name[i], ts.param.kor[i], ts.param.eng[i], ts.param.math[i]);
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
 ?€??
 1. êµ?–´ ?´ë¦¼ì°¨ìˆœ
 2. ?ì–´ ?¤ë¦„ì°¨ìˆœ
 3. ?˜í•™ ?´ë¦¼ì°¨ìˆœ
 4. ?´ë¦„ ?¬ì „???¤ë¦„ì°¨ìˆœ)
*/

struct StudentScore {
	string name{};
	int kor{}, eng{}, math{};

	StudentScore() = default;
	StudentScore( string name, int kor, int eng, int math ) :
		name{ name }, kor{ kor }, eng{ eng }, math{ math } {}
};

Result MySolution( Param param )
{
	Result result{};

	struct Comp {
		bool operator()( const StudentScore& lhs, const StudentScore& rhs ) const
		{
			if ( lhs.kor != rhs.kor )
				return lhs.kor > rhs.kor; // êµ?–´ ?ìˆ˜ê°€ ?’ì? ?™ìƒ???ì— ?¤ë„ë¡?
			if ( lhs.eng != rhs.eng )
				return lhs.eng < rhs.eng; // ?ì–´ ?ìˆ˜ê°€ ??? ?™ìƒ???ì— ?¤ë„ë¡?
			if ( lhs.math != rhs.math )
				return lhs.math > rhs.math; // ?˜í•™ ?ìˆ˜ê°€ ?’ì? ?™ìƒ???ì— ?¤ë„ë¡?
			return lhs.name < rhs.name; // ?´ë¦„???¬ì „ ?œìœ¼ë¡??ì„  ?™ìƒ???ì— ?¤ë„ë¡?
		}
	};

	vector<StudentScore> students{};

	for ( int i{}; i < param.n; ++i )
		students.emplace_back( param.name[i], param.kor[i], param.eng[i], param.math[i] );

	sort( students.begin(), students.end(), Comp() );

	result.n = param.n;

	for ( const auto& student : students )
		result.v.push_back( student.name );

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

#ifdef SUBMIT_LOOP
	while ( true ) {
#endif SUBMIT_LOOP
		// Start coding here

#ifdef SUBMIT_LOOP
	}
#endif SUBMIT_LOOP

	return 0;
}

#endif SUBMIT
#endif