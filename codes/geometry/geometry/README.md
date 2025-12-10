# Basic elements - geometry lib

- Basic elements for using the geometry lib, contains points, vector operations and distances between points, distance between point and segment, distance between segments, segment intersection check, orientation check (ccw).
- Always use long double for floating point. Only use floating point if indispensable.
- For a == b, use |a - b| < eps.!!!!

Time:  $\mathcal{O}(1)$

## Polygon Area

- **Heron's Formula for triangle area**: $$A = \sqrt{s(s -a)(s-b)(s-c)}$$, where a, b, and c are the triangle sides and $s = (a + b+ c)/2$

TODO Shoelace

- **Pick's Theorem for polygon area with integer coordinates**: $$A = a + b/2 - 1$$, where a is the number of integer coordinates inside the polygon and b is the number of integer coordinates on the polygon boundary. b can be calculated for each edge as $$b = gcd(x_{i + 1} - x_i, y_{i + 1} - y_i) + 1$$.

Polygon Area
Time:  $\mathcal{O}(n)$

## Point in polygon
Sum of edge angles relative to the point must sum to 2pi
Time:  $\mathcal{O}(n\log n)$