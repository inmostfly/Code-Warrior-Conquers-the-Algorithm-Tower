#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
};

int n, m;
vector<vector<int>> grid;
vector<vector<Node>> parent;  // 记录路径
vector<vector<bool>> visited;

int dx[4] = {-1, 1, 0, 0};  // 上下左右
int dy[4] = {0, 0, -1, 1};
char dirChar[4] = {'W', 'S', 'A', 'D'}; // 对应 WASD

// BFS 搜索最短路径
string bfs(Node start, Node target) {
    queue<Node> q;
    q.push(start);
    visited[start.x][start.y] = true;
    while(!q.empty()){
        Node front=q.front();q.pop();    
        if(front.x==target.x&&front.y==target.y){
            Node p=target;
            string path;
            while(!(p.x==start.x&&p.y==start.y)){
                Node tem=parent[p.x][p.y];
                if(tem.x+1==p.x&&tem.y==p.y) path.push_back('S');//父节点在下，父节点来往p
                else if(tem.x-1==p.x&&tem.y==p.y) path.push_back('W');
                else if(tem.x==p.x&&tem.y+1==p.y) path.push_back('D');
                else if(tem.x==p.x&&tem.y-1==p.y) path.push_back('A');
                p=tem;
            }
            reverse(path.begin(),path.end());
            return path;
        }
        for(int i=0;i<4;i++){
            int ux=front.x+dx[i];
            int uy=front.y+dy[i];
            if(ux>=0&&ux<n&&uy>=0&&uy<m&&!visited[ux][uy]&&grid[ux][uy]!=1){
                visited[ux][uy]=true;
                parent[ux][uy]=Node{front.x,front.y};
                q.push(Node{ux,uy});
            }
        }
    
    }
    return "NO PATH"; // 如果找不到
}

int main() {
    FILE* pf;
    pf = fopen("bfs_data3.txt","r");
    fscanf(pf, "%d", &n);
    fscanf(pf, "%d", &m);
    grid.assign(n, vector<int>(m));
    visited.assign(n, vector<bool>(m, false));
    parent.assign(n, vector<Node>(m, {-1,-1}));

    // 固定起点
    Node start{3, 3}, target{-1, -1};
//寻找终点
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(pf,"%d",&grid[i][j]);
            if (grid[i][j] == 9) target = {i, j}; // 终点=9
        }
    }
    fclose(pf);

    string path = bfs(start, target);
    string abc="abc";
    pf = fopen("bfs_out3.txt","w");
    fprintf(pf,"%d %d\n", n, m);
    fprintf(pf,"%s\n", path.c_str());
    // fprintf(pf,"%s",abc.c_str());
    fclose(pf);
    pf = NULL;
    return 0;
}