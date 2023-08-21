#include <stdio.h>
#include <time.h>

int main()
{

    time_t rawtime;
    struct tm timeinfo;
    time(&rawtime);
    localtime_r(&rawtime, &timeinfo);
    // % 02d / % 02d / % d\n ", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900
    // %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec

    printf("\n===========================================================\n\n");
    printf("SBSA SYSTEM      ----    SITEMA DE INFORMAÇÕES STAR BANK SA\n");
    printf("%02d/%02d/%d      ----   AUTOATENDIMENTO      --     %02d:%02d:%02d\n\n", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    printf("\t\tComprovente de Transferência\n\n");
    printf("CLIENTE: (DEB CLIENTE)\t\n");
    printf("AGÊNCIA: (AGENCIA DEB CLIENTE) - CONTA: (CONTA DEB CLIENTE)\t\n");
    printf("\n===========================================================\n\n");
    printf("SOBRE A TRANSAÇÃO\n");
    printf("\n-----------------------------------------------------------\n\n");
    printf("CPF DO PAGADOR:                            (CPF DO PAGADOR)\n");
    printf("VALOR:                                              (VALOR)\n");
    printf("DATA:                               %02d/%02d/%d  -  %02d:%02d:%02d\n", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    printf("\n-----------------------------------------------------------\n\n");
    printf("PAGO PARA:  (NOME PAGO)\n");
    printf("CPF:  (CPF PAGO)\n");
    printf("INSTITUIÇÃO:  (STAR BANK SA)\n");
    printf("AGÊNCIA: (AGENCIA CRED CLIENTE) CONTA: (CONTA CRED CLIENTE)\n");
    printf("TIPO DE CONTA:  (TIPO CONTA CRED)\n");
    printf("\n-----------------------------------------------------------\n\n");
    printf("Notificacação enviada em:           %02d/%02d/%d  -  %02d:%02d:%02d\n", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec + 10);
    printf("\n===========================================================\n\n");
    printf("OBRIGADO POR ESCOLHER STARBANK PARA CUIDAR DO SEU DINHEIRO!\n");
    printf("\n===========================================================\n\n\n");
}