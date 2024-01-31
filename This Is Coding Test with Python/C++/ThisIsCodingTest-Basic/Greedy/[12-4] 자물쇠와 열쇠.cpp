#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

using Mat = vector<vector<int>>;
const int GROOVE{ 0 }, BUMP{ 1 };

struct Param {
	int n{}, k{};
	Mat key;
	Mat lock;

	friend istream& operator>>( istream& is, Param& p ) {
		is >> p.n >> p.k;

		for ( int i{}; i < p.n; ++i ) {
			p.key.emplace_back();

			for ( int j{}; j < p.n; ++j ) {
				int num{};
				is >> num;
				p.key.back().emplace_back( num );
			}
		}

		for ( int i{}; i < p.k; ++i ) {
			p.lock.emplace_back();

			for ( int j{}; j < p.k; ++j ) {
				int num{};
				is >> num;
				p.lock.back().emplace_back( num );
			}
		}

		return is;
	}
};

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
		out = format_to( out, "N: {} M: {} ", ts.param.n, ts.param.k );

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );

		string tmp{ "key" };
		for ( int i{}; i < ts.param.n; ++i ) {
			out = format_to( out, "\n" );
			out = format_to( out, " {:4} | ", tmp );
			tmp.clear();

			for ( int j{}; j < ts.param.n; ++j )
				out = format_to( out, "{} ", ts.param.key[i][j] );
		}
		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );

		tmp = { "lock" };
		for ( int i{}; i < ts.param.k; ++i ) {
			out = format_to( out, "\n" );
			out = format_to( out, " {:4} | ", tmp );
			tmp.clear();

			for ( int j{}; j < ts.param.k; ++j )
				out = format_to( out, "{} ", ts.param.lock[i][j] );
		}

		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "\n" );
		out = format_to( out, "{:5} | ", "" );

		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-4.txt" ) };

	cout << "My Solution : Greedy ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << endl;
	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

/*
풀이:
 열쇠 돌기 개수와 자물쇠 홈 개수가 일치할 때의 경우에만 이동 및 회전을 통하여 홈을 맞춰본다.
 여기서 열쇠 돌기 개수가 자물쇠 홈 개수보다 적을 때 무조건 false
*/

pair<int, int> CountGrooveAndBump( const Mat& m )
{
	int cnt_groove{}, cnt_bump{};

	for ( const auto& row : m )
		for ( const auto& elm : row )
			if ( elm == GROOVE )
				++cnt_groove;
			else
				++cnt_bump;

	return { cnt_groove, cnt_bump };
}

Mat MakeFittedKey( const Mat& key, int ext_lock_size, pair<int, int> offset )
{
	Mat new_key{};

	for ( int i{}; i < ext_lock_size; ++i ) {
		new_key.emplace_back( vector<int>{} );

		for ( int j{}; j < ext_lock_size; ++j )
			new_key[i].emplace_back(0);
	}

	for ( int i{}; i < key.size(); ++i )
		for ( int j{}; j < key[i].size(); ++j )
			new_key[i + offset.second][j + offset.first] = key[i][j];

	return new_key;
}

Mat RotateMatrix( const Mat& mat )
{
	Mat new_mat{};

	for ( int i{}; i < mat.size(); ++i ) {
		new_mat.push_back( {} );
		for ( int j{}; j < mat[i].size(); ++j )
			new_mat[i].emplace_back(mat[mat.size() - 1 - j][i]);
	}

	return new_mat;
}

/*

000
000
000

00
00

00000
00000
00000
00000
00000

*/

bool CheckKeyToLock( const Mat& key, const Mat& lock, int origin_key_size )
{
	const int offset{ origin_key_size - 1 };
	for ( int i{ offset }; i < key.size() - offset; ++i )
		for ( int j{ offset }; j < key[i].size() - offset; ++j )
			if ( key[i][j] + lock[i][j] != BUMP )
				return false;
	return true;
}

Result MySolution( Param param )
{
	if ( CountGrooveAndBump( param.key ).second < CountGrooveAndBump( param.lock ).first )
		return "false";

	int ext_lock_size = ( param.k - 1 ) * 2 + param.n;

	Mat ext_lock = MakeFittedKey( param.lock, ext_lock_size, { param.k - 1, param.k - 1 } );

	Mat key{};

	for ( int i{}; i < param.k; ++i ) {
		key.push_back( {} );

		for ( int j{}; j < param.k; ++j )
			key[i].emplace_back( param.key[i][j] );
	}

	int max_iter{ ext_lock_size - param.k + 1 };
	for ( int i{}; i < 4; ++i ) {
		key = RotateMatrix( key );

		for ( int i{}; i < max_iter; ++i )
			for ( int j{}; j < max_iter; ++j ) {
				Mat fitted_key = MakeFittedKey( key, ext_lock_size, { j, i } );
				if ( CheckKeyToLock( fitted_key, ext_lock, param.k ) )
					return "true";
			}
	}

	return "false";
}

Result BookSolution( Param param )
{
	Result result{};
	return result;
}