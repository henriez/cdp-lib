// heavily inspired by brunomaletta/biblioteca
using T = long long; // change to ld if necessary
const ld DINF = 2e18;
const ld pi = acosl(-1.0);
const ld eps = 1e-9;
#define sq(x) ((x)*(x))
// -1 for negative, 0 for zero, 1 for positive
int sgn(T x) {
  if constexpr (is_floating_point_v<T>) 
    return (x > eps) - (x < -eps);
  return (x > 0) - (x < 0);
}
struct pt {
  T x, y;
  pt(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
  bool operator<(const pt p) const {
    if (sgn(x-p.x) != 0) return sgn(x-p.x) < 0;
    return sgn(y-p.y) < 0;
  }
  bool operator==(const pt p) const { 
    return sgn(x-p.x) == 0 && sgn(y-p.y) == 0; 
  }
  pt operator+(pt p) const {return pt(x+p.x, y+p.y);}
  pt operator-(pt p) const {return pt(x-p.x, y-p.y);}
  pt operator*(T c) const {return pt(x*c, y*c);}
  pt operator/(T c) const {return pt(x/c, y/c);}
  T operator*(pt p) const {return x*p.x + y*p.y;}
  T operator^(pt p) const {return x*p.y - y*p.x;}
  friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};
struct line {
  pt p, q;
  line() {}
  line(pt p_, pt q_) : p(p_), q(q_) {}
  friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

// --- INTEGER SAFE OPERATIONS --- //

ld dist(pt p, pt q) { 
  return hypot((ld)(p.y - q.y), (ld)(p.x - q.x)); 
}
T dist2(pt p, pt q) {return sq(p.x-q.x) + sq(p.y-q.y);}
ld norm(pt v) { return dist(pt(0, 0), v); }
// Angle with +x axis in [0, 2*pi)
ld angle(pt v) { 
  ld ang = atan2((ld)v.y, (ld)v.x); 
  return ang < 0 ? ang + 2*pi : ang; 
}
// 2x signed area of triangle p-q-r (>0 if ccw)
T sarea2(pt p, pt q, pt r) { return (q-p)^(r-q); }
// True if p, q, r are collinear
bool col(pt p,pt q,pt r){return sgn(sarea2(p,q,r))==0;}
// True if r is strictly to the left of line p->q
bool ccw(pt p,pt q,pt r) {return sgn(sarea2(p,q,r))>0;}
bool isvertical(line r) {return sgn(r.p.x-r.q.x) == 0;}
// True if point p lies on segment r
bool isinseg(pt p, line r) {
  pt a = r.p - p, b = r.q - p;
  return sgn(a ^ b) == 0 && sgn(a * b) <= 0;
}
bool interseg(line r, line s) {
  if (isinseg(r.p, s) || isinseg(r.q, s) || 
      isinseg(s.p, r) || isinseg(s.q, r)) return 1;
  return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) &&
         ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}
ld disttoline(pt p, line r) { 
  return (ld)abs(sarea2(p, r.p, r.q)) / dist(r.p, r.q); 
}
ld disttoseg(pt p, line r) {
  if (sgn((r.q-r.p)*(p-r.p)) < 0) return dist(r.p,p);
  if (sgn((r.p-r.q)*(p-r.q)) < 0) return dist(r.q,p);
  return disttoline(p, r);
}

// --- POLYGONS (INTEGER SAFE) --- //

ld polarea(const vector<pt> &v) {
  T ans = 0;
  for (int i = 0; i < sz(v); i++) 
    ans += (v[i] ^ v[(i+1)%sz(v)]);
  return abs((ld)ans / 2.0);
}
// Returns 0 if out, 1 if inside, 2 if on border
int inpol(const vector<pt> &v, pt p) {
  int qt = 0;
  for (int i = 0; i < sz(v); i++) {
    if (p == v[i]) return 2;
    int j = (i+1)%sz(v);
    if (sgn(p.y-v[i].y)==0 && sgn(p.y-v[j].y)==0) {
      if (sgn((v[i]-p)*(v[j]-p)) <= 0) return 2;
      continue;
    }
    bool lower = sgn(v[i].y - p.y) < 0;
    if (lower == (sgn(v[j].y - p.y) < 0)) continue;
    auto t = (p-v[i])^(v[j]-v[i]);
    if (sgn(t) == 0) return 2;
    if (lower == (sgn(t) > 0)) qt += lower ? 1 : -1;
  }
  return qt != 0;
}
// Monotone chain convex hull - O(N log N)
// icol - include_collinear
vector<pt> convex_hull(vector<pt> v, bool icol = 0) {
  sort(all(v)); 
  v.erase(unique(all(v)), v.end());
  int n = sz(v);
  if (n <= 1) return v;
  vector<pt> l, u;
  auto bad = [&](pt a, pt b, pt c) {
    if (icol) return sgn(sarea2(a, b, c)) < 0;
    return sgn(sarea2(a, b, c)) <= 0;
  };
  for (int i = 0; i < n; i++) {
    while (sz(l)>1 && 
           bad(l[sz(l)-2], l[sz(l)-1], v[i])) 
      l.pop_back();
    l.push_back(v[i]);
  }
  for (int i = n-1; i >= 0; i--) {
    while (sz(u)>1 && bad(u[sz(u)-2], u[sz(u)-1], v[i])) 
      u.pop_back();
    u.push_back(v[i]);
  }
  l.pop_back(); u.pop_back();
  l.insert(l.end(), all(u));
  return l;
}
// d^2 of closest pair - O(N log N)
T closest_pair(vector<pt> v) {
  if (sz(v) <= 1) return 0;
  sort(all(v));
  vector<pt> t(sz(v));
  auto go = [&](auto& go, int l, int r) -> T {
    if (r-l <= 1) return DINF;
    int m = l + (r-l)/2;
    T mid = v[m].x;
    T ans = min(go(go, l, m), go(go, m, r));
    merge(begin(v)+l, begin(v)+m, begin(v)+m, begin(v)+r,
          begin(t),[](pt a,pt b){return sgn(a.y-b.y)<0;}
      );
    copy(t.begin(), t.begin()+(r-l), v.begin()+l);
    int k = 0;
    for (int i = l; i < r; i++) {
      if (sgn(sq(v[i].x - mid) - ans) >= 0) continue;
      for (int j = k-1; j >= 0; j--){
        if (sgn(sq(v[i].y-t[j].y)-ans) >= 0) break;
        ans = min(ans, dist2(v[i], t[j]));
      }
      t[k++] = v[i];
    }
    return ans;
  };
  return go(go, 0, sz(v));
}
struct convex_pol {
  vector<pt> pol;
  convex_pol(vector<pt> v) : pol(convex_hull(v)) {} 
  // O(log N) check if p is inside convex polygon
  bool is_inside(pt p) {
    if (pol.empty()) return false;
    if (sz(pol) == 1) return p == pol[0];
    int l = 1, r = sz(pol);
    while (l < r) {
      int m = l + (r - l) / 2;
      if (ccw(p, pol[0], pol[m])) l = m+1;
      else r = m;
    }
    if (l == 1) return isinseg(p,line(pol[0],pol[1]));
    if (l == (int)sz(pol)) return false;
    return !ccw(p, pol[l], pol[l-1]);
  }
  // O(log N) extreme vertex given custom comparator
  int extreme(const function<bool(pt, pt)>& cmp) {
    int n = sz(pol);
    auto extr = [&](int i, bool& cur_dir) {
      cur_dir = cmp(pol[(i+1)%n], pol[i]);
      return !cur_dir && !cmp(pol[(i+n-1)%n], pol[i]);
    };
    bool last_dir, cur_dir;
    if (extr(0, last_dir)) return 0;
    int l = 0, r = n;
    while (l+1 < r) {
      int m = l + (r - l) / 2;
      if (extr(m, cur_dir)) return m;
      bool rel_dir = cmp(pol[m], pol[l]);
      if ((!last_dir && cur_dir) || 
          (last_dir==cur_dir && rel_dir==cur_dir)) {
        l = m; last_dir = cur_dir;
      } else r = m;
    }
    return l;
  }
  // O(log N) furthest vertex in direction of vector v
  int max_dot(pt v) { 
    return extreme(
      [&](pt p, pt q) { return sgn(p*v - q*v) > 0; }
    ); 
  }
  // O(log N) indices of tangent vertices 
  // from point p strictly outside
  pair<int, int> tangents(pt p) {
    return {
      extreme([&](pt q, pt r){ return ccw(p,r,q); }), 
      extreme([&](pt q, pt r){ return ccw(p,q,r); })};
  }
};

// =============================================//
// --- FLOAT ONLY (REQUIRE 'using T = ld;') --- //
// =============================================//

// th in radians
pt rotate(pt p, ld th) { 
  return pt(
    p.x*cos(th) - p.y*sin(th), 
    p.x*sin(th) + p.y*cos(th)
  ); 
}
pt rotate90(pt p) { return pt(-p.y, p.x); }
// Scalar t such that 
// r.p + t*(r.q - r.p) intersects line pt(0,0) -> v
ld get_t(pt v, line r) { 
  return (ld)(r.p^r.q) / (ld)((r.p-r.q)^v); 
}
pt proj(pt p, line r) {
  if (r.p == r.q) return r.p;
  r.q = r.q - r.p; p = p - r.p;
  return r.q * ((p*r.q) / (r.q*r.q)) + r.p;
}
pt inter(line r, line s) {
  if (sgn((r.p - r.q) ^ (s.p - s.q)) == 0) 
    return pt(DINF, DINF);
  pt rq = r.q - r.p;
  return rq * get_t(rq, s) + r.p;
}
// Cuts polygon with line r leaving points 
// strictly to the left of r
vector<pt> cut_polygon(vector<pt> v, line r) {
  vector<pt> ans;
  for (int j = 0; j < (int)sz(v); j++) {
    if (ccw(r.p, r.q, v[j])) ans.push_back(v[j]);
    if (sz(v) == 1) continue;
    line s(v[j], v[(j+1)%sz(v)]);
    pt p = inter(r, s);
    if (isinseg(p, s)) ans.push_back(p);
  }
  ans.erase(unique(all(ans)), ans.end());
  if (sz(ans) > 1 && ans.back() == ans[0]) 
    ans.pop_back();
  return ans;
}
struct circle {
  pt c; ld r; // customizable to ll
  circle(pt x, pt y, pt z) {
    y = (x+y)/2.0; z = (x+z)/2.0;
    c = inter(line(y, y + rotate90(x-y)), 
              line(z, z + rotate90(x-z)));
    r = dist(c, x);
  }
  circle(pt c, ld r) : c(c), r(r) {}
};
vector<pt> circ_line_inter(const line &l, circle &c) {
  vector<pt> ans;
  pt b = l.q - l.p, a = l.p - c.c;
  ld A = b*b, B = a*b, C = a*a - c.r*c.r;
  ld D = B*B - A*C;
  if (sgn(D) < 0) return ans;
  ans.push_back(c.c+a+b*(-B+sqrt(max((ld)0,D)))/A);
  if (sgn(D) > 0) 
    ans.push_back(c.c+a+b*(-B-sqrt(max((ld)0, D)))/A);
  return ans;
}
vector<pt> circ_inter(circle ca, circle cb) {
  pt a = ca.c, b = cb.c;
  ld r = ca.r, R = cb.r, d = dist(a, b);
  vector<pt> ans;
  if (sgn(d - (r+R)) > 0 || 
      sgn(d + min(r, R) - max(r, R)) < 0) return ans;
  ld x = (d*d - R*R + r*r) / (2.0*d);
  ld y = sqrt(max((ld)0.0, r*r - x*x));
  pt v = (b-a)/d;
  ans.push_back(a + v*x + rotate90(v)*y);
  if (sgn(y) > 0) ans.push_back(a+v*x-rotate90(v)*y);
  return ans;
}

// --- POLYGON & LATTICE (INTEGER SAFE) --- //

// Centroid of a polygon. Area must be > 0.
pt centroid(const vector<pt>& v) {
  pt c(0, 0); ld A = 0;
  for (int i = 0; i < (int)sz(v); i++) {
    ld cross = (v[i] ^ v[(i+1)%sz(v)]);
    A += cross; 
    c = c + (v[i] + v[(i+1)%sz(v)]) * cross;
  }
  return c / (3.0 * A);
}
// Num of integer lattice points on polygon boundary
int boundary_pts(const vector<pt>& v) {
  int b = 0;
  for (int i = 0; i < (int)sz(v); i++) {
    pt p = v[i], q = v[(i+1)%sz(v)];
    b += gcd(abs((int)(p.x-q.x)),abs((int)(p.y-q.y)));
  }
  return b; // Obs: Interior pts I = (2*Area-B+2)/2
}
// Minkowski sum of two CONVEX polygons - O(N+M)
void reorder_pol(vector<pt>& p) {
  int pos = 0;
  for(int i = 1; i < (int)sz(p); i++) {
    if(p[i].y < p[pos].y || 
      (p[i].y==p[pos].y && p[i].x<p[pos].x)) pos = i;
  }
  rotate(p.begin(), p.begin() + pos, p.end());
}
vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
  reorder_pol(P); reorder_pol(Q);
  P.push_back(P[0]); P.push_back(P[1]);
  Q.push_back(Q[0]); Q.push_back(Q[1]);
  vector<pt> ans;
  int i = 0, j = 0;
  while(i < (int)sz(P)-2 || j < (int)sz(Q)-2) {
    ans.push_back(P[i] + Q[j]);
    auto cross = (P[i+1] - P[i]) ^ (Q[j+1] - Q[j]);
    if(cross >= 0 && i < (int)sz(P) - 2) i++;
    if(cross <= 0 && j < (int)sz(Q) - 2) j++;
  }
  return ans;
}
// O(N) diameter of CONVEX pol by rotating calipers
ld diameter(vector<pt> p) {
  if(sz(p) <= 1) return 0;
  if(sz(p) == 2) return dist(p[0], p[1]);
  ld ans = 0;
  for(int i = 0, j = 1; i < (int)sz(p); i++) {
    pt nxt = p[(i+1)%sz(p)];
    while(sarea2(p[i], nxt, p[(j+1)%sz(p)]) > 
          sarea2(p[i], nxt, p[j])) j = (j+1)%sz(p);
    ans = max({ans, dist(p[i],p[j]), dist(nxt,p[j])});
  }
  return ans;
}

