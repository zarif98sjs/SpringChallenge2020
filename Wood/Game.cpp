
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

const int nmax = 1e2+7;
const LL LINF = 1e17;

string to_str(LL x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}

string grid[nmax];

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
        return A.dist > B.dist;
    return A.val>B.val;
}

bool cmpPel2(const Pellet &A,const Pellet &B)
{
    if(A.val==B.val)
        return A.dist < B.dist;
    return A.val<B.val;
}

vector<PII>init_pos;

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

    init_pos.push_back({0,0});
    init_pos.push_back({width/2,0});
    init_pos.push_back({0,height/2});
    init_pos.push_back({width/2,height/2});

    init_pos.push_back({0+width/2,0+height/2});
    init_pos.push_back({width-1,0+height/2});
    init_pos.push_back({0+width/2,height-1});
    init_pos.push_back({width-1,height-1});

    // game loop
    int game = 0;
    vector<Pac> myPacsNow;
    vector<Pac> enPacsNow;
    vector<Pac> myPacsPrev;
    vector<int> nowid(100,0);
    vector<Pellet>vpell[100];

    while (1)
    {
        myPacsPrev = myPacsNow;
        myPacsNow.clear();
        enPacsNow.clear();

        game++;

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

            if(game==1)
            {
                for(auto myPac:myPacsNow)
                {
                    int dist = abs(myPac.x-x) + abs(myPac.y-y);
                    vpell[myPac.id].push_back(Pellet(x,y,value,dist));
                }
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cerr<<"MyPacs"<<endl;
        for(auto x:myPacsNow)
            cerr<<x.id<<": "<<x.x<<" , "<<x.y<<endl;

        cerr<<"EnPacs"<<endl;
        for(auto x:enPacsNow)
            cerr<<x.id<<": "<<x.x<<" , "<<x.y<<endl;

        int len = 0;
        for(auto myPac:myPacsNow)
        {
            int id = (len + nowid[myPac.id])%8;

            if(len==0)
                cout<<"MOVE "<<myPac.id<<" "<<init_pos[id].F<<" "<<init_pos[id].S;
            else
                cout<<"|MOVE "<<myPac.id<<" "<<init_pos[id].F<<" "<<init_pos[id].S;

            if(game>1)
            {
                if(myPac.x==myPacsPrev[len].x && myPac.y==myPacsPrev[len].x)
                nowid[myPac.id] += 4;
            }

            len++;

        }

        cout<<endl;


//        cout << "MOVE 0 15 10" << endl; // MOVE <pacId> <x> <y>
    }
}

/**

TODO:
1 . Collision hoile change route
2. DFS

**/
