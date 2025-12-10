// n escolhe k
// linha n, coluna k no triangulo (indexadas em 0)
int pascal(int n, int k){
    int num = fat[n];
    int den = (fat[k]*fat[n-k])%ZAP;
    return (num*expbin(den, ZAP-2))%ZAP;
}