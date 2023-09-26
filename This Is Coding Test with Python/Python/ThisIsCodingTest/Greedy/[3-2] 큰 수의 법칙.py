class Param:
    def __init__(self, values: list):
        self.n, self.m, self.k = values[:3]
        self.nums = values[3:]


def MySolution(param: Param):
    param.nums.sort(reverse=True)

    snd_cnt = param.m // (param.k + 1)
    max_extra_cnt = param.m % (param.k + 1)
    max_cnt = (1 if snd_cnt < 1 else snd_cnt) * param.k + max_extra_cnt

    return param.nums[0] * max_cnt + param.nums[1] * snd_cnt


def BookSolution(param):
    param.v.sort() # 입력 받은 수들 정렬하기
    first = param.v[param.n - 1] # 가장 큰 수
    second = param.v[param.n - 2] # 두 번째로 큰 수

    # 가장 큰 수가 더해지는 횟수 계산
    count = int(param.m / (param.k + 1)) * param.k
    count += param.m % (param.k + 1)

    result = 0
    result += (count) * first # 가장 큰 수 더하기
    result += (param.m - count) * second # 두 번째로 큰 수 더하기

    return result # 최종 답안 출력


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
            a = f" {num_str:4} | n: {self.param.n}, m: {self.param.m}, k: {self.param.k}\n"
            b = f"      | array: {self.param.nums}\n"
            c = f"      | result: {self.result}"
            return a + b + c

    file = CodingTester.ReadTestFile("../../../TestSets/3-2.txt")
    test_sets = list()

    i = 0
    while i < len(file):
        test_sets.append(TestSet(0, file[i:i + file[i] + 3], file[i + file[i] + 3]))
        i += file[i] + 4

    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(MySolution, i + 1, test_set.param, test_set.result, TestSet)
        print()

    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(BookSolution, i + 1, test_set.param, test_set.result, TestSet)
        print()
