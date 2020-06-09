
int media_pesada(int i) {
    static int h[5] = {0, 0, 0, 0, 0};
    int j, res;
    for (j = 4; j > 0; j--)
        h[j] = h[j - 1];
    h[0] = i;
    res = (5 * h[0] + 4 * h[1] + 3 * h[2] + 2 * h[3] + 1 * h[4]) / 15;
    return res;
}

int media_simples(int i) {
    static int h[5] = {0, 0, 0, 0, 0};
    int j, res;
    for (j = 4; j > 0; j--)
        h[j] = h[j - 1];
    h[0] = i;
    res = (h[0] + h[1] + h[2] + h[3] + h[4]) / 5;
    return res;
}
