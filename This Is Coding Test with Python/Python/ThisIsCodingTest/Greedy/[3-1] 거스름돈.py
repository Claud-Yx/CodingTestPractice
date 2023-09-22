def Solution(money):
    coins = [500, 100, 50, 10]
    coin_cnt = 0

    for coin in coins:
        coin_cnt += money // coin
        money %= coin

    return coin_cnt

if __name__ == "__main__":
    import CodingTester

    class TestSet:
        def __init__(self, money, result):
            self.money = money
            self.result = result

    file = CodingTester.ReadTestFile("../../../TestSets/3-1.txt")
    TestSets = [TestSet(money, result) for money, result in ]

    print(file)
    # CodingTester.OutputTestSolution(Solution, )
