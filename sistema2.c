#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 100 // QUANTIDADE DE CONTAS QUE PODEM SER ABERTAS

// DEFININDO CORES PARA DEIXAR A APARÊNCIA MAIS AGRADÁVEL
#define VERMELHO "\x1B[31m"
#define AMARELO "\x1B[33m"
#define AZUL "\x1B[34m"
#define VERDE "\x1B[32m"
#define RESET "\x1B[0m"

// FUNÇÃO PARA LIMPAR O BUFFER DE ENTRADA PARA EVITAR PROBLEMAS COM AS PROXIMAS LEITURAS
void limparBuffer()
{
    int c; // ARMAZENA CARACTERES LIDOS DO BUFFER
    while ((c = getchar()) != '\n' && c != EOF); // LOOP PARA ENCONTRAR UMA QUEBRA DE LINHA
}

// EXIBE AS LINHAS DOS MENUS
void linha()
{
    printf(AZUL "\t|-----------------------------------------------------|\n" RESET);
}

// ARMAZENA OS DADOS BANCÁRIOS
struct Contas
{
    char tipoConta[10];
    char numConta[6];
    char agencia[10];
    float saldo;
    float percRendimento;
    float situacaoEmprestimo;
};

// ARMAZENA OS DADOS DOS TITULARES E SEUS RESPECTIVOS DADOS BANCÁRIOS
struct Titulares
{
    char nome[55];
    char CPF[25];
    char endereco[55];
    char tel[16];
    struct Contas contas[TAM];
};

