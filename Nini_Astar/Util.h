#pragma once
#ifndef NINI_ASTAR_UTIL_H
#define NINI_ASTAR_UTIL_H

#include <fstream>
#include <sstream>
#include <vector>
#include "Map.h"

using namespace std;
class Util{
public:
    //static void drawFirstMap();
    //static void drawSecondMap();
    static void readMapData(int maze, Point*& pStart, Point*& pEnd, vector<vector<Point*>>& mapData);//读取地图数据
};


#endif //NINI_ASTAR_UTIL_H