vi next_greater_elem(n, n);

stack<ii> st;
for (int i = 0; i < n; i++){
    while (!st.empty() && st.top().first < h[i]){
        next_greater_elem[st.top().second] = i;
        st.pop();
    }
    st.emplace(h[i], i);
}