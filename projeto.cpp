#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

/*
 * Compara o tempo de execucao da ordenacao de n numeros com m digitos cada
 * com os algoritmos de ordenacao digital, quicksort e selectionSort.
 * 
 * uso: ordenacao min max d r i
 * 
 * onde:
 *   min = tamanho do menor vetor a ser ordenado
 *	 max = tamanho do maior vetor a ser ordenado
 *   d = numero de digitos de cada numero (max. 19)
 *   r = numero de repeticoes de ordenacao de vetores com n entradas
 *   i = valor de incremento de min, para min<max
 *	 s(1/0) = testar selectionSort (opcional)
 *	 o(1/0) = vetores ordenados (opcional)
 */



// Rearranja em ordem lexicografica um vetor v[0..n-1] 
// de strings. Cada v[i] e uma string v[i][0..W-1]
// cujos elementos pertencem ao conjunto 0..9.
// Fonte: Prof. Paulo Feofiloff
//        https://www.ime.usp.br/~pf/algoritmos/aulas/radix.html
void ordenacaoDigital (char **v, int n, int W) 
{
   int *fp;
   char **aux;
   fp = (int *)malloc ((11) * sizeof (int));
   aux = (char **)malloc (n * sizeof (char *));

   for (int d = W-1; d >= 0; --d) {
      int r;

      // ordenacao por contagem pelo digito de ordem d
      for (r = 0; r <= 10; ++r) 
         fp[r] = 0;
      for (int i = 0; i < n; ++i) {
         r = v[i][d]-'0';
         fp[r+1] += 1; 
      }
      for (r = 1; r <= 10; ++r) 
         fp[r] += fp[r-1]; 
      for (int i = 0; i < n; ++i) {
         r = v[i][d]-'0';
         aux[fp[r]] = v[i]; 
         fp[r]++; 
      }
      for (int i = 0; i < n; ++i) 
         v[i] = aux[i];
   }
   free (fp);
   free (aux);
}

// imprime o vetor de strings para testes
void print_v(char *mensagem, char **v, int n)
{
  printf("%s\n", mensagem);
  for (int i = 0; i < n; ++i)
    printf("%s\n", v[i]);
  printf("\n");
}

// imprime o vetor de inteiros para testes
void print_vi(char *mensagem, long long *vi, int n)
{
  printf("%s\n", mensagem);
  for (int i = 0; i < n; ++i)
    printf("%lld\n", vi[i]);
  printf("\n");
}

// A funcao randomInteger devolve um inteiro aleatorio entre low e high inclusive,
// Vamos supor que low <= high e que high - low <= RAND_MAX. 
//(O codigo foi copiado da biblioteca random de Eric Roberts.)
int randomInteger (int low, int high)
{
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}

// Gera n strings aleatorios 
void strings_aleatorias(char **v, int n, int m)
{
  int i, j;

  for (i = 0; i<n; ++i) {
    for (j = 0; j<m; j++) 
      v[i][j] = randomInteger(48,57); // digito aleatorio de 0 a 9 em ASCii
    v[i][j] = '\0';//final de cada array(numero)
  }
}

// compara dois inteiros para o qsort()
int comparador(const void * a, const void * b)
{
  long long d =  *(long long *)a - *(long long *)b;
  if (d > 0)
    return 1;
  else if (d < 0)
    return -1;
  else return 0;
}

/*/ funcao para testar os algoritmos de ordenacao
int teste()
{
  char *v1[10] = { "3847121", "9585345", "0498413", "1134995", "2222222",
		   "2222432", "3244232", "1123231", "6233213", "1923342"};
  int v2[10];
  
  print_v("NÃ£o Ordenado:", v1, 10);
  ordenacaoDigital (v1, 10, 7);
  print_v("Ordenado por ordenacaoDigital():", v1, 10);

  for(int i=0; i<10; ++i)
    v2[i] = atoi(v1[i]);
  
  qsort(v2, 10, sizeof(int), comparador);
  printf("Ordenado pelo qsort():\n");
  for (int i=0; i<10; ++i)
    printf("%d\n", v2[i]);
}*/

// ordena o vetor v com ordenacaoDital() e
// retorna o tempo de execucao
double ordena_por_digitos(char **v, int n, int m)
{
  clock_t t;
  double tempo;
  
  t = clock(); 
  ordenacaoDigital (v, n, m);
  t = clock() - t; 

  tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  //printf("Tempo da digital(): %f seg.\n", tempo); 
  return tempo; 
}

// ordena o vetor v com o qsort() e
// retorna o tempo de execucao
double quicksort(long long *v, int n, int m)
{
  clock_t t;
  double tempo;
  
  t = clock(); 
  qsort(v, n, sizeof(long long), comparador);
  t = clock() - t;

  tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  //tempo para ordenar min elementos
  //printf("Tempo da Quickl(): %f seg.\n", tempo); 
  return tempo; 
}



//Ordena o vetor com selection sort
//e retorna o tempo de execucao
double selectionsort(long long *A,int n)
 {
 int tmp;
 int min;
	clock_t t;
	double tempo;
	
 t = clock();
 
 	for(int i=0; i< n-1; i++)
 		{
 			min=i;
 				for(int j=i; j<n; j++)
 				{
 					if (A[j]<A[min]){
 						min=j;
 					}
 				}
 			tmp=A[i];
 			A[i]=A[min];
 			A[min]=tmp;
 		}
 
 t = clock() - t;
 tempo = ((double)t)/CLOCKS_PER_SEC;
 return tempo; 
 }


