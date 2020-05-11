
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

/**
 * Grab the pellets as fast as you can!
 **/

inline void optimizeIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int nmax = 40;
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

string grid[nmax];
bool vis[nmax][nmax];
vector<PII>moves[10];

vector<int>dx = {0,1,0,-1};
vector<int>dy = {1,0,-1,0};

bool isSafe(int i,int j,int top_left_x,int top_left_y,int x_len,int y_len)
{
    if(i>=top_left_x && i<=top_left_x+x_len-1 && j>=top_left_y && j<= top_left_y+y_len-1)
        return true;
    return false;
}

int dfs(int id,int x,int y,int top_left_x,int top_left_y,int x_len,int y_len)
{
    vis[x][y] = true;

//    cout<<x<<","<<y<<endl;
    moves[id].push_back({x,y});

    if(id%2==1)
    {
        for(int i=0; i<4; i++)
        {
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(!vis[nx][ny] && grid[nx][ny]!='#' && isSafe(nx,ny,top_left_x,top_left_y,x_len,y_len))
                dfs(id,nx,ny,top_left_x,top_left_y,x_len,y_len);
        }
    }
    else
    {
        for(int i=3; i>=0; i--)
        {
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(!vis[nx][ny] && grid[nx][ny]!='#' && isSafe(nx,ny,top_left_x,top_left_y,x_len,y_len))
                dfs(id,nx,ny,top_left_x,top_left_y,x_len,y_len);
        }
    }
}

class Pac
{
public:
    int id;
    bool isMine;
    int x,y;

    Pac() {}

    Pac(int id,bool isMine,int x,int y)
    {
        this->id = id;
        this->isMine = isMine;
        this->x = x;
        this->y = y;
    }
};

class Pellet
{
public:
    int x,y,val,dist;

    Pellet() {}

    Pellet(int x,int y,int val,int dist)
    {
        this->x = x;
        this->y = y;
        this->val = val;
        this->dist = dist;
    }
};

int main()
{
    int width; // size of the grid
    int height; // top left corner is (x=0, y=0)
    cin >> width >> height;
    cin.ignore();
    for (int i = 0; i < height; i++)
    {
        string row;
        getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
        grid[i] = row;
    }

    vector<Pac> myPacsNow;
    vector<Pac> enPacsNow;

    int game = 0;

    // game loop
    while (1)
    {

        game++;

        myPacsNow.clear();
        enPacsNow.clear();

        int myScore;
        int opponentScore;
        cin >> myScore >> opponentScore;
        cin.ignore();


        int visiblePacCount; // all your pacs and enemy pacs in sight
        cin >> visiblePacCount;
        cin.ignore();
        for (int i = 0; i < visiblePacCount; i++)
        {
            int pacId; // pac number (unique within a team)
            bool mine; // true if this pac is yours
            int x; // position in the grid
            int y; // position in the grid
            string typeId; // unused in wood leagues
            int speedTurnsLeft; // unused in wood leagues
            int abilityCooldown; // unused in wood leagues
            cin >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown;
            cin.ignore();

            if(mine==1)
            {
                myPacsNow.push_back(Pac(pacId,mine,x,y));
            }
            else
            {
                enPacsNow.push_back(Pac(pacId,mine,x,y));
            }
        }

        int visiblePelletCount; // all pellets in sight
        cin >> visiblePelletCount;
        cin.ignore();
        for (int i = 0; i < visiblePelletCount; i++)
        {
            int x;
            int y;
            int value; // amount of points this pellet is worth
            cin >> x >> y >> value;
            cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if(game==1)
        {
            for(auto me:myPacsNow)
            {
                memset(vis,0,sizeof vis);
                dfs(me.id,me.x,me.y,0,0,width,height);
            }
        }

        int len = 0;

        for(auto me:myPacsNow)
        {
            if(len==0)
                cout<<"MOVE "<<me.id<<" "<<moves[me.id][game].F<<" "<<moves[me.id][game].S;
            else
                cout<<"|MOVE "<<me.id<<" "<<moves[me.id][game].F<<" "<<moves[me.id][game].S;
            len++;

        }
        cout<<endl;

//        cout << "MOVE 0 15 10" << endl; // MOVE <pacId> <x> <y>
    }
}
