#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
#define eps 1e-9
#define pi 3.141592653589
#define int long long int


struct pt {
    int x, y;
    int operator==(pt b) {
        return x == b.x && y == b.y;
    }
    int operator<(pt b) {
        if(x == b.x) return y < b.y;
        return x < b.x;
    }
    pt operator-(pt b) {
        return {x - b.x, y - b.y};
    }
    pt operator+(pt b) {
        return {x+b.x, y + b.y};
    }
};
int cross(pt u, pt v) {
    return u.x * v.y - u.y * v.x;
}
int dot(pt u, pt v) {
    return u.x * v.x + u.y * v.y;
}
ld norm(pt u) {
    return sqrt(dot(u, u));
}
ld dist(pt u, pt v) {
    return norm(u - v);
}
int ccw(pt u, pt v) { // cuidado com colineares!!!!
    return (cross(u, v) > eps)?1:((fabs(cross(u, v)) < eps)?0:-1);
}
int pointInSegment(pt a, pt u, pt v) { // checks if a lies in uv
    if(ccw(v - u, a - u)) return 0;
    vector<pt> pts = {a, u, v};
    sort(pts.begin(), pts.end());
    return pts[1] == a;
}
ld angle(pt u, pt v) { // angle between two vectors
    ld c = cross(u, v);
    ld d = dot(u,v);
    return atan2l(c, d);
}
int intersect(pt sa, pt sb, pt ra, pt rb) {// not sure if it works when one of the segments is a point
    pt s = sb - sa, r = rb - ra;
    if(pointInSegment(sa, ra, rb) || pointInSegment(sb, ra, rb) ||pointInSegment(ra, sa, sb) || pointInSegment(rb, sa, sb)) return 1;
    return !(ccw(s, ra - sa) == ccw(s, rb - sa) || ccw(r, sa - ra) == ccw(r, sb - ra));
}

ld polygonArea(vector<pt>& p) {// not signed (for signed area remove the absolute value at the end)
    ld area = 0;
    int n = p.size() - 1; // p[n] = p[0]
    for(int i = 0; i < n; i++) {
        area += cross(p[i], p[i + 1]);
    }
    return fabs(area)/2;
}
int pointInPolygon(pt a, vector<pt>& p) {// returns 0 for point in BOUNDARY, 1 for point in polygon and -1 for outside
    ld total = 0;
    int n = p.size() - 1;
    for(int i = 0; i < n; i++) {
        pt u = p[i] - a;
        pt v = p[i + 1] - a;
        if(fabs(dist(p[i], a) + dist(p[i + 1], a) - dist(p[i], p[i + 1])) < eps) {
            return 0;
        }
        total += angle(u, v);
    }
    
    return (fabs(fabs(total) - 2 * pi) < eps)?1:-1;
}



signed main() {
    int n, m; scanf("%lld %lld", &n, &m);
    vector<pt> p(n + 1);
    for(int i = 0; i < n; i++) {
        scanf("%lld %lld", &p[i].x, &p[i].y);
    }
    p[n] = p[0];
    
    while(m--) {
        pt a; scanf("%lld %lld", &a.x, &a.y);
        int ans = pointInPolygon(a, p);
        printf("%s\n", (ans > 0)?"INSIDE":(ans?"OUTSIDE":"BOUNDARY"));
    }
}