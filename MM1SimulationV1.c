//includes-
#include <stdio.h>
#include <stdlib.h>   
#include <math.h>    
#include <x86intrin.h>
#include <cpuid.h>
#include <inttypes.h>
#include <string.h>

//prototipo das funcoes
//float exp(float x);   
float package_received (int sample);
float package_interval (int sample);
void logfilefloat(float entrance);
void logfilestr();
void logpackage_received(float entrance);
void logpackage_interval(float entrance);
void log_several_data(float data1, float data2, float data3, float data4, float data5);

int main(void) {
	//variaveis utilizadas
	float midium_analysis = 0, x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0 ,variance = 0;
	double interval_maior = 0, interval_minor = 0;
	float TA1 = 0, TA2 = 0, TA3 = 0, TA4 = 0, TA5 = 0, IC1 = 0, IC2 = 0, IC3 = 0, IC4 = 0, IC5 = 0; 
	float lambda1 = 0, lambda2 = 0, lambda3 = 0, lambda4 = 0, lambda5 = 0; 
	float utilization1 = 0, utilization2 = 0, utilization3 = 0, utilization4 = 0, utilization5 = 0;
	float mu1 = 0, mu2 = 0, mu3 = 0, mu4 = 0, mu5 = 0;
	
	//media de pacotes recebidos
	TA1 = package_received(100);
	TA2 = package_received(100);
	TA3 = package_received(100);
	TA4 = package_received(100);
	TA5 = package_received(100);
	log_several_data(TA1,TA2,TA3,TA4,TA5);
	logfilestr();

	//Media do intervalo medio de chegada dos pacotes
	IC1 = package_interval(100);
	IC2 = package_interval(100);
 	IC3 = package_interval(100);	
	IC4 = package_interval(100);
	IC5 = package_interval(100);
	log_several_data(IC1,IC2,IC3,IC4,IC5);
	logfilestr();
	
	//taxa de chegada
	lambda1 = 1/IC1; 
	lambda2 = 1/IC2; 
	lambda3 = 1/IC3; 
	lambda4 = 1/IC4; 
	lambda5 = 1/IC5; 
	float lambdamedio = (lambda1+lambda2+lambda3+lambda4+lambda5)/5;
	log_several_data(lambda1,lambda2,lambda3,lambda4,lambda5);
	logfilestr();
	
	//Taxa media de recebimento dos pacotes
	mu1 = 1/TA1;
	mu2 = 1/TA2;
	mu3 = 1/TA3;
	mu4 = 1/TA4;
	mu5 = 1/TA5;
	log_several_data(mu1,mu2,mu3,mu4,mu5);
	logfilestr();
	
	//utilizacao
	utilization1 = lambda1/mu1;
	utilization2 = lambda2/mu2;
	utilization3 = lambda3/mu3;
	utilization4 = lambda4/mu4;
	utilization5 = lambda5/mu5;
	float media_utilization = (utilization1 + utilization2 + utilization3 + utilization4 + utilization5)/5;
	log_several_data(utilization1,utilization2,utilization3,utilization4,utilization5);
	logfilestr();

	//media
	midium_analysis = (TA1 + TA2 + TA3 + TA4 + TA5)/5;
	logfilefloat(midium_analysis);
	logfilestr();
 	
	//calculo para obter a variancia
	x1 = pow(TA1 - midium_analysis,2);
	x2 = pow(TA2 - midium_analysis,2);
	x3 = pow(TA3 - midium_analysis,2);
	x4 = pow(TA4 - midium_analysis,2);
	x5 = pow(TA5 - midium_analysis,2);
	
	//variancia
	variance = (x1+x2+x3+x4+x5)/(5-1);
	logfilefloat(variance);
	logfilestr();
	
	//intervalo de confianca de 95%		
	interval_maior = midium_analysis + (1.96*(sqrt(variance/(5-1))));   
	interval_minor = midium_analysis - (1.96*(sqrt(variance/(5-1))));
	logfilefloat(interval_maior);
	logfilefloat(interval_minor);
	logfilestr();
			
	//Numero de pacotes na fila  
	float N1 = (pow(lambda1,2)/(mu1*(mu1-lambda1)));
	float N2 = (pow(lambda2,2)/(mu2*(mu2-lambda2)));
	float N3 = (pow(lambda3,2)/(mu3*(mu3-lambda3)));
	float N4 = (pow(lambda4,2)/(mu4*(mu4-lambda4)));
	float N5 = (pow(lambda5,2)/(mu5*(mu5-lambda5)));
	float NM = (N1+N2+N3+N4+N5)/5;
	
	//Numero de pacotes no sistema
	float NS1 = (lambda1/(mu1/lambda1));  
	float NS2 = (lambda2/(mu2/lambda2)); 
	float NS3 = (lambda3/(mu3/lambda3)); 
	float NS4 = (lambda4/(mu4/lambda4)); 
	float NS5 = (lambda5/(mu5/lambda5)); 
	float NSM = (NS1+NS2+NS3+NS4+NS5)/5;
	

  	printf("=                                  *** Results from M/M/1 simulation ***                                      \n");
 // 	printf("============================================================================================================= \n");
 //	printf("=  INPUTS:                                    \n");
 // 	printf("=    Taxa de Media de Atendimento               = %lf   p/min   == \n", ritmo_atendimento);
 // 	printf("=    Ritmo de Atendimento                       = %lf   p/min   == \n", tempo_atendimento);
  	printf("============================================================================================================= \n");
  	printf("=  OUTPUTS:                                   \n");
  	printf("=    Media de pacotes recebidos na primeira analise                                                = %f       \n", TA1);
  	printf("=    Media de pacotes recebidos na segunda analise                                                 = %f       \n", TA2);
  	printf("=    Media de pacotes recebidos na terceira analise                                                = %f       \n", TA3);
  	printf("=    Media de pacotes recebidos na quarta analise                                                  = %f       \n", TA4);
  	printf("=    Media de pacotes recebidos na quinta analise                                                  = %f       \n", TA5);
  	printf("=    Media do intervalo medio de chegada dos pacotes na primeira analise primeira analise          = %f       \n", IC1);
  	printf("=    Media do intervalo medio de chegada dos pacotes na primeira analise segunda analise           = %f       \n", IC2);
  	printf("=    Media do intervalo medio de chegada dos pacotes na primeira analise terceira analise          = %f       \n", IC3);
  	printf("=    Media do intervalo medio de chegada dos pacotes na primeira analise quarta analise            = %f       \n", IC4);
  	printf("=    Media do intervalo medio de chegada dos pacotes na primeira analise quinta analise            = %f       \n", IC5);
  	printf("=    Taxa media de pacotes recebidos na primeira analise                                           = %f       \n", lambda1);
  	printf("=    Taxa media de pacotes recebidos na segunda analise                                            = %f       \n", lambda2);
  	printf("=    Taxa media de pacotes recebidos na terceira analise                                           = %f       \n", lambda3);
  	printf("=    Taxa media de pacotes recebidos na quarta analise                                             = %f       \n", lambda4);
  	printf("=    Taxa media de pacotes recebidos na quinta analise                                             = %f       \n", lambda5);
	printf("=    Taxa media de pacotes recebidos em toda analise                                               = %f       \n", lambdamedio);
	printf("=    Taxa media de recebimento dos pacotes na primeira analise                                     = %f       \n", mu1);
	printf("=    Taxa media de recebimento dos pacotes na segunda analise                                      = %f       \n", mu2);
	printf("=    Taxa media de recebimento dos pacotes na terceira analise                                     = %f       \n", mu3);
	printf("=    Taxa media de recebimento dos pacotes na quarta analise                                       = %f       \n", mu4);
	printf("=    Taxa media de recebimento dos pacotes na quinta analise                                       = %f       \n", mu5);
	printf("=    Media de recebimento dos pacotes                                                              = %f       \n", midium_analysis);
	printf("=    Utilizacao do sistema na primeira analise                                                     = %f       \n", utilization1);
	printf("=    Utilizacao do sistema na segunda analise                                                      = %f       \n", utilization2);
	printf("=    Utilizacao do sistema na terceira analise                                                     = %f       \n", utilization3);
	printf("=    Utilizacao do sistema na quarta analise                                                       = %f       \n", utilization4);
	printf("=    Utilizacao do sistema na quinta analise                                                       = %f       \n", utilization5);
	printf("=    Utilizacao media                                                                              = %f       \n", media_utilization);
	printf("=    Numero medio de pacotes no sistema                                                            = %f       \n", NSM);
	printf("=    Variancia                                                                                     = %f       \n", variance);	
	if (NM < 0){
	printf("=    Nessa analise nao houve um valor medio para pacotes na fila                                              \n");
	}else{	
	printf("=    Numero medio de pacotes na fila                                                               = %f       \n", NM);
	}
	if(utilization1 < 1){
	printf("=    A primeia analise e estavel                                                                              \n");
	}
	if(utilization2 < 1){
	printf("=    A segunda analise e estavel                                                                              \n");
	}
	if(utilization3 < 1){
	printf("=    A terceira analise e estavel                                                                             \n");
	}
	if(utilization4 < 1){
	printf("=    A quarta analise e estavel                                                                               \n");
	}
	if(utilization5 < 1){
	printf("=    A quinta analise e estavel                                                                               \n");
	}
  	printf("============================================================================================================= \n");
	
	

	return(0);
}

