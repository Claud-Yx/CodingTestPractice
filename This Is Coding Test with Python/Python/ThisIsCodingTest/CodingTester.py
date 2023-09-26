import os


def ReadTestFile(path):
    with open(path, 'r') as file:
        elms = file.read().split()
        elms = [int(elm) if elm.isdigit() else elm for elm in elms]

    return elms


def TestSolution(solution, test, valid):
    return valid == solution(test)


def OutputResult(num, test, expect, valid, result):
    numstr = "[" + str(num) + "]"
    print(f"{numstr:>4} | {test:20} | {expect:15} | {valid:15} | {result}")


def OutputTestSolution(solution, num, test, valid):
    OutputResult(num, test, solution(test), valid, TestSolution(solution, test, valid))


def OutputTestSolutionExt(solution, num, test, valid, TestSetClass):
    result = solution(test)
    test_set = TestSetClass(num, test, result)

    print(format(test_set))
    print("=" * 50)
    print(f" Valid Result: {valid} | {result == valid}")


if __name__ == "__main__":
    a = ReadTestFile("../../TestSets/3-1.txt")
    for e in a:
        print(e)
