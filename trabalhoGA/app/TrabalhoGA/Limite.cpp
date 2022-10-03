#include "Limite.h"

Limite demilitarLimite(int topo, int baixo, int esquerda, int direita)
{
	Limite box;
	box.topo = topo;
	box.baixo = baixo;
	box.esquerda = esquerda;
	box.direita = direita;
	
	return box;
}