int main() // FUNÇÃO PRINCIPAL
{
    int acao = 0;               // CONTROLA AS OPÇÕES DO MENU
    int totalTitulares = 0;     // CONTADOR DE TITULARES COM CONTAS ABERTAS
    int opcao = 0;              // CONTROLA A OPÇÃO DE DEPÓSITO E SAQUE
    int opcaoConta = 0;         // CONTROLA A OPÇÃO DA CONTA (CORRENTE OU POUPANÇA)
    int rendimentos[TAM] = {0}; // CONTADOR DE CONTAS QUE PODEM ATRIBUIR RENDIMENTO, NO CASO POUPANÇA
    float valor = 0;            // ARMAZENA TEMPORÁRIAMENTE O VALOR DE DEPÓSITO E SAQUE
    char pesquisa[15];          // ARMAZENA O NÚMERO DA CONTA QUE DESEJA PESQUISAR

    // ONDE OS DADOS DOS TITULARES SÃO ARMAZENADOS
    struct Titulares titulares[TAM];

    // ONDE OS DADOS BANCÁRIOS DOS TITULARES SÃO ARMAZENADOS

    do
    {
        rendimentos[totalTitulares] = 0; // USADA PRA VERIFICAR SE A CONTA ENCONTRDAD É POUPANÇA
        char conferirConta[TAM][6];      // ARMAZENA O NÚMERO DA CONTA ADICIONADA PARA VERIFICAÇÃO SE JÁ NÃO EXISTE
        float valTransf = 0;             // ARMAZENA O VALOR DA TRANSFERÊNCIA
        float aplyRendimentos = 0;       // ARMAZENA O PERCENTUAL DE RENDIMENTOS A SEREM APLICADOS
        float qntEmprestimo = 0;         // ARMAZENA O A QUANTIA DE QUE DESEJA MOVIMENTAR EM EMPRÉSTIMOS
        int encontrada = 0;              // USADO PARA VERIFICAR SE A CONTA PROCUCARADA FOI ENCONTRADA
        int index = 0;                   // ARAMENA O INDICE DA CONTA QUE DESEJA REMOVER
        int contDebit = 0;               // CONTADOR DO INDICE DA CONTA A SER DIBITADA
        int contCredit = 0;              // CONTADOR DO INDICE DA CONTA A SER CRÉDITADA
        int opcaoEmprestimo = 0;         // VERIFICA A OPÇÃO DO EMPRÉSTIMO (PEDIR OU PAGAR)
        int contaExistente = 0;          // VERIFICA SE A CONTA CRIADA JÁ EXISTE

        // EXIBE MENU DE OPÇÕES
        printf(AMARELO "\n=========================== MENU DE OPÇÕES ===========================\n\n" RESET);
        printf(AZUL "--------------------------  ---------------------  --------------------\n" RESET);
        printf("| 1 | Criar Conta        |  | 4 | Remover Conta |  | 7 | Rendimentos  |\n");
        printf(AZUL "|---|--------------------|  |---|---------------|  |---|--------------|\n" RESET);
        printf("| 2 | Consultar Conta    |  | 5 | Ver Lista     |  | 8 | Empréstimo   |\n");
        printf(AZUL "|---|--------------------|  |---|---------------|  |---|--------------|\n" RESET);
        printf("| 3 | Realizar Transação |  | 6 | Tranferência  |  | 9 | Sair         |\n");
        printf(AZUL "--------------------------  ---------------------  --------------------\n" RESET);

        scanf("%d", &acao); // OPÇÃO

        switch (acao)
        {
        case 1: // OPÇÃO DE CRIAR CONTA
            printf(AMARELO "\n=========================== CRIAR CONTA ===========================\n\n" RESET);
            printf("Qual tipo de conta?\n");

            printf(AZUL "----------------  ----------------\n" RESET);
            printf("| 1 | Corrente |  | 2 | Poupança |\n");
            printf(AZUL "----------------  ----------------\n" RESET);

            scanf("%d", &opcaoConta);
            limparBuffer();

            switch (opcaoConta)
            {
            case 1: // OPÇÃO DE CONTA CORRENTE
                strcpy(titulares[totalTitulares].contas[totalTitulares].tipoConta, "Corrente");
                printf("\nDigite o nome: ");
                scanf("%50[^\n]s", titulares[totalTitulares].nome);
                limparBuffer();

                printf("Digite o CPF: ");
                scanf("%20[^\n]s", titulares[totalTitulares].CPF);
                limparBuffer();

                printf("Digite o endereço: ");
                scanf("%50[^\n]s", titulares[totalTitulares].endereco);
                limparBuffer();

                printf("Digite o telefone: ");
                scanf("%15[^\n]s", titulares[totalTitulares].tel);
                printf("\n");
                limparBuffer();

                printf("Número da conta: ");
                scanf("%5[^\n]", conferirConta[totalTitulares]);
                limparBuffer();

                // VERIFICAÇÃO DE CONTA EXISTENTE
                for (int i = 0; i < totalTitulares + 1; i++)
                {
                    if (strcmp(titulares[i].contas[i].numConta, conferirConta[totalTitulares]) == 0) // USANDO FUMÇÃO STRCMP PARA COMPARAR AS STRINGS
                    {
                        contaExistente = 1;
                    }
                }

                // SE A CONTA JÁ EXISTE RETORNA UM ERRO
                if (contaExistente)
                {
                    printf(VERMELHO "\n[ERROR] NÚMERO DE CONTA JÁ EXISTENTE!\n" RESET);
                    break;
                }
                else
                {
                    strcpy(titulares[totalTitulares].contas[totalTitulares].numConta, conferirConta[totalTitulares]); // USANDO A FUNÇÃO STRCPY PARA ATRBUIR O VALOR AO NÚMERO DA CONTA
                    printf("Digite a agência: ");
                    scanf("%2[^\n]", titulares[totalTitulares].contas[totalTitulares].agencia);
                    limparBuffer();
                    printf("\n");

                    printf(VERDE "\nCONTA CRIADA COM SUCESSO!\n" RESET);
                }

                totalTitulares++; // ATUALIZA O NÚMERO DE TITULARES
                titulares[totalTitulares].contas[totalTitulares].saldo = 0; // INICIALIZA O SALDO DA NOVA CONTA COM 0
                break;

            case 2: // OPÇÃO DE CONTA POUPANÇA
                rendimentos[totalTitulares] = 1;
                strcpy(titulares[totalTitulares].contas[totalTitulares].tipoConta, "Poupança");
                printf("\nDigite nome: ");
                scanf("%30[^\n]s", titulares[totalTitulares].nome);
                limparBuffer();

                printf("Digite o CPF: ");
                scanf("%15[^\n]s", titulares[totalTitulares].CPF);
                limparBuffer();

                printf("Digite o endereço: ");
                scanf("%50[^\n]s", titulares[totalTitulares].endereco);
                limparBuffer();

                printf("Digite o telefone: ");
                scanf("%15[^\n]s", titulares[totalTitulares].tel);
                printf("\n");
                limparBuffer();

                printf("Número da conta: ");
                scanf("%5[^\n]", conferirConta[totalTitulares]);
                limparBuffer();

                // VERIFICAÇÃO DE CONTA EXISTENTE
                for (int i = 0; i < totalTitulares + 1; i++)
                {
                    if (strcmp(titulares[i].contas[i].numConta, conferirConta[totalTitulares]) == 0) // USANDO FUMÇÃO STRCMP PARA COMPARAR AS STRINGS
                    {
                        contaExistente = 1;
                    }
                }

                // SE A CONTA JÁ EXISTE RETORNA UM ERRO
                if (contaExistente)
                {
                    printf(VERMELHO "\n[ERROR] NÚMERO DE CONTA JÁ EXISTENTE!\n" RESET);
                    break;
                }
                else
                {
                    strcpy(titulares[totalTitulares].contas[totalTitulares].numConta, conferirConta[totalTitulares]); // USANDO A FUNÇÃO STRCPY PARA ATRBUIR O VALOR AO NÚMERO DA CONTA
                    printf("Digite a agência: ");
                    scanf("%2[^\n]", titulares[totalTitulares].contas[totalTitulares].agencia);
                    limparBuffer();
                    printf("\n");

                    printf(VERDE "\nCONTA CRIADA COM SUCESSO!\n" RESET);
                }

                totalTitulares++; // ATUALIZA O NÚMERO DE TITULARES
                titulares[totalTitulares].contas[totalTitulares].saldo = 0; // INICIALIZA O SALDO DA NOVA CONTA COM 0
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
                if (strcmp(titulares[i].contas[i].numConta, pesquisa) == 0)
                {
                    encontrada = 1; // USADO PARA VERIFICAR SE A CONTA FOI ENCONTRADA
                    printf(VERDE "CONTA ENCONTRADA\n\n" RESET);

                    if (rendimentos[i] == 1) // SE RENDIMETOS FOR IGUAL A 1, ENCONTROU UMA CONTA CORRENTE
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        linha();
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].endereco, RESET);
                        linha();
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].tel, RESET);
                        linha();
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].CPF, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].agencia, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                        linha();
                        printf(AMARELO "\t| RENDIMENTO%s          %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].percRendimento, RESET);
                        linha();
                        printf("\n");
                    }
                    else
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        linha();
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].endereco, RESET);
                        linha();
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].tel, RESET);
                        linha();
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].CPF, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].agencia, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                        linha();
                        printf("\n");
                    }
                    rendimentos[i] = 0; // INICIALIZA REDIMENTOS PARA A PŔOXIMA BUSCA
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
                if (strcmp(titulares[i].contas[i].numConta, pesquisa) == 0) // VERIFICA SE A VARIÁVEL PESQUISA É IGUAL A ALGUMA CONTA EXISTENTE
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n\n" RESET);

                    linha();
                    printf(AMARELO "\t| TITULAR%s %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                    linha();
                    printf(AMARELO "\t| SALDO%s   %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                    linha();
                    printf("\n");

                    printf(AZUL "----------------  -------------\n" RESET);
                    printf("| 1 | Depósito |  | 2 | Saque |\n");
                    printf(AZUL "----------------  -------------\n" RESET);
                    scanf("%d", &opcao);

                    switch (opcao)
                    {
                    case 1:
                        printf("\nValor a ser depositado: R$ ");
                        scanf("%f", &valor);

                        titulares[i].contas[i].saldo += valor;

                        printf("\n");
                        printf(VERDE "\nVALOR CREDITADO COM SECESSO\n\n" RESET);
                        linha();
                        printf(AMARELO "\t| TITULAR%s          %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO ATUALIZADO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf("\n");

                        break;

                    case 2:
                        printf("\nValor a ser sacado: R$ ");
                        scanf("%f", &valor);

                        if (titulares[i].contas[i].saldo > valor)
                        {

                            titulares[i].contas[i].saldo -= valor;

                            printf(VERDE "\nVALOR DEBITADO COM SECESSO\n\n" RESET);
                            linha();
                            printf(AMARELO "\t| TITULAR%s          %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                            linha();
                            printf(AMARELO "\t| SALDO ATUALIZADO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                            linha();
                            printf("\n");
                        }
                        else
                        {
                            printf(VERMELHO "S\nALDO INSUFICIENTE: %.2f\n\n" RESET, titulares[i].contas[i].saldo);
                        }

                        break;

                    default:
                        printf(VERMELHO "\n[ERROR] Opção inválida\n\n" RESET);
                        break;
                    }
                }
            }
            if (encontrada == 0) // CASO NÃO ENCONTRE
            {
                printf(VERMELHO "\nCONTA NÃO ENCONTRADA\n\n");
            }
            break;

        case 4:

            limparBuffer();
            printf(AMARELO "\n=========================== REMOVER CONTA ===========================\n" RESET);
            printf("Digite o número da conta que deseja remover: ");
            scanf("%15[^\n]", pesquisa);
            printf("\n\n");

            for (int i = 0; i < totalTitulares; i++)
            {
                if (strcmp(titulares[i].contas[i].numConta, pesquisa) == 0)
                {
                    encontrada = 1;
                    index = i;

                    printf(VERMELHO "CONTA REMOVIDA" RESET);
                    printf(AZUL "\n\t* DADOS\n" RESET);
                    linha();
                    printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                    linha();
                    printf(AMARELO "\t| ENDEREÇO%s      %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].endereco, RESET);
                    linha();
                    printf(AMARELO "\t| TELEFONE%s      %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].tel, RESET);
                    linha();
                    printf(AMARELO "\t| CPF%s           %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].CPF, RESET);
                    linha();
                    printf("\n");

                    for (int j = index; j < totalTitulares - 1; j++)
                    {
                        strcpy(titulares[j].nome, titulares[j + 1].nome);
                        strcpy(titulares[j].CPF, titulares[j + 1].CPF);
                        strcpy(titulares[j].endereco, titulares[j + 1].endereco);
                        strcpy(titulares[j].tel, titulares[j + 1].tel);
                        strcpy(titulares[j].contas[j].tipoConta, titulares[j + 1].contas[j + 1].tipoConta);
                        strcpy(titulares[j].contas[j].numConta, titulares[j + 1].contas[j + 1].numConta);
                        strcpy(titulares[j].contas[j].agencia, titulares[j + 1].contas[j + 1].agencia);
                        titulares[j].contas[j].situacaoEmprestimo = titulares[j + 1].contas[j + 1].situacaoEmprestimo;
                        titulares[j].contas[j].saldo = titulares[j + 1].contas[j + 1].saldo;
                    }
                    totalTitulares--;

                    // Limpar os dados do titular removido
                    strcpy(titulares[totalTitulares].nome, "");
                    strcpy(titulares[totalTitulares].CPF, "");
                    strcpy(titulares[totalTitulares].endereco, "");
                    strcpy(titulares[totalTitulares].tel, "");
                    strcpy(titulares[totalTitulares].contas[totalTitulares].tipoConta, "");
                    strcpy(titulares[totalTitulares].contas[totalTitulares].numConta, "");
                    strcpy(titulares[totalTitulares].contas[totalTitulares].agencia, "");
                    titulares[totalTitulares].contas[totalTitulares].saldo = 0;
                    titulares[totalTitulares].contas[totalTitulares].situacaoEmprestimo = 0;
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
                        linha();
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].endereco, RESET);
                        linha();
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].tel, RESET);
                        linha();
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].CPF, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].agencia, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                        linha();
                        printf(AMARELO "\t| RENDIMENTO%s          %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].percRendimento, RESET);
                        linha();
                        printf("\n");
                    }
                    else
                    {
                        printf(AZUL "\n\t* DADOS DA %dª CONTA%s\n", i + 1, RESET);
                        linha();
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| ENDEREÇO%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].endereco, RESET);
                        linha();
                        printf(AMARELO "\t| TELEFONE%s            %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].tel, RESET);
                        linha();
                        printf(AMARELO "\t| CPF%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].CPF, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| AGÊNCIA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].agencia, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                        linha();
                        printf("\n");
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
                if (strcmp(titulares[contDebit].contas[contDebit].numConta, pesquisa) == 0)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n\n" RESET);
                    printf(AZUL "\n\t* DADOS\n" RESET);
                    linha();
                    printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contDebit].nome, RESET);
                    linha();
                    printf(AMARELO "\t| CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contDebit].contas[contDebit].numConta, RESET);
                    linha();
                    printf(AMARELO "\t| SALDO%s         %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[contDebit].contas[contDebit].saldo, RESET);
                    linha();

                    printf("Digite o valor a ser transferido: R$ ");
                    scanf("%f", &valTransf);

                    limparBuffer();
                    printf("Digite o número da conta para qual deseja transferir: ");
                    scanf("%15[^\n]", pesquisa);
                    printf("\n");

                    for (contCredit = 0; contCredit < totalTitulares; contCredit++)
                    {
                        if (strcmp(titulares[contCredit].contas[contCredit].numConta, pesquisa) == 0)
                        {
                            encontrada = 1;
                            printf(VERDE "CONTA ENCONTRADA\n\n" RESET);
                            printf(AZUL "\n\t* DADOS\n" RESET);
                            linha();
                            printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contCredit].nome, RESET);
                            linha();
                            printf(AMARELO "\t| CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contCredit].contas[contCredit].numConta, RESET);
                            linha();
                            printf(AMARELO "\t| SALDO%s         %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[contCredit].contas[contCredit].saldo, RESET);
                            linha();
                            printf("\n");

                            if (valTransf <= titulares[contDebit].contas[contDebit].saldo)
                            {
                                titulares[contDebit].contas[contDebit].saldo -= valTransf;
                                titulares[contCredit].contas[contCredit].saldo += valTransf;

                                printf(VERDE "\nTRANSFERÊNCIA DE R$ %.2f REALIZADA COM SUCESSO!\n\n" RESET, valTransf);
                                printf(AZUL "\n\t* DADOS CONTA CRÉDITADA\n" RESET);
                                linha();
                                printf(AMARELO "\t| TITULAR%s           %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contCredit].nome, RESET);
                                linha();
                                printf(AMARELO "\t| CONTA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contCredit].contas[contCredit].numConta, RESET);
                                linha();
                                printf(AMARELO "\t| SALDO ATUALIZADO%s  %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[contCredit].contas[contCredit].saldo, RESET);
                                linha();
                                printf("\n");

                                printf(AZUL "\n\t* DADOS CONTA DEBITADA\n" RESET);
                                linha();
                                printf(AMARELO "\t| TITULAR%s           %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contDebit].nome, RESET);
                                linha();
                                printf(AMARELO "\t| CONTA%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[contDebit].contas[contDebit].numConta, RESET);
                                linha();
                                printf(AMARELO "\t| SALDO ATUALIZADO%s  %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[contDebit].contas[contDebit].saldo, RESET);
                                linha();
                                printf("\n");
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
                if (strcmp(titulares[i].contas[i].numConta, pesquisa) == 0 && rendimentos[i] == 1)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n\n" RESET);
                    printf(AZUL "\n\t* DADOS\n" RESET);
                    linha();
                    printf(AMARELO "\t| TITULAR%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                    linha();
                    printf(AMARELO "\t| TIPO DE CONTA%s %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                    linha();
                    printf(AMARELO "\t| CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                    linha();
                    printf(AMARELO "\t| RENDIMENTO%s    %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].percRendimento, RESET);
                    linha();
                    printf("\n");

                    printf("Digite o percentual de rendimentos que seja aplicar: ");
                    scanf("%f", &aplyRendimentos);

                    if (aplyRendimentos <= 10)
                    {
                        titulares[i].contas[i].percRendimento = aplyRendimentos;

                        printf(VERDE "\nRENDIMENTO DE %.2f%% ATUALIZADO COM SUCESSO!\n\n" RESET, aplyRendimentos);
                        linha();
                        printf(AMARELO "\t| TITULAR%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s         %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s                 %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| RENDIMENTO ATUALIZADO%s %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].percRendimento, RESET);
                        linha();
                        printf("\n");
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
                if (strcmp(titulares[i].contas[i].numConta, pesquisa) == 0)
                {
                    encontrada = 1;
                    printf(VERDE "CONTA ENCONTRADA\n\n" RESET);

                    if (rendimentos[i] == 1)
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        linha();
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf(AMARELO "\t| RENDIMENTO%s          %s|%s %s%.2f%%%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].percRendimento, RESET);
                        linha();
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                        linha();
                        printf("\n");
                    }
                    else
                    {
                        printf(AZUL "\n\t* DADOS\n" RESET);
                        linha();
                        printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                        linha();
                        printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                        linha();
                        printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                        linha();
                        printf(AMARELO "\t| SALDO%s               %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                        linha();
                        printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                        linha();
                        printf("\n");
                    }

                    printf(AZUL "-------------  -------------\n" RESET);
                    printf("| 1 | Pedir |  | 2 | Pagar |\n");
                    printf(AZUL "-------------  -------------\n" RESET);
                    scanf("%d", &opcaoEmprestimo);

                    switch (opcaoEmprestimo)
                    {
                    case 1:

                        if (titulares[i].contas[i].saldo >= 1000 && titulares[i].contas[i].situacaoEmprestimo == 0)
                        {
                            printf(AZUL "\nPEDIR EMPRÉSTIMO\n\n" RESET);
                            printf(VERMELHO "ATENÇÃO: A TAXA DE JUROS É DE 15%% E EMPRÉSTIMO MÍNIMO DE R$ 5000.00!\n" RESET);
                            printf("Digite a quantia que deseja pedir emprestado: R$ ");
                            scanf("%f", &qntEmprestimo);
                            printf("\n");

                            if (qntEmprestimo >= 5000)
                            {
                                titulares[i].contas[i].saldo += qntEmprestimo;
                                titulares[i].contas[i].situacaoEmprestimo += qntEmprestimo + (qntEmprestimo * 0.15);

                                printf(VERDE "\nEMPRÉSTIMO DE R$ %.2f BEM SUCEDIDO%s\n\n", qntEmprestimo, RESET);
                                linha();
                                printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                                linha();
                                printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                                linha();
                                printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                                linha();
                                printf(AMARELO "\t| SALDO ATUALIZADO%s    %s|%s %s%.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                                linha();
                                printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                                linha();
                                printf("\n");

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

                        if (titulares[i].contas[i].situacaoEmprestimo > 0)
                        {
                            printf(AZUL "\nPAGAR EMPRÉSTIMO\n\n" RESET);

                            printf(VERMELHO "\nATENÇÃO: A TAXA DE JUROS DE 15%% APLICADA. TOTAL A PAGAR:%s %sR$ %.2f%s\n", RESET, AZUL, titulares[i].contas[i].situacaoEmprestimo, RESET);
                            printf("Pagar: R$ ");
                            scanf("%f", &qntEmprestimo);

                            if (qntEmprestimo == titulares[i].contas[i].situacaoEmprestimo)
                            {
                                titulares[i].contas[i].situacaoEmprestimo -= qntEmprestimo;
                                titulares[i].contas[i].saldo -= qntEmprestimo;

                                printf(VERDE "\nPAGAMENTO DE EMPRÉSTIMO DE%s %sR$ %.2f BEM SUCEDIDO%s\n", RESET, AZUL, qntEmprestimo, RESET);
                                linha();
                                printf(AMARELO "\t| TITULAR%s             %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].nome, RESET);
                                linha();
                                printf(AMARELO "\t| TIPO DE CONTA%s       %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].tipoConta, RESET);
                                linha();
                                printf(AMARELO "\t| CONTA%s               %s|%s %s%s%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].numConta, RESET);
                                linha();
                                printf(AMARELO "\t| SALDO ATUALIZADO%s    %s|%s %s%.2f%s\n", RESET, AZUL, RESET, VERDE, titulares[i].contas[i].saldo, RESET);
                                linha();
                                printf(AMARELO "\t| SITUAÇÃO EMPRÉSTIMO%s %s|%s %sR$ %.2f%s\n", RESET, AZUL, RESET, VERMELHO, titulares[i].contas[i].situacaoEmprestimo, RESET);
                                linha();
                                printf("\n");
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
                    }          // fim do switch
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

    } while (totalTitulares <= TAM && acao != 9);

    return 0;
}