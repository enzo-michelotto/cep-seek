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

//	fseek(f,0,SEEK_END);
// 	fseek(f,0,SEEK_CUR);
//  fseek(f,0,SEEK_SET);

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	long tamanhoArquivo, posicao, primeiro, ultimo, meio;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	f = fopen("cep_ordenado.dat","r");
	fseek(f,0,SEEK_END);
	tamanhoArquivo = ftell(f);
	rewind(f); // fseek(f,0,SEEK_SET);
	printf("Tamanho do Arquivo: %ld\n", tamanhoArquivo);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", tamanhoArquivo/sizeof(Endereco));
	primeiro = 0;
	ultimo = (tamanhoArquivo/sizeof(Endereco))-1;
	meio = (primeiro+ultimo)/2;


while(primeiro <= ultimo)
{
	qt++;

	fseek(f, meio * sizeof(Endereco), SEEK_SET);	
	fread(&e,sizeof(Endereco),1,f);
    
	
	if (strncmp(argv[1],e.cep,8)==0)
	{
			printf("Achou:\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;

	} else if (strcmp(e.cep, argv[1])<0)
	{
		primeiro = meio + 1;
		meio = (primeiro+ultimo)/2;
	} else {
		ultimo = meio - 1;
		meio = (primeiro+ultimo)/2;
	}

}

if (strncmp(argv[1],e.cep,8)!=0)
{
	printf("Nao Encontrado\n");
}


printf("Quantidade de Iteracoes: %d\n",qt);

fclose(f);
	
	return 0;
}

