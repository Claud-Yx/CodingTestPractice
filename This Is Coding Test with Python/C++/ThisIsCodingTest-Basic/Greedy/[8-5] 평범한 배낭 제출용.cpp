#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

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

Result MySolution( Param param );

int main()
{
	Param param;
	cin >> param;
	cout << MySolution( param );
}

Result MySolution( Param param )
{
	static int g_count{};
	++g_count;
	//{
	//	auto itr = remove_if( param.v.begin(), param.v.end(), []( const auto& lhs ) {
	//		return lhs.second <= 0;
	//		} );
	//	param.v.erase( itr, param.v.end() );
	//}

	vector<int> v_values( param.k + 1, 0 );	// 최대 무게에 따른 가치 최대값
	vector<vector<vector<int>>> v_indices( param.k + 1, vector<vector<int>>{} );	// DP Table, 무게에 따라 담을 물건의 index를 가짐
	v_indices[0].push_back( {} );	//

	for ( int i{ 1 }; i <= param.k; ++i ) {
		v_values[i] = v_values[i - 1];	// 이전 무게를 기준
		//v_indices[i] = v_indices[i - 1];

		for ( int j{}; j < param.v.size(); ++j ) {
			const int cur_w = param.v[j].first;		// 현 물건 무게
			const int cur_v = param.v[j].second;	// 현 물건 가치
			const int sub_i{ i - cur_w };			// 현 물건을 뺐을 때의 무게

			// 최대 무게보다 물건이 무거우면 무시
			if ( sub_i < 0 )
				continue;

			// 최대값이 되는 모든 경우의 수를 경유
			for ( int k{ -1 }; const auto & vi : v_indices[sub_i] ) {
				++k;

				// v_indices[sub_i]에 해당 index(j)가 있다면? 이미 가방에 싸놓은 상태, 무시.
				if ( find( vi.begin(), vi.end(), j ) != vi.end() )
					continue;

				// 가치가 가장 높은 경우'들' 찾기
				const int sum_v = v_values[sub_i] + cur_v;
				if ( v_values[i] <= sum_v ) {
					v_values[i] = sum_v;
					v_indices[i].push_back( vi );
					v_indices[i].back().emplace_back( j );
				}
			}

		}

		// 최댓값이 아닌 값들 제거
		{
			auto itr = remove_if( v_indices[i].begin(), v_indices[i].end(), [&]( const auto& lhs ) {
				int num = accumulate( lhs.begin(), lhs.end(), 0, [&]( const auto& lhs, const auto& rhs ) {
					return lhs + param.v[rhs].second;
					} );
				return num < v_values[i];
				} );

			v_indices[i].erase( itr, v_indices[i].end() );
		}

		// 중복배열 제거
		{
			for ( auto& v : v_indices[i] )
				sort( v.begin(), v.end() );
			sort( v_indices[i].begin(), v_indices[i].end() );


			auto itr = unique( v_indices[i].begin(), v_indices[i].end() );

			v_indices[i].erase( itr, v_indices[i].end() );
		}

	}

	return v_values.back();
}