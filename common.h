/******************************************************************************
 ** ISCTE-IUL: Trabalho prático 2 de Sistemas Operativos
 **
 ** Aluno: Nº: XXXXXX  Nome: Este Módulo não precisa ser entregue
 ** Nome do Módulo: common.h
 ** Descrição/Explicação do Módulo: 
 **     Definição das estruturas de dados comuns aos módulos servidor e cidadao
 **     Os alunos não deverão alterar os nomes dos ficheiros definidos em FILE_*
 **
 ** OS ALUNOS NÃO DEVERÃO ACRESCENTAR NADA A ESTE FICHEIRO!
 **
 ******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>

/**
 *  KEY to be used on all Linux IPC get operations
 */
#define IPC_KEY 0x0a104991      // Suggestion: Replace with your student number

#define MIN_PROCESSAMENTO   1   // Tempo mínimo de processamento do Servidor
#define MAX_PROCESSAMENTO   7   // Tempo máximo de processamento do Servidor
#define NUM_PASSAGENS      20   // Tamanho máximo do buffer de Passagens

typedef struct {
    int tipo_passagem;          // Tipo de Passagem: 1-Normal, 2-Via Verde
    char matricula[9];          // Matrícula da viatura
    char lanco[50];             // Lanço da autoestrada
    int pid_cliente;            // PID do processo (Cliente) que pede passagem
    int pid_servidor_dedicado;  // PID do processo (Servidor) dedicado ao pedido
} Passagem;

typedef struct {
    int contadorNormal;         // Contador de Passagens correspondente ao Tipo de Passagem: 1-Normal
    int contadorViaVerde;       // Contador de Passagens correspondente ao Tipo de Passagem: 2-Via Verde
    int contadorAnomalias;      // Contador de Passagens detetadas com anomalias diversas
} Contadores;

typedef struct {                // Estrutura de dados a ser guardada em Memória Partilhada
    Contadores contadores;
    Passagem lista_passagens[NUM_PASSAGENS];
} DadosServidor;

typedef struct {
    long tipoMensagem;          // Tipo de Mensagem (ou Mailbox)
    struct {
        int action;             // Ação associada à mensagem
        union {                 // Nos dados, OU vai um pedido OU vão contadores
            Passagem pedido_cliente;        // Preenchida se action == 1
            Contadores contadores_servidor; // Preenchida se action == 3
        } dados;
    } conteudo;
} Mensagem;

#define FILE_STATS "estatisticas.dat"       // Ficheiro que armazena as estatísticas necessárias para o programa

/* OS ALUNOS NÃO DEVERÃO ACRESCENTAR NADA A ESTE FICHEIRO! */

#endif
