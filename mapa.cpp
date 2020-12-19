#include <iostream>
#include <cstdlib>
#include "mapa.h"
#include <cstring>
#include <cmath>

using namespace std;

void lemapa(MAPA &m) {
    FILE *f;
    f = fopen("mapa.txt", "r");
    if (f == 0) {
        cout << "Erro na leitura do mapa";
        exit(1);
    }

    fscanf(f, "%d %d", &(m.linhas), &(m.colunas));
    alocamapa(m);

    for (int i = 0; i < m.linhas; i++) {
        fscanf(f, "%s", m.matriz[i]);
    }

    fclose(f);
}

void alocamapa(MAPA &m) {
    m.matriz = (char **) (malloc(sizeof(char *) * m.linhas));

    for (int i = 0; i < m.linhas; i++) {
        m.matriz[i] = (char *) (malloc(sizeof(char) * m.colunas + 1));
    }
}

void copiamapa(MAPA &destino, MAPA &origem) {
    destino.linhas = origem.linhas;
    destino.colunas = origem.colunas;
    alocamapa(destino);
    for (int i = 0; i < origem.linhas; i++) {
        strcpy(destino.matriz[i], origem.matriz[i]);
    }
}

void liberamapa(MAPA &m) {
    for (int i = 0; i < m.linhas; i++) {
        free(m.matriz[i]);
    }

    free(m.matriz);
}

bool encontramapa(MAPA &m, POSICAO &p, char c) {

    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            if (m.matriz[i][j] == c) {
                p.x = i;
                p.y = j;
                return true;
            }
        }
    }

    return false;
}

bool podeandar(MAPA &m, char personagem, int x, int y) {
    return
            ehvalida(m, x, y) &&
            !ehparede(m, x, y) &&
            !ehpersonagem(m, personagem, x, y);
}

bool ehvalida(MAPA &m, int x, int y) {
    if (x >= m.linhas)
        return false;
    if (y >= m.colunas)
        return false;

    return true;
}

bool ehpersonagem(MAPA &m, char personagem, int x, int y) {
    return
            m.matriz[x][y] == personagem;
}

bool ehparede(MAPA &m, int x, int y) {
    return m.matriz[x][y] == PAREDE_VERTICAL || m.matriz[x][y] == PAREDE_HORIZONTAL;
}

bool ehpilula(MAPA &m, int x, int y) {
    return m.matriz[x][y] == PILULA;
}

void andanomapa(MAPA &m, int xorigem, int yorigem, int xdestino, int ydestino) {

    char personagem = m.matriz[xorigem][yorigem];
    m.matriz[xdestino][ydestino] = personagem;
    m.matriz[xorigem][yorigem] = VAZIO;

}

double distanciamapa(int x, int y, int heroix, int heroiy) {
    return sqrt(pow(heroix - x, 2) + pow(heroiy - y, 2));
}