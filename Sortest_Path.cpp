#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

vector<vector<int>> graph = {{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                                { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                                { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                                { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                                { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                                { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                                { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                                { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                                { 0, 0, 2, 0, 0, 0, 6, 7, 0 }};

void find_path(int node,int source_node ,vector<int>&parent ,vector<int>&path)
{
    if(node == source_node)
    {
        path.push_back(source_node);return;
    }
    find_path(parent[node] ,source_node, parent , path);
    path.push_back(node);
}

void remove_node(int node , map<int , pair<int,int>>&mp)
{
    mp.erase(node);
    for(int i = 0;i < graph.size();i += 1)graph[node][i] = 0,graph[i][node] = 0;
}

int main()
{
    int V = 9,x,y,x1,x2,y1,y2,tx,ty,stepX,stepY,d,source_node,destination_node,steps,x_mid,y_mid;
    source_node = 0 , destination_node = 4 , steps = 50;  // More steps = smoother animation
    char graphics_driver_path[] = "C:\\MinGW\\lib\\libbgi.a";//requirement
    char dist_val[] = "00" , num[] = "0";
    char s[] = "Start Node is 0" ,  e[] = "End Node is 0";
    char res[] = "Shortest Path has a Distance of 00unit";
    map<int , pair<int,int>>mp;
    mp[0] = {100 , 300};
    mp[1] = {300 , 100};
    mp[2] = {500 , 100};
    mp[3] = {700 , 100};
    mp[4] = {900 , 300};
    mp[5] = {700 , 500};
    mp[6] = {500 , 500};
    mp[7] = {300 , 500};
    mp[8] = {500 , 300};

    vector<int>ans(V , 1e9) , parent(V , 0) , path;
    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>>pq;//min heap pq -> dist , node
     
    int graphics_driver = DETECT , graphics_mode;
    
    initgraph(&graphics_driver , &graphics_mode , graphics_driver_path);

    /*
    initgraph() : function that initializes the grpahics system by loading a graphics driver 
                from disk then putting the system into graphics mode

    Graphics Driver : tells the compiler that what graphics driver to use OR 
                        to automatically detect the Driver 
                        (i.e. graphics_driver = DETECT using detect macro of graphics.h) 

    Graphics Mode : it specifies the graphics mode to be used
                    if graphics mode is set to DETECT 
                    then initgraph() set the graphicmode to (the highest resolution available for the detected driver)
    
    Graphics Driver Path : specifies the directory path where graphics driver file(BGI file)
                            are located. If directory file is not provided then it will search 
                            for driver file in the current working directory
    */

    int window = initwindow(1000 , 600);
    
    // remove_node(5 , mp );
    // remove_node(1 , mp );
    // remove_node(6 , mp);

    settextstyle(DEFAULT_FONT , HORIZ_DIR , 2);
    for(int i = 0;i < V;i += 1)
    {
        for(int j = i;j < V;j += 1)
        {
            d = graph[i][j];
            if(d == 0)continue;
            dist_val[1] = '0' + d % 10;
            d /= 10;
            dist_val[0] = '0' + d % 10;
            x1 = mp[i].first , y1 = mp[i].second;
            x2 = mp[j].first , y2 = mp[j].second;
            line(x1,y1,x2,y2);
            x_mid = (x1 + x2)/2 , y_mid = (y1 + y2)/2;
            outtextxy(x_mid-25 , y_mid-25 , dist_val);
        }
    }
    
    for(auto it : mp)
    {
        x = it.second.first , y = it.second.second;
        fillellipse(x,y,15,15);
        num[0] = '0' + it.first;
        outtextxy(x-8 , y-8 , num);
    }
    
    settextstyle(TRIPLEX_FONT , HORIZ_DIR , 2);
    s[14] = '0' + source_node;
    outtextxy(20 ,20 , s);
    e[12] = '0' + destination_node;
    outtextxy(20 ,50 , e);
    ans[source_node] = 0;//dist of source_node node is 0
    pq.push({0 , source_node});

    while(!pq.empty())
    {
        int n = pq.size();
        while(n--)
        {
            int dist = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for(int i = 0;i < V;i += 1)
            {
                if(graph[node][i] != 0 && dist + graph[node][i] < ans[i])
                {
                    ans[i] = graph[node][i] + dist;
                    parent[i] = node;
                    pq.push({graph[node][i] + dist , i});
                }
            }
        }
    }
    
    find_path(destination_node , source_node , parent , path);

    getch();

    for(int i = 1;i < path.size();i += 1)
    {
        x1 = mp[path[i-1]].first , y1 = mp[path[i-1]].second;
        x2 = mp[path[i]].first , y2 = mp[path[i]].second;

        tx = x2 - x1 , ty = y2 - y1;
        stepX = tx / steps , stepY = ty / steps;
        for (int j = 0; j <= steps; j++) 
        {
            // Draw the moving circle
            setcolor(YELLOW);
            circle(x1 + (j * stepX), y1 + (j * stepY), 7);
            delay(20);
        }
    }
    destination_node = ans[destination_node];
    res[33] = destination_node % 10 + '0';
    destination_node /= 10;
    res[32] = destination_node % 10 + '0';

    outtextxy(20 , 550 , res);
    getch();
    closegraph();
    /*
    closegraph() : de-allocate all memory allocated by graphics system 
                and restore the screen to text mode 
    */
    
    cout<<"\n";
    for(int i=0;i<V;i++)cout<<ans[i]<<" ";            
    return 0;
}