#pragma once
#ifndef NINI_ASTAR_H
#define NINI_ASTAR_H

#include "Map.h"

#define COST_NORMAL 1.0 // 直线代价
#define COST_DIAGONAL sqrt(2.0) // 对角代价
#define COST_RIVER 2.0 // 溪流代价
#define COST_DESERT 4.0 // 沙漠代价


class AStar{
public:
    explicit AStar(int type);
    static void init(){
        int imap = 1, iSearch = 1;
        cout << "请选择地图：" << endl;
        cin >> imap;
        cout << "请选择单项或双向" << endl;
        cin >> iSearch;

        AStar* aStart = new AStar(imap - 1);
        if (iSearch == 1)
            aStart->singleSearch();
        if (iSearch == 2)
            aStart->doubleSearch();
        aStart->render();
    }


    Point* getF_min(vector<Point*> list);
    void deletePoint(Point* p, vector<Point*>& list);
    bool isInList(Point* p, vector<Point*> list);
    vector<Point*> getNeighborPoints(Point* curPnt, bool isFromStart);
    void render();
    void singleSearch();
    void doubleSearch();


    // 从起点到当前结点的代价
    double buildG(Point* curPnt, Point* nexPnt);

    double buildH(Point* nexPnt, bool isFromStart);

    double judgeNeighbour(Point* p1, Point* p2){
        int dx = abs(p1->x - p2->x);
        int dy = abs(p1->y - p2->y);

        if (dx + dy == 1)
            return COST_NORMAL;
        if (dx == 1 && dy == 1)
            return COST_DIAGONAL;
        return -1.0;
    }



public:
    int mHeight, mWidth;//地图的宽和高
    Point* startPoint;  Point* endPoint;//定义起点与终点
    vector<vector<Point*>> mapData;//定义地图数据
    vector<Point*> openListStart;
    vector<Point*> closeListStart;
    vector<Point*> openListEnd;
    vector<Point*> closeListEnd;
    bool isCorner = true;
};

#endif  //NINI_ASTAR_H