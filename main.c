#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



// programa principal
void main(){

    int op;
    FILE *arq;


    do{

        system("CLS");

        printf("1-cadastrar\n2-consultar\n3-editar\n4-excluir\n5-sair\n");
        scanf("%i", &op);

        switch(op){

            // Inseri um novo dado
            case 1:
                printf("Cadastrar: \n");
                cadast_veiculo(arq);
                system("PAUSE");
            break;

            // Consulta a lista de dados armazenados
            case 2:
                printf("Consultar: \n");
                system("PAUSE");
            break;

            // Editar algum dado
            case 3:
                printf("Editar: \n");
                system("PAUSE");
            break;

            // Excluir algum dado
            case 4:
                printf("Excluir: \n");
                system("PAUSE");
            break;

            // Sair do programa
            case 5:
                printf("Encerrando...\n");
                system("PAUSE");
            break;

            default:
                printf("Opção inválida!\n");
                system("PAUSE");
            break;

        }

    }while(op != 5);
}
// função que inclui um novo cadastro
void cadast_veiculo(FILE *arq){

    char modelo[70], cor[20], marca[50];
    int ano;
    float peso, preco;

    printf("Digite o modelo do veiculo: \n");
    setbuf(stdin, NULL);
    gets(modelo);
    printf("Digite a marca do veiculo: \n");
    setbuf(stdin, NULL);
    gets(marca);
    printf("Digite a cor do veiculo: \n");
    setbuf(stdin, NULL);
    gets(cor);
    printf("Digite o ano do veículo");
    scanf("%i", &ano);
    printf("Digite o peso do veículo");
    scanf("%f", &peso);
    printf("Digite o preco do veículo");
    scanf("%f", &preco);

    if(!(arq = fopen("db_veiculos", "a"))){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    } else {
        fprintf(arq, "%s;%s;%s;%i;%.2f;%.2f", modelo, marca, cor, ano, peso, preco);
        printf("Cadastrado com sucesso");
    }

    fclose(arq);

}
// função que mostra na tela todos os registros
void consulta_veiculo(){

}
// função que edita um registro
void editar(){

}
// função que deleta um registro
