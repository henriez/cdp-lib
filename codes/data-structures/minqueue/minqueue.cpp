template<typename T>
struct MinQueue{
  deque<pair<T,int>> q;
  int added = 0;
  int removed = 0;
  // returns [value,index]
  pair<T,int> getmin(){ return q.front(); }
  
  void push(T x){
    // < for MaxQueue
	  while (!q.empty() && q.back().first > x) q.pop_back();
	  q.push_back({x, added++});
  }
  void pop(){
	  if (!q.empty() && q.front().second == removed) q.pop_front();
	  removed++;
  }
  bool empty() { return added == removed; }
};
