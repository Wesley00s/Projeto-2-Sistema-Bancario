#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 100
#define VERMELHO "\x1B[31m"
#define AMARELO "\x1B[33m"
#define AZUL "\x1B[34m"
#define VERDE "\x1B[32m"
#define PRETO "\x1B[30m"
#define RESET "\x1B[0m"

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int sair = 0;
    int totalTitulares = 0;
    int opcao = 0;
    int opcaoConta = 0;
    float valor = 0;
    int acao = 0;
    char pesquisa[15];

    char nome[TAM][TAM];
    char CPF[TAM][TAM];
    char endereco[TAM][TAM];
    char tel[TAM][TAM];

    char tipoConta[TAM][10];
    char numConta[TAM][TAM];
    char agencia[TAM][TAM];
    float saldo[TAM];

    do
    {
        int encontrada = 0;
        int index = 0;
        int indexRemove = -1;

        printf("1 - Criar Conta | 2 - Consultar Conta | 3 - Realizar Transação | 4 - Remover Conta | 5 - Ver Lista de Contas | 9 - Sair: ");
        scanf("%d", &acao);

        switch (acao)
        {
        case 1:
            printf(AMARELO "\nCRIAR CONTA\n\n" RESET);
            printf("Qual tipo de conta?\n");

            printf("1 - Corrente ou 2 - Poupança: ");
            scanf("%d", &opcaoConta);
            limparBuffer();

            switch (opcaoConta)
            {
            case 1:
                strcpy(tipoConta[totalTitulares], "Corrente");
                printf("\nDigite o nome: ");
                scanf("%30[^\n]s", nome[totalTitulares]);
                limparBuffer();

                printf("Digite o CPF: ");
                scanf("%15[^\n]s", CPF[totalTitulares]);
                limparBuffer();

                printf("Digite o endereço: ");
                scanf("%50[^\n]s", endereco[totalTitulares]);
                limparBuffer();

                printf("Digite o telefone: ");
                scanf("%15[^\n]s", tel[totalTitulares]);
                printf("\n");
                limparBuffer();

                printf("Número da conta: ");
                scanf("%10[^\n]", numConta[totalTitulares]);
                limparBuffer();

                printf("Digite a agência: ");
                scanf("%5[^\n]", agencia[totalTitulares]);
                limparBuffer();
                printf("\n");

                totalTitulares++;
                saldo[totalTitulares] = 0; // Adicionar essa linha para inicializar o saldo da nova conta com 0
            break;

            case 2:
                strcpy(tipoConta[totalTitulares], "Poupança");
                printf("\nDigite o nome: ");
                scanf("%30[^\n]s", nome[totalTitulares]);
                limparBuffer();

                printf("Digite o CPF: ");
                scanf("%15[^\n]s", CPF[totalTitulares]);
                limparBuffer();

                printf("Digite o endereço: ");
                scanf("%50[^\n]s", endereco[totalTitulares]);
                limparBuffer();

                printf("Digite o telefone: ");
                scanf("%15[^\n]s", tel[totalTitulares]);
                printf("\n");
                limparBuffer();

                printf("Número da conta: ");
                scanf("%10[^\n]", numConta[totalTitulares]);
                limparBuffer();

                printf("Digite a agência: ");
                scanf("%5[^\n]", agencia[totalTitulares]);
                limparBuffer();
                printf("\n");

                totalTitulares++;
                saldo[totalTitulares] = 0; // Adicionar essa linha para inicializar o saldo da nova conta com 0
            break;

            default:
                printf(VERMELHO "\n[ERROR] Opção inválida!\n\n" RESET);
            break;

            }
        break;

        case 2:
            printf(AMARELO "\nCONSULTAR CONTA\n" RESET);
            limparBuffer();
            printf("Digite o número da conta que deseja encontrar: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (int i = 0; i < totalTitulares; i++)
            {

                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    printf("Conta encontrada\n");
                    printf(AZUL "\nDADOS DO TITULAR:\n" RESET);
                    printf("Titular: %s\nCPF: %s\nEndereço: %s\nTelefone: %s\n\n\n", nome[i], CPF[i], endereco[i], tel[i]);

                    printf(AZUL "DADOS E SALDO BANCÁRIO:\n" RESET);
                    printf("Tipo de conta: %s\nNúmero da conta: %s\nAgência: %s\nSaldo atual: R$ %.2f\n\n", tipoConta[i], numConta[i], agencia[i], saldo[i]);

                    break;
                }

            }
            if(encontrada == 0){
                printf("Conta não encontrada\n");
            }
        break;

        case 3:
            limparBuffer();
            char numContaPesquisa[10];
            printf("REALIZAR TRANSAÇÃO:\n");
            printf("Número da conta: ");
            scanf("%15[^\n]", pesquisa);
            limparBuffer();

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    printf("Conta encontrada\n");
                    printf("1 - Depósito | 2 - Saque | 3 - Visualizar saldo: ");
                    scanf("%d", &opcao);

                    switch (opcao)
                    {
                    case 1:
                        printf("Valor: R$ ");
                        scanf("%f", &valor);

                        saldo[i] += valor;

                        printf("Valor creditado com sucesso.\nSaldo atualizado %s+ R$ %.2f%s: R$ %.2f\n\n", VERDE, valor, RESET, saldo[i]);

                        break;
                    case 2:
                        printf("Valor: R$ ");
                        scanf("%f", &valor);

                        if(saldo[i] > valor){

                            saldo[i] -= valor;

                            printf("Valor debitado com sucesso.\nSaldo atualizado %s+ R$ %.2f%s: R$%.2f\n\n", VERMELHO, valor, RESET, saldo[i]);
                        }else{
                            printf("Saldo insufuciente. Saldo atual: %.2f\n\n", saldo[i]);
                        }

                        break;
                    case 3:
                        printf("Saldo Atual: R$ %.2f\n", saldo[i]);

                        break;
                    default:
                        printf(VERMELHO "[ERROR] Opção inválida\n\n" RESET);
                        break;
                    }
                }
            }
            if(encontrada == 0){
                printf("Conta não encontrada\n\n");
            }
        break;

        case 4:

            limparBuffer();
            printf(AMARELO "\nREMOVER CONTA\n" RESET);
            printf("Digite o número da conta que deseja remover: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    indexRemove = i;

                    printf(AZUL "CONTA REMOVIDA: %s\nTitular: %s\nCPF: %s\nEndereço: %s\nTelefone: %s\n\n\n", RESET, nome[i], CPF[i], endereco[i], tel[i]);

                    for (int j = index; j < totalTitulares - 1; j++){

                        strcpy(nome[j], nome[j + 1]);
                        strcpy(CPF[j], CPF[j + 1]);
                        strcpy(endereco[j], endereco[j + 1]);
                        strcpy(tel[j], tel[j + 1]);
                        strcpy(tipoConta[j], tipoConta[j + 1]);
                        strcpy(numConta[j], numConta[j + 1]);
                        strcpy(agencia[j], agencia[j + 1]);
                        saldo[j] = saldo[j + 1];
                    }
                    totalTitulares--;

                    // Limpar os dados do titular removido
                    strcpy(nome[totalTitulares], "");
                    strcpy(CPF[totalTitulares], "");
                    strcpy(endereco[totalTitulares], "");
                    strcpy(tel[totalTitulares], "");
                    strcpy(tipoConta[totalTitulares], "");
                    strcpy(numConta[totalTitulares], "");
                    strcpy(agencia[totalTitulares], "");
                    saldo[totalTitulares] = 0;
                }
            }
            if (encontrada == 0) {
                printf("Conta não encontrada\n");
            }
        break;
        case 5:
            if(totalTitulares == 0) {
                printf("\nNenhuma conta listada ainda\n\n");
            }else{

                for(int i = 0; i < totalTitulares; i++){

                    printf(AZUL "\nDADOS DO TITULAR:\n" RESET);
                    printf("Titular: %s\nCPF: %s\nEndereço: %s\nTelefone: %s\n\n", nome[i], CPF[i], endereco[i], tel[i]);

                    printf(AZUL "DADOS E SALDO BANCÁRIO:\n" RESET);
                    printf("Tipo de conta: %s\nNúmero da conta: %s\nAgência: %s\nSaldo atual: R$ %.2f\n\n", tipoConta[i], numConta[i], agencia[i], saldo[i]);
                    printf("==================================================\n");
                }
            }
        }

    } while (totalTitulares < TAM && acao != 9);

    return 0;
}
