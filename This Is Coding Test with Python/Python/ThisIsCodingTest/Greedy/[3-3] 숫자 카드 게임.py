class Param:
    def __init__(self, values: list):
        self.n, self.m, = values[:2]
        self.v = [values[2+n*self.m:2+n*self.m+self.m] for n in range(0, self.n)]


def MySolution(param: Param):
    v = param.v
    mins = list()

    for i in v:
        i.sort()
        mins.append(i[0])

    return max(mins)


def BookSolution(param):
    v = param.v
    result = 0

    for i in v:
        result = max(min(i), result)

    return result


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
            a = f" {num_str:4} | n: {self.param.n}, m: {self.param.m}\n"
            b = str()
            for n in range(self.param.n):
                b += f"      | "
                for m in range(self.param.m):
                    b += f"{self.param.v[n][m]} "
                b += "\n"
            c = f"      | result: {self.result}"
            return a + b + c

    file = CodingTester.ReadTestFile("../../../TestSets/3-3.txt")
    test_sets = list()

    i = 0
    while i < len(file):
        test_sets.append(TestSet(0, file[i:i + file[i] * file[i+1] + 2], file[i + file[i] * file[i+1] + 2]))
        i += file[i] * file[i+1] + 3

    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(MySolution, i + 1, test_set.param, test_set.result, TestSet)
        print()

    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(BookSolution, i + 1, test_set.param, test_set.result, TestSet)
        print()
