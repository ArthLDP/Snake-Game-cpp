#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

bool print;
bool gameover = false;
char dnovo;
int largura = 20;
int altura = 20;
int pontos = 0;

int raboX[100];
int raboY[100];
int registrorabo = 0; // contador de comida para desenhar o rabo da cobra

int comidinhaX = rand() % largura;
int comidinhaY = rand() % altura;

int posicaocobraX = largura / 2;
int posicaocobraY = altura / 2;

enum direcao {ESQUERDA, DIREITA, CIMA, BAIXO}; // tipo de dado criado com o nome direcao que pode possuir restritamente esses valores
direcao dir; // variável dir do tipo direcao


void desenhar()
{
	system("cls");

	for (int i = 0; i < largura + 2; i++) // escrever "#" 22 vezes
	{
		cout << "#";
	}
	cout << endl; // passar pra linha de baixo

	for (int i = 0; i < altura; i++) // i para desenhar elementos na vertical (linhas)
	{
		for (int j = 0; j < largura; j++) // j para desenhar elementos na horizontal (colunas)
		{

			if (j == 0) // desenhar # na horizontal 0, ou seja, no início de cada linha
			{
				cout << "#";
			}

			if (i == posicaocobraY && j == posicaocobraX) // desenhar a cobra "O" na posição X e Y que ela nascer
			{
				cout << "O";
			}

			else if (i == comidinhaY && j == comidinhaX) // desenhar a comida "$" na posição X e Y que ela nascer
			{
				cout << "$";
			}
			
			else
			{
				print = false; // booleano para escrever os espaços " " em lugares no mapa fora das condições acima

				for (int k = 0; k < registrorabo; k++) // desenhar o rabo da cobrinha
				{
					if (raboX[k] == j && raboY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (print == false)
				{
					cout << " "; // desenhar os espaços " " na área vazia que o loop estiver passando
				}
			}

			if (j == largura - 1) // fechar o mapa na posição horizontal 19
			{
				cout << "#";
			}
		}
		cout << endl;
	}


	for (int i = 0; i < largura + 2; i++) // escrever # 22 vezes para completar a ultima linha do mapa
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
		switch (_getch()) // condição para checar caracteres que foram pressionados
		{
		case 'a':
			if (dir == DIREITA) // checar se a posicao que tem que ir é a inversa para ele não entrar nele mesmo
			{
				dir = DIREITA; // continuar andando pra mesma direção se o usuário tentar ir para a pos inversa
			}
			else
			{
				dir = ESQUERDA; // se apertar 'a', ir para direção esquerda se ele não tiver indo pra direita
			}
				
				break;

		case 'd':

			if (dir == ESQUERDA)
			{
				dir = ESQUERDA;
			}
			else
			{
				dir = DIREITA;
			}
			break;

		case 'w':
			if (dir == BAIXO)
			{
				dir = BAIXO;
			}
			else
			{
				dir = CIMA;
			}
			break;

		case 's':
			if (dir == CIMA)
			{
				dir = CIMA;
			}
			else
			{
				dir = BAIXO;
			}
			break;

		case 'x': // encerrar o jogo
			gameover = true;
			break;
		}
	}
}

void logica()
{
	for (int i = registrorabo; i > 0; i--) // posição do rabo da cobrinha
	{
		raboX[i] = raboX[i - 1];
		raboY[i] = raboY[i - 1];
	}

	raboX[0] = posicaocobraX; // a pos X e Y da primeira posição do array do rabo sempre vai ser a pos da cobra para que o rabo siga a cobra
	raboY[0] = posicaocobraY;

	switch (dir) // switch para fazer a posicao da cobra atualizar para a direção que ela estiver indo
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

	//não deixar comida nascer no rabo da cobra

	for (int i = 0; i < registrorabo; i++) // for para checar todas as posições do rabo da cobra
	{
		if (comidinhaX == raboX[i] && comidinhaY == raboY[i])
		{
			comidinhaX = rand() % largura;
			comidinhaY = rand() % altura;
		}
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
				comidinhaX = rand() % largura;
				comidinhaY = rand() % altura;
			}
			else
			{
				gameover = true;
			}

		}
	}
}

int main()
{
	while (gameover == false)
	{
		desenhar();
		controle();
		logica();
		Sleep(10);
	}
	return 0;
}