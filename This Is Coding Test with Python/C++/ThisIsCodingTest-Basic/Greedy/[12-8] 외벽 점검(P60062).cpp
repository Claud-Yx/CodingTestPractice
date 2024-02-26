// https://school.programmers.co.kr/learn/courses/30/lessons/60062

#include "core.h"

#ifdef P12_8
#ifdef VSTOOL

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, weak_n, dist_n{};
	vector<int> weak{};
	vector<int> dist{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.weak_n;

		int num{};
		for ( int i{}; i < self.weak_n; ++i ) {
			is >> num;
			self.weak.emplace_back( num );
		}

		is >> self.dist_n;

		for ( int i{}; i < self.dist_n; ++i ) {
			is >> num;
			self.dist.emplace_back( num );
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

		out = format_to( out, "n: {}", ts.param.n );

		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | [ ", "Weak" );
		for ( int i{}; const auto & elm : ts.param.weak ) {
			out = format_to( out, "{} ", elm );
		}

		out = format_to( out, "]\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | [ ", "Dist" );
		for ( int i{}; const auto & elm : ts.param.dist ) {
			out = format_to( out, "{} ", elm );
		}

		out = format_to( out, "]\n{:5} | ", "" );
		out = format_to( out, "\n{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

Result MySolution( Param param );
Result BookSolution( Param param );

int main()
{
	cout << "Practice 12-8 =======================" << endl;

	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/12-8.txt" ) };

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
친구들은 항상 약한 지점부터 시작하여 돌아야 최대 효율을 낼 것이다.
그러므로 약한 지점부터 점검을 시작하며, 모든 약한 지점을 기준으로
시계 방향으로 점검하며 투입 수가 가장 적은 경우를 찾는다.

(예시 1번을 기준)
1. data table을 만들어 각 취약 지점들의 거리를 구한다. 이 때, 시계(cw) 방향만 구하면 반시계(ccw)도 구할 수 있다.

   cw │ 1  5  6  10      ccw│ 1  5  6  10
   ───┼────────────	     ───┼────────────
   1  │ 0  8  7  3	     1  │ 0  4  5  9
   5  │ 4  0  11 7	     5  │ 8  0  1  5
   6  │ 5  1  0  8	     6  │ 7  11 0  4
   10 │ 9  5  4  0	     10 │ 3  7  8  0

2. 예를 들어, 1번에서 4의 거리를 간다면, 1과 5 지점은 확인하고 6과 10 지점만 남는다.
   이는 더 많은 벽을 확인하는, 즉 내림차순으로 확인하도록 한다.
   여기서 남은 dist는 3, 2, 1 이다.

   cw │ 1  5  6  10			cw │ 6  10
   ───┼────────────			───┼──────
   1  │ 0  8  7  3			6  │ 0  8
   5  │ 4  0  11 7    ->	10 │ 4  0
   6  │ 5  1  0  8
   10 │ 9  5  4  0

3. 다음은 한 명이 한 번에 확인할 수 없기 때문에 외벽 확인에 두 명이 소모될 것이다.
   이런식으로 진행하나, 전체 탐색이 필요하므로 DFS 알고리즘을 사용할 것이다.
*/

#undef max
//int DFS( vector<int>::iterator dist, const vector<int>::iterator& end, const vector<vector<int>>& dist_table )
//{
//	static const int kIntMax{ numeric_limits<int>::max() };
//	int result{ kIntMax };
//
//	for ( int i{}; i < dist_table.size(); ++i )
//	{
//		// 하위 탐색으로 넘길 인덱스 번호를 저장할 벡터 생성
//		vector<int> indices{};
//
//		for ( int j{}; j < dist_table.size(); ++j )
//		{
//			// 현재 갈 수 있는 최대 거리보다 멀다면 다음 탐색에서 사용될 인덱스 번호 저장
//			if ( dist_table[i][j] > *dist )
//				indices.push_back( j );
//		}
//
//		// 다음으로 넘길 벽의 정보가 없다면? -> 모든 벽을 확인한 것
//		if ( indices.empty() ) 
//		{
//			result = 1;
//			break;
//		}
//
//		// 다음으로 넘길 벽의 정보가 존재한다면? -> 아직 확인해야 함
//		else
//		{
//			auto next = dist;
//			++next;
//
//			// 남은 친구가 없다면? -> 벽을 다 돌 수 없음
//			if ( next == end )
//			{
//				result = kIntMax;
//				break;
//			}
//
//			// 친구가 남아있다면? -> 하위 탐색
//			else
//			{
//				// 하위 탐색에 사용될 테이블 생성
//				vector<vector<int>> sub_dist_table{};
//
//				for ( int y{}; y < indices.size(); ++y ) {
//					sub_dist_table.push_back( {} );
//					for ( int x{}; x < indices.size(); ++x ) {
//						sub_dist_table.back().push_back( dist_table[indices[y]][indices[x]] );
//					}
//				}
//
//				// 하위 탐색
//				int sub_result = DFS( next, end, sub_dist_table );
//
//				// 1이라면 가장 작은 값이기 때문에 바로 대입
//				if ( sub_result == 1 )
//					result = sub_result + 1;
//
//				// 1보다 높은 값이 들어왔다면 비교 후 반복 진행, 초기값(INT_MAX) 또는 이전 값과 비교함
//				else if ( sub_result > 1 )
//					result = min( result, sub_result + 1 );
//
//				// 친구들이 벽을 다 돌 수 없다면 다음 반복 진행, 코드 불필요
//				//else if ( sub_result == kIntMax )
//				//	continue;
//			}
//		}
//	}
//
//	if ( result == kIntMax )
//		result = -1;
//
//	return result;
//}

int DFS( vector<int>::iterator dist, const vector<int>::iterator& end, const vector<vector<int>>& dist_table, const vector<int> indices )
{
	static const int kIntMax{ numeric_limits<int>::max() };
	static int kCount{};
	int result{ kIntMax };

	for ( int i{}; i < indices.size(); ++i )
	{
		++kCount;
		// 하위 탐색으로 넘길 인덱스 번호를 저장할 벡터 생성
		vector<int> sub_indices{};

		for ( int j{}; j < indices.size(); ++j )
		{
			// 현재 갈 수 있는 최대 거리보다 멀다면 다음 탐색에서 사용될 인덱스 번호 저장
			if ( dist_table[indices[i]][indices[j]] > *dist )
				sub_indices.push_back( indices[j] );
		}

		// 다음으로 넘길 벽의 정보가 없다면? -> 모든 벽을 확인한 것
		if ( sub_indices.empty() )
		{
			result = 1;
			break;
		}

		// 다음으로 넘길 벽의 정보가 존재한다면? -> 아직 확인해야 함
		else
		{
			auto next = dist;
			++next;

			// 남은 친구가 없다면? -> 벽을 다 돌 수 없음
			if ( next == end )
			{
				result = kIntMax;
				break;
			}

			// 친구가 남아있다면? -> 하위 탐색
			else
			{
				// 하위 탐색
				int sub_result = DFS( next, end, dist_table, sub_indices );

				// 1이라면 가장 작은 값이기 때문에 바로 대입
				if ( sub_result == 1 )
					result = sub_result + 1;

				// 친구들이 벽을 다 돌 수 없다면 다음 반복문은 의미 없음.
				else if ( sub_result == kIntMax )
					break;

				// 1보다 높은 값이 들어왔다면 비교 후 반복 진행, 초기값(INT_MAX) 또는 이전 값과 비교함
				else if ( sub_result > 1 )
					result = min( result, sub_result + 1 );
			}
		}
	}

	if ( result == kIntMax )
		result = -1;

	return result;
}



Result MySolution( Param param )
{
	Result answer{};
	int n{ param.n };
	vector<int> weak( param.weak );
	vector<int> dist( param.dist );

	sort( dist.begin(), dist.end(), greater() );

	vector<vector<int>> cw_dist_table{};

	for ( int i{}; i < weak.size(); ++i ) {
		cw_dist_table.push_back( {} );

		for ( int j{}; j < weak.size(); ++j ) {
			int distance{};
			distance = weak[i] - weak[j];

			if ( distance < 0 )
				distance = abs( distance );
			else if ( distance > 0 )
				distance = n - distance;

			cw_dist_table.back().push_back( distance );
		}
	}

	// solution

	vector<int> indices;

	for ( int i{}; i < weak.size(); ++i )
		indices.push_back( i );

	answer = DFS( dist.begin(), dist.end(), cw_dist_table, indices );

	return answer;
}

Result BookSolution( Param param )
{
	Result answer{};
	int n{ param.n };
	vector<int> weak( param.weak );
	vector<int> dist( param.dist );

	int length = weak.size();
	// 길이를 2배로 늘려서 '원형' 을 '일자' 형태로 변형
	for ( int i{}; i < length; ++i )
		weak.push_back( weak[i] + n );

	// 최댓값으로 설정
	answer = dist.size() + 1;


	// 0부터 length - 1 까지의 위치를 각각 시작점으로 설정

	for ( int start{}; start < length; ++start )
	{
		// 친구를 나열하는 모든 경우의 수 각각에 대하여 확인
		sort( dist.begin(), dist.end() );

		do
		{
			for ( int i{}; i < dist.size(); ++i ) 
			{
				int count = 1; // 투입할 친구 수

				// 해당 친구가 점검할 수 있는 마지막 위치
				int position = weak[start] + dist[count - 1];

				// 시작점부터 모든 취약 지점 확인
				for ( int idx{ start }; idx < start + length; ++idx )
				{
					// 점검 위치를 벗어나는 경우
					if ( position < weak[idx] ) {
						count += 1; // 친구 더 투입

						if ( count > dist.size() )	// 투입이 불가능하면 종료
							break;

						position = weak[idx] + dist[count - 1];
					}
				}

				answer = min( answer, count );
			}

		} while ( next_permutation( dist.begin(), dist.end() ) );
	}

	if ( answer > dist.size() )
		answer = -1;

	return answer;
}


#endif VSTOOL

#ifdef SUBMIT
#endif SUBMIT

#endif P12_8