// ============================================ //  
// --- FLOAT ONLY (REQUIRE 'using T = ld;') --- //
// ============================================ //

struct halfplane {
  pt p, pq; ld ang;
  halfplane() {}
  halfplane(pt a, pt b) : p(a), pq(b - a) { 
    ang = atan2((ld)pq.y, (ld)pq.x); 
  }
  bool out(pt r) { return sgn(pq ^ (r - p)) < 0; }
  bool operator<(const halfplane& e) const { 
    if(sgn(ang-e.ang) == 0) return sgn(pq^(e.p-p))<0;
    return ang < e.ang;
  }
  pt inter(const halfplane& s) {
    pt rq = s.p - p;
    ld t = (ld)(s.pq ^ rq) / (ld)(pq ^ s.pq);
    return p + pq * t;
  }
};
// Half-Plane Intersection - O(N log N)
// Returns convex polygon bounding the intersection
vector<pt> hpi(vector<halfplane> H) {
  sort(all(H));
  deque<halfplane> q; deque<pt> ans;
  for(int i = 0; i < (int)sz(H); i++) {
    while(!ans.empty() && H[i].out(ans.back())) { 
      ans.pop_back(); q.pop_back(); 
    }
    while(!ans.empty() && H[i].out(ans.front())) { 
      ans.pop_front(); q.pop_front(); 
    }
    if(i>0 && sgn(H[i].ang-H[i-1].ang) == 0) continue;
    q.push_back(H[i]);
    if(sz(q) > 1) 
      ans.push_back(q.back().inter(q[sz(q)-2]));
  }
  while(!ans.empty() && q.front().out(ans.back())) { 
    ans.pop_back(); q.pop_back(); 
  }
  if(sz(q) < 3) return {};
  ans.push_back(q.back().inter(q.front()));
  return vector<pt>(all(ans));
}
// Minimum Enclosing Circle (Welzl's Algorithm)
// O(N) randomized
circle welzl(vector<pt> v) {
  mt19937 rng(1337); // change to chrono
  shuffle(all(v), rng);
  circle c(pt(0,0),0);
  for (int i = 0; i < sz(v); i++) {
    if (dist(c.c, v[i]) <= c.r + eps) continue;
    c = circle(v[i], 0);
    for (int j = 0; j < i; j++) {
      if (dist(c.c, v[j]) <= c.r + eps) continue;
      c = circle((v[i]+v[j])/2.0, dist(v[i],v[j])/2.0);
      for (int k = 0; k < j; k++) {
        if (dist(c.c, v[k]) <= c.r + eps) continue;
        c = circle(v[i], v[j], v[k]);
      }
    }
  }
  return c;
}

