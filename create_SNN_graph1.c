#include <stdlib.h>
#include <stdio.h>

void create_SNN_graph1(int N, char **table2D, int ***SNN_table){

  *SNN_table = (int **) calloc(N, sizeof(int*));
  (*SNN_table)[0] = (int*) calloc(N * N, sizeof(int));
  for (size_t i=1; i<N; i++){
    (*SNN_table)[i] = &(*SNN_table)[0][i * N];
  } 
  #pragma omp parallel for schedule(dynamic)
  for(size_t i=0; i<N; i++){
    for(size_t j=i+1; j<N; j++){
      if (table2D[i][j] == 1){
        int countSNN = 0;

        for(size_t k=0; k<N; k++){
          if(table2D[i][k] && (table2D[j][k])){
            countSNN ++;
          }
        }
        (*SNN_table)[i][j] = countSNN;
        (*SNN_table)[j][i] = countSNN;
      }
    }
  }
  return;
}

  
