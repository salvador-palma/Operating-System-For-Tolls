#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

/******************************************************************************
 *  Macros para tratamento de mensagens de DEBUG
 ******************************************************************************/
#define TRUE  1
#define FALSE 0

/**
 *  Impressão de mensagens de DEBUG incluindo o módulo e a linha de código. Para ativar, alterar DEBUG_MODE para 1
 */
#define DEBUG_MODE TRUE   // Se estiver a TRUE, apresentará mensagens de DEBUG, caso contrário, não apresenta

/**
 *  Escreve uma mensagem de debug (parâmetros iguais ao printf) se DEBUG_MODE estiver a TRUE
 */
#define debug(fmt, ...) do { if (DEBUG_MODE) fprintf(stderr, "@@Debug@@:%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__); } while (0)

/******************************************************************************
 *  Macros para impressão de mensagens de sucesso e de erro
 ******************************************************************************/

/**
 *  Valida se uma operação teve sucesso ou não. Se não teve, escreve uma mensagem de erro e sai com erro -1, e mostrando a mensagem de erro,
 *  @param status   resultado da operação anterior. Se < 0 é porque houve erro, e nesse caso afixa a mensagem de erro e sai com status -1
 *  @param errorMsg mensagem de erro a apresentar em caso de erro
 */
#define exit_on_error(status, errorMsg) do { if (status < 0) { perror(errorMsg); exit(-1); } } while (0)

/**
 *  Valida se uma operação teve sucesso ou não. Se não teve, escreve uma mensagem de erro e sai com erro -1, e mostrando a mensagem de erro,
 *  @param status   resultado da operação anterior. Se == NULL é porque houve erro, e nesse caso afixa a mensagem de erro e sai com status -1
 *  @param errorMsg mensagem de erro a apresentar em caso de erro
 */
#define exit_on_null(status, errorMsg) do { if (NULL == status) { perror(errorMsg); exit(-1); } } while (0)

/******************************************************************************
 *  Macros para leitura de Strings de um ficheiro ou do STDIN
 ******************************************************************************/

/**
 *  Macro para leitura de Strings de um ficheiro
 *  Esta macro basicamente efetua a leitura de uma string de um ficheiro, definido um buffer_size. Semelhante a fgets(), mas removendo o '\n' e os caracteres extra.
 *  @param buffer        (char*) buffer onde vai ser depositada a informação
 *  @param buffer_size   (int) tamanho do buffer acima (em bytes)
 *  @param file          (FILE*) handler do ficheiro a ler
 */
#define my_fgets(buffer, buffer_size, file) ({          \
    char* _result = fgets(buffer, buffer_size, file);   \
    if (NULL != _result) {                              \
        if ('\n' == buffer[strlen(buffer) - 1])         \
            buffer[strlen(buffer) - 1] = '\0';          \
        else {                                          \
            int c;                                      \
            do                                          \
                c = getc(file);                         \
            while ('\n' != c && EOF != c);              \
        }                                               \
    }                                                   \
    _result;                                            \
})

/**
 *  Macro para leitura de Strings do STDIN
 *  Esta macro basicamente efetua a leitura de uma string do STDIN, definido um buffer_size. Semelhante a fgets(), mas removendo o '\n' e os caracteres extra.
 *  @param buffer        (char*) buffer onde vai ser depositada a informação
 *  @param buffer_size   (int) tamanho do buffer acima (em bytes)
 */
#define my_gets(buffer, buffer_size) my_fgets(buffer, buffer_size, stdin)

/******************************************************************************
 *  Macros utilitárias
 ******************************************************************************/

#define my_rand() ({         \
    struct timeval tv;       \
    gettimeofday(&tv, NULL); \
    srand(tv.tv_usec);       \
    rand();                  \
})

/******************************************************************************
 *  Macros para impressão de mensagens de sucesso e de erro
 ******************************************************************************/

/**
 *  Escreve uma mensagem de sucesso (parâmetros iguais ao printf), deve ser usado em todas as mensagens "positivas" que a aplicação mostra
 *  @param passo (o passo do enunciado) ... os argumentos são os mesmos que os do printf(), logo recebe uma string de formatação e depois um número variável de argumentos
 */
#define success(passo, fmt, ...) do { printf("@@Success@@ {" passo "} " fmt "\n", ## __VA_ARGS__); } while (0)

/**
 *  Escreve uma mensagem de erro (parâmetros iguais ao printf), deve ser usado em todas as mensagens "de erro" que a aplicação mostra.
 *  Estas mensagens de erro são as "de negócio", e não as de erros referentes a problemas técnicos como abertura de ficheiros, etc. (onde se deve usar perror)
 *  @param passo (o passo do enunciado) ... os argumentos são os mesmos que os do printf(), logo recebe uma string de formatação e depois um número variável de argumentos
 */
#define error(passo, fmt, ...) do { printf("@@Error@@ {" passo "} " fmt "\n", ## __VA_ARGS__); } while (0)

#endif
