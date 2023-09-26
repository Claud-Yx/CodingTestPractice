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
    test_sets = list()
    for i in range(0, len(file), 2):
        test_sets.append(TestSet(file[i], file[i+1]))

    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolution(Solution, i + 1, test_set.money, test_set.result)

