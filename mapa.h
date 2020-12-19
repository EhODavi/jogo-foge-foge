#ifndef _MAPA_H_
#define _MAPA_H_


#define HEROI '@'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define FANTASMA 'F'
#define PILULA 'P'

struct mapa {
    char **matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA;

void alocamapa(MAPA &m);

void lemapa(MAPA &m);

void liberamapa(MAPA &m);

struct posicao {
    int x;
    int y;
};

typedef struct posicao POSICAO;

bool encontramapa(MAPA &m, POSICAO &p, char c);

bool ehvalida(MAPA &m, int x, int y);

bool ehparede(MAPA &m, int x, int y);

bool ehpersonagem(MAPA &m, char personagem, int x, int y);

void andanomapa(MAPA &m, int xorigem, int yorigem,
                int xdestino, int ydestino);

void copiamapa(MAPA &destino, MAPA &origem);

bool podeandar(MAPA &m, char personagem, int x, int y);

bool ehpilula(MAPA &m, int x, int y);

double distanciamapa(int x, int y, int heroix, int heroiy);

#endif