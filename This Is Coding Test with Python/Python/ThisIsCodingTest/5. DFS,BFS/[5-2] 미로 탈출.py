class Param:
    def __init__(self, values: list):
        self.n, self.m, = values[:2]
        self.v = [values[2+n*self.m:2+n*self.m+self.m] for n in range(0, self.n)]


def MySolution(param: Param):
    pass


def BookSolution(param):
    from collections import deque

    # N, M을 공백을 기준으로 구분하여 입력 받기
    n, m = param.n, param.m
    # 2차원 리스트의 맵 정보 입력 받기
    graph = [[i for i in v] for v in param.v]

    # 이동할 네 가지 방향 정의 (상, 하, 좌, 우)
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]

    # BFS 소스코드 구현
    def bfs(x, y):
        # 큐(Queue) 구현을 위해 deque 라이브러리 사용
        queue = deque()
        queue.append((x, y))
        # 큐가 빌 때까지 반복하기
        while queue:
            x, y = queue.popleft()
            # 현재 위치에서 4가지 방향으로의 위치 확인
            for i in range(4):
                nx = x + dx[i]
                ny = y + dy[i]
                # 미로 찾기 공간을 벗어난 경우 무시
                if nx < 0 or nx >= n or ny < 0 or ny >= m:
                    continue
                # 벽인 경우 무시
                if graph[nx][ny] == 0:
                    continue
                # 해당 노드를 처음 방문하는 경우에만 최단 거리 기록
                if graph[nx][ny] == 1:
                    graph[nx][ny] = graph[x][y] + 1
                    queue.append((nx, ny))
        # 가장 오른쪽 아래까지의 최단 거리 반환
        return graph[n - 1][m - 1]

    return bfs(0, 0)


if __name__ == "__main__":
    import CodingTester

    class TestSet:
        def __init__(self, num, p, r):
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

    file = CodingTester.ReadTestFile("../../../TestSets/5-2.txt")
    test_sets = list()

    i = 0
    while i < len(file):
        params = [int(file[i]), int(file[i+1])]
        i += 2
        params += [int(item) for sub in file[i:i+params[1]] for item in sub]
        i += params[0]
        test_sets.append(TestSet(0, params, int(file[i])))
        i += 1

    print("My Solution =======>")
    # for i, test_set in enumerate(test_sets):
    #     CodingTester.OutputTestSolutionExt(MySolution, i + 1, test_set.param, test_set.result, TestSet)
    #     print()

    print("Book's Solution =======>")
    for i, test_set in enumerate(test_sets):
        CodingTester.OutputTestSolutionExt(BookSolution, i + 1, test_set.param, test_set.result, TestSet)
        print()
