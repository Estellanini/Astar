#include "AStar.h"
#include "Util.h"


AStar::AStar(int type){
    Util::readMapData(type, startPoint, endPoint, mapData);//读取地图数据
    this->mHeight = mapData.size();//读取地图高度
    this->mWidth = mapData[0].size();//读取地图宽度
}
Point* AStar::getF_min(vector<Point*> list){//获取最小的f值  f=当前代价g+预估代价h
    if (list.empty())  return nullptr;
    Point* p = list[0];
    for (int i = 1; i < list.size(); ++i)
        if (list[i]->F <= p->F)
            p = list[i];
    return p;//返回F值最小的点
}

void AStar::deletePoint(Point* p, vector<Point*>& list){
    if (list.empty())   return;
    int key = -1;
    for (int i = 0; i < list.size(); ++i){
        if (list[i]->x == p->x && list[i]->y == p->y){
            key = i;
            break;
        }
    }
    if (key != -1)
        list.erase(list.begin() + key);
}

bool AStar::isInList(Point* p, vector<Point*> list){//是否在list中
    if (list.empty())
        return false;
    for (auto& i : list){
        if (p->x == i->x && p->y == i->y)
            return true;
    }
    return false;
}

vector<Point*> AStar::getNeighborPoints(Point* currentPoint, bool isFromStart){
    vector<Point*> list;

    int hMove[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };//y轴的九宫格变化
    int wMove[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };//x轴的九宫格变化

    for (int i = 0; i < 9; ++i){
        int y = currentPoint->y + hMove[i];
        int x = currentPoint->x + wMove[i];

        if (i == 4 || y < 0 || x < 0 || y >= mHeight || x >= mWidth)    continue;  // 点本身或超出地图范围
        Point* nexPnt = mapData[y][x];
        if (nexPnt->pointType == 1)    continue;   // 障碍物或已经遍历过

        if (isFromStart && isInList(nexPnt, closeListStart))
            continue;
        if (!isFromStart && isInList(nexPnt, closeListEnd))
            continue;

        list.push_back(nexPnt);
    }
    return list;
}

double AStar::buildG(Point* curPnt, Point* nexPnt){//计算G
    // 移动代价
    int dx = abs(curPnt->x - nexPnt->x);
    int dy = abs(curPnt->y - nexPnt->y);
    double moveCost = (dx + dy == 1) ? COST_NORMAL : COST_DIAGONAL;//直线代价 以及对角代价
    // 地形代价
    double landCost = 0;
    if (mapData[nexPnt->y][nexPnt->x]->pointType == 2)
        landCost += COST_DESERT;
    else if (mapData[nexPnt->y][nexPnt->x]->pointType == 3)
        landCost += COST_RIVER;
    // 当前步代价
    double curCost = moveCost + landCost;
    //    double previousCost = curPnt->parent == nullptr ? 0 : curPnt->parent->G;
    double previousCost = curPnt->G;
    return previousCost + curCost;
}

double AStar::buildH(Point* nexPnt, bool isFromStart){

    Point* finalPnt = isFromStart ? endPoint : startPoint;//用于判断双向单向

    int dx = finalPnt->x - nexPnt->x;
    int dy = finalPnt->y - nexPnt->y;

    // 欧几里得距离作为启发函数
    dx = abs(dx);
    dy = abs(dy);
    return sqrt(dx * dx + dy * dy) + nexPnt->G;//欧几里得距离
   // return abs(dx) + abs(dy) + nexPnt->G;//曼哈顿距离
  
}

void AStar::render(){
    Map map;
    map.renderMap(mapData, startPoint, endPoint);
}

void AStar::singleSearch(){
    startPoint->G = 0;
    startPoint->H = buildH(startPoint, true);
    startPoint->F = startPoint->G + startPoint->H;

    openListStart.push_back(startPoint);
    while (!openListStart.empty()){
        Point* curPnt = getF_min(openListStart);
        closeListStart.push_back(curPnt);//取openlist的拥有最小F值的点curPnt，加入closelist
        deletePoint(curPnt, openListStart);//在openlist中删除当前节点

        // 获取周围邻居节点
        vector<Point*> neighbors = getNeighborPoints(curPnt, true);//true代表单向
        if (neighbors.empty())
            continue;

        for (Point* nextPoint : neighbors){
            if (!isInList(nextPoint, openListStart)){
                nextPoint->parent = curPnt;//父节点指向当前节点
                nextPoint->G = buildG(curPnt, nextPoint);
                nextPoint->H = buildH(nextPoint, true);
                nextPoint->F = nextPoint->G + nextPoint->H;
                openListStart.push_back(nextPoint);

            }
            else{
                double curG = buildG(curPnt, nextPoint);
                if (curG < nextPoint->G){
                    nextPoint->parent = curPnt;
                    nextPoint->G = curG;
                    nextPoint->F = curG + nextPoint->H;
                }
            }
        }

        // 已经到达终点
        if (isInList(endPoint, openListStart)){
            Point* p = endPoint;
            while (p != nullptr){
                p->pointType = 4;
                p = p->parent;
            }
            //showPointInfo(endPoint);
            return;
        }
    }
}

void AStar::doubleSearch(){
    openListStart.push_back(startPoint);
    openListEnd.push_back(endPoint);

    //int key = 0;

    while (!openListStart.empty() && !openListEnd.empty()){
        Point* curPntS = getF_min(openListStart);
        Point* curPntE = getF_min(openListEnd);

        //++key;

        closeListStart.push_back(curPntS);
        closeListEnd.push_back(curPntE);
        deletePoint(curPntS, openListStart);
        deletePoint(curPntE, openListEnd);

        // 获取当前结点周围的点
        vector<Point*> startNeighbors = getNeighborPoints(curPntS, true);
        vector<Point*> endNeighbors = getNeighborPoints(curPntE, false);

        for (Point* nexPnt : startNeighbors){
            if (!isInList(nexPnt, openListStart)){
                nexPnt->parent = curPntS;
                nexPnt->G = buildG(curPntS, nexPnt);
                nexPnt->H = buildH(nexPnt, true);
                nexPnt->F = nexPnt->G + nexPnt->H;
                openListStart.push_back(nexPnt);
            }
  
        }

        for (Point* nexPnt : endNeighbors){
            if (!isInList(nexPnt, openListEnd)){
                nexPnt->parent = curPntE;
                nexPnt->G = buildG(curPntE, nexPnt);
                nexPnt->H = buildH(nexPnt, false);
                nexPnt->F = nexPnt->G + nexPnt->H;
                openListEnd.push_back(nexPnt);
            }
  
        }

        // 检查两个活结点表是否已经存在相交点
        Point* nPntStart=nullptr;
        Point* nPntEnd=nullptr;
        double dis = INT_MAX;
        bool flag = false;

        for (auto ps : openListStart){
            for (auto pe : openListEnd){
                double curDis = judgeNeighbour(ps, pe);
                double allDis = curDis + ps->G + pe->G;
                if (curDis > 0 && allDis < dis){
                    nPntStart = ps;
                    nPntEnd = pe;
                    dis = allDis;
                    flag = true;
                }
  
            }
        }

        if (flag){
            cout << dis << endl;
            while (nPntStart != nullptr){
                nPntStart->pointType = 4;
                nPntStart = nPntStart->parent;
            }

            while (nPntEnd != nullptr){
                nPntEnd->pointType = 5;
                nPntEnd = nPntEnd->parent;
            }
            return;
        }

    }

}