//Funcao Principal
int main(int argc, char *argv[])
{
	//range[min,n]  digitos[m] repeticoes[r] intervalos de iteracao[v]
	int min, n, m, r,v;
	//tempos medios e desvios
	double t_quick, t_count, t_select, d_quick, d_count, d_select;
	int s = 0;
	int o =0;
	// recebe uma semente para o gerador aleatorio
	// como parametro opcional
/*	if (argc == 7) {
		printf("seed = %u\n", atoi(argv[6]));
		srand((unsigned) atoi(argv[6]));
	}*/	if (argc == 7) {
		s = atoi(argv[6]);
	}
		if (argc == 8) {
		s = atoi(argv[6]);
		o = atoi(argv[7]);
	}
	
	//parametros obrigatorios
	if (argc >= 6) {
		min = atoi(argv[1]); //inicio intervalo[qtd mín de elementos]
		n = atoi(argv[2]); //fim intervalo[qtd max de elementos]
		m = atoi(argv[3]); //digitos p/elemento
		r = atoi(argv[4]); //numero de execucoes para cada n
		v = atoi(argv[5]); //valor de iteracao de min<n
	} else {
		printf("uso: ord-digital min max d r i [seed-opcional]\n");
		printf("min[numero minimo de entradas]\n");
		printf("max[numero maximo de entradas]\n");
		printf("d[tamanho de cada entrada/digitos]\n");
		printf("r[numero de repeticoes do algoritmo para cada valor de entrada]\n");
		printf("i[valor de incremento de min enquanto min<max]\n");
		printf("0/1[testar SelectionSort]\n");
		printf("0/1[Vetores ordenados]");
		exit(1);
	}
  
	//inicia o loop para o primeiro valor de n=min
	while(min<=n){
	//zerando as medias quando min iterar
		t_quick=0;
		t_count =0;
		t_select = 0;
		d_quick = 0;
		d_count = 0;
		d_select = 0;
		int c =1; //reinicia contador
 
	//ordenando r vetores com min entradas 
		while(c <= r){

			// aloca um vetor v de min strings de tamanho m cada para a ordenacao digital
 			char **v = (char **)malloc (min * sizeof (char *));
 			for (int i=0; i<min; ++i)
			{
   			 v[i] = (char *)malloc( (m+1)*sizeof(char) );
  			}
  
 			//aloca dois vetores vie vs de min inteiros e tamanho long long
 			//para executar o quicksort/selectionsort
 			long long *vi = (long long *)malloc(min * sizeof(long long));
			long long *vs = (long long *)malloc(min * sizeof(long long));
			
 			//preenche v com min strings aleatorias formadas por m digitos cada
 			strings_aleatorias(v, min, m);

  			// copia as min strings de m digitos com formato longlong para vi e vs, usados no quicksort e selecitonsort
 			//o tamanho longlong de vi e vs restringe m a 18 digitos
 			for (int i=0; i<min; ++i){
   			 vi[i] = atoll(v[i]);
   			 if(s){
				vs[i] = atoll(v[i]);}
			}

  			// tempo medio e desvio do quicksort - calcula tempo medio e desvio em tempo de execucao
 			//para cada novo x(tempo) para ordenacao de min elementos
 			double media1_q = t_quick;
 			if(o){	//ordena antecipadamente se a opcao for ativada
 				quicksort(vi, min, m);
 				//print_vi("qsort", vi, min);
			 }
 			double x_q = quicksort(vi, min, m);
 			t_quick += (x_q-t_quick)/c;
 			d_quick+= (x_q-t_quick)*(x_q-media1_q);
 			//print_vi("qsort", vi, min);
  			
 			// tempo medio e desvio ordenacao digital 
 			double media1_c = t_count;
 			if(o){
 				ordena_por_digitos(v, min, m); 
 				//print_v("digital", v, min);
			 }
 			double x_c = ordena_por_digitos(v, min, m); 
 			t_count += (x_c-t_count)/c;
 		 	d_count+= (x_c-t_count)*(x_c-media1_c);
 		 	 //print_v("digital", v, min);
  
 		 	//tempo e desvio selectionsort
  			if(s){
			double media1_s = t_select; //media anterior para n=min-v
			if(o){
				quicksort(vs, min, m);
				//print_vi("select", vs, min);
			}
 		 	double x_s = selectionsort(vs, min); //tempo atualpara n=min
 		 	t_select += (x_s-t_select)/c; //update media
 		 	d_select+= (x_s-t_select)*(x_s-media1_s); //update desvio
 		 	//print_vi("select", vs, min);
  			}
  			//liberando memoria apos ordenacao
  		 	for (int i=0; i<min; ++i){
   				 free(v[i]);
			}
    
			free(vi);
			free(vs);
 			free(v);
 
 		 	c++;//ate c<-r
		}
 

		printf("%d %f %f %f %f %f %f\n", min, t_quick, sqrt(d_quick/r), t_count, sqrt(d_count/r), t_select, sqrt(d_select/r));
		/* 
		min = entradas
		tempomedio_ordenacao(min)
		desvio(tempomedio)
		*/

		//variando a entrada de v em v
		min+=v;
}
 //system("gnuplot -p g.gp");
 return 0;
}

