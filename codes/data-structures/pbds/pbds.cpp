#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int,null_type,less<int>,rb_tree_tag,
    tree_order_statistics_node_update>;
// multiset: store {value, unique_id}
using ordered_multiset = tree<pair<ii,null_type,less<ii>,
    rb_tree_tag,tree_order_statistics_node_update>;

// set:
s.insert(x); s.erase(x);
s.order_of_key(x);    // # < x
*s.find_by_order(k);  // k-th smallest (0-indexed)

// multiset:
ms.order_of_key({x,0});     // # < x
ms.order_of_key({x,INF});   // # <= x
ms.find_by_order(k)->first; // k-th value

