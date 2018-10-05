#include <stdio.h>
#include <stdlib.h>
#include<time.h> //srand() icin
#include <string.h>
#define FILE_PATH  "/home/mrk0debian/dev/c/proLab1/inputFile"
#define FILE_PATH_MAP  "/home/mrk0debian/dev/c/proLab1/harita"
#define ROWS 3
#define COLS 3

struct street{
    char name;
    char route[2];
    int dens;
};


void initMap();
int *initInputArray();
int createInputFile(int inputCount);
//windowsta file path farklıdır

int main() {
    //girdi adedi SIMDILIK hardcoded
    //SPARSE MATRIS
    createInputFile(9);
    int *inputArray;
    inputArray = initInputArray();
    struct street strt[8];
    int i,j,nullCount = 0;
    const char JUNCTION[4] = {'A','B','C','D'};
    const char outerStrt[4] = {'x','y','z','t'};
    const char innerStrt[4] = {'a','b','c','d'};
    initMap();

    for ( i = 0; i < 9; i++) {
        if (inputArray[i] == -1) {
            nullCount++;
        }
    }
    char inpStr[2];
    char outStr[2];
    int k = 0;

    printf("-> girişleri seçin ve çıkışları seçin (x,y,z,t) \n" );
    while(1){
        printf("-> %d. girişi seçin:  ",k+1 );
        scanf(" %c",&inpStr[k]);
        if (inpStr[k] != 'x' && inpStr[k] != 'y' &&inpStr[k] != 'z' &&inpStr[k] != 't') {
            printf("-> hatalı giriş yaptınız! (girdi x,y,z,t değil)\n" );
            continue;
        }
        printf(" >>> %c\n",inpStr[k] );
        k++;
        if (k == 2) {
            if (inpStr[0] == inpStr[1]) {
                printf("-> hatalı giriş yaptınız! (2 giriş aynı)\n" );
                k = 0;
                continue;
            }
            break;
        }
    }
    // string girince control patlıyor
    k = 0;
    while(1){
        printf("-> %d. çıkış seçin:  ",k+1 );
        scanf(" %c",&outStr[k]);
        if (outStr[k] != 'x' && outStr[k] != 'y' && outStr[k] != 'z' && outStr[k] != 't' || outStr[k] == inpStr[0] || outStr[k] == inpStr[1]) {
            printf("-> hatalı çıkış yaptınız! (girdi x,y,z,t değil v giriş ve çıkış aynı)\n" );
            continue;
        }
        printf(" >>> %c\n",outStr[k] );
        k++;
        if (k == 2) {
            if (outStr[0] == outStr[1]) {
                printf("-> hatalı girdi yaptınız! (2 çıkış aynı)\n" );
                k = 0;
                continue;
            }
            break;
        }
    }

    strt[0].name = inpStr[0];
    strt[1].name = inpStr[1];
    strt[2].name = outStr[0];
    strt[3].name = outStr[1];
    strt[0].route[0] = 'I';
    strt[1].route[0] = 'I';
    strt[2].route[1] = 'O';
    strt[3].route[1] = 'O';

    //ALLAHIN INAYETI START
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (strt[i].name == outerStrt[j]) {
                strt[i].route[1] = JUNCTION[j];
            }
        }
    }
    for (i = 2; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (strt[i].name == outerStrt[j]) {
                strt[i].route[0] = JUNCTION[j];
            }
        }
    }
    //ALLAHIN INAYETI END
    while(1){
        char tmpc;
        printf("\n-> caddlerin yönlerini seçin \n" );
        printf("-> a caddesinin yönünü seçin (x,t): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'x' || tmpc =='z') {
            strt[4].name = 'a';
            if (tmpc == 'x') {
                strt[4].route[0] = 'D';
                strt[4].route[1] = 'A';
            }else{
                strt[4].route[0] = 'A';
                strt[4].route[1] = 'D';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> b caddesinin yönünü seçin (x,y): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'x' || tmpc =='y') {
            strt[5].name = 'b';
            if (tmpc == 'x') {
                strt[5].route[0] = 'B';
                strt[5].route[1] = 'A';
            }
            else{
                strt[5].route[0] = 'A';
                strt[5].route[1] = 'B';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> c caddesinin yönünü seçin (y,z): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'z' || tmpc =='y') {
            strt[6].name = 'c';
            if (tmpc == 'z') {
                strt[6].route[0] = 'B';
                strt[6].route[1] = 'C';
            }
            else{
                strt[6].route[0] = 'C';
                strt[6].route[1] = 'B';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> d caddesinin yönünü seçin (t,z): " );
        scanf(" %c",&tmpc );
        if (tmpc == 't' || tmpc =='z') {
            strt[7].name = 'd';
            if (tmpc == 't') {
                strt[7].route[0] = 'C';
                strt[7].route[1] = 'D';
            }
            else{
                strt[7].route[1] = 'D';
                strt[7].route[0] = 'C';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        break;
    }
    //dens burada giriliyor
    for ( i = 0; i < 8; i++) {
        inputArray[i];
    }
    for (i = 0; i < 8; i++) {
        strt[i].dens = inputArray[i];
        if (strt[i].dens == -1) {
            strt[i].dens = NULL;
        }
        printf(">>> strt[%d].name >>> %c, strt.route %c -> %c  strt.dens -> %d\n",i,strt[i].name,strt[i].route[0],strt[i].route[1],strt[i].dens );
    }

    

    return 0;
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
int createInputFile(int inputCount){
    FILE *inputFile;
    if ((inputFile = fopen(FILE_PATH,"r")) == NULL) {
        printf("-> dosya bulunamadı yeniden oluşturulutor\n" );
        inputFile = fopen(FILE_PATH,"w");
        int i;
        srand(time(0));//rasgele sayi üretimi icin
        int fileArray[inputCount];
        for (i = 0; i < inputCount; i++) {
            fileArray[i] = rand() % 100;
            fprintf(inputFile, "%d ",fileArray[i] );
        }
        fclose(inputFile);
    }
    //flclose seg fault veriyor , dosya kapanmış
    //gözüküyor ama nasıl ? hocaya sor
    printf("-> inputFile oluştu veya zaten vardı :)\n");
}

int *initInputArray(){
    FILE * inputFile = fopen(FILE_PATH,"r");
    if (inputFile == NULL) {
        printf("-> dosya açılamadı\n" );
    }
    int* readbuf;
    readbuf = (int *) malloc (9 * sizeof(int));
        for (int i=0; i<9; i++){
         int j = 0;
         fscanf (inputFile, "%d", &j);
         readbuf[i] = j;
    }
    fclose(inputFile);
    return readbuf;
}

void initMap() {
    printf("        x       \n" );
    printf("      /a b\\         \n" );
    printf("    t-     -y    \n" );
    printf("      \\d c/         \n" );
    printf("        z       \n" );
}
