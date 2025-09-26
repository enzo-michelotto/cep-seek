#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main()
{
    FILE *entrada, *saida;
    Endereco e;
    float probabilidade;
    

    entrada = fopen("cep.dat", "rb");
    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    
    
    saida = fopen("saida_b.dat", "wb");
    if (saida == NULL)
    {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    
    srand(time(NULL));

    
    while (fread(&e, sizeof(Endereco), 1, entrada))
    {
        
        probabilidade = (float) rand() / RAND_MAX;

        
        if (probabilidade < 0.8)
        {
            fwrite(&e, sizeof(Endereco), 1, saida);
        }
    }

    
    fclose(entrada);
    fclose(saida);

    return 0;
}
