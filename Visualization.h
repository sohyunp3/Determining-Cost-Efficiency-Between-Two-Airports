#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <math.h>
#include <vector>
#include "Graph.h"

using namespace cs225;

class Visualization {
    public:
        Visualization(string filename);
        ~Visualization() {}
        long double degToRad(long double);
        long double lonToOffsets(long double, int);
        long double latToOffsets(long double, int, int);
        PNG emptyMap;
        void drawMap(Graph<int> g);

    private:
        void mapRoutes(long double srcIdx, long double dstIdx, PNG& img, vector<pair<long double, long double>> vertexLoc);
        void drawRoutes(long double scr_long, long double src_lat, long double dst_long, long double dst_lat,  PNG& img);
        const cs225::HSLAPixel routecolor = cs225::HSLAPixel(100, 1, 0.6, 1);
            
};