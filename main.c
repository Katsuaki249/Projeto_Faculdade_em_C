#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

typedef struct car{

    int id;
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
                consulta_veiculo(file);
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
            break;

            default:
                printf("Opçco invalida!\n");
                system("PAUSE");
            break;

        }

    }while(op != 5);

    exit(1);

}
// função que inclui um novo cadastro
void cadast_veiculo(FILE *file){

    car car;

    printf("Digite o modelo do veiculo: ");
    setbuf(stdin, NULL);
    gets(car.model);
    printf("Digite a marca do veiculo: ");
    setbuf(stdin, NULL);
    gets(car.brand);
    printf("Digite a cor do veiculo: ");
    setbuf(stdin, NULL);
    gets(car.color);
    printf("Digite o ano do veiculo: ");
    scanf("%i", &car.year);
    printf("Digite o peso do veiculo: ");
    scanf("%f", &car.weight);
    printf("Digite o preco do veiculo: ");
    scanf("%f", &car.price);

    toUpper(car.model);
    toUpper(car.brand);
    toUpper(car.color);

    if(!(file = fopen("db_veiculos", "a"))){
        perror("ERROR");
        exit(1);
    } else {
        fprintf(file, "%s;%s;%s;%i;%.2f;%.2f", car.model, car.brand, car.color, car.year, car.weight, car.price);
        printf("Cadastrado com sucesso\n");
    }

    fclose(file);

}
// função que mostra na tela todos os registros
void consulta_veiculo(FILE *file){

    car car;
    char temp[255];

    if(!(file = fopen("db_veiculos", "r"))){
        perror("ERROR");
        exit(1);
    } else {
        printf("->\n");

        while(fgets(temp, 255, file) != NULL){
            printf("\tMODELO: %s\n", strtok(temp, ";"));
            printf("\tMARCA: %s\n", strtok(NULL, ";"));
            printf("\tCOR: %s\n", strtok(NULL, ";"));
            printf("\tANO: %s\n", strtok(NULL, ";"));
            printf("\tPESO: %s\n", strtok(NULL, ";"));
            printf("\tPRECO: %s\n", strtok(NULL, ";"));
        }

        fclose(file);
    }
}
// função que edita um registro
void editar_veiculo(){

}
// função que deleta um registro
void excluir_veiculo(){

}
void toUpper(char *str){
    int i;
    for(i = 0; i < (strlen(str)); i++){
        str[i] = toupper(str[i]);
    }
}
