#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxCharSize = 31;
const int nxt[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Point
{
    int row;
    int col;
    int step;
};

struct PrevLoc
{
    int x;
    int y;
};

int bfs(vector<Point> queue, char* map, Point end, int mapCol, PrevLoc prev[])
{
    int row = 0, col = 0;
    Point current;
    while(!queue.empty()) {
        // pop
        current = queue.front();
        if (current.col == end.col && current.row == end.row) {
            return current.step;
        }
        queue.erase(queue.begin());
        map[current.row * mapCol + current.col] = '#';

        // push
        for (int i = 0; i < 4; i++) {
            int nxtRow = current.row + nxt[i][0];
            int nxtCol = current.col + nxt[i][1];
            if (map[nxtRow * mapCol + nxtCol] != '#') {
                queue.push_back({nxtRow, nxtCol, current.step + 1});
                prev[nxtRow * mapCol + nxtCol] = {current.col, current.row};
            }
        }
    }

    return 0;
}

void printPath(PrevLoc prev[], int mapCol, Point exit) {
    vector<PrevLoc> path;
    PrevLoc current = {exit.col, exit.row};
    while(!(current.x == -1 && current.y == -1)) {
        path.push_back(current);
        current = prev[current.y * mapCol + current.x];
    }

    printf("Path = \n");
    for (int i = path.size() - 1; i >= 0; i--) {
        printf("Step %d: (Row = %d, Col = %d)\n", path.size() - i - 1, path[i].y - 1, path[i].x - 1);
    }
}

int main()
{
    int row, col;
    scanf("%d %d", &row, &col);
    const int paddingRow = row + 2;
    const int paddingCol = col + 2;

    char line[maxCharSize];
    char map[paddingRow * paddingCol];
    PrevLoc cameFrom[paddingRow * paddingCol];
    
    vector<Point> queue;
    Point start;
    Point exit;

    fill(&map[0], &map[0] + paddingRow * paddingCol, '#');

    // read maze
    for (int r = 0; r < row; r++) {
        scanf("%s", line);
        for (int c = 0; c < col; c++) {
            if (line[c] == 'S') {
                start = {r+1, c+1, 0};
                queue.push_back(start);
                cameFrom[(r+1) * paddingCol + (c+1)] = {-1, -1};
            }
            else if (line[c] == 'E') {
                exit = {r+1, c+1, 0};
            }
            map[(r+1) * paddingCol + (c+1)] = line[c];
        }
    }

    // search algorithm
    int result = bfs(queue, map, exit, paddingCol, cameFrom);

    if (result > 0) {
        printPath(cameFrom, paddingCol, exit);
        printf("Escaped in %d minute(s).", result);
    }
    else {
        printf("Trapped!");
    }

    return 0;
}