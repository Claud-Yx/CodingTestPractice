#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{}, k{};
	vector<vector<int>> v{};

	friend istream& operator>>( istream& is, Param& p )
	{
		is >> p.n >> p.k;

		char elm{};
		for ( int i{}; i < p.n; ++i ) {
			p.v.push_back( {} );
			for ( int j{}; j < p.k; ++j ) {
				is >> elm;
				p.v[i].push_back( atoi( &elm ) );
			}
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

		out = format_to( out, "n: {} | m: {}\n", ts.param.n, ts.param.k );

		out = format_to( out, " {:4} | {}\n", "", "Map" );
		for ( const auto& v : ts.param.v ) {
			out = format_to( out, " {:4} | ", "" );
			for ( const auto i : v )
				out = format_to( out, "{}", i );
			out = format_to( out, "\n" );
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
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/5-3.txt" ) };

	cout << "My Solution ==================\n";
	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, Result, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	//cout << "Book's Solution ==================\n";
	//for ( int i{}; const auto & test_set : test_sets ) {
	//	OutputTestSolution<Param, Result, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
	//	cout << endl;
	//}
}

Result MySolution( Param param )
{
	// 
	using MAP = vector<vector<int>>;

	const static int BLANK{ 0 }, WALL{ 6 }, WATCHING{ 7 };	// ���� ���� 7�� ����

	enum DIR { N, E, S, W, CNT };	// ����

	struct POS { int y{}, x{}; };	// ��ġ 2D ����
	const static POS DIRS[]{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} };	// ���� ���� ����

	struct CCTV {
		int num{};	// ����(1~5)
		POS pos{};	// ��ġ
		array<bool, DIR::CNT> dirs{};	// ������ ���� ����
		CCTV* next{};	// ���� CCTV(���� ����Ʈ)

		CCTV() = default;
		CCTV( int num, POS pos, array<bool, DIR::CNT> dirs ) :
			num{ num }, pos{ pos }, dirs{ dirs } {}

		// �ش��ϴ� ���� �����ϱ�
		void Watch( MAP& map )
		{
			// 4���� Ȯ��
			for ( DIR d{}; d < DIR::CNT; d = DIR( int( d ) + 1 ) ) {

				// �� ������ �� �����ΰ�?
				if ( dirs[d] ) {
					POS np{ pos.y, pos.x };

					while ( true ) {
						// �ٶ󺸴� ������ ���� ĭ(��ǥ)
						np = { np.y + DIRS[d].y, np.x + DIRS[d].x };

						// map ���� ����°�
						if ( np.y < 0 or np.y >= map.size() or np.x < 0 or np.x >= map.front().size() )
							break;

						// 6(��)�ΰ�
						if ( map[np.y][np.x] == WALL )
							break;

						// �ش� ��ġ�� ������
						map[np.y][np.x] = WATCHING;
					}
				}
			}
		}

		// ȸ����Ű��
		void Rotate( int cnt )
		{
			// bool[4]�� �� ĭ�� �̴� ���
			// ��) ( T, F, F, F ) -> ( F, T, F, F )
			rotate( dirs.begin(), dirs.begin() + cnt, dirs.end() );
		}

		// DFS�� ��� ������ ����� �� Ȯ�� (map�� ����)
		// ��) 1[W], 2[W]: 5, 1[W], 2[E]: 3 ...
		void WatchDFS( MAP map, int& min_bs ) {

			// CCTV���� �ּ� ȸ�� ���� �޶� �̹��� ����ȭ�� �غ�����
			int iter{};
			switch ( num ) {
			case 1:
			case 3:
			case 4:
				iter = 4;
				break;
			case 2:
				iter = 2;
				break;
			case 5:
				iter = 1;
			}

			// ȸ�� �� ��ŭ�� �ݺ�
			for ( int i{}; i < iter; ++i ) {
				// �� �ܰ迡�� ���� map�� ����
				MAP tmp_map{ map };

				// ���ô� ���۷������� map�� �����ϵ���
				Watch( tmp_map );

				// ��尡 �����ٸ�? (next == end)
				if ( not next ) {

					// ���������� ������� map�� �簢���� ���� ����
					int cnt = accumulate( tmp_map.begin(), tmp_map.end(), 0, []( const int& lhs, auto& rhs ) {
						return lhs + accumulate( rhs.begin(), rhs.end(), 0, []( const int& lhs, auto& rhs ) {
							return lhs + ( rhs == BLANK ? 1 : 0 );
							} );
						} );

					// �ּҰ�(���۷���)�� ��� ���� �簢������ �� �� �� ���� ���� min_bs�� �Ҵ�
					min_bs = min( min_bs, cnt );
				}
				else
					// ���� ���(CCTV)�� �ִٸ� �ش� CCTV�� ���� ������ Ȯ��
					next->WatchDFS( tmp_map, min_bs );

				// �� ���� ȸ��
				Rotate( 1 );
			}

		}
	};

	// �ּҰ��� map�� ũ��
	Result min_bs{ param.n * param.k };

	// CCTV ����Ʈ
	CCTV* CCTVs{};

	for ( int y{}; y < param.n; ++y )
		for ( int x{}; x < param.k; ++x ) {
			int i = param.v[y][x];
			array<bool, DIR::CNT> tmp_dirs{};

			// CCTV �������� ���� ������ �����ش�.
			switch ( i ) {
			case 1:
				tmp_dirs = { false, true, false, false };	// E
				break;
			case 2:
				tmp_dirs = { false, true, false, true };	// E W
				break;
			case 3:
				tmp_dirs = { true, true, false, false };	// N E
				break;
			case 4:
				tmp_dirs = { true, true, true, false };		// N E S
				break;
			case 5:
				tmp_dirs = { true, true, true, true };		// N E S W
				break;
			default:
				continue;
			}

			// ����Ʈ�� �߰�
			CCTV* new_cctv{ new CCTV{ i, {y, x}, tmp_dirs } };

			if ( not CCTVs )
				CCTVs = new_cctv;
			else {
				new_cctv->next = CCTVs;
				CCTVs = new_cctv;
			}
		}

	// CCTV�� �� �� �̻� �ִٸ� Ž�� ����
	if ( CCTVs != nullptr )
		CCTVs->WatchDFS( param.v, min_bs );

	// CCTV�� ���ٸ� �� ĭ�� ã����
	else {
		int cnt = accumulate( param.v.begin(), param.v.end(), 0, []( const int& lhs, auto& rhs ) {
			return lhs + accumulate( rhs.begin(), rhs.end(), 0, []( const int& lhs, auto& rhs ) {
				return lhs + ( rhs == BLANK ? 1 : 0 );
				} );
			} );

		min_bs = min( min_bs, cnt );
	}

	return min_bs;
}

Result BookSolution( Param param )
{
	return 0;
}

//#include <iostream>
//#include <vector>
//#include <array>
//#include <functional>
//#include <numeric>
//
//using namespace std;
//
//struct Param {
//	int n{}, m{};
//	vector<vector<int>> v{};
//
//	friend istream& operator>>( istream& is, Param& p )
//	{
//		is >> p.n >> p.m;
//
//		char elm{};
//		for ( int i{}; i < p.n; ++i ) {
//			p.v.push_back( {} );
//			for ( int j{}; j < p.m; ++j ) {
//				is >> elm;
//				p.v[i].push_back( atoi( &elm ) );
//			}
//		}
//
//		return is;
//	}
//};
//
//using Result = int;
//
//using MAP = vector<vector<int>>;
//
//const static int BLANK{ 0 }, WALL{ 6 }, WATCHING{ 7 };
//
//enum DIR { N, E, S, W, CNT };
//
//struct POS { int y{}, x{}; };
//const static POS DIRS[]{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
//
//struct CCTV {
//	int num{};
//	POS pos{};
//	array<bool, DIR::CNT> dirs{};
//	CCTV* next{};
//
//	CCTV() = default;
//	CCTV( int num, POS pos, array<bool, DIR::CNT> dirs ) :
//		num{ num }, pos{ pos }, dirs{ dirs } {}
//
//	void Watch( MAP& map )
//	{
//		for ( DIR d{}; d < DIR::CNT; d = DIR( int( d ) + 1 ) ) {
//			if ( dirs[d] ) {
//				POS np{ pos.y, pos.x };
//
//				while ( true ) {
//					np = { np.y + DIRS[d].y, np.x + DIRS[d].x };
//
//					if ( np.y < 0 or np.y >= map.size() or np.x < 0 or np.x >= map.front().size() )
//						break;
//					if ( map[np.y][np.x] == WALL )
//						break;
//
//					map[np.y][np.x] = WATCHING;
//				}
//			}
//		}
//	}
//
//	void Rotate( int cnt )
//	{
//		rotate( dirs.begin(), dirs.begin() + cnt, dirs.end() );
//	}
//
//	void WatchDFS( MAP map, int& min_bs ) {
//		int iter{};
//		switch ( num ) {
//		case 1:
//		case 3:
//		case 4:
//			iter = 4;
//			break;
//		case 2:
//			iter = 2;
//			break;
//		case 5:
//			iter = 1;
//		}
//
//		for ( int i{}; i < iter; ++i ) {
//			MAP tmp_map{ map };
//			Watch( tmp_map );
//
//			if ( not next ) {
//				int cnt = accumulate( tmp_map.begin(), tmp_map.end(), 0, []( const int& lhs, auto& rhs ) {
//					return lhs + accumulate( rhs.begin(), rhs.end(), 0, []( const int& lhs, auto& rhs ) {
//						return lhs + ( rhs == BLANK ? 1 : 0 );
//						} );
//					} );
//
//				min_bs = min( min_bs, cnt );
//			}
//			else
//				next->WatchDFS( tmp_map, min_bs );
//
//			Rotate( 1 );
//		}
//
//	}
//};
//
//Result MySolution( Param param )
//{
//	Result min_bs{ param.n * param.m };
//
//	CCTV* CCTVs{};
//
//	for ( int y{}; y < param.n; ++y )
//		for ( int x{}; x < param.m; ++x ) {
//			int i = param.v[y][x];
//			array<bool, DIR::CNT> tmp_dirs{};
//
//			switch ( i ) {
//			case 1:
//				tmp_dirs = { false, true, false, false };
//				break;
//			case 2:
//				tmp_dirs = { false, true, false, true };
//				break;
//			case 3:
//				tmp_dirs = { true, true, false, false };
//				break;
//			case 4:
//				tmp_dirs = { true, true, true, false };
//				break;
//			case 5:
//				tmp_dirs = { true, true, true, true };
//				break;
//			default:
//				continue;
//			}
//
//			CCTV* new_cctv{ new CCTV{ i, {y, x}, tmp_dirs } };
//
//			if ( not CCTVs )
//				CCTVs = new_cctv;
//			else {
//				new_cctv->next = CCTVs;
//				CCTVs = new_cctv;
//			}
//		}
//
//	if ( CCTVs != nullptr )
//		CCTVs->WatchDFS( param.v, min_bs );
//	else {
//		int cnt = accumulate( param.v.begin(), param.v.end(), 0, []( const int& lhs, auto& rhs ) {
//			return lhs + accumulate( rhs.begin(), rhs.end(), 0, []( const int& lhs, auto& rhs ) {
//				return lhs + ( rhs == BLANK ? 1 : 0 );
//				} );
//			} );
//
//		min_bs = min( min_bs, cnt );
//	}
//
//	return min_bs;
//}
//
//int main()
//{
//	while ( true ) {
//		Param param;
//
//		cin >> param;
//
//		cout << MySolution( param ) << endl;
//	}
//
//	return 0;
//}