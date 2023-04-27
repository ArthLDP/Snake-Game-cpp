#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

bool gameover = false;
char dnovo;
int largura = 20;
int altura = 20;
int pontos = 0;

int raboX[100];
int raboY[100];
int registrorabo;

int comidinhaX = rand() % largura;
int comidinhaY = rand() % altura;

int posicaocobraX = largura / 2;
int posicaocobraY = altura / 2;

enum direcao {PARAR = 0, ESQUERDA, DIREITA, CIMA, BAIXO};
direcao dir;


void desenhar()
{
	system("cls");

	for (int i = 0; i < largura + 2; i++) // escrever 22 "#"
	{
		cout << "#";
	}
	cout << endl; // passar pra linha de baixo

	for (int i = 0; i < altura; i++)
	{
		for (int j = 0; j < largura; j++)
		{

			if (j == 0)
			{
				cout << "#";
			}

			if (i == posicaocobraY && j == posicaocobraX)
			{
				cout << "O";
			}

			else if (i == comidinhaY && j == comidinhaX)
			{
				cout << "$";
			}
			
			else
			{
				bool print = false;

				for (int k = 0; k < registrorabo; k++)
				{
					if (raboX[k] == j && raboY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (!print)
				{
					cout << " ";
				}
			}

			if (j == largura - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}


	for (int i = 0; i < largura + 2; i++) // escrever 22 "#"
	{
		cout << "#";
	}
	cout << endl;
	cout << "\nPontuacao: " << pontos << endl;
}

void controle()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (dir == DIREITA)
			{
				dir == DIREITA;
			}
			else
			{
				dir = ESQUERDA;
			}
				
				break;

		case 'd':

			if (dir == ESQUERDA)
			{
				dir == ESQUERDA;
			}
			else
			{
				dir = DIREITA;
			}
			break;

		case 'w':
			if (dir == BAIXO)
			{
				dir == BAIXO;
			}
			else
			{
				dir = CIMA;
			}
			break;

		case 's':
			if (dir == CIMA)
			{
				dir == CIMA;
			}
			else
			{
				dir = BAIXO;
			}
			break;

		case 'x':
			gameover = true;
			break;
		}
	}
}

void logica()
{
	// posição do rabo da cobrinha

	for (int i = registrorabo; i > 0; i--)
	{
		raboX[i] = raboX[i - 1];
		raboY[i] = raboY[i - 1];
	}

	raboX[0] = posicaocobraX;
	raboY[0] = posicaocobraY;

	// atualizar posição da cobrinha

	switch (dir)
	{
	case ESQUERDA:
		posicaocobraX--;
		break;

	case DIREITA:
		posicaocobraX++;
		break;

	case CIMA:
		posicaocobraY--;
		break;

	case BAIXO:
		posicaocobraY++;
		break;
	}

	// fazer a cobrinha teleportar quando passa pela parede

	if (posicaocobraX < 0)
	{
		posicaocobraX = largura - 1;
	}
	else if (posicaocobraX >= largura)
	{
		posicaocobraX = 0;
	}

	if (posicaocobraY < 0)
	{
		posicaocobraY = altura - 1;
	}
	else if (posicaocobraY >= altura)
	{
		posicaocobraY = 0;
	}

	// o que acontece se a cobrinha comer a comida

	if (posicaocobraY == comidinhaY && posicaocobraX == comidinhaX)
	{
		pontos += 10;
		comidinhaX = rand() % largura;
		comidinhaY = rand() % altura;
		registrorabo++;
	}

	// se a cobrinha encostar no rabo ele morre

	for (int i = 0; i < registrorabo; i++)
	{
		if (posicaocobraX == raboX[i] && posicaocobraY == raboY[i])
		{
			cout << "\nVOCE MORREU :( " << endl;
			cout << "Deseja jogar novamente? s/n: ";
			cin >> dnovo;

			if (dnovo == 's' || dnovo == 'S')
			{
				pontos = 0;
				registrorabo = 0;
				posicaocobraX = largura / 2;
				posicaocobraY = altura / 2;
				desenhar();
				controle();
				logica();
			}
			else
			{
				gameover = true;
			}

		}
	}

	//não deixar comida nascer no rabo da cobra

	for (int i = 0; i < registrorabo; i++)
	{
		if (comidinhaX == raboX[i] && comidinhaY == raboY[i])
		{
			comidinhaX = rand() % largura;
			comidinhaY = rand() % altura;
		}
	}
}

int main()
{
	while (!gameover)
	{
		desenhar();
		controle();
		logica();
		Sleep(10);
	}
	return 0;
}