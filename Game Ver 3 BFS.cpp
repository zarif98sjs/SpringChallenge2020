
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
bool visited[10][nmax][nmax];
int dist[10][nmax][nmax];
vector<PII>moves[10];

vector<int>dx = {0,1,0,-1};
vector<int>dy = {1,0,-1,0};

bool isSafe(int i,int j,int top_left_x,int top_left_y,int x_len,int y_len)
{
    if(i>=top_left_x && i<=top_left_x+x_len-1 && j>=top_left_y && j<= top_left_y+y_len-1)
        return true;
    return false;
}

void bfs(int id,int x,int y,int x_len,int y_len)
{
    for(int i=0; i<x_len; i++) // ditance inf
    {
        for(int j=0; j<y_len; j++)
        {
            dist[id][i][j]=INF;
            visited[id][i][j]=false;
        }
    }

    dist[id][x][y]=0;
    visited[id][x][y]=true;

    int prevx,prevy;

    queue< PII > Q;
    Q.push(MP(x,y));

    while(!Q.empty())
    {
        prevx = Q.front().F;
        prevy = Q.front().S;

        Q.pop();

        for(int i=0; i<4; i++)
        {
            x = prevx + dx[i];
            y = prevy + dy[i];

            if( isSafe(x,y,0,0,x_len,y_len) && visited[id][x][y]!=true && grid[x][y]!='#')
            {
                dist[id][x][y] = min(dist[id][prevx][prevy]+1,dist[id][x][y]);
                visited[id][x][y] = true;
                Q.push(MP(x,y));
            }
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

bool cmpPel(const Pellet &A,const Pellet &B)
{
    if(A.val==B.val)
        return A.dist < B.dist;
    return A.val>B.val;
}

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

    vector<Pellet>vpell[10];

    int game = 0;

    // game loop
    while (1)
    {
        for(int i=0;i<10;i++)
            vpell[i].clear();

        game++;
        vector<Pac> myPacsNow;
        vector<Pac> enPacsNow;

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
                grid[x][y] = '#';
            }
            else
            {
                enPacsNow.push_back(Pac(pacId,mine,x,y));
                grid[x][y] = '#';
            }
        }

        for(auto me:myPacsNow)
        {
            bfs(me.id,me.x,me.y,width,height);
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

            for(auto myPac:myPacsNow)
            {
                int distance = dist[myPac.id][x][y];
                if(distance!=0) vpell[myPac.id].push_back(Pellet(x,y,value,distance));
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for(auto myPac:myPacsNow)
        {
            sort(ALL(vpell[myPac.id]),cmpPel);
        }

        int len = 0;

        for(auto myPac:myPacsNow)
        {
            if(len==0) cout<<"MOVE "<<myPac.id<<" "<<vpell[myPac.id][0].x<<" "<<vpell[myPac.id][0].y;
            else cout<<"|MOVE "<<myPac.id<<" "<<vpell[myPac.id][0].x<<" "<<vpell[myPac.id][0].y;
            len++;
        }

        cout<<endl;

        for(auto me:myPacsNow)
        {
            grid[me.x][me.y] = ' ';
        }
        for(auto en:myPacsNow)
        {
            grid[en.x][en.y] = ' ';
        }

//        cout << "MOVE 0 15 10" << endl; // MOVE <pacId> <x> <y>
    }
}
