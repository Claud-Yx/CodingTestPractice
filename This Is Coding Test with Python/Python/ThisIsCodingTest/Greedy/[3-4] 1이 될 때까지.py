class Param:
    def __init__(self, values: list):
        self.n, self.k, = values


def MySolution(param: Param):
    dividend = param.n
    divisor = param.k
    amount, remainder = 0, 0

    while dividend > 1:
        remainder = dividend % divisor
        dividend //= divisor
        amount += remainder + (1 if dividend >= 1 else -1)

        # if dividend <= 1:
        #     break

    return amount


def BookSolution(param):
    result = 0
    n, k = param.n, param.k

    while True:
        target = (n // k) * k
        result += (n - target)
        n = target

        if n < k:
            break

        result += 1
        n //= k

    return result + (n - 1)


if __name__ == "__main__":
    import CodingTester

    class TestSet:
        def __init__(self, num, p: list, r):
            self.num = num
            self.param: Param
            if p.__class__ is list:
                self.param = Param(p)
            elif p.__class__ is Param:
                self.param = p

            self.result = r

        def __format__(self, format_spec):
            num_str = "[" + str(self.num) + "]"
            a = f" {num_str:4} | n: {self.param.n}, k: {self.param.k}\n"
            b = f"      | result: {self.result}"
            return a + b

    file = CodingTester.ReadTestFile("../../../TestSets/3-4.txt")
    test_sets = list()

    i = 0
    while i < len(file):
        test_sets.append(TestSet(0, file[i:i+2], file[i+2]))
        i += 3

    print("My Solution =======>")
    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(MySolution, i + 1, test_set.param, test_set.result, TestSet)
        print()

    print("Book's Solution =======>")
    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(BookSolution, i + 1, test_set.param, test_set.result, TestSet)
        print()
