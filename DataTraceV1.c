//includes-
#include <stdio.h>
#include <stdlib.h>   
#include <math.h>    
#include <string.h>

//struct que coleta os dados e faz a media
struct retorno {
  float package_time;
  float package_size;
};

//struct que coleta os dados e faz a media
struct retorno funcao(){
  	struct retorno resultado;
	char url[]="data.txt";
	float package_time=0, package_size=0;
	FILE *arq;
	
	arq = fopen(url, "r");
	if(arq == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
	}else{
		float data1 = 0;
		float data2 = 0;
		while((fscanf(arq," %f %f \n", &data1, &data2))!=EOF ){
			package_time = package_time + data1;
			package_size = package_size + data2;
		}
	
	fclose(arq);
	}
  	resultado.package_time = package_time/166060;
  	resultado.package_size = package_size/166060;
  	return(resultado);
}
//main
float main(){
	//variaveis utilizadas
	float midium_analysis = 0, variance = 0;
	double interval_maior = 0, interval_minor = 0;
	float TA = 0,IC = 0; 
	float lambda = 0;
	float utilization = 0;
	float mu = 0;
	float NS=0;
	
	//chamada da struct no main
	struct retorno data;
	data = funcao();
	IC = data.package_size;
	TA = data.package_time;
	//taxa média de chegada
	lambda = 1/IC; 
	//Taxa media de recebimento dos pacotes
	mu = 1/TA;
	//utilizacao
	utilization = lambda/mu;
	//variancia
	variance = 1/pow(lambda,2);
	//media do servico realizado
	midium_analysis = 1/lambda;
	//tamanho médio da fila
	NS = pow(lambda,2)/(mu*(mu-lambda));
	//intervalo de confianca de 95%
	interval_maior = midium_analysis + (1.96*(sqrt(variance/100)));   
	interval_minor = midium_analysis - (1.96*(sqrt(variance/100)));
	
	//resultados	
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
	printf("=    Tamanho Medio da Fila                     = %f       \n", NS);
	printf("=    O Intervalo de Confianca Maior (95%)      = %f       \n", interval_maior);
	printf("=    O Intervalo de Confianca Menor (95%)      = %f       \n", interval_minor);		
	if(utilization < 1){
	printf("=    A Analise e Estavel                                  \n");
	}
        printf("===========================================================\n");
	return(0);
	 
}

