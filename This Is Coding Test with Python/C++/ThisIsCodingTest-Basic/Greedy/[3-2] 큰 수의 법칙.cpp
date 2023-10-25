/*
����)
  'ū ���� ��Ģ'�� �Ϲ������� ��� �о߿��� �ٷ������ ���������� �����̴� ���θ��� ������� �ٸ���
 ����ϰ� �ִ�. �������� ū ���� ��Ģ�� �پ��� ���� �̷���� �迭�� ���� �� �־��� ������
 M�� ���Ͽ� ���� ū ���� ����� ��Ģ�̴�. ��, �迭�� Ư���� �ε���(��ȣ)�� �ش��ϴ� ���� ����
 �ؼ� K���� �ʰ��Ͽ� ������ �� ���� ���� �� ��Ģ�� Ư¡�̴�.
  ���� ��� ������� 2, 4, 5, 4, 6���� �̷���� �迭�� ���� �� M�� 8�̰�, K�� 3�̶�� ��������.
 �� ��� Ư���� �ε����� ���� �����ؼ� �� �������� ������ �� �����Ƿ� ū ���� ��Ģ�� ���� �����
 6 + 6 + 6 + 5 + 6 + 6 + 6 + 5�� 46�� �ȴ�.
  ��, ���� �ٸ� �ε����� �ش��ϴ� ���� ���� ��쿡�� ���� �ٸ� ������ �����Ѵ�. ���� ��� ����
 ��� 3, 4, 3, 4, 3���� �̷���� �迭�� ���� �� M�� 7�̰�, K�� 2��� ��������, �� ��� �� ��°
 ���ҿ� �ش��ϴ� 4�� �� ��° ���ҿ� �ش��ϴ� 4�� ������ �� ���� ���ϴ� ���� �����ϴ�. ���������
 4 + 4 + 4 + 4 + 4 + 4 + 4�� 28�� ����ȴ�.
 �迭�� ũ�� N, ���ڰ� �������� Ƚ�� M, �׸��� K�� �־��� �� �������� ū ���� ��Ģ�� ���� �����
 ����Ͻÿ�.

�Է� ����)
 1. ù° �ٿ� N(2 <= N <= 1,000), M(1 <= M <= 1,000), K(1 <= K <= 10,000)�� �ڿ����� �־�����,
    �� �ڿ����� �������� �����Ѵ�.
 2. ��° �ٿ� N���� �ڿ����� �־�����. �� �ڿ����� �������� �����Ѵ�. ��, ������ �ڿ����� 1 �̻�
    10,000 ������ ���� �־�����.
 3. �Է����� �־����� K�� �׻� M���� �۰ų� ����.

��� ����)
 1. ù° �ٿ� �������� ū ���� ��Ģ�� ���� ������ ���� ����Ѵ�.

�Է� ����)
 5 8 3
 2 4 5 4 6

��� ����)
 46
*/

#include <iostream>
#include <vector>
#include "CodingTester.h"

using namespace std;

struct Param {
	int n{};
	int k{};
	int k{};
	vector<int> v{};

	friend istream& operator>>( istream& is, Param& self )
	{
		is >> self.n >> self.k >> self.k;
		self.v.reserve( self.n );

		int elm{};
		for ( int i{}; i < self.n; ++i ) {
			is >> elm;
			self.v.emplace_back( elm );
		}

		return is;
	}
};

struct TestSet {	
	int num{};
	Param param{};
	int result{};

	TestSet() = default;
	TestSet( Param p, int r ) {
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
		auto out = format_to( ctx.out(), " {:4} | ", strnum);
		
		out = format_to( out, "N:{}, M:{}, K:{}\n", ts.param.n, ts.param.k, ts.param.k );
		
		out = format_to( out, "{:5} | ", "");
		out = format_to( out, "Array: " );
		for ( int i{}; const auto & elm : ts.param.v ) {
			if ( ts.param.v.size() == ++i )
				out = format_to( out, "{}", elm );
			else
				out = format_to( out, "{}, ", elm );
		}
		out = format_to( out, "\n" );

		out = format_to( out, "{:5} | ", "" );
		out = format_to( out, "Result: {}", ts.result );

		return out;
	}
};

int MySolution( Param param );
int BookSolution( Param param );

int main()
{
	auto test_sets{ ReadTestFile<TestSet>( "../../../TestSets/3-2.txt" ) };

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, int, TestSet>( MySolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}

	for ( int i{}; const auto & test_set : test_sets ) {
		OutputTestSolution<Param, int, TestSet>( BookSolution, ++i, test_set.param, test_set.result );
		cout << endl;
	}
}

int MySolution( Param param )
{
    sort( param.v.begin(), param.v.end(), greater<>() );

    int snd_cnt = param.k / ( param.k + 1 );
	int max_extra_cnt = param.k % ( param.k + 1 );
    int max_cnt = ( snd_cnt < 1 ? 1 : snd_cnt ) * param.k + max_extra_cnt;

    return param.v[0] * max_cnt + param.v[1] * snd_cnt;
}

int BookSolution( Param param )
{
	sort( param.v.begin(), param.v.end() ); // �Է� ���� ���� �����ϱ�
	int first = param.v[param.n - 1]; // ���� ū ��
	int second = param.v[param.n - 2]; // �� ��°�� ū ��

	// ���� ū ���� �������� Ƚ�� ���
	int cnt = ( param.k / ( param.k + 1 ) ) * param.k;
	cnt += param.k % ( param.k + 1 );

	int result = 0;
	result += cnt * first; // ���� ū �� ���ϱ�
	result += ( param.k - cnt ) * second; // �� ��°�� ū �� ���ϱ�

	return result; // ���� ��� ���
}