// --- COMPARATORS FOR SWEEP-LINE ALGORITHMS --- //

// Comparator for lines (assumes p < q)
bool operator<(const line& a, const line& b) {
  pt v1 = a.q - a.p, v2 = b.q - b.p;
  ld a1 = angle(v1), a2 = angle(v2);
  if (sgn(a1 - a2) != 0) return a1 < a2;
  return ccw(a.p, a.q, b.p);
}
bool operator==(const line& a, const line& b) {
  return !(a < b) && !(b < a);
}
// Sweep-line state comparator
// (horizontal sweep, vertical sort)
struct cmp_sweepline {
  bool operator()(const line& a,const line& b)const{
    if (a.p == b.p) return ccw(a.p, a.q, b.q);
    if (sgn(a.p.x - a.q.x) != 0 && 
       (sgn(b.p.x-b.q.x)==0 || sgn(a.p.x-b.p.x)<0))
      return ccw(a.p, a.q, b.p);
    return ccw(a.p, b.q, b.p);
  }
};
// Sweep-angle state comparator
// (radial sweep, distance sort)
struct cmp_sweepangle {
  pt dir; // Set this globally before comparing
  bool operator()(const line& a, const line& b) const {
    return sgn(get_t(dir, a) - get_t(dir, b)) < 0;
  }
};