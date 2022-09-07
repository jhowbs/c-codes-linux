//Simulação com trace de dados
//Como ordenador de eventos (cheda de pacote), plotar gráfico tamanho médio da fila x utilização.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct retorno { 								//struct que coleta os dados e faz a media
  float package_time;							//intervalo de chegada ds pacotes
  float package_size;							//tamanho do pacote
};

struct retorno funcao(){ 						//struct que coleta os dados e faz a media
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

float main(){
	double interval_maior = 0, interval_minor = 0;
	float TA = 42, IC = 0, lambda = 0, Media = 0, utilization = 0, mu = 0,  NF = 0, variance = 0;

	struct retorno data;					//chamada da struct no main
	data = funcao();
	Media = data.package_size;
	IC = data.package_time;

	lambda = 1/IC;							//taxa média de chegada
	mu = 1/TA;								//Taxa media de recebimento dos pacotes
	utilization = lambda/mu; 				//utilizacao
	variance = 1/pow(lambda,2); 			//variancia
	NF = pow(lambda,2)/(mu*(mu - lambda));  //numero de pck na fila

	interval_maior = Media + (1.96*(variance/sqrt(166060))); //ic (+95%)
	interval_minor = Media - (1.96*(variance/sqrt(166060))); //ic (-95%)

	printf("Int Chegada             = %f\n", IC);
	printf("Temp Atendimento        = %f\n", TA);
	printf("Media                   = %f\n", Media);
	printf("Utilizacao          	= %f\n", utilization);
	printf("Pacotes na Fila         = %f\n", NF);
	printf("O IntConf(+95%)	        = %fl\n", interval_maior);
	printf("O IntConf(-95%)	        = %fl\n", interval_minor);

	return(0);
}
