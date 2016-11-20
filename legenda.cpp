#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	std::vector<string> linhas;
	ifstream legenda;
	legenda.open(argv[1]);
	int tempo_a_recuar = (argv[2][0] - '0');

	// Se o arquivo existir, então
	if (legenda.is_open()) // Se o arquivo existe, graças a Deus ele existe
	{
		// Guarda todas as linhas da legenda no vetor de strings
		while(!legenda.eof())
		{	
			string x;
			getline(legenda,x);
			linhas.push_back(x);
		}
		legenda.close();

		// Cria novo arquivo para a legenda atualizada
		ofstream legenda;
		legenda.open("legenda.srt", ios::trunc);

		// Estrutura de tempo
		struct time
		{
			int hora;
			int minuto;
			int segundo;
		};

		// Faz análise das linhas para impressão
		for (int i = 0; i < linhas.size(); ++i)
		{
			 //Imprime linhas de tempo
			if (linhas[i][0] == '0')
			{
				// Cria estrutura de tempo
				time temp;

				// Cria variáveis que passam valores de char para int
				char hora1 = linhas[i][0];
				char hora2 = linhas[i][1];
				char minuto1 = linhas[i][3];
				char minuto2 = linhas[i][4];
				char segundo1 = linhas[i][6];
				char segundo2 = linhas[i][7];

				// Coloca os valores na estrutura
				temp.hora = (hora1 - '0')*10 + (hora2 - '0');
				temp.minuto = (minuto1 - '0')*10 + (minuto2 - '0');
				temp.segundo = (segundo1 - '0')*10 + (segundo2 - '0');

				// Reduz o tempo requerido
				if ((temp.segundo - tempo_a_recuar) >= 0)
				{
					temp.segundo = temp.segundo - tempo_a_recuar;
				}
				else 
				{
					if (temp.minuto > 0)
					{
						temp.minuto = temp.minuto - 1;
						temp.segundo = 60 + (temp.segundo - tempo_a_recuar);
					}
					else
					{
						if (temp.hora > 0)
						{
							temp.hora = temp.hora - 1;
							temp.minuto = 60 - 1;
							temp.segundo = 60 + (temp.segundo - tempo_a_recuar);
						}
					}
				}

				// Coloca zeros se necessário
				if (temp.hora < 10)
				{
					legenda<< '0';
				}
				legenda << temp.hora << ':';

				if (temp.minuto < 10)
				{
					legenda << '0';
				}
				legenda << temp.minuto << ':';

				if (temp.segundo < 10)
				{
					legenda << '0';
				}
				legenda << temp.segundo;


				// Imprime caracteres até a segunda faixa de tempo
				for (int j = 8; j < (17); ++j)
				{
					legenda << linhas[i][j];
				}

				// Armazena os novos caracteres
				hora1 = linhas[i][17];
				hora2 = linhas[i][18];
				minuto1 = linhas[i][20];
				minuto2 = linhas[i][21];
				segundo1 = linhas[i][23];
				segundo2 = linhas[i][24];

				// Coloca os valores na estrutura
				temp.hora = (hora1 - '0')*10 + (hora2 - '0');
				temp.minuto = (minuto1 - '0')*10 + (minuto2 - '0');
				temp.segundo = (segundo1 - '0')*10 + (segundo2 - '0');

				// Reduz o tempo novamente
				if ((temp.segundo - tempo_a_recuar) >= 0)
				{
					temp.segundo = temp.segundo - tempo_a_recuar;
				}
				else 
				{
					if (temp.minuto > 0)
					{
						temp.minuto = temp.minuto - 1;
						temp.segundo = 60 + (temp.segundo - tempo_a_recuar);
					}
					else 
					{
						if (temp.hora > 0)
						{
							temp.hora = temp.hora - 1;
							temp.minuto = 60 - 1;
							temp.segundo = 60 + (temp.segundo - tempo_a_recuar);
						}
					}
				}

				// Adiciona os zeros necesários
				if (temp.hora < 10)
				{
					legenda << '0';
				}
				legenda << temp.hora << ':';

				if (temp.minuto < 10)
				{
					legenda << '0';
				}
				legenda << temp.minuto << ':';

				if (temp.segundo < 10)
				{
					legenda << '0';
				}
				legenda << temp.segundo;

				// Imprime o restante das linhas
				for (int j = 25; j < (29); ++j)
				{
					legenda << linhas[i][j];
				}
				legenda << endl;
			}
 			
 			//Imprime linhas comuns
			else 
			{
				legenda << linhas[i] << endl;
			}
		}
	} 
	else
	{
		std::cout << " Arquivo não encontrado :( " << std::endl;
	}

	return 0;
}