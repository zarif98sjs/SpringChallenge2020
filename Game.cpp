
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

const int nmax = 1e3+7;
const LL LINF = 1e17;

string to_str(LL x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}

string grid[nmax];

class Pac{
public:
    int id;
    bool isMine;
    int x,y;

    Pac(){}

    Pac(int id,bool isMine,int x,int y)
    {
        this->id = id;
        this->isMine = isMine;
        this->x = x;
        this->y = y;
    }
};

class Pellet{
public:
    int x,y,val,dist;

    Pellet(){}

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
    if(A.val==B.val) return A.dist > B.dist;
    return A.val>B.val;
}

int main()
{
    int width; // size of the grid
    int height; // top left corner is (x=0, y=0)
    cin >> width >> height; cin.ignore();
    for (int i = 0; i < height; i++) {
        string row;
        getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
        grid[i] = row;
    }

    // game loop
    int game = 0;
    int now = 0;
    Pac myPac;
    vector<Pellet>vpell;

    while (1) {
        game++;

        int myScore;
        int opponentScore;
        cin >> myScore >> opponentScore; cin.ignore();

        int visiblePacCount; // all your pacs and enemy pacs in sight
        cin >> visiblePacCount; cin.ignore();
        for (int i = 0; i < visiblePacCount; i++) {
            int pacId; // pac number (unique within a team)
            bool mine; // true if this pac is yours
            int x; // position in the grid
            int y; // position in the grid
            string typeId; // unused in wood leagues
            int speedTurnsLeft; // unused in wood leagues
            int abilityCooldown; // unused in wood leagues
            cin >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown; cin.ignore();

            if(mine==1)
                myPac = Pac(pacId,mine,x,y);
        }

        int visiblePelletCount; // all pellets in sight
        cin >> visiblePelletCount; cin.ignore();
        for (int i = 0; i < visiblePelletCount; i++) {
            int x;
            int y;
            int value; // amount of points this pellet is worth
            cin >> x >> y >> value; cin.ignore();
            int dist = abs(myPac.x-x) + abs(myPac.y-y);

            if(game==1)vpell.push_back(Pellet(x,y,value,dist));
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for(auto x:vpell)
            cerr<<x.dist<<" ";
        cerr<<"DONE"<<endl;

        cerr<<"Pac "<<myPac.x<<" , "<<myPac.y<<endl;

        if(game==1)sort(ALL(vpell),cmpPel);

        int go_x = vpell[now].x;
        int go_y = vpell[now].y;
        cout<<"MOVE "<<myPac.id<<" "<<go_x<<" "<<go_y<<endl;
        if(myPac.x==go_x && myPac.y==go_y)
            now++;
        cerr <<vpell[0].x<<" "<<vpell[0].y<<endl;

//        cout << "MOVE 0 15 10" << endl; // MOVE <pacId> <x> <y>
    }
}
