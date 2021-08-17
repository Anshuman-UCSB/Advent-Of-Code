template <class T>
void DisjointSet<T>::makeSet(const vector<T>& universe){
	for(auto& v: universe){
		parent[v] = v;
		rank[v] = 0;
	}
}

template <class T>
T DisjointSet<T>::Find(const T& k){
	if(parent[k] != k){
		parent[k] = Find(parent[k]);
	}
	return parent[k];
}

template <class T>
void DisjointSet<T>::Union(const T& a, const T& b){
	T x = Find(a);
	T y = Find(b);
	if(x==y) return;
	if(rank[x] > rank[y]){
		parent[y] = x;
	}else if(rank[x]<rank[y]){
		parent[x] = y;
	}else{
		parent[x] = y;
		rank[y]++;
	}
}