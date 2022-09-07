/*
 ============================================================================
  - Fazer um programa de simulação e coletar dados para plotar um gráfico retardo
  médio x utilização.
  - A utilização é a razão entre a taxa de chegada e a taxa de serviço do servidor.
  - Assuma que o intervalo entre chegada de pacotes é exponencialmente distribuído,
 bem como o tamanho dos pacotes.
  - Entregar relatório com gráfico, código fonte e explicação como derivou
  intervalo de confiança e qual foi o critério adotado para eliminar o transiente
  da simulação.
 ============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <x86intrin.h>
#include <cpuid.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

float packageMedium (int sample);
void logfileFloat(float entrance);
void logfileStr();
void logpackageInterval(float entrance);
float intervalArrive();

int main(void) {

	double interval_maior = 0, interval_minor = 0;
	float TA = 0.35, Media = 0, IC = 0, lambda = 0, utilization = 0, mu = 0, retardo_medio = 0, variance = 0;

	Media = packageMedium(100);						//media dos pacotes
	IC = intervalArrive();							//intervalo medio de pacotes
	lambda = 1/IC; 									//taxa média de chegada
	mu = 1/TA; 										//Taxa media de recebimento dos pacotes
	utilization = lambda/mu; 						//utilizacao
	variance = 1/pow(lambda,2);						//variancia
	logfileStr(); 									//divisão das amostras no log

	retardo_medio = 1/(mu-lambda); 					//retardo medio - lei de little
	if (retardo_medio < 0) retardo_medio = 0;		//condição de retardo

	interval_maior = Media + (1.96*(variance/sqrt(100)));logfileFloat(interval_maior); //ic (+95%)
	interval_minor = Media - (1.96*(variance/sqrt(100)));logfileFloat(interval_minor); //ic (-95%)

	printf("Int Chegada             = %f\n", IC);
	printf("Temp Atendimento        = %f\n", TA);
	printf("Media                   = %f\n", Media);
	printf("Utilizacao          	= %f\n", utilization);
	printf("Retardo Médio	        = %f\n", retardo_medio); //segundos
	printf("O IntConf(+95%)	        = %f\n", interval_maior);
	printf("O IntConf(-95%)	        = %f\n", interval_minor);
	return(0);
}

float packageMedium (int sample) { 		//media dos pacotes
	float x;
	float soma;
	srand(_rdtsc());
	for (int i=0; i<sample; i++){
		x = rand() % 100;
		logpackageInterval(x);
		soma = soma + x; }
	soma = soma/sample;
	soma = soma/100;
	return (soma);
}

float intervalArrive() { 				//intervalo de chegada
	double x;
	srand(_rdtsc());
	x = rand() % 10;
	x = x/10;
	return (x);
}

void logfileFloat(float entrance) { 	//gera o arquivo log.dat e insere 1 valor
	char url[]="log.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }
	fclose(arq);
}

void logfileStr() { 					//string no log.dat
        char str[100];
        FILE *arq;
        arq = fopen("log.dat", "a");
        if (arq == NULL){ printf("problemas na abertura do arquivo\n"); return; }
        strcpy(str,"dados\n");
        fputs(str, arq);
        fclose(arq);
}

void logpackageInterval(float entrance) { //loga os intervalos dos pacotes
	char url[]="package_interval.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }
	fclose(arq);
}