//funcao que gera valores randomicos para o recebimento dos pacotes
float package_received (int sample){
	float x;
	float soma;	
	//srand((unsigned)time(NULL));
	srand(_rdtsc());    	
	for (int i=0; i<sample; i++){ x = rand() % 100; 
	logpackage_received(x);
	soma = soma + x; }
	soma = soma/sample;
	soma = soma/100;
	return (soma);
}

// funcao que gera valores randomicos para o intervalo de chegada de pacotes
float package_interval (int sample) {
	float x;
	float soma;	
	//srand((unsigned)time(NULL));
	srand(_rdtsc());    	
	for (int i=0; i<sample; i++){ x = rand() % 100;	
	logpackage_interval(x); 	
	soma = soma + x; }
	soma = soma/sample;
	soma = soma/100;
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
//logando 5 valores no log.dat
void log_several_data(float data1, float data2, float data3, float data4, float data5) {
	logfilefloat(data1);
	logfilefloat(data2);
	logfilefloat(data3);
	logfilefloat(data4);
	logfilefloat(data4);
}

void logpackage_received(float entrance) {
	char url[]="package_received.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }	
	fclose(arq);
}

void logpackage_interval(float entrance) {
	char url[]="package_interval.dat";
	FILE *arq;
	arq = fopen(url, "a");
	if(arq == NULL){ printf("problemas na abertura do arquivo\n"); }
	else{ fprintf(arq, "%f\n",entrance); }	
	fclose(arq);
}

