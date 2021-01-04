#pragma once
#ifndef NINI_ASTAR_H
#define NINI_ASTAR_H

#include "Map.h"

#define COST_NORMAL 1.0 // ֱ�ߴ���
#define COST_DIAGONAL sqrt(2.0) // �ԽǴ���
#define COST_RIVER 2.0 // Ϫ������
#define COST_DESERT 4.0 // ɳĮ����


class AStar{
public:
    explicit AStar(int type);
    static void init(){
        int imap = 1, iSearch = 1;
        cout << "��ѡ���ͼ��" << endl;
        cin >> imap;
        cout << "��ѡ�����˫��" << endl;
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


    // ����㵽��ǰ���Ĵ���
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
    int mHeight, mWidth;//��ͼ�Ŀ�͸�
    Point* startPoint;  Point* endPoint;//����������յ�
    vector<vector<Point*>> mapData;//�����ͼ����
    vector<Point*> openListStart;
    vector<Point*> closeListStart;
    vector<Point*> openListEnd;
    vector<Point*> closeListEnd;
    bool isCorner = true;
};

#endif  //NINI_ASTAR_H