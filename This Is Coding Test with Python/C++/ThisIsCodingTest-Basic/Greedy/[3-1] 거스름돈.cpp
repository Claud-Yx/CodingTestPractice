#include <iostream>
#include <array>
#include "CodingTester.h"

using namespace std;

class TestSet {
public:
	int money;
	int result;

	friend istream& operator>>( istream& is, TestSet& t )
	{
		is >> t.money;
		is >> t.result;
		return is;
	}
};

int MySolution( int money );
int BookSolution( int money );

int main()
{
	/*
	���� 3-1 �Ž�����
	����� �������� ����� �����ִ� �����̴�. ī���Ϳ��� �Ž��������� ����� 500��, 100��,
	50��, 10��¥�� ������ ������ �����Ѵٰ� �����Ѵ�. �մԿ��� �Ž��� ��� �� ���� N���� ��,
	�Ž��� ��� �� ������ �ּ� ������ ���Ͽ���. ��, �Ž��� ��� �� �� N�� �׻� 10�� ����̴�.
	*/

	auto v = ReadTestFile<TestSet>( filesystem::path( "../../../TestSets/3-1.txt" ) );

	cout << "My Solution ===========\n";
	for ( auto elm : v ) {
		OutputTestSolution<int, int>( MySolution, elm.money, elm.result );
	}

	cout << "Book's Solution ===========\n";
	for ( auto elm : v ) {
		OutputTestSolution<int, int>( BookSolution, elm.money, elm.result );
	}
}

int MySolution( int money )
{
	const array<int, 4> coins{ 500, 100, 50, 10 };
	int coin_cnt{};

	for ( int i{}; i < coins.size(); ++i ) {
		for ( int j{}; ; ++j ) {
			money -= coins[i];
		
			if ( money < 0 ) {
				money += coins[i];
				break;
			}

			++coin_cnt;
		}
	}

	return coin_cnt;
}

int BookSolution( int money )
{
	const array<int, 4> coins{ 500, 100, 50, 10 };
	int coin_cnt{};

	for ( auto coin : coins ) {
		coin_cnt += money / coin;
		money %= coin;
	}

	return coin_cnt;
}