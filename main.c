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

        printf("= Menu Inicial -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
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
                consult_menu(file);
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
                excluir_veiculo(file);
                system("PAUSE");
            break;

            // Sair do programa
            case 5:
                printf("Encerrando...\n");
            break;

            case 6: // opcao para testar funcoes
                exit(1);
            break;

            default:
                printf("Opcao invalida!\n");
                system("PAUSE");
            break;

        }

    }while(op != 5);

    exit(1);

} // FIM MAIN
// fun��o que inclui um novo cadastro
void cadast_veiculo(FILE *file){

    car car;

    // leitura dos dados via usuario
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

    // upper case nas strings
    toUpper(car.model);
    toUpper(car.brand);
    toUpper(car.color);

    // Abrindo arquivo para escrever os dados
    if(!(file = fopen("db_veiculos", "a+"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {
        fprintf(file, "%i;%s;%s;%s;%i;%.2f;%.2f\n", geraId(), car.model, car.brand, car.color, car.year, car.weight, car.price);
        printf("Cadastrado com sucesso\n");
    }

    fclose(file);

}
// fun��o que mostra na tela todos os registros
void consulta_veiculo(FILE *file){

    car car;
    char temp[255];
    int id;
    // Abrindo arquivo para leitura e exibi��o dos dados
    if(!(file = fopen("db_veiculos", "r"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        while(fgets(temp, 255, file) != NULL){
            printf("\tID: %i\n", atoi(strtok(temp, ";")));
            printf("\tMODELO: %s\n", strtok(NULL, ";"));
            printf("\tMARCA: %s\n", strtok(NULL, ";"));
            printf("\tCOR: %s\n", strtok(NULL, ";"));
            printf("\tANO: %s\n", strtok(NULL, ";"));
            printf("\tPESO: %s\n", strtok(NULL, ";"));
            printf("\tPRECO: %s\n", strtok(NULL, ";"));
        }

        fclose(file);
    }
}
// funcao que edita um registro
void editar_veiculo(FILE *file){

    int item;
    char temp[255];
    // Abrindo arquivo para leitura e exibicao dos dados
    if(!(file = fopen("db_veiculos", "r+"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        while(fgets(temp, 255, file) != NULL){
            printf("\tMODELO: %s\n", strtok(temp, ";"));
            printf("\tMARCA: %s\n", strtok(NULL, ";"));
            printf("\tCOR: %s\n", strtok(NULL, ";"));
            printf("\tANO: %s\n", strtok(NULL, ";"));
            printf("\tPESO: %s\n", strtok(NULL, ";"));
            printf("\tPRECO: %s\n", strtok(NULL, ";"));
        }

        printf("Informe o numero do item que deseja alterar: ");
        scanf("%i", &item);

        fclose(file);
    }
}
// funcao que deleta um registro
void excluir_veiculo(FILE *file){

    char temp[100];
    char excl[] = {'E', 'X', 'C'};
    int id, b;  // B de boolean
    fpos_t position;

    if(!(file = fopen("db_veiculos", "r+"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        printf("Digite a posicao: \n");
        scanf("%i", &id);

        while(fgets(temp, 100, file) != NULL){

            if(atoi(strtok(temp, ";")) == id - 1){

                fseek(file, 0, SEEK_CUR);
                fprintf("%i;", 0);


                b = 1;
            }
        }
        b == 1 ? printf("O registro foi removido!\n") : printf("Registro inexistente!\n");
        fclose(file);
    }
}
// Tranforma todos os caracteres de uma string em upper case
void toUpper(char *str){
    int i;
    for(i = 0; i < (strlen(str)); i++){

        if(isalpha(str[i])){
                str[i] = toupper(str[i]);
        }
    }
}
int geraId(FILE *file){

    char temp[100];
    int id;

    if(!(file = fopen("db_veiculos", "r"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        id = 0;
        while(fgets(temp, 100, file) != NULL){


            //printf("ID: %i\n", atoi(strtok(temp, ";")));

            /*do{

                printf("%s\n", strtok(NULL, ";"));

                i++;
            }while(i != 1);*/

            id++;
        }

        fclose(file);
    }
    //printf("%i\n", id + 1);
    return id + 1;

}
void consult_indiv(FILE *file){

    char temp[100];
    int id, b;  // B de boolean

    if(!(file = fopen("db_veiculos", "r"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        printf("Digite o numero do ID: \n");
        scanf("%i", &id);

        while(fgets(temp, 100, file) != NULL){

            if(atoi(strtok(temp, ";")) == id){
                printf("\tMODELO: %s\n", strtok(NULL, ";"));
                printf("\tMARCA: %s\n", strtok(NULL, ";"));
                printf("\tCOR: %s\n", strtok(NULL, ";"));
                printf("\tANO: %s\n", strtok(NULL, ";"));
                printf("\tPESO: %s\n", strtok(NULL, ";"));
                printf("\tPRECO: %s\n", strtok(NULL, ";"));
                b = 1;
            }
        }
        b == 1 ? printf("Registro encontrado!\n") : printf("Registro inexistente!\n");
        fclose(file);
    }
}
void consult_menu(FILE *file){

    int op;

    do{

        system("CLS");

        printf("= Consultar =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("= 1-Listar Todos   2-consultar por ID    3-Voltar =\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

        scanf("%i", &op);

        switch(op){

            case 1:
                consulta_veiculo(file);
                system("PAUSE");
            break;

            case 2:
                consult_indiv(file);
                system("PAUSE");
            break;

            case 3:
                printf("voltando para o Menu Inicial...\n");
            break;

            default:
                printf("Opacao invalida!\n");
            break;

        }
    }while(op != 3);
}
