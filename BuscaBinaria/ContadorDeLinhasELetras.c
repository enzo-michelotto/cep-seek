#include <stdio.h>
#include <string.h>

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


int main(int argc, char**argv)
{
    FILE *f;
    int qt;
    int c;
    Endereco endereco[256] = {0, 0 , 0};
    int ocorrencias[256] = {0};
    if(argc != 2){
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "r");
    c = fgetc(f);

    while(c != EOF){
        if(c == '\n'){
            qt++;
        }
        c = fgetc(f);
        ocorrencias[c]++;
    }
    printf("numero de linhas: %d\n", qt);
    c = 65;
    while (c < 91)
    {
        printf("%c: %d\n", c, ocorrencias[c]);
        c++;
    }

c = 97;
       while (c < 123)
    {
        printf("%c: %d\n", c, ocorrencias[c]);
        c++;
    }
    
    
    fclose(f);
    return 0;

}