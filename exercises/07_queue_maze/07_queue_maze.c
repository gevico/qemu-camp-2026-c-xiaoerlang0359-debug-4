#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef struct{
	int row,col;
} Point;

Point queue[MAX_ROW*MAX_COL];
int front = 0;
int rear = 0;

int visited[MAX_ROW][MAX_COL] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
};

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

bool enqueue(Point p){
	if (rear >= MAX_ROW*MAX_COL)
		return false;
	queue[rear++] = p;
	return true;
}

Point dequeue(void){
	Point empty = {0, 0};
	if (front >= rear)
		return empty;
	return queue[front++];
}

bool is_empty(){
	return front == rear;
}

Point predecessor[MAX_ROW][MAX_COL] = {
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
};

int main(void)
{
	// TODO: 在这里添加你的代码
	bool success = false;
	Point trace;
    Point start = {0,0};
	visited[start.row][start.col] = 1;
	enqueue(start);
	while (!is_empty()){
		Point cur;
		cur = dequeue();
		if (cur.row == (MAX_ROW-1) && cur.col == (MAX_COL-1)){
			success = true;
			break;
		}
		Point left;
		left.row = cur.row;
		left.col = cur.col-1;
		if (left.col>=0 && visited[left.row][left.col]==0 && maze[left.row][left.col]==0){
			enqueue(left);
			visited[left.row][left.col] = 1;
			predecessor[left.row][left.col] = cur;
		}
		Point right;
		right.row = cur.row;
		right.col = cur.col+1;
		if (right.col<MAX_COL && visited[right.row][right.col]==0 && maze[right.row][right.col]==0){
			enqueue(right);
			visited[right.row][right.col] = 1;
			predecessor[right.row][right.col] = cur;
		}
		Point up;
		up.row = cur.row-1;
		up.col = cur.col;
		if (up.row>=0 && visited[up.row][up.col]==0 && maze[up.row][up.col]==0){
			enqueue(up);
			visited[up.row][up.col] = 1;
			predecessor[up.row][up.col] = cur;
		}
		Point down;
		down.row = cur.row+1;
		down.col = cur.col;
		if (down.row<MAX_ROW && visited[down.row][down.col]==0 && maze[down.row][down.col]==0){
			enqueue(down);
			visited[down.row][down.col] = 1;
			predecessor[down.row][down.col] = cur;
		}
	}
	if (success){
		trace.row = MAX_ROW-1;
		trace.col = MAX_COL-1;
		printf("(%d, %d)\n", trace.row, trace.col);
		while (predecessor[trace.row][trace.col].row != -1){
			trace = predecessor[trace.row][trace.col];
			printf("(%d, %d)\n", trace.row, trace.col);
		}
	}else{
		printf("没有找到可行路径\n");
	}

	return 0;
}