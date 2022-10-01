#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

typedef struct car{

    char model[MAX_LENGTH];
    char brand[MAX_LENGTH];
    char color[MAX_LENGTH];
    int year;
    float weight;
    float price;

}car;


// programa principal
void main(){

    int op;
    FILE *file;

    do{

        system("CLS");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("= 1-cadastrar   2-consultar   3-editar   4-excluir   5-sair =\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        scanf("%i", &op);

        switch(op){

            // Inseri um novo dado
            case 1:

                printf("Cadastrar: \n");
                cadast_veiculo(file);
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
void cadast_veiculo(FILE *file){

    car car;

    printf("Digite o modelo do veiculo: \n");
    setbuf(stdin, NULL);
    gets(car.model);
    printf("Digite a marca do veiculo: \n");
    setbuf(stdin, NULL);
    gets(car.brand);
    printf("Digite a cor do veiculo: \n");
    setbuf(stdin, NULL);
    gets(car.color);
    printf("Digite o ano do veículo");
    scanf("%i", &car.year);
    printf("Digite o peso do veículo");
    scanf("%f", &car.weight);
    printf("Digite o preco do veículo");
    scanf("%f", &car.price);

    if(!(file = fopen("db_veiculos", "a"))){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    } else {
        fprintf(file, "%s;%s;%s;%i;%.2f;%.2f", car.model, car.brand, car.color, car.year, car.weight, car.price);
        printf("Cadastrado com sucesso");
    }

    fclose(file);

}
// função que mostra na tela todos os registros
void consulta_veiculo(){

}
// função que edita um registro
void editar(){

}
// função que deleta um registro
