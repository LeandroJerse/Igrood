#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// função para mostrar senha em pontinho
char changePassword(char password[], char secretPassword[])
{

    for (int i = 0; i < 21; i++)
    {
        if (password[i] != '\0')
        {
            secretPassword[i] = '*';

            // Por questão de aparecer 1 * a mais, fiz isso
            if (password[i] == '\n')
            {
                secretPassword[i] = '\n';
            }
        }
    }
}

//Função Para selecionar tipo de usuario
void TypeUserSelector(char *userSelector)
{
    char selector;
    printf("--------------------------------------------\n               Welcome to Igrood \n--------------------------------------------\n\n");
    printf("HOW ARE YOU?\n\n\n\t[1]Client\t[2]Company\n\n");
    scanf("%c",userSelector);
    getchar();
    
}

// struct de comida
typedef struct
{
    char food[21];
    float price;

} Food;

// Struct referente ao usuario
typedef struct
{
    char user[21];
    char password[21];
} Client;

// Struct referente ao resturante
typedef struct
{
    char name[26];
    char password[21];
    char secretPassword[21];
    char category[21];
    // este typo abaixo é suer importante, pois é o responsavel por alocar dinamicamente as comidas
    Food *foods;
    char adress[50];
    int sizeOfFood;
} Company;

