#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 100 //QUANTIDADE DE CONTAS QUE PODEM SER ABERTAS

//DEFININDO CORES PARA DEIXAR A APARÊNCIA MAIS AGRADÁVEL
#define VERMELHO "\x1B[31m"
#define AMARELO "\x1B[33m"
#define AZUL "\x1B[34m"
#define VERDE "\x1B[32m"
#define RESET "\x1B[0m"

//FUNÇÃO PARA LIMPAR O BUFFER DE ENTRADA PARA EVITAR PROBLEMAS COM AS PROXIMAS LEITURAS
void limparBuffer()
{
    int c;  //ARMAZENA CARACTERES LIDOS DO BUFFER
    while ((c = getchar()) != '\n' && c != EOF); //LOOP PARA ENCONTRAR UMA QUEBRA DE LINHA
}

int main()  //FUNÇÃO PRINCIPAL
{
    int acao = 0; //CONTROLA AS OPÇÕES DO MENU
    int totalTitulares = 0; //CONTADOR DE TITULARES COM CONTAS ABERTAS
    int opcao = 0; //CONTROLA A OPÇÃO DE DEPÓSITO E SAQUE
    int opcaoConta = 0; //CONTROLA A OPÇÃO DA CONTA (CORRENTE OU POUPANÇA)
    int rendimentos[TAM] = {0}; //CONTADOR DE CONTAS QUE PODEM ATRIBUIR RENDIMENTO, NO CASO POUPANÇA
    float valor = 0; //ARMAZENA TEMPORÁRIAMENTE O VALOR DE DEPÓSITO E SAQUE
    char pesquisa[15]; //ARMAZENA O NÚMERO DA CONTA QUE DESEJA PESQUISAR

    //ONDE OS DADOS DOS TITULARES SÃO ARMAZENADOS
    char nome[TAM][TAM];
    char CPF[TAM][25];
    char endereco[TAM][TAM];
    char tel[TAM][TAM];

    //ONDE OS DADOS BANCÁRIOS DOS TITULARES SÃO ARMAZENADOS
    char tipoConta[TAM][10];
    char numConta[TAM][6];
    char agencia[TAM][10];
    float saldo[TAM];
    float percRendimento[TAM];
    float situacaoEmprestimo[TAM];

    do
    {
        rendimentos[totalTitulares] = 0; //INICIALIZA A OPÇÃO DE RENDIMENTOS PARA NOVA CONTA CRIADA
        char conferirConta[TAM][6]; //ARMAZENA O NÚMERO DA CONTA ADICIONADA PARA VERIFICAÇÃO SE JÁ NÃO EXISTE
        float valTransf = 0; //ARMAZENA O VALOR DA TRANSFERÊNCIA
        float aplyRendimentos = 0; //ARMAZENA O PERCENTUAL DE RENDIMENTOS A SEREM APLICADOS
        float qntEmprestimo = 0; //ARMAZENA O A QUANTIA DE QUE DESEJA MOVIMENTAR EM EMPRÉSTIMOS
        int encontrada = 0; //USADO PARA VERIFICAR SE A CONTA PROCUCARADA FOI ENCONTRADA
        int index = 0; //ARAMENA O INDICE DA CONTA QUE DESEJA REMOVER
        int contDebit = 0; //CONTADOR DO INDICE DA CONTA A SER DIBITADA
        int contCredit = 0; //CONTADOR DO INDICE DA CONTA A SER CRÉDITADA
        int opcaoEmprestimo = 0; //VERIFICA A OPÇÃO DO EMPRÉSTIMO (PEDIR OU PAGAR)
        int contaExistente = 0; //VERIFICA SE A CONTA CRIADA JÁ EXISTE

        //EXIBE MENU DE OPÇÕES
        printf(AMARELO "\n=========================== MENU DE OPÇÕES ===========================\n\n" RESET);
        printf(AZUL "--------------------------  ---------------------  --------------------\n" RESET);
        printf("| 1 | Criar Conta        |  | 4 | Remover Conta |  | 7 | Rendimentos  |\n");
        printf(AZUL "|---|--------------------|  |---|---------------|  |---|--------------|\n" RESET);
        printf("| 2 | Consultar Conta    |  | 5 | Ver Lista     |  | 8 | Empréstimo   |\n");
        printf(AZUL "|---|--------------------|  |---|---------------|  |---|--------------|\n" RESET);
        printf("| 3 | Realizar Transação |  | 6 | Tranferência  |  | 9 | Sair         |\n");
        printf(AZUL "--------------------------  ---------------------  --------------------\n" RESET);

        scanf("%d", &acao); //OPÇÃO

        switch (acao)
        {
        case 1: //OPÇÃO DE CRIAR CONTA
            printf(AMARELO "\n=========================== CRIAR CONTA ===========================\n\n" RESET);
            printf("Qual tipo de conta?\n");

            printf(AZUL "----------------  ----------------\n" RESET);
            printf("| 1 | Corrente |  | 2 | Poupança |\n");
            printf(AZUL "----------------  ----------------\n" RESET);

            scanf("%d", &opcaoConta);
            limparBuffer();

            switch (opcaoConta)
            {
            case 1: //OPÇÃO DE CONTA CORRENTE
                strcpy(tipoConta[totalTitulares], "Corrente");
                printf("\nDigite o nome: ");
                scanf("%50[^\n]s", nome[totalTitulares]);
                limparBuffer();

                printf("Digite o CPF: ");
                scanf("%20[^\n]s", CPF[totalTitulares]);
                limparBuffer();

                printf("Digite o endereço: ");
                scanf("%50[^\n]s", endereco[totalTitulares]);
                limparBuffer();

                printf("Digite o telefone: ");
                scanf("%15[^\n]s", tel[totalTitulares]);
                printf("\n");
                limparBuffer();

                printf("Número da conta: ");
                scanf("%5[^\n]", conferirConta[totalTitulares]);
                limparBuffer();

                //VERIFICAÇÃO DE CONTA EXISTENTE
                for(int i = 0; i < totalTitulares + 1; i++){
                    if(strcmp(numConta[i], conferirConta[totalTitulares]) == 0) //USANDO FUMÇÃO STRCMP PARA COMPARAR AS STRINGS
                    {
                        contaExistente = 1;
                    }
                }

                if(contaExistente)
                {
                    printf(VERMELHO "\n[ERROR] NÚMERO DE CONTA JÁ EXISTENTE!\n" RESET);
                    break;
                }
                else
                {
                    strcpy(numConta[totalTitulares], conferirConta[totalTitulares]); //USANDO A FUNÇÃO STRCPY PARA ATRBUIR O VALOR AO NÚMERO DA CONTA
                    printf("Digite a agência: ");
                    scanf("%2[^\n]", agencia[totalTitulares]);
                    limparBuffer();
                    printf("\n");

                    printf(VERDE "\nCONTA CRIADA COM SUCESSO!\n" RESET);
                }

                totalTitulares++;
                saldo[totalTitulares] = 0; //INICIALIZA O SALDO DA NOVA CONTA COM 0
                break;

            case 2:
                rendimentos[totalTitulares] = 1;
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
                scanf("%5[^\n]", conferirConta[totalTitulares]);
                limparBuffer();

                // VERIFICAÇÃO DE CONTA EXISTENTE
                for (int i = 0; i < totalTitulares + 1; i++)
                {
                    if (strcmp(numConta[i], conferirConta[totalTitulares]) == 0) //USANDO FUMÇÃO STRCMP PARA COMPARAR AS STRINGS
                    {
                        contaExistente = 1;
                    }
                }

                if (contaExistente)
                {
                    printf(VERMELHO "\n[ERROR] NÚMERO DE CONTA JÁ EXISTENTE!\n" RESET);
                    break;
                }
                else
                {
                    strcpy(numConta[totalTitulares], conferirConta[totalTitulares]); //USANDO A FUNÇÃO STRCPY PARA ATRBUIR O VALOR AO NÚMERO DA CONTA
                    printf("Digite a agência: ");
                    scanf("%2[^\n]", agencia[totalTitulares]);
                    limparBuffer();
                    printf("\n");

                    printf(VERDE "\nCONTA CRIADA COM SUCESSO!\n" RESET);
                }

                totalTitulares++;
                saldo[totalTitulares] = 0; //INICIALIZA O SALDO DA NOVA CONTA COM 0
                break;

            default:
                printf(VERMELHO "\n[ERROR] Opção inválida!\n\n" RESET);
                break;
            }
            break;

        case 2: // OPÇÃO DE COSULTAR CONTA
            printf(AMARELO "\n=========================== CONSULTAR CONTA ===========================\n\n" RESET);
            limparBuffer();
            printf("Digite o número da conta que deseja encontrar: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n" RESET);

                    if (rendimentos[i] == 1)
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, endereco[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tel[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, CPF[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, agencia[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| RENDIMENTO%s          %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, percRendimento[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }
                    else
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, endereco[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tel[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, CPF[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, agencia[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }
                    rendimentos[i] = 0;
                    break;
                }
            }
            if (encontrada == 0)
            {
                printf(VERMELHO "CONTA NÃO ENCONTRADA\n\n" RESET);
            }
            break;

        case 3:
            limparBuffer();
            printf(AMARELO "\n=========================== REALIZAR TRANSAÇÃO ===========================\n\n" RESET);
            printf("Número da conta: ");
            scanf("%15[^\n]", pesquisa);
            limparBuffer();

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n" RESET);

                    printf(AZUL "\t-----------------------------------------------------\n" RESET);
                    printf(AMARELO "\t| TITULAR%s %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| SALDO%s   %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                    printf(AZUL "\t-----------------------------------------------------\n\n" RESET);

                    printf(AZUL "----------------  -------------\n" RESET);
                    printf("| 1 | Depósito |  | 2 | Saque |\n");
                    printf(AZUL "----------------  -------------\n" RESET);
                    scanf("%d", &opcao);

                    switch (opcao)
                    {
                        case 1:
                            printf("\nValor a ser depositado: R$ ");
                            scanf("%f", &valor);

                            saldo[i] += valor;

                            printf(VERDE "\nVALOR CREDITADO COM SECESSO\n\n" RESET);
                            printf(AZUL "\t-----------------------------------------------------\n" RESET);
                            printf(AMARELO "\t| TITULAR%s          %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                            printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                            printf(AMARELO "\t| SALDO ATUALIZADO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                            printf(AZUL "\t-----------------------------------------------------\n\n" RESET);

                            break;

                        case 2:
                            printf("\nValor a ser sacado: R$ ");
                            scanf("%f", &valor);

                            if (saldo[i] > valor)
                            {

                                saldo[i] -= valor;

                                printf(VERDE "\nVALOR DEBITADO COM SECESSO\n\n" RESET);
                                printf(AZUL "\t-----------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| TITULAR%s          %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| SALDO ATUALIZADO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                                printf(AZUL "\t-----------------------------------------------------\n" RESET);
                            }
                            else
                            {
                                printf(VERMELHO "S\nALDO INSUFICIENTE: %.2f\n\n" RESET, saldo[i]);
                            }

                            break;

                        default:
                            printf(VERMELHO "\n[ERROR] Opção inválida\n\n" RESET);
                        break;
                    }
                }
            }
            if (encontrada == 0)
            {
                printf(VERMELHO "\nCONTA NÃO ENCONTRADA\n\n");
            }
            break;

        case 4:

            limparBuffer();
            printf(AMARELO "\n=========================== REMOVER CONTA ===========================\n" RESET);
            printf("Digite o número da conta que deseja remover: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    index = i;

                    printf(VERMELHO "CONTA REMOVIDA" RESET);
                    printf(AZUL "\n\t* DADOS\n" RESET);
                    printf(AZUL "\t-----------------------------------------------------\n" RESET);
                    printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| ENDEREÇO%s      %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, endereco[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| TELEFONE%s      %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tel[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| CPF%s           %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, CPF[i], RESET);
                    printf(AZUL "\t-----------------------------------------------------\n\n" RESET);

                    for (int j = index; j < totalTitulares - 1; j++)
                    {
                        strcpy(nome[j], nome[j + 1]);
                        strcpy(CPF[j], CPF[j + 1]);
                        strcpy(endereco[j], endereco[j + 1]);
                        strcpy(tel[j], tel[j + 1]);
                        strcpy(tipoConta[j], tipoConta[j + 1]);
                        strcpy(numConta[j], numConta[j + 1]);
                        strcpy(agencia[j], agencia[j + 1]);
                        situacaoEmprestimo[j] = situacaoEmprestimo[j + 1];
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
                    situacaoEmprestimo[totalTitulares] = 0;
                }
            }
            if (encontrada == 0)
            {
                printf(VERMELHO "CONTA NÃO ENCONTRADA\n\n" RESET);
            }
            break;
        case 5:
            printf(AMARELO "\n=========================== VER LISTA ===========================\n" RESET);

            if (totalTitulares == 0)
            {
                printf(VERMELHO "\nNENHUMA CONTA LISTADA\n\n" RESET);
            }
            else
            {
                for (int i = 0; i < totalTitulares; i++)
                {
                    if (rendimentos[i] == 1)
                    {
                        printf(AZUL "\n\t* DADOS DA %dª CONTA%s\n", i + 1, RESET);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, endereco[i], RESET); 
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tel[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, CPF[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, agencia[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| RENDIMENTO%s          %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, percRendimento[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }
                    else
                    {
                        printf(AZUL "\n\t* DADOS DA %dª CONTA%s\n", i + 1, RESET);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, endereco[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tel[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, CPF[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, agencia[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }
                }
            }
            break;

        case 6:
            printf(AMARELO "\n=========================== FAZER TRANSFERÊNCIA ===========================\n\n" RESET);

            limparBuffer();
            printf("Digite o número da conta que deseja debitar: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (contDebit = 0; contDebit < totalTitulares; contDebit++)
            {
                if (strcmp(numConta[contDebit], pesquisa) == 0)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n" RESET);
                    printf(AZUL "\n\t* DADOS\n" RESET);
                    printf(AZUL "\t-----------------------------------------------------\n" RESET);
                    printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[contDebit], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[contDebit], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| SALDO%s         %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[contDebit], RESET);
                    printf(AZUL "\t-----------------------------------------------------\n\n" RESET);

                    printf("Digite o valor a ser transferido: R$ ");
                    scanf("%f", &valTransf);

                    limparBuffer();
                    printf("Digite o número da conta para qual deseja transferir: ");
                    scanf("%15[^\n]", pesquisa);
                    printf("\n");

                    for (contCredit = 0; contCredit < totalTitulares; contCredit++)
                    {
                        if (strcmp(numConta[contCredit], pesquisa) == 0)
                        {
                            encontrada = 1;
                            printf(VERDE "CONTA ENCONTRADA\n" RESET);
                            printf(AZUL "\n\t* DADOS\n" RESET);
                            printf(AZUL "\t-----------------------------------------------------\n" RESET);
                            printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[contCredit], RESET);
                            printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                            printf(AMARELO "\t| CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[contCredit], RESET);
                            printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                            printf(AMARELO "\t| SALDO%s         %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[contCredit], RESET);
                            printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                            if (valTransf <= saldo[contDebit])
                            {
                                saldo[contDebit] -= valTransf;
                                saldo[contCredit] += valTransf;

                                printf(VERDE "\nTRANSFERÊNCIA DE R$ %.2f REALIZADA COM SUCESSO!\n\n" RESET, valTransf);
                                printf(AZUL "\n\t* DADOS CONTA CRÉDITADA\n" RESET);
                                printf(AZUL "\t-----------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| TITULAR%s           %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[contCredit], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| CONTA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[contCredit], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| SALDO ATUALIZADO%s  %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[contCredit], RESET);
                                printf(AZUL "\t-----------------------------------------------------\n\n" RESET);

                                printf(AZUL "\n\t* DADOS CONTA DEBITADA\n" RESET);
                                printf(AZUL "\t-----------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| TITULAR%s           %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[contDebit], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| CONTA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[contDebit], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| SALDO ATUALIZADO%s  %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[contDebit], RESET);
                                printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                            }
                            else
                            {
                                printf(VERMELHO "\nSALDO INSUFICIENTE!\n\n" RESET);
                            }
                            valTransf = 0;

                            break;
                        }
                        if (encontrada == 0)
                        {
                            printf(VERMELHO "CONTA NÃO ENCONTRADA\n\n" RESET);
                        }
                    }
                    break;
                }
            }
            if (encontrada == 0)
            {
                printf(VERMELHO "CONTA NÃO ENCONTRADA\n\n" RESET);
            }
            break;

        case 7:

            printf(AMARELO "\n=========================== RENDIMENTOS ===========================\n\n" RESET);

            limparBuffer();
            printf("Digite o número da conta que deseja aplicar rendimentos: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0 && rendimentos[i] == 1)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n" RESET);
                    printf(AZUL "\n\t* DADOS\n" RESET);
                    printf(AZUL "\t-----------------------------------------------------\n" RESET);
                    printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| TIPO DE CONTA%s %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                    printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                    printf(AMARELO "\t| RENDIMENTO%s    %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, percRendimento[i], RESET);
                    printf(AZUL "\t-----------------------------------------------------\n\n" RESET);

                    printf("Digite o percentual de rendimentos que seja aplicar: ");
                    scanf("%f", &aplyRendimentos);

                    if (aplyRendimentos <= 10)
                    {
                        percRendimento[i] = aplyRendimentos;

                        printf(VERDE "\nRENDIMENTO DE %.2f%% ATUALIZADO COM SUCESSO!\n\n" RESET, aplyRendimentos);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| RENDIMENTO ATUALIZADO%s %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, percRendimento[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }
                    else
                    {
                        printf(VERMELHO "\nNEGADO! TAXA LIMITE DE 10%% ATINGIDA\n" RESET);
                    }
                    aplyRendimentos = 0;

                    break;
                }
            }
            if (encontrada == 0)
            {
                printf(VERMELHO "CONTA NÃO ENCONTRADA, OU NÃO FAZ PARTE DA MODALIDADE:%s %sPOUPANÇA%s\n\n", RESET, AZUL, RESET);
            }

            break;

        case 8:

            printf(AMARELO "\n=========================== EMPRÉSTIMOS ===========================\n\n" RESET);

            limparBuffer();
            printf("Digite o número da conta que deseja para empréstimo: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n");

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(numConta[i], pesquisa) == 0)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n" RESET);

                    if (rendimentos[i] == 1)
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| RENDIMENTO%s          %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, percRendimento[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }
                    else
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        printf(AZUL "\t-----------------------------------------------------\n" RESET);
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SALDO%s               %s|%s %s%.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                        printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                        printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                    }

                    printf(AZUL "-------------  -------------\n" RESET);
                    printf("| 1 | Pedir |  | 2 | Pagar |\n");
                    printf(AZUL "-------------  -------------\n" RESET);
                    scanf("%d", &opcaoEmprestimo);

                    switch (opcaoEmprestimo)
                    {
                    case 1:

                        if (saldo[i] >= 1000 && situacaoEmprestimo[i] == 0)
                        {
                            printf(AZUL "\nPEDIR EMPRÉSTIMO\n\n" RESET);
                            printf(VERMELHO "ATENÇÃO: A TAXA DE JUROS É DE 15%% E EMPRÉSTIMO MÍNIMO DE R$ 5000.00!\n" RESET);
                            printf("Digite a quantia que deseja pedir emprestado: R$ ");
                            scanf("%f", &qntEmprestimo);
                            printf("\n");

                            if (qntEmprestimo >= 5000)
                            {
                                saldo[i] += qntEmprestimo;
                                situacaoEmprestimo[i] += qntEmprestimo + (qntEmprestimo * 0.15);

                                printf(VERDE "\nEMPRÉSTIMO DE R$ %.2f BEM SUCEDIDO%s\n\n", qntEmprestimo, RESET);
                                printf(AZUL "\t-----------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| SALDO ATUALIZADO%s    %s|%s %s%.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------|\n" RESET);
                                printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                                printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                                break;
                            }
                            else
                            {
                                printf(VERMELHO "RECUSADO! VALOR MINIMO DO EMPRÉSTIMO É R$ 5000.00\n" RESET);
                                break;
                            }
                        }
                        else
                        {
                            printf(VERMELHO "\nPEDIDO DE EMPRÉSTIMO NEGADO! VERIFIQUE SE NÃO TEM NENHUMA PENDÊNCIA COM O BANCO OU SE SEU SALDO È SUFICIENTE (MINÍMO R$ 1000)\n" RESET);
                            break;
                        }

                        break; // fim do case 1

                    case 2:

                        if (situacaoEmprestimo[i] > 0)
                        {
                            printf(AZUL "\nPAGAR EMPRÉSTIMO\n\n" RESET);

                            printf(VERMELHO "\nATENÇÃO: A TAXA DE JUROS DE 15%% APLICADA. TOTAL A PAGAR:%s %sR$ %.2f%s\n", RESET, AZUL, situacaoEmprestimo[i], RESET);
                            printf("Pagar: R$ ");
                            scanf("%f", &qntEmprestimo);

                            if (qntEmprestimo == situacaoEmprestimo[i])
                            {
                                situacaoEmprestimo[i] -= qntEmprestimo;
                                saldo[i] -= qntEmprestimo;

                                printf(VERDE "\nPAGAMENTO DE EMPRÉSTIMO DE%s %sR$ %.2f BEM SUCEDIDO%s\n", RESET, AZUL, qntEmprestimo, RESET);
                                printf(AZUL "\t-----------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, nome[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, tipoConta[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, numConta[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| SALDO ATUALIZADO%s    %s|%s %s%.2f%s\n", RESET, AZUL, RESET, VERDE, saldo[i], RESET);
                                printf(AZUL "\t|---------------------------------------------------\n" RESET);
                                printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, situacaoEmprestimo[i], RESET);
                                printf(AZUL "\t-----------------------------------------------------\n\n" RESET);
                            }
                            else
                            {
                                printf(VERMELHO "\nPAGAMENTO RECUSADO, VOCÊ SÓ PODE PAGAR O VALOR TOTAL!\n" RESET);
                            }

                            opcaoEmprestimo = 0;
                            qntEmprestimo = 0;
                            break;
                        }
                        else
                        {
                            printf(AZUL "\nVOCÊ NÃO TEM PEDÊNCIAS COM O BANCO\n" RESET);
                        }

                        break; // fim do case 2
                    } // fim do switch
                    break;
                }
            }
            if (encontrada == 0)
            {
                printf(VERMELHO "CONTA NÃO ENCONTRADA\n\n" RESET);
            }

            break;

        case 9:
            printf(VERMELHO "\nEncerrando...\n\n" RESET);
            break;

        default:
            printf(VERMELHO "\n[ERROR] OPÇÃO INVÁLIDA!\n\n" RESET);
            break;
        }

    } while (totalTitulares < TAM && acao != 9);

    return 0;
}