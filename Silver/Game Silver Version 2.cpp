
/**

Upgraded to SILVER with this

isInSpeed ke true korte bhule gesilam
isPacInDanger correction korsi
isInSpeed e duita same distance 2 hoile clash korto , oita thik korsi

**/

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

string isPacInDanger(int mr,int mc,int er,int ec,string mtype,string etype)
{
    if(mr-er!=0 && mc-ec!=0)
        return "-1";

    if(mr-er==0 && abs(mc-ec)>2)
        return "-1";

    if(mc-ec==0 && abs(mr-er)>2)
        return "-1";

    if(mtype=="ROCK" && etype=="SCISSORS")
        return "-1";
    if(mtype=="SCISSORS" && etype=="PAPER")
        return "-1";
    if(mtype=="PAPER" && etype=="ROCK")
        return "-1";

    if(mtype=="ROCK" && etype=="ROCK")
        return "PAPER";
    if(mtype=="ROCK" && etype=="PAPER")
        return "SCISSORS";

    if(mtype=="SCISSORS" && etype=="SCISSORS")
        return "ROCK";
    if(mtype=="SCISSORS" && etype=="ROCK")
        return "PAPER";

    if(mtype=="PAPER" && etype=="PAPER")
        return "SCISSORS";
    if(mtype=="PAPER" && etype=="SCISSORS")
        return "ROCK";

}

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

        for(int i=3; i>=0; i--)
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

