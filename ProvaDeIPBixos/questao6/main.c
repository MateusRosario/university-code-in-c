#include <stdio.h>

int main() {
    float N1, N2, N3, media;
    scanf("%f %f %f", &N1, &N2, &N3);
    media = (N1+N2+N3)/3;
    if(media < 4){
        printf("Media: %f\nReprovado\n", media);
    }else if(media < 7){
        N1 = 10 - media;
        printf("Media: %f\nExame Final\nDeve tirar: %f\n", media, N1);
    }else{
        printf("Media: %f\nAprovado\n", media);
    }
    return 0;
}