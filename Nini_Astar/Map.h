#pragma once
#ifndef NINI_ASTAR_MAP_H
#define NINI_ASTAR_MAP_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>

using namespace std;
struct Point{
    int x; int y; // 当前结点的坐标
    double F; // G + H
    double G; // 从起点到当前结点的代价
    double H; // 从当前结点到终点的预估代价
    Point* parent = nullptr; // 当前结点的父结点

    int pointType;//定义点的类型包括0和1

    Point(int xx = 0, int yy = 0) : parent(nullptr), F(0), G(0), H(0), x(xx), y(yy)
    {}
};

class Map{
public:
    void renderMap(vector<vector<Point*>> maze, Point* pStart, Point* pEnd);
    void renderBlock(cv::Mat& image, Point* aPoint, int size);
    void renderText(cv::Mat& image, Point* aPoint, int size, const string& text);

};

#endif //NINI_ASTAR_MAP_H