#include "Util.h"
const char* MAP1_PATH = "F:\\Nini_Astar\\Nini_Astar\\map\\map1.txt";//��ͼ1 �ļ�
const char* MAP2_PATH = "F:\\Nini_Astar\\Nini_Astar\\map\\map2.txt";//��ͼ2 �ļ�


void Util::readMapData(int map, Point*& pStart, Point*& pEnd, vector<vector<Point*>>& mapData){//��ȡ��ͼ����
    const char* path = map == 0 ? MAP1_PATH : MAP2_PATH;
   
    ifstream in(path);

    int height, width;//�����ͼ���
    int startY, startX;//�������ĺ�������
    int endY, endX;//�����յ�ĺ�������
    in >> height >> width; // ��ȡ�ı��ļ��е�һ�п��
    in >> startY >> startX; // ��ȡ�ı��ļ��еڶ������
    in >> endY >> endX; // ��ȡ�ı��ļ��е������յ�


    for (int h = 0; h < height; ++h){
        vector<Point*> vec;
        for (int w = 0; w < width; ++w){
            int type;
            in >> type;//��ȡ�ı��ļ���ÿ�����ֵ0��1

            auto* p = new Point;//auto �����ı��������ɱ������ڱ���ʱ���Ƶ�����
            p->x = w;
            p->y = h;
            p->pointType = type;
            vec.push_back(p);//���˵�����ջ

            if (p->x == startX && p->y == startY)//�������
                pStart = p;
            else if (p->x == endX && p->y == endY)//�����յ�
                pEnd = p;
        }
        mapData.push_back(vec); //��vectorβ������һ���㣬ÿ��������һ����̬�������������������
    }

    in.close();//�������ر�
}

/*void Util::drawFirstMap(){
    ofstream out(MAP1_PATH);

    int height = 14;
    int width = 17;

    out << height << " " << width << endl;

    vector<vector<int>> mapData;

    for (int h = 0; h < height; ++h){
        vector<int> vec;
        for (int w = 0; w < width; ++w){
            vec.push_back(0);
        }
        mapData.push_back(vec);
    }

    mapData[5][6] = 1;
    mapData[6][6] = 1;
    mapData[7][7] = 1;
    mapData[8][7] = 1;
    mapData[9][7] = 1;
    mapData[9][8] = 1;
    mapData[10][8] = 1;
    mapData[11][8] = 1;


    // ��ʼ��
    out << 8 << " " << 3 << endl;
    // ��ֹ��
    out << 9 << " " << 14 << endl;


    if (out.is_open()){
        for (int h = 0; h < height; ++h){
            for (int w = 0; w < width; ++w){
                out << mapData[h][w];
                if (w < width - 1)
                    out << " ";
            }
            if (h < height - 1)
                out << endl;
        }
    }
    out.close();
}

void Util::drawSecondMap(){
    ofstream out(MAP2_PATH);

    int height = 20;
    int width = 40;

    out << height << " " << width << endl;

    vector<vector<int>> mapData;

    for (int h = 0; h < height; ++h){
        vector<int> vec;
        for (int w = 0; w < width; ++w)
            vec.push_back(0);

        mapData.push_back(vec);
    }

    // ���ƻ�ɫ 1
    for (int i = 0; i < 11; ++i){
        if (i == 6)
            continue;
        mapData[2][i] = 1;
    }

    for (int i = 2; i <= 7; ++i)
        mapData[6][i] = 1;
    for (int i = 2; i <= 5; ++i)
        mapData[11][i] = 1;
    for (int i = 3; i <= 8; ++i)
        mapData[15][i] = 1;

    for (int i = 6; i <= 11; ++i)
        mapData[i][5] = 1;

    for (int i = 11; i <= 19; ++i){
        if (i == 17) continue;
        mapData[i][3] = 1;
    }

    for (int i = 2; i <= 15; ++i){
        if (i == 4) continue;
        if (i >= 6 && i <= 9) continue;
        mapData[i][8] = 1;
    }

    for (int i = 0; i < 20; ++i){
        if (i >= 8 && i <= 11)
            continue;
        mapData[i][12] = 1;
    }

    for (int i = 0; i < 20; ++i){
        if (i == 3 || i == 4 || i == 8 || i == 16)
            continue;
        if (i >= 11 && i <= 14)
            continue;
        mapData[i][7] = 1;
    }

    mapData[0][3] = 1;
    mapData[7][2] = 1;
    mapData[10][2] = 1;
    mapData[13][9] = 1;
    mapData[13][11] = 1;


    for (int i = 10; i <= 12; ++i)
        for (int j = 19; j <= 21; ++j)
            mapData[i][j] = 1;

    for (int i = 15; i <= 16; ++i)
        for (int j = 24; j <= 25; ++j)
            mapData[i][j] = 1;

    mapData[10][28] = 1;
    mapData[11][31] = 1;
    mapData[13][31] = 1;
    mapData[7][36] = 1;
    mapData[9][36] = 1;



    // ���ƻ�ɫ 2

    int l[8] = { 24, 25, 26, 26, 26, 27, 27, 29 };
    int r[8] = { 39, 39, 39, 36, 35, 32, 32, 32 };

    for (int i = 0; i < 8; i++)
        for (int j = l[i]; j <= r[i]; j++)
            mapData[i][j] = 2;

    // ������ɫ 3

    int top0[9] = { 19, 18, 17, 15, 13, 12, 11, 10, 10 };
    int bot0[9] = { 19, 19, 19, 18, 17, 16, 14, 11, 10 };
    for (int i = 0; i < 9; i++)
        for (int j = top0[i]; j <= bot0[i]; j++)
            mapData[j][i + 28] = 3;

    int top1[4] = { 8, 4, 5, 7 };
    int bot1[4] = { 11, 10, 9, 8 };
    for (int i = 0; i < 4; i++)
        for (int j = top1[i]; j <= bot1[i]; j++)
            mapData[j][i + 32] = 3;

    mapData[1][34] = 3;
    mapData[2][33] = 3;
    mapData[3][32] = 3;


    // ��ʼ��
    out << 10 << " " << 4 << endl;
    // ��ֹ��
    out << 0 << " " << 35 << endl;


    if (out.is_open()){
        for (int h = 0; h < height; ++h){
            for (int w = 0; w < width; ++w){
                out << mapData[h][w];
                if (w < width - 1)
                    out << " ";
            }
            if (h < height - 1)
                out << endl;
        }
    }
    out.close();
}
*/