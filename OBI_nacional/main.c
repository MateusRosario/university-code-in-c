#include <stdio.h>
#include <math.h>

long medir(int tipo, int nr){
    if(tipo > nr){
        return 0;
    }else if(tipo == nr){
        if(tipo == 1){
            return 1;
        }else if(tipo == 2){
            return 4;
        }else if(tipo == 3){
            return 2;
        }
    }
    if(tipo == 1){
        return medir(1,nr-1) + medir(2,nr-1) + medir(3,nr-1);
    }else if(tipo == 2){
        return 4*(medir(1,nr-2) + medir(2,nr-2) + medir(3,nr-2));
    }else if(tipo == 3){
        return 2*(medir(1,nr-3) + medir(2,nr-3) + medir(3,nr-3));
    }
}

int main() {
    int N;
    scanf("%d", &N);
    if(N == 0){
        printf("1");
    }else{
        long soma = medir(1,N) + medir(2,N) + medir(3,N);
        printf("%li\n", soma%(1000000007));
    }

}