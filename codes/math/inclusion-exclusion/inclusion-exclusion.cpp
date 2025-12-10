// Exemplo: 
// Contar numeros de 1 a n divisveis por uma lista de primos.
int n;
vi primes;
int factors = primes.size();
int total_divisible = 0;

// Itera pelas bitmasks nao vazias de 'primes'
for (int i = 1; i < (1 << factors); i++) {
    int current_lcm = 1;
    int subset_size = 0;

    // calcula lcm do subconjunto
    for (int j = 0; j < factors; j++) {
        if (i & (1<<j)) {
            subset_size++;
            current_lcm = lcm(current_lcm, primes[j]);
            if (current_lcm > n) break;
        }
    }

    if (current_lcm > n) {
        continue;
    }

    int count = n / current_lcm;

    // Aplica o Principio da Inclusao-Exclusao:
    // Se o tamanho do subconjunto eh impar, adiciona.
    // Se o tamanho do subconjunto eh par, subtrai.
    if (subset_size & 1) {
        total_divisible += count;
    } else {
        total_divisible -= count;
    }
}
