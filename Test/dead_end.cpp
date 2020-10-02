
/**Which of the favors of your Lord will you deny ?**/

#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define MP make_pair
#define F first
#define S second
#define INF INT_MAX

#define ALL(x) (x).begin(), (x).end()
#define DBG(x) cerr << __LINE__ << " says: " << #x << " = " << (x) << endl

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class TIn>
using indexed_set = tree<
                    TIn, null_type, less<TIn>,
                    rb_tree_tag, tree_order_statistics_node_update>;

/*
PBDS
-------------------------------------------------
1) insert(value)
2) erase(value)
3) order_of_key(value) // 0 based indexing
4) *find_by_order(position) // 0 based indexing

*/

inline void optimizeIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int nmax = 2e5+7;
const LL LINF = 1e17;

string to_str(LL x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}

//bool cmp(const PII &A,const PII &B)
//{
//
//}

string grid[40];
bool vis[40][40];

vector<int>dx = {0,1,0,-1};
vector<int>dy = {1,0,-1,0};

bool isSafe(int r,int c,int top_left_r,int top_left_c,int r_len,int c_len)
{
    if(c>=top_left_c && c<=top_left_c+c_len-1 && r>=top_left_r && r<= top_left_r+r_len-1)
        return true;
    return false;
}

int dfs(int x,int y,int top_left_x,int top_left_y,int x_len,int y_len)
{
    vis[x][y] = true;

    cout<<x<<","<<y<<endl;

    for(int i=0;i<4;i++)
    {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(!vis[nx][ny] && grid[nx][ny]!='#' && isSafe(x,y,top_left_x,top_left_y,x_len,y_len))
            dfs(nx,ny,top_left_x,top_left_y,x_len,y_len);
    }

}

int main()
{
    //freopen("out.txt","w",stdout);

    optimizeIO();

    int width; // size of the grid
    int height; // top left corner is (x=0, y=0)
    cin >> width >> height;
    for (int i = 0; i < height; i++)
    {
        string row;
        cin>>row; // one line of the grid: space " " is floor, pound "#" is wall
        grid[i] = row;
    }

    for (int i = 0; i < height; i++)
        cout<<grid[i]<<endl;

    PII one = {2,8};

    dfs(one.F-1,one.S-1,0,0,width,height);

    return 0;
}


