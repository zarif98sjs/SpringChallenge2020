
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

vector<int>dr = {0,1,0,-1};
vector<int>dc = {1,0,-1,0};

bool isMyPel(int mr,int mc,int pr,int pc)
{
    if(mr-pr==0 || mc-pc==0)
        return true;
    return false;
}

bool isSafe(int r,int c,int top_left_r,int top_left_c,int r_len,int c_len)
{
    if(c>=top_left_c && c<=top_left_c+c_len-1 && r>=top_left_r && r<= top_left_r+r_len-1)
        return true;
    return false;
}

void bfs(int id,int r,int c,int r_len,int c_len)
{
    for(int i=0; i<r_len; i++) // ditance inf
    {
        for(int j=0; j<c_len; j++)
        {
            dist[id][i][j]=INT_MAX;
            visited[id][i][j]=false;
        }
    }

    dist[id][r][c]=0;
    visited[id][r][c]=true;

    int prevr,prevc;

    queue< PII > Q;
    Q.push(MP(r,c));

    while(!Q.empty())
    {
        prevr = Q.front().F;
        prevc = Q.front().S;

        Q.pop();

        for(int i=0; i<4; i++)
        {
            r = prevr + dr[i];
            c = (prevc + dc[i])%c_len;

            if(isSafe(r,c,0,0,r_len,c_len) && visited[id][r][c]!=true && grid[r][c]!='#')
            {
                dist[id][r][c] = min(dist[id][prevr][prevc]+1,dist[id][r][c]);
                visited[id][r][c] = true;
                Q.push(MP(r,c));
            }
        }
    }

}

class Pac
{
public:
    int id;
    bool isMine;
    int r,c;
    string type;
    int speedTurnsLeft;
    int abilityCoolDown;

    Pac() {}

    Pac(int id,bool isMine,int r,int c,string type,int speedTurnsLeft,int abilityCoolDown)
    {
        this->id = id;
        this->isMine = isMine;
        this->r = r;
        this->c = c;
        this->type = type;
        this->speedTurnsLeft = speedTurnsLeft;
        this->abilityCoolDown = abilityCoolDown;
    }
};

class Pellet
{
public:
    int r,c,val,dist;

    Pellet() {}

    Pellet(int r,int c,int val,int dist)
    {
        this->r = r;
        this->c = c;
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

    int game = -1;

    bool isInSpeed = true;

    // game loop
    while (1)
    {
        for(int i=0;i<10;i++)
            vpell[i].clear();

        game++;
        bool speedHappen = false;

        cerr<<"Game : "<<game<<endl;

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
            cerr<<speedTurnsLeft<<" "<<abilityCooldown<<endl;
            cin.ignore();

            int r = y;
            int c = x;

            if(mine==1)
            {
                if(abilityCooldown==0)speedHappen = true;
                if(speedTurnsLeft==0)isInSpeed = false;
                myPacsNow.push_back(Pac(pacId,mine,r,c,typeId,speedTurnsLeft,abilityCooldown));
                grid[r][c] = '#';
            }
            else
            {
                enPacsNow.push_back(Pac(pacId,mine,r,c,typeId,speedTurnsLeft,abilityCooldown));
                grid[r][c] = '#';
            }
        }

        for(auto me:myPacsNow)
        {
            grid[me.r][me.c] = ' ';
            bfs(me.id,me.r,me.c,height,width);
            grid[me.r][me.c] = '#';
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

            int r = y;
            int c = x;

            if(value==10)
            {
                int pid = 0;
                int min_d = INT_MAX;

                for(auto myPac:myPacsNow)
                {
                    int distance = dist[myPac.id][r][c];

                    if(distance<min_d)
                    {
                        min_d = distance;
                        pid = myPac.id;
                    }
                }

                if(min_d!=0) vpell[pid].push_back(Pellet(r,c,value,min_d));

                continue;

            }

            for(auto myPac:myPacsNow)
            {
                int distance = dist[myPac.id][r][c];
                if(isInSpeed)
                {
                    if(distance>1) vpell[myPac.id].push_back(Pellet(r,c,value,distance));
                    continue;
                }
                if(distance!=0) vpell[myPac.id].push_back(Pellet(r,c,value,distance));
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for(auto myPac:myPacsNow)
        {
            sort(ALL(vpell[myPac.id]),cmpPel);
        }

        if(speedHappen)
        {
            cerr<<"SPEEEEEEEED"<<endl;
            isInSpeed = true;

            int len = 0;

            for(auto myPac:myPacsNow)
            {
                if(len==0) cout<<"SPEED "<<myPac.id;
                else cout<<"|SPEED "<<myPac.id;
                len++;
            }
            cout<<endl;
            continue;
        }

        int len = 0;

        for(auto myPac:myPacsNow)
        {
            cerr<<vpell[myPac.id].size()<<endl;

            if(len==0) cout<<"MOVE "<<myPac.id<<" "<<vpell[myPac.id][0].c<<" "<<vpell[myPac.id][0].r;
            else cout<<"|MOVE "<<myPac.id<<" "<<vpell[myPac.id][0].c<<" "<<vpell[myPac.id][0].r;
            len++;
        }

        cout<<endl;

        for(auto me:myPacsNow)
        {
            grid[me.r][me.c] = ' ';
        }
        for(auto en:myPacsNow)
        {
            grid[en.r][en.c] = ' ';
        }

//        cout << "MOVE 0 15 10" << endl; // MOVE <pacId> <x> <y>
    }
}
