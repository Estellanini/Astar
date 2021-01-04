#include "Util.h"
const char* MAP1_PATH = "F:\\Nini_Astar\\Nini_Astar\\map\\map1.txt";//地图1 文件
const char* MAP2_PATH = "F:\\Nini_Astar\\Nini_Astar\\map\\map2.txt";//地图2 文件


void Util::readMapData(int map, Point*& pStart, Point*& pEnd, vector<vector<Point*>>& mapData){//读取地图数据
    const char* path = map == 0 ? MAP1_PATH : MAP2_PATH;
   
    ifstream in(path);

    int height, width;//定义地图宽高
    int startY, startX;//定义起点的横纵坐标
    int endY, endX;//定义终点的横纵坐标
    in >> height >> width; // 读取文本文件中第一行宽高
    in >> startY >> startX; // 读取文本文件中第二行起点
    in >> endY >> endX; // 读取文本文件中第三行终点


    for (int h = 0; h < height; ++h){
        vector<Point*> vec;
        for (int w = 0; w < width; ++w){
            int type;
            in >> type;//读取文本文件中每个点的值0或1

            auto* p = new Point;//auto 声明的变量必须由编译器在编译时期推导而得
            p->x = w;
            p->y = h;
            p->pointType = type;
            vec.push_back(p);//将此点推入栈

            if (p->x == startX && p->y == startY)//定义起点
                pStart = p;
            else if (p->x == endX && p->y == endY)//定义终点
                pEnd = p;
        }
        mapData.push_back(vec); //在vector尾部加入一个点，每个点又是一个动态数组里面包括横纵坐标
    }

    in.close();//输入流关闭
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


    // 起始点
    out << 8 << " " << 3 << endl;
    // 终止点
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

    // 绘制灰色 1
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



    // 绘制黄色 2

    int l[8] = { 24, 25, 26, 26, 26, 27, 27, 29 };
    int r[8] = { 39, 39, 39, 36, 35, 32, 32, 32 };

    for (int i = 0; i < 8; i++)
        for (int j = l[i]; j <= r[i]; j++)
            mapData[i][j] = 2;

    // 绘制蓝色 3

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


    // 起始点
    out << 10 << " " << 4 << endl;
    // 终止点
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