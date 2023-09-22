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
	예제 3-1 거스름돈
	당신은 음식점의 계산을 도와주는 점원이다. 카운터에는 거스름돈으로 사용할 500원, 100원,
	50원, 10원짜리 동전이 무한히 존재한다고 가정한다. 손님에게 거슬러 줘야 할 돈이 N원일 때,
	거슬러 줘야 할 동전의 최소 개수를 구하여라. 단, 거슬러 줘야 할 돈 N은 항상 10의 배수이다.
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