int main()
{

    Client *client = NULL;
    Company *company = NULL;
    // sizeCompany é responsavel pela quantidade de restaurantes
    int sizeCompany = 0;
    char userSelector='n';
    char condiction = 'n';
    char confirmPassowrd[21];
    char nameCompanyConfirm[26];
    int numberAccount = -1;

    // while principal do programa
    do
    {
        // Responsavel por escolher o tipo de usuario
        TypeUserSelector(&userSelector);
        ///////////////////////////////////////////////

        //===============================================================================================
        // Aqui inicia-se à área voltada a(s) conta(s) do(s) restaurante(s)
        if (userSelector == '2')
        {
            char accountExistence;
            //"do" feito para criar conta até logar
            do
            {
                // Pergunta ao usuario restaurante se ele possui conta.
                printf("\nYou have account?\n\n\t[1]Yes\t[2]No\n");

                scanf("%c", &accountExistence);
                getchar();

                //////////////////////////////////////////////////////////////////////
                // se sim
                if (accountExistence == '1')
                {
                    // caso não existe dados na memoria
                    if (sizeCompany == 0)
                    {
                        printf("\tThere are not accounts in my memory\n\n");
                        break;
                    }
                    // caso tenha
                    else
                    {
                        // number acount serve para entrar no loop
                        numberAccount = -1;
                        // While para encontrar loggin
                        while (numberAccount == -1)
                        {
                            printf("Nickname: ");
                            fgets(nameCompanyConfirm, 26, stdin);

                            // verifica se o nome existe
                            for (int i = 0; i < sizeCompany; i++)
                            {
                                if (strcmp(nameCompanyConfirm, company[i].name) == 0)
                                {
                                    numberAccount = i;
                                    break;
                                }
                                else if (i == (sizeCompany - 1))
                                {
                                    printf("Account not found\n");
                                    // Caso queira encerrar o programa
                                    printf("[1]Continue\t[2]exit\n");

                                    int nickNameExit;
                                    scanf("%d", &nickNameExit);
                                    getchar();
                                    if (nickNameExit == 2)
                                    {
                                        return 0;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                        //"do" para encontrar senha
                        do
                        {
                            printf("Password: ");
                            fgets(confirmPassowrd, 21, stdin);
                            if (strcmp(confirmPassowrd, company[numberAccount].password) != 0)
                            {
                                printf("Incorrector password, try again\n");
                            }
                            else
                            {
                                changePassword(company[numberAccount].password, company[numberAccount].secretPassword);
                            }

                        } while (strcmp(confirmPassowrd, company[numberAccount].password) != 0);

                        // while para qundo você já esta logado como company
                        do
                        {
                            // Mostra as informações da empresa e permite modificalas
                            if (condiction == '1')
                            {
                                char condictionCompanyStatus = 'n';
                                while (condictionCompanyStatus != '5')
                                {
                                    printf("------------------------------------------------------------------------------\n\n\nName:     %s\n\nPassword: %s\n\nCategory: %s\n\nAdress:   %s\n\n------------------------------------------------------------------------------\n\n", company[numberAccount].name, company[numberAccount].secretPassword, company[numberAccount].category, company[numberAccount].adress);
                                    printf("\nChange:  [1]Name\t[2]Password\t[3]Adress\t[4]Category\t[5]Exit\n");
                                    scanf(" %c", &condictionCompanyStatus);
                                    getchar();

                                    // mudar nome
                                    if (condictionCompanyStatus == '1')
                                    {
                                        printf("New name:(Maximum 25 letters)\t");
                                        // digita o novo nome da compania
                                        char changeName[26];
                                        fgets(changeName, 26, stdin);

                                        for (int i = 0; i < sizeCompany; i++)
                                        {
                                            // se o nome não alterar
                                            if (strcmp(changeName, company[i].name) == 0 && (i == numberAccount))
                                            {

                                                break;
                                            }

                                            else if (strcmp(changeName, company[i].name) == 0)
                                            {
                                                printf("Nickname already exists, please, type other:  ");
                                                fgets(changeName, 26, stdin);
                                                i = -1;
                                            }
                                        }
                                        strcpy(company[numberAccount].name, changeName);
                                    }

                                    // Reescrever senha
                                    if (condictionCompanyStatus == '2')
                                    {
                                        do
                                        {

                                            printf("Write your new password: (Maximum 20 letters): ");
                                            fgets(company[numberAccount].password, 21, stdin);
                                            printf("confirm your password: (Maximum 20 letters): ");
                                            fgets(confirmPassowrd, 21, stdin);

                                            // caso não seja igual
                                            if (strcmp(company[numberAccount].password, confirmPassowrd) != 0)
                                            {
                                                printf("they're not the same\n");
                                            }

                                        } while (strcmp(company[numberAccount].password, confirmPassowrd) != 0);
                                        changePassword(company[numberAccount].password, company[numberAccount].secretPassword);
                                    }

                                    // escreva o endereço
                                    if (condictionCompanyStatus == '3')
                                    {
                                        printf("Wirte your address: ");
                                        fgets(company[numberAccount].adress, 50, stdin);
                                    }

                                    // Escreva a Categoria.
                                    if (condictionCompanyStatus == '4')
                                    {
                                        printf("Tipe your food category: ");
                                        fgets(company[numberAccount].category, 21, stdin);
                                    }
                                }
                            }
                            // ver comidas
                            if (condiction == '2')
                            {
                                getchar();
                                for (int i = 0; i < (company[numberAccount].sizeOfFood); i++)
                                {
                                    printf("\t[%d]  Name:%s\n     Price:$%.2f\n", i + 1, company[numberAccount].foods[i].food, company[numberAccount].foods[i].price);
                                }
                            }

                            // adicionando comida
                            if (condiction == '3')
                            {

                                // entrando em loop de adicionar comida
                                char condictionAddFood = 's';
                                while (condictionAddFood != 'n')
                                {
                                    getchar();
                                    // fazendo a alocação dinamica do ponteiro company para o ponteiro food que aponta o struct Foods
                                    company[numberAccount].sizeOfFood++;
                                    company[numberAccount].foods = (Food *)realloc(company[numberAccount].foods, company[numberAccount].sizeOfFood * sizeof(Food));
                                    printf("Set the food's name:\t");

                                    // Leia devagar, company na posição number em food na posição sizeofFood será escrita agora
                                    fgets(company[numberAccount].foods[(company[numberAccount].sizeOfFood) - 1].food, 21, stdin);

                                    printf("Set the food's price now:\t");
                                    // Recebe o valor
                                    scanf("%f", &company[numberAccount].foods[(company[numberAccount].sizeOfFood) - 1].price);

                                    printf("Add more food?(y/n):\t");

                                    scanf(" %c", &condictionAddFood);
                                    if (condictionAddFood == 'n')
                                    {
                                        getchar();
                                    }
                                }
                            }
                            printf("------------------------------------------------------------------------------\n\n\t\t\t\t%s\n------------------------------------------------------------------------------\n\n", company[numberAccount].name);
                            printf("\t[1]Show informations\t[2]Show foods\t[3]add food\t[4]Exit\n");
                            scanf("%c", &condiction);

                        } while (condiction != '4');
                    }
                }
                /////////////////////////////////////////////////////////////////////////////////////////////

                /////////////////////////////////////////////////////////////////////////////////////////////
                // Se não
                else if (accountExistence == '2')
                {
                    sizeCompany++;
                    printf("Write your company's name: (Maximum 25 letters)");
                    company = (Company *)realloc(company, sizeCompany * sizeof(Company));

                    if (company == NULL)
                    {
                        return 0;
                    }

                    // digita o nome da compania
                    fgets(company[sizeCompany - 1].name, 26, stdin);

                    for (int i = 0; i < sizeCompany - 1; i++)
                    {
                        // se o nome já existir, reescreva.
                        if (strcmp(company[sizeCompany - 1].name, company[i].name) == 0)
                        {
                            printf("Nickname already exists, please, tipe other:  ");
                            fgets(company[sizeCompany - 1].name, 26, stdin);
                            i = -1;
                        }
                    }
                    do
                    {
                        // escreva a senha
                        printf("Write your password: (Maximum 20 letters): ");
                        fgets(company[sizeCompany - 1].password, 21, stdin);

                        printf("confirm your password: (Maximum 20 letters): ");
                        fgets(confirmPassowrd, 21, stdin);

                        // caso não seja igual
                        if (strcmp(company[sizeCompany - 1].password, confirmPassowrd) != 0)
                        {
                            printf("they're not the same\n");
                        }

                    } while (strcmp(company[sizeCompany - 1].password, confirmPassowrd) != 0);

                    // Será utilizado para o ponteiro de struct em Food
                    company[sizeCompany - 1].sizeOfFood = 0;
                }
            } while (accountExistence == '2');
            /////////////////////////////////////////////////////////////////////////////////////////////
        }
        //===============================================================================================
        // Aqui termina a aŕe conta restaurantes

    } while (1);

    return 0;
}
