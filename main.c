#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

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

    setlocale(LC_ALL, "Portuguese");

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
                editar_veiculo(file);
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
    if(!(file = fopen("db_veiculos.txt", "a"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {
        fprintf(file, "%i;%s;%s;%s;%i;%.2f;%.2f\n", geraId(), car.model, car.brand, car.color, car.year, car.weight, car.price);
        printf("Cadastrado com sucesso\n");
    }

    fclose(file);

}
// funcao que mostra na tela todos os registros
void consulta_veiculo(FILE *file){

    char temp[255];
    int id;
    // Abrindo arquivo para leitura e exibi��o dos dados
    if(!(file = fopen("db_veiculos.txt", "r"))){
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


    int id, op, i = 0, count = 0, ret = 0, iaux, edited = 0;
    float faux;
    char temp[255], caux[MAX_LENGTH];
    car car[countLines(file)];

    // Abrindo arquivo para leitura e exibicao dos dados
    if(!(file = fopen("db_veiculos.txt", "r+"))){
        printf("ERRO: Nao foi possivel localizar o arquivo ou ele nao existe\n");
        exit(1);
    } else {

        printf("Arquivo foi aberto.\n");

        while(fgets(temp, 255, file) != NULL){

            car[i].id =  atoi(strtok(temp, ";"));
            strcpy(car[i].model, strtok(NULL, ";"));
            strcpy(car[i].brand, strtok(NULL, ";"));
            strcpy(car[i].color, strtok(NULL, ";"));
            car[i].year = atoi(strtok(NULL, ";"));
            car[i].weight = atof(strtok(NULL, ";"));
            car[i].price = atof(strtok(NULL, ";"));
            i++;
        }
        count = i;

        do{
            do{
                printf("Informe o ID do carro que deseja alterar: \n");
                scanf("%i", &id);
                id -= 1;
            }while(id > (countLines(file) - 1) || id < 0);


            print_car(car, id);

            printf("O que você deseja alterar?\n");
            printf("1-Modelo\n2-Marca\n3-Cor\n4-Ano\n5-Peso\n6-Preço\n\n");
            scanf("%i", &op);

            switch(op){

                case 1: // Altera a string do modelo
                    printf("Informe o novo modelo: ");
                    setbuf(stdin, NULL);
                    gets(caux);
                    toUpper(caux);
                    do{
                        printf("Cofirma a alteração?\nMODELO: %s -> %s\n1-SIM / 2-NÃo\n", car[id].model, caux);
                        scanf("%i", &op);
                        if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
                    }while(op != 1 && op != 2);

                    if(op == 1){
                       strcpy(car[id].model, caux);
                       edited = 1;
                    }
                    else printf("Sem alterações.\n");

                break;

                case 2: // Altera a string da marca
                    printf("Informe a nova marca: ");
                    setbuf(stdin, NULL);
                    gets(caux);
                    toUpper(caux);
                    do{
                        printf("Cofirma a alteração?\nMARCA: %s -> %s\n1-SIM / 2-NÃo\n", car[id].brand, caux);
                        scanf("%i", &op);
                        if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
                    }while(op != 1 && op != 2);

                    if(op == 1){
                        strcpy(car[id].brand, caux);
                        edited = 1;
                    }
                    else printf("Sem alterações.\n");

                break;

                case 3:
                    printf("Informe a nova cor: ");
                    setbuf(stdin, NULL);
                    gets(caux);
                    toUpper(caux);
                    do{
                        printf("Cofirma a alteração?\nCOR: %s -> %s\n1-SIM / 2-NÃo\n", car[id].color, caux);
                        scanf("%i", &op);
                        if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
                    }while(op != 1 && op != 2);

                    if(op == 1){
                        strcpy(car[id].color, caux);
                        edited = 1;
                    }
                    else printf("Sem alterações.\n");

                break;

                case 4:
                    printf("Informe o novo ano: ");
                    scanf("%i", &iaux);

                    do{
                        printf("Cofirma a alteração?\nANO: %i -> %i\n1-SIM / 2-NÃo\n", car[id].year, iaux);
                        scanf("%i", &op);
                        if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
                    }while(op != 1 && op != 2);

                    if(op == 1){
                        car[id].year = iaux;
                        edited = 1;
                    }
                    else printf("Sem alterações.\n");

                break;

                case 5:
                    printf("Informe o novo peso: ");
                    scanf("%f", &faux);

                    do{
                        printf("Cofirma a alteração?\nPESO: %f -> %f\n1-SIM / 2-NÃo\n", car[id].weight, faux);
                        scanf("%i", &op);
                        if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
                    }while(op != 1 && op != 2);

                    if(op == 1){
                        car[id].weight = faux;
                        edited = 1;
                    } else printf("Sem alterações.\n");

                break;

                case 6:
                    printf("Informe o novo preco: ");
                    scanf("%f", &faux);

                    do{
                        printf("Cofirma a alteração?\nPRECO: %f -> %f\n1-SIM / 2-NÃo\n", car[id].price, faux);
                        scanf("%i", &op);
                        if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
                    }while(op != 1 && op != 2);

                    if(op == 1){
                        car[id].price = faux;
                        edited = 1;
                    }
                    else printf("Sem alterações.\n");

                break;

                default:
                    printf("Opção inválida, tente novamente\n");
                break;
            }



            do{
                printf("Continuar com as alteraçoes?\n1-SIM / 2-NÃo\n");
                scanf("%i", &op);
                if(op != 1 & op != 2) printf("Opção inválida! Tente novamente.\n");
            }while(op != 1 && op != 2);

        }while(op != 2);

        fclose(file);

        print_car(car, id);

        if(edited == 1){

            ret = remove("db_veiculos.txt");

            if(ret == 0 && file == fopen("db_veiculos.txt", "w")){
                printf("arquivo antigo foi deletado.\nGerando novo arquivo com as alterações...\n");
                i = 0;
                do{
                    fprintf(file, "%i;%s;%s;%s;%i;%.2f;%.2f\n", car[i].id, car[i].model, car[i].brand, car[i].color, car[i].year, car[i].weight, car[i].price);
                    i++;
                }while(i < count);


                fclose(file);

            } else printf("Erro ao tentar excluir o arquivo.\n");

        }
    }

    printf("Voltando para o menu inicial...\n");

}
// funcao que deleta um registro
void excluir_veiculo(FILE *file){

    char temp[100];
    char excl[] = {'E', 'X', 'C'};
    int id, b;  // B de boolean
    fpos_t position;

    if(!(file = fopen("db_veiculos.txt", "r+"))){
        printf("ERRO: Nao foi possivel localizar o arquivo ou ele nao existe");
        exit(1);
    } else {

        printf("Digite a posicao: \n");
        scanf("%i", &id);

        while(fgets(temp, 100, file) != NULL){

            if(atoi(strtok(temp, ";")) == id - 1){

                fseek(file, 0, SEEK_CUR);
                //fprintf("%i;", 0);


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

    if(!(file = fopen("db_veiculos.txt", "r"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        id = 0;
        while(fgets(temp, 100, file) != NULL){
            id++;
        }

        fclose(file);
    }
    return id + 1;
}
int countLines(FILE *file){

    char temp[100];
    int id;

    if(!(file = fopen("db_veiculos.txt", "r"))){
        printf("ERRO: Nao foi possivel localizar o arquivo");
        exit(1);
    } else {

        id = 0;
        while(fgets(temp, 100, file) != NULL){
            id++;
        }
        fclose(file);
    }
    return id;
}
void consult_indiv(FILE *file){

    char temp[100];
    int id, b;  // B de boolean

    if(!(file = fopen("db_veiculos.txt", "r"))){
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
// printa na tela os dados de um carro a partir de um array
void print_car(car car[], int id){

    printf("\tID: %i\n", car[id].id);
    printf("\tMODELO: %s\n", car[id].model);
    printf("\tMARCA: %s\n", car[id].brand);
    printf("\tCOR: %s\n", car[id].color);
    printf("\tANO: %i\n", car[id].year);
    printf("\tPESO: %.2fkg\n", car[id].weight);
    printf("\tPRECO: R$%.2f\n", car[id].price);

}
