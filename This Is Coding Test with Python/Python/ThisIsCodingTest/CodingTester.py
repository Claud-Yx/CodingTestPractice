import os


def ReadTestFile(path):
    with open(path, 'r') as file:
        elms = file.read().split()
        elms = [int(elm) if elm.isdigit() else elm for elm in elms]

    return elms


def TestSolution(solution, test, valid):
    return valid == solution(test)


def OutputResult(num, test, expect, valid, result):
    numstr = "[" + num + "]"
    print(f"{numstr:>4} | {test:20} | {expect:15} | {valid:15} | {result}")


def OutputTestSolution(solution, num, test, valid):
    OutputResult(num, test, solution(test), valid, TestSolution(solution, test, valid))


if __name__ == "__main__":
    a = ReadTestFile("../../TestSets/3-1.txt")
    for e in a:
        print(e)
