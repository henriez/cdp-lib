// OBS: tem outras variantes mais rapidas no caderno da UDESC

// O(sqrt(n)) fatores repetidos
vi fatora(int n) {
    vi factors;
    for (int x = 2; x * x <= n; x++) {
        while (n % x == 0) {
            factors.push_back(x);
            n /= x;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

// O(sqrt(n))
// Calcula a quantidade de divisores de um numero n.
int qtdDivisores(int n) {
    int ans = 1;
    for (int i = 2; i * i <= n; i += 2) {
        int exp = 0;
        while (n % i == 0) {
            n /= i; exp++;
        }
        if (exp > 0) ans *= (exp + 1);
        if (i == 2) i--;
    }
    if (n > 1) ans *= 2;
    return ans;
}

// O(sqrt(n))
// Calcula a soma de todos os divisores de um numero n.
ll somaDivisores(int n) {
    ll ans = 1;
    for (int i = 2; i * i <= n; i += 2) {
        if (n % i == 0) {
            int exp = 0;
            while (n % i == 0) {
                n /= i; exp++;
            }
            
            ll aux = expbin(i, exp + 1);
            ans *= ((aux - 1) / (i - 1));
        }
        if (i == 2) i--;
    }
    
    if (n > 1) ans *= (n + 1);
    return ans;
}