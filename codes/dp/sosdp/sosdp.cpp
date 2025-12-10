int k; // amount of bits
vi a(1<<k);
// sosdp
for (int bit = 0; bit < k; bit++){
    for (int mask = 0; mask < (1<<k); mask++){
        if ((1<<bit) & mask) {
            a[mask] += a[mask ^ (1<<bit)];
        }
    }
}

// do stuff (such as multiplication for OR convolution)

// sosdp inverse
for (int bit = 0; bit < k; bit++){
    for (int mask = 0; mask < (1<<k); mask++){
        if ((1<<bit) & mask) {
            a[mask] -= a[mask ^ (1<<bit)];
        }
    }
}