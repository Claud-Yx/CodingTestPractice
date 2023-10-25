#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{};
	vector<pair<int, int>> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.k;

		int elm1{}, elm2{};
		for ( int i{}; i < p.n; ++i ) {
			is >> elm1 >> elm2;
			p.v.emplace_back( elm1, elm2 );
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

		out = format_to( out, "N: {} K: {}\n", ts.param.n, ts.param.k );

		for ( const auto i : ts.param.v ) {
			out = format_to( out, "{:5} | ", "" );
			out = format_to( out, "W: {} V: {}\n", i.first, i.second );
		}

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/8-5.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	cout << "Book's Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

Result MySolution( Param param )
{
	{
		auto itr = remove_if( param.v.begin(), param.v.end(), []( const auto& lhs ) {
			return lhs.second <= 0;
			} );
		param.v.erase( itr, param.v.end() );
	}

	vector<int> v_values( param.k + 1, 0 );	// �ִ� ���Կ� ���� ��ġ �ִ밪
	vector<vector<vector<int>>> v_indices( param.k + 1, vector<vector<int>>{} );	// DP Table, ���Կ� ���� ���� ������ index�� ����
	v_indices[0].push_back( {} );	//

	for ( int i{ 1 }; i <= param.k; ++i ) {
		v_values[i] = v_values[i - 1];	// ���� ���Ը� ����
		//v_indices[i] = v_indices[i - 1];

		for ( int j{}; j < param.v.size(); ++j ) {
			const int cur_w = param.v[j].first;		// �� ���� ����
			const int cur_v = param.v[j].second;	// �� ���� ��ġ
			const int sub_i{ i - cur_w };			// �� ������ ���� ���� ����

			// �ִ� ���Ժ��� ������ ���ſ�� ����
			if ( sub_i < 0 )
				continue;

			// �ִ밪�� �Ǵ� ��� ����� ���� ����
			for ( int k{ -1 }; const auto & vi : v_indices[sub_i] ) {
				++k;

				// v_indices[sub_i]�� �ش� index(j)�� �ִٸ�? �̹� ���濡 �γ��� ����, ����.
				if ( find( vi.begin(), vi.end(), j ) != vi.end() )
					continue;

				// ��ġ�� ���� ���� ���'��' ã��
				const int sum_v = v_values[sub_i] + cur_v;
				if ( v_values[i] <= sum_v ) {
					v_values[i] = sum_v;
					v_indices[i].push_back( vi );
					v_indices[i].back().emplace_back( j );
				}
			}

		}

		// �ִ��� �ƴ� ���� ����
		{
			auto itr = remove_if( v_indices[i].begin(), v_indices[i].end(), [&]( const auto& lhs ) {
				int num = accumulate( lhs.begin(), lhs.end(), 0, [&]( const auto& lhs, const auto& rhs ) {
					return lhs + param.v[rhs].second;
					} );
				return num < v_values[i];
				} );

			v_indices[i].erase( itr, v_indices[i].end() );
		}

		// �ߺ��迭 ����
		{
			for ( auto& v : v_indices[i] )
				sort( v.begin(), v.end() );
			sort( v_indices[i].begin(), v_indices[i].end() );


			auto itr = unique( v_indices[i].begin(), v_indices[i].end() );

			v_indices[i].erase( itr, v_indices[i].end() );
		}

	}

	return v_values.back();

	// 1 = 1 : 1
	// 2 = 2 : 2
	// 3 = 1, 2 : 3 | 3 : 3
	// 4 = 1, 3 : 4 | 4 : 4
	// 5 = 1, 4 : 5 | 2, 3 : 5 | 5 : 5
	// 6 = 1, 5 : 6 | 2, 4 : 6 | 1, 2, 3 : 6
	// 7 = 2, 5 : 7 | 3, 4 : 7

	// 201 = 98, 103 : 201 | 100, 101 : 201
	// ...
	// 203 = 98, 4, 101 : 203 | 100, 103 | 203
	// 204 = 98, 6, 100 : 204 | 101, 103 | 204
	// ...
	// 304 = 100, 101, 103 | 304
}

Result BookSolution( Param param )
{
	vector<vector<int>> dp( param.n + 1, vector<int>( param.k + 1, 0 ) );

	for ( int i{ 1 }; i < param.n + 1; ++i ) {
		for ( int j{ 1 }; j < param.k + 1; ++j ) {
			if ( j < param.v[j - 1].first )
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max( dp[i - 1][j], dp[i - 1][j - param.v[i - 1].first] + param.v[i - 1].second );
		}
	}

	return dp[param.n][param.k];
}