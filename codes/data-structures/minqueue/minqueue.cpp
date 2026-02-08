struct MinQueue{
  deque<ii> q;
  int added = 0;
  int removed = 0;

  // returns [value,index]
  ii getmin(){ return q.front(); }

  void push(int x){
	while (!q.empty() && q.back().first > x)
	  q.pop_back();
	q.push_back({x, added});
	added++;
  }

  void pop(){
	if (!q.empty() && q.front().second == removed) 
	  q.pop_front();
	removed++;
  }
};