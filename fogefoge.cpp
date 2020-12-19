#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

using namespace std;

MAPA m;
POSICAO heroi;
bool tempilula = false;
int turnos = 0;

bool acabou() {
    POSICAO pos;

    bool perdeu = !encontramapa(m, pos, HEROI);
    bool ganhou = !encontramapa(m, pos, FANTASMA);

    return ganhou || perdeu;

}

bool ehdirecao(char direcao) {
    return
            direcao == ESQUERDA ||
            direcao == CIMA ||
            direcao == BAIXO ||
            direcao == DIREITA;
}

void move(char direcao) {

    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch (direcao) {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case BAIXO:
            proximox++;
            break;
        case DIREITA:
            proximoy++;
            break;
    }

    if (!podeandar(m, HEROI, proximox, proximoy))
        return;

    if (turnos == 0 && m.matriz[proximox][proximoy] == FANTASMA) {
        m.matriz[heroi.x][heroi.y] = VAZIO;
        return;
    }

    if (ehpersonagem(m, PILULA, proximox, proximoy)) {
        tempilula = true;
        turnos = 21;
    }

    andanomapa(m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;

    if (turnos != 0) {
        turnos--;
    }
}

bool praondefantasmavai(int xatual, int yatual, int &xdestino, int &ydestino) {

    int opcoes[4][2] = {
            {xatual,     yatual + 1},
            {xatual + 1, yatual},
            {xatual,     yatual - 1},
            {xatual - 1, yatual}
    };

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if (podeandar(m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1]) &&
            !ehpilula(m, opcoes[posicao][0], opcoes[posicao][1]) &&
            distanciamapa(opcoes[posicao][0], opcoes[posicao][1], heroi.x, heroi.y) <
            distanciamapa(xatual, yatual, heroi.x, heroi.y)) {
            xdestino = opcoes[posicao][0];
            ydestino = opcoes[posicao][1];
            return true;
        }
    }

    return false;
}

void fantasmas() {
    MAPA copia;

    copiamapa(copia, m);

    for (int i = 0; i < copia.linhas; i++) {
        for (int j = 0; j < copia.colunas; j++) {
            if (copia.matriz[i][j] == FANTASMA) {

                int xdestino;
                int ydestino;

                bool encontrou = praondefantasmavai(i, j, xdestino, ydestino);

                if (encontrou) {
                    andanomapa(m, i, j, xdestino, ydestino);
                }
            }
        }
    }

    liberamapa(copia);
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {

    for (int i = 0; i < qtd; i++) {
        x += somax;
        y += somay;

        if (!ehvalida(m, x, y)) return;
        if (ehparede(m, x, y)) return;

        m.matriz[x][y] = VAZIO;
    }

}

void explodepilula() {
    if (!tempilula) return;

    explodepilula2(heroi.x, heroi.y, 0, 1, 3);
    explodepilula2(heroi.x, heroi.y, 0, -1, 3);
    explodepilula2(heroi.x, heroi.y, 1, 0, 3);
    explodepilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = false;
}

int main() {

    lemapa(m);
    encontramapa(m, heroi, HEROI);

    do {
        cout << "Pilula: " << (tempilula ? "SIM" : "NAO") << endl;
        cout << "Turnos: " << turnos << endl;;
        imprimemapa(m);

        char comando;
        cin >> comando;

        char novocomando = tolower(comando);

        if (ehdirecao(novocomando)) move(novocomando);
        if (novocomando == BOMBA) explodepilula();

        fantasmas();

    } while (!acabou());

    liberamapa(m);

    return 0;
}