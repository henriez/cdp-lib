vi _p, _rank;

int _find(int u) { return _p[u] == u ? u: _p[u] = _find(_p[u]); }
void _union(int u, int v){
	u = _find(u);
	v = _find(v);
	if(_rank[u] < _rank[v]){
		_p[u] = v;
	}
	else{
		_p[v] = u;
		if(_rank[u] == _rank[v]) _rank[u]++;
	}
}
void _make(int u){
	_rank = vi(u, 0);
	_p = vi(u);
	for(int i = 0; i < u; i++) _p[i] = i;
}