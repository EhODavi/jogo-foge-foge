#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

bool acabou();

void move(char direcao);

bool ehdirecao(char direcao);

void fantasmas();

void explodepilula();

void explodepilula2(int x, int y, int somax, int somay, int qtd);

#endif