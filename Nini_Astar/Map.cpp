#include "Map.h"

const cv::Scalar COLOR_BLACK(0, 0, 0);
const cv::Scalar COLOR_GRAY(128, 128, 128);
const cv::Scalar COLOR_YELLOW(0, 173, 230);
const cv::Scalar COLOR_BLUE(120, 88, 0);

const cv::Scalar COLOR_PATH1(223, 224,132);
const cv::Scalar COLOR_PATH2(191, 162, 199);


const int BLOCK_SIZE = 30;

void Map::renderMap(vector<vector<Point*>> map, Point* pStart,Point* pEnd)
{
    int height = map.size();
    int width = map[0].size();

    cv::Mat image(height * BLOCK_SIZE, width * BLOCK_SIZE, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int h = 0; h < height; ++h)
        for (int w = 0; w < width; ++w)
            renderBlock(image, map[h][w], BLOCK_SIZE);

    // 标记起始点和终止点
    renderText(image, pStart, BLOCK_SIZE, "S");
    renderText(image, pEnd, BLOCK_SIZE, "E");

    imshow("map", image);
    cv::waitKey(0);
}

void Map::renderBlock(cv::Mat& image, Point* aPoint, int size)
{

    cv::Point pnt0(aPoint->x * size, aPoint->y * size);
    cv::Point pnt1((aPoint->x + 1) * size, (aPoint->y + 1) * size);

    if (aPoint->pointType == 1) // 灰色墙路径
        cv::rectangle(image, pnt0, pnt1, COLOR_GRAY, -1);
    else if (aPoint->pointType == 2) // 沙漠路径
        cv::rectangle(image, pnt0, pnt1, COLOR_YELLOW, -1);
    else if (aPoint->pointType == 3) // 河流路径
        cv::rectangle(image, pnt0, pnt1, COLOR_BLUE, -1);
    else if (aPoint->pointType == 4) // 单向最优路径
        cv::rectangle(image, pnt0, pnt1, COLOR_PATH1, -1);
    else if (aPoint->pointType == 5) // 双向最优路径
        cv::rectangle(image, pnt0, pnt1, COLOR_PATH2, -1);

    cv::rectangle(image, pnt0, pnt1, COLOR_BLACK);
}

void Map::renderText(cv::Mat& image, Point* aPoint, int size, const string& text)
{
    cv::Point originPnt(aPoint->x * size + 0.4 * size, aPoint->y * size + 0.6 * size);
    cv::putText(image, text, originPnt, 1.0, 1.0, COLOR_BLACK, 2.0);
}