#include "Visualization.h"

Visualization::Visualization(string filename) {
    emptyMap.readFromFile(filename);
}
long double Visualization::degToRad(long double degrees) {
    return (degrees * M_PI) / 180;
}

long double Visualization::lonToOffsets(long double longitude, int mapWidth) {
    int FE = 180;
    long double radius = mapWidth / (2 * M_PI);

    long double lonRad = degToRad(longitude + FE);
    long double x = lonRad * radius;

    return x;
}

long double Visualization::latToOffsets(long double latitude, int mapWidth, int mapHeight) {
    long double radius = mapWidth / (2 * M_PI);

    long double latRad = degToRad(latitude);
    long double yFromEquator = radius * log(tan(M_PI / 4 + latRad / 2));
    long double y = mapHeight / 2 - yFromEquator;

    return y;
} 

void Visualization::mapRoutes(long double srcIdx, long double dstIdx, PNG& img, vector<pair<long double, long double>> vertexLoc){
    long double x1, x2, y1, y2;
    x1 = vertexLoc[srcIdx].first;
    y1 = vertexLoc[srcIdx].second;
    x2 = vertexLoc[dstIdx].first;
    y2 = vertexLoc[dstIdx].second;
    drawRoutes(x1, y1, x2, y2, img);
}

void Visualization::drawRoutes(long double src_long, long double src_lat, long double dst_long, long double dst_lat, PNG& img){
    long double x1, y1, x2, y2, dx, dy, ix, iy;
    x1 = src_long;
    y1 = src_lat;
    x2 = dst_long;
    y2 = dst_lat;
    dx = dst_long - src_long;
    dy = dst_lat - src_lat;
    long double dis = sqrt((dx * dx) + (dy * dy));
    long double w_x1, w_x2, w_dx, w_dis;
    if (src_long <= dst_long){
        w_x2 = w_x2 - img.width();
    }
    else{
        w_x1 = w_x1 - img.width();
    }
    w_dx = w_x2 - w_x1;
    w_dis = sqrt((w_dx * w_dx) + (dy * dy));
    if (w_dis <= dis){
        dx = w_dx;
        x1 = w_x1;
        x2 = w_x2;
    }
    long double slope;
    if (abs(dx) > abs(dy)){
        slope = abs(dx);
    }
    else{
        slope = abs(dy);
    }
    ix = dx / slope;
    iy = dy / slope;
    for (unsigned i; i < slope; i++){
        int w = emptyMap.width();
        int x = (((int)round(x1) % w) + w) % w;
        cs225::HSLAPixel& pixel = emptyMap.getPixel((unsigned) x, unsigned(round(y1)));
        pixel = routecolor;
        x1 = x1 + ix;
        y1 = y1 + iy;
    }
}

void Visualization::drawMap(Graph<int> g){
    //emptyMap.readFromFile("world-map.png");
    cs225::PNG routeMap(emptyMap);
    vector<pair<int, int>> edgeList = g.getEdgeList();
    for (int i = 0; i < edgeList.size(); i++){
        mapRoutes(edgeList[i].first, edgeList[i].second, routeMap, g.getVertexLoc());
    }
    routeMap.writeToFile("results/output");
}