int ASE[nmax][nmax];

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

    //bool isInSpeed = true;

    vector<Pac> myPacsNow;
    vector<Pac> myPacsPrev;
    vector<Pac> enPacsNow;
    vector<Pac> enPacsPrev;

    // game loop
    while (1)
    {
        myPacsPrev = myPacsNow;
        enPacsPrev = enPacsNow;

        myPacsNow.clear();
        enPacsNow.clear();

        for(int i=0; i<10; i++)
            vpell[i].clear();

        game++;
        bool speedHappen[10];
        bool isInSpeed[10];
        string convertToType[10];

        for(int i=0; i<10; i++)
            speedHappen[i] = false, isInSpeed[i] = false, convertToType[i] = "-1";

        cerr<<"Game : "<<game<<endl;

        int myScore;
        int opponentScore;
        cin >> myScore >> opponentScore;
        cin.ignore();

        bool SPEEEED = false;


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
            //if(mine) cerr<<pacId<<" : "<<speedTurnsLeft<<" "<<abilityCooldown<<endl;
            if(mine) cerr<<pacId<<" : "<<speedTurnsLeft<<" "<<abilityCooldown<<endl;
            cin.ignore();

            int r = y;
            int c = x;

            ASE[r][c] = 0;

            if(mine==1)
            {
                if(abilityCooldown==0)
                    speedHappen[pacId] = true,SPEEEED = true;
                if(speedTurnsLeft==0)
                    isInSpeed[pacId] = false;
                if(speedTurnsLeft>0)
                    isInSpeed[pacId] = true;
                myPacsNow.push_back(Pac(pacId,mine,r,c,typeId,speedTurnsLeft,abilityCooldown));
                grid[r][c] = '#';
            }
            else
            {
                enPacsNow.push_back(Pac(pacId,mine,r,c,typeId,speedTurnsLeft,abilityCooldown));
                grid[r][c] = '#';
            }
        }

        for(auto me:myPacsNow) /** inefficient **/
        {
            for(auto me0:myPacsPrev)
            {
                if(me.id==me0.id)
                {
                    cerr<<"dasdasd"<<endl;

                    if(abs(me.r-me0.r)+abs(me.c-me0.c)==2)
                    {
                        if(me.r-me0.r==0)
                        {
                            int mx = max(me.c,me0.c);
                            ASE[me.r][mx-1] = 0;
                            if(me.id==0) cerr<<mx-1<<" , "<<me.r<<endl;
                        }
                        else if(me.c-me0.c==0)
                        {
                            int mx = max(me.r,me0.r);
                            ASE[mx-1][me.c] = 0;
                            if(me.id==0) cerr<<me.c<<" , "<<mx-1<<endl;
                        }
                        else
                        {
                            ASE[me.r][me0.c] = 0;
                            if(me.id==0) cerr<<me.r<<" , "<<me0.c<<endl;
                        }
                    }
                }
            }
        }

        for(auto en:enPacsNow) /** inefficient **/
        {
            for(auto en0:enPacsPrev)
            {
                if(en.id==en0.id)
                {
                    if(abs(en.r-en0.r)+abs(en.c-en0.c)==2)
                    {
                        if(en.r-en0.r==0)
                        {
                            int mx = max(en.c,en0.c);
                            ASE[en.r][mx-1] = 0;
                            if(en.id==0) cerr<<mx-1<<" , "<<en.r<<endl;
                        }
                        else if(en.c-en0.c==0)
                        {
                            int mx = max(en.r,en0.r);
                            ASE[mx-1][en.c] = 0;
                            if(en.id==0) cerr<<en.c<<" , "<<mx-1<<endl;
                        }
                        else
                        {
                            ASE[en.r][en0.c] = 0;
                            if(en.id==0) cerr<<en.r<<" , "<<en0.c<<endl;
                        }
                    }
                }
            }
        }


        if(SPEEEED)
        {
            for(auto en:enPacsNow)
                grid[en.r][en.c] = ' ';
        }

        for(auto me:myPacsNow)
        {
            grid[me.r][me.c] = ' ';
            bfs(me.id,me.r,me.c,height,width);
            grid[me.r][me.c] = '#';
        }

        for(auto me:myPacsNow)
        {
            for(auto en:enPacsNow)
            {
                string whatToDo = isPacInDanger(me.r,me.c,en.r,en.c,me.type,en.type);
                if(whatToDo!="-1")
                {
                    if(speedHappen[me.id])
                    {
                        speedHappen[me.id] = false;
                        convertToType[me.id] = whatToDo;
                    }
                }
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

            int r = y;
            int c = x;

            ASE[r][c] = 1;

            if(value==10)
            {
                ASE[r][c] = 10;

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

                if(min_d!=0)
                    vpell[pid].push_back(Pellet(r,c,value,min_d));

                continue;

            }

//            for(auto myPac:myPacsNow)
//            {
//                int distance = dist[myPac.id][r][c];
//                if(isInSpeed[myPac.id])
//                {
//                    if(distance>1)
//                        vpell[myPac.id].push_back(Pellet(r,c,value,distance));
//                    continue;
//                }
//                if(distance!=0)
//                    vpell[myPac.id].push_back(Pellet(r,c,value,distance));
//            }
        }

        bool dui_ase[10];
        for(int i=0;i<10;i++)
            dui_ase[i] = false;

        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                if(ASE[i][j]==1)
                {
                    for(auto myPac:myPacsNow)
                    {
                        int distance = dist[myPac.id][i][j];

                        if(distance==2)
                            dui_ase[myPac.id] = true;
                    }
                }
            }
        }



        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                if(ASE[i][j]==1)
                {
                    for(auto myPac:myPacsNow)
                    {
                        int distance = dist[myPac.id][i][j];

                        bool gamela = false;

                        for(auto m2:myPacsNow)
                        {
                            if(myPac.id!=m2.id)
                            {
                                int distance2 = dist[m2.id][i][j];

                                if(distance==1 && distance2==1)
                                {
                                    gamela = true;
                                }

                                if(distance==2 && distance2==2 && isInSpeed[myPac.id]==true && isInSpeed[m2.id]==true)
                                {
                                    gamela = true;
                                }

                            }
                        }

                        if(gamela)
                            continue;

                        if(isInSpeed[myPac.id] && dui_ase[myPac.id])
                        {
//                            if(myPac.id==0) /** FOR DEBUGGING **/
//                            {
//                                if(distance<7)
//                                {
//                                    cerr<<j<<" , "<<i<<" : "<<distance<<endl;
//                                }
//
//                            }

                            if(distance>1)
                                vpell[myPac.id].push_back(Pellet(i,j,1,distance));
                            continue;
                        }
                        if(distance!=0)
                            vpell[myPac.id].push_back(Pellet(i,j,1,distance));
                    }
                }
            }
        }

        for(auto en:enPacsNow)
        {
            for(auto me:myPacsNow)
            {
                int distance = dist[me.id][en.r][en.c];
                vpell[me.id].push_back(Pellet(en.r,en.c,0,distance));
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for(auto myPac:myPacsNow)
        {
            sort(ALL(vpell[myPac.id]),cmpPel);
        }

        bool speedHoyeGese = false;

        int len = 0;

        for(auto myPac:myPacsNow)
        {
            if(speedHappen[myPac.id])
            {
                if(len==0)
                    cout<<"SPEED "<<myPac.id;
                else
                    cout<<"|SPEED "<<myPac.id;
                len++;
                speedHoyeGese = true;
                isInSpeed[myPac.id] = true;
            }
        }

        if(speedHoyeGese)
        {
            cerr<<"SPEEEEEEEED"<<endl;
        }

        bool changeHoyeGese = false;

        for(auto myPac:myPacsNow)
        {
            if(convertToType[myPac.id]!="-1")
            {
                if(len==0)
                    cout<<"SWITCH "<<myPac.id<<" "<<convertToType[myPac.id];
                else
                    cout<<"|SWITCH "<<myPac.id<<" "<<convertToType[myPac.id];
                len++;
                changeHoyeGese = true;
            }
        }

        if(changeHoyeGese)
        {
            cerr<<"CHANGEEEEEEE"<<endl;
        }

        if(speedHoyeGese || changeHoyeGese)
        {
            cout<<endl;
            continue;
        }


//        if(speedHappen)
//        {
//            cerr<<"SPEEEEEEEED"<<endl;
//            isInSpeed = true;
//
//            int len = 0;
//
//            for(auto myPac:myPacsNow)
//            {
//                if(len==0) cout<<"SPEED "<<myPac.id;
//                else cout<<"|SPEED "<<myPac.id;
//                len++;
//            }
//            cout<<endl;
//            continue;
//        }

        len = 0;

        for(auto myPac:myPacsNow)
        {
            //cerr<<vpell[myPac.id].size()<<endl;

            bool same_jayga = false;

            for(auto me0:myPacsPrev)
            {
                if(myPac.id==me0.id)
                {
                    if(myPac.r == me0.r && myPac.c==me0.c)
                    {
                        same_jayga = true;
                        break;
                    }
                }
            }

            int go_id = 0;

            if(same_jayga)  go_id = vpell[myPac.id].size()/2;


            if(len==0)
                cout<<"MOVE "<<myPac.id<<" "<<vpell[myPac.id][go_id].c<<" "<<vpell[myPac.id][go_id].r<<" "<<myPac.c<<","<<myPac.r;
            else
                cout<<"|MOVE "<<myPac.id<<" "<<vpell[myPac.id][go_id].c<<" "<<vpell[myPac.id][go_id].r<<" "<<myPac.c<<","<<myPac.r;
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
