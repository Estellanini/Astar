#pragma once
#ifndef NINI_ASTAR_MAP_H
#define NINI_ASTAR_MAP_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>

using namespace std;
struct Point{
    int x; int y; // ��ǰ��������
    double F; // G + H
    double G; // ����㵽��ǰ���Ĵ���
    double H; // �ӵ�ǰ��㵽�յ��Ԥ������
    Point* parent = nullptr; // ��ǰ���ĸ����

    int pointType;//���������Ͱ���0��1

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