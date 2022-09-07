//includes-
#include <stdio.h>
#include <stdlib.h>   
#include <math.h>    
#include <x86intrin.h>
#include <cpuid.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
//prototipo das funcoes
//float exp(float x);   
float package_received (int sample);
float package_interval (int sample);
void logfilefloat(float entrance);
void logfilestr();
void logpackage_received(float entrance);
void logpackage_interval(float entrance);

int main(void) {
	//variaveis utilizadas
	float midium_analysis = 0, variance = 0;
	double interval_maior = 0, interval_minor = 0;
	float TA = 0,IC = 0; 
	float lambda = 0;
	float utilization = 0;
	float mu = 0;
	
	//media de pacotes recebidos
	TA = package_received(100);
	//Media do intervalo medio de chegada dos pacotes
	IC = package_interval(100);
	//taxa média de chegada
	lambda = 1/IC; 
	//Taxa media de recebimento dos pacotes
	mu = 1/TA;
	//utilizacao
	utilization = lambda/mu;
	//variancia
	variance = 1/pow(lambda,2);
	//media do servico realizado
	midium_analysis = TA;
	//intervalo de confianca de 95%
	interval_maior = midium_analysis + (1.96*(sqrt(variance/100)));   
	interval_minor = midium_analysis - (1.96*(sqrt(variance/100)));

        printf("===========================================================\n");	
  	printf("=           *** Results from M/M/1 simulation ***         \n");
        printf("===========================================================\n");
 	printf("=  INPUTS:                                    \n");
 	printf("=    Media dos Pacotes Recebidos               = %lf      \n", TA);
	printf("=    Intervalo Medio de Chegada                = %lf      \n", IC);
  	printf("===========================================================\n");
  	printf("=  OUTPUTS:                                   \n");
  	printf("=    Taxa Media de Chegada dos Pacotes         = %f       \n", lambda);
	printf("=    Taxa Media de Recebimento dos Pacotes     = %f       \n", mu);
	printf("=    Utilizacao do Sistema                     = %f       \n", utilization);
	printf("=    Variancia                                 = %f       \n", variance);
	printf("=    Media das Amostras                        = %f       \n", midium_analysis);
	printf("=    O Intervalo de Confianca Maior (95%)      = %f       \n", interval_maior);
	printf("=    O Intervalo de Confianca Menor (95%)      = %f       \n", interval_minor);		
	if(utilization < 1){
	printf("=    A Analise e Estavel                                  \n");
	}
        printf("===========================================================\n");
	return(0);
}

//funcao que gera valores randomicos para o recebimento dos pacotes
float package_received (int sample){
	float x;
	float soma;	
	srand(_rdtsc());    	
	for (int i=0; i<sample; i++){ x = rand() % 10; 
	logpackage_received(x);
	soma = soma + x; }
	soma = soma/sample;
	soma = soma/10;
	return (soma);
}

// funcao que gera valores randomicos para o intervalo de chegada de pacotes
float package_interval (int sample) {
	float x;
	float soma;	
	srand(_rdtsc());    	
	for (int i=0; i<sample; i++){ x = rand() % 10;	
	logpackage_interval(x); 
	soma = soma + x; }
	soma = soma/sample;
	soma = soma/10;
	return (soma);
}

//funcao que gera o arquivo log.dat e insere 1 valor
void logfilefloat(float entrance) {
	char url[]="log.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }	
	fclose(arq);
}

//funcao que gera uma string no log.dat
void logfilestr() {
        char str[100];
        FILE *arq;
        arq = fopen("log.dat", "a");
        if (arq == NULL){ printf("problemas na abertura do arquivo\n"); return; }
        strcpy(str,"dados\n");
        fputs(str, arq);
        fclose(arq);
}

//loga os pacotes recebidos
void logpackage_received(float entrance) {
	char url[]="package_received.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }	
	fclose(arq);
}
//loga os intrvalos dos pacotes 
void logpackage_interval(float entrance) {
	char url[]="package_interval.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }	
	fclose(arq);
}

