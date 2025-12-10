#define CLOCKWISE -1
#define COUNTERCLOCKWISE 1
#define INCLUDE_COLLINEAR 0 // pode mudar

struct Point {
    ll x, y;
    bool operator==(Point const& t) const {
        return x == t.x && y == t.y;
    }
};

struct Vec {
    int x, y, z;
};

Vec cross(Vec v1, Vec v2){
    int x = v1.y*v2.z - v1.z*v2.y;
    int y = -v1.x*v2.z + v1.z*v2.x;
    int z = v1.x*v2.y - v1.y*v2.x;
    return {x,y,z};
}

ll dist2(Point p1, Point p2){
    int dx = p1.x-p2.x;
    int dy = p1.y-p2.y;
    return dx*dx+dy*dy;
}

ll orientation(Point pivot, Point a, Point b){
    Vec va = {a.x-pivot.x, a.y-pivot.y, 0};
    Vec vb = {b.x-pivot.x, b.y-pivot.y, 0};
    Vec v = cross(va,vb); 
    if (v.z < 0) return CLOCKWISE;
    if (v.z > 0) return COUNTERCLOCKWISE;
    return 0;
}

bool clock_wise(Point pivot, Point a, Point b) {
    int o = orientation(pivot, a, b);
    return o < 0 || (INCLUDE_COLLINEAR && o == 0);
}

bool collinear(Point a, Point b, Point c) { return orientation(a, b, c) == 0; }
    
vector<Point> convex_hull(vector<Point> &points, bool counterClockwise) {
    int n = points.size();
    Point pivot = *min_element(points.begin(), points.end(), [](Point a, Point b) {
        return ii(a.y, a.x) < ii(b.y, b.x);
    });

    sort(points.begin(), points.end(), [&](Point a, Point b) {
        int o = orientation(pivot, a, b);
        if (o == 0) return dist2(pivot, a) < dist2(pivot, b);
        return o == CLOCKWISE;
    });

    if (INCLUDE_COLLINEAR) {
        int i = n-1;
        while (i >= 0 && collinear(pivot, points[i], points.back())) i--;
        reverse(points.begin()+i+1, points.end());
    }

    vector<Point> hull;
    for (auto p : points) {
        while (hull.size() > 1 && !clock_wise(hull[hull.size()-2], hull.back(), p))
        hull.pop_back();
        hull.push_back(p);
    }
    if (!INCLUDE_COLLINEAR && hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();

    if (counterClockwise && hull.size() > 1) {
        vector<Point> reversed_hull = hull;
        reverse(reversed_hull.begin() + 1, reversed_hull.end());
        return reversed_hull;
    }
    return hull;
}
