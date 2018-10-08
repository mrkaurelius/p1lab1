#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#define FILE_PATH  "/home/mrk0debian/dev/c/proLab1/inputFile" //windowsta file path farklıdır
#define FILE_PATH_MAP  "/home/mrk0debian/dev/c/proLab1/harita" //windowsta file path farklıdır
#define ROWS 3
#define COLS 3
//STRUCTLAR FONKSYONDA CALISI
struct streetMap1{
    char name;
    char route[2];
    int dens;
}strt1[8];

struct streetMap2{
    char name;
    char route[2];
    int dens;
}strt2[9];

void initMap();
int *initInputArray();
int createInputFile(int inputCount);
void getstrt1Direction(struct streetMap1 strt1f[],int strt1Size);
void printstrt1MasterMatris(struct streetMap1 strt1f[], int s1MasterMatris[4][9]);
int * findEmptyColstrt1(int s1MasterMatris[4][9],int nullCount);

int main() {
    int strt1Size = 8;
    //GIRDI VE MODEL TEST EDILDI I/O DENKLEMI KALDI
    //TUM GIRIS CIKISA IHTIYAC VARMI ?
    createInputFile(9);  //girdi adedi SIMDILIK hardcoded
    int *inputArray;
    inputArray = initInputArray();
    int i,j,k = 0,nullCount = 0;
    int s1MasterMatris[4][9]; // MATRISLE OYNAYABILMEK ICIN DINAKIK ALOOCATE MI GEREKIYOR
    const char JUNCTION[4] = {'A','B','C','D'}; // GEREK YOK AMA SIMDILIK KALSIN
    char inpStr[2];
    char outStr[2];
    initMap();
    getstrt1Direction(strt1,strt1Size);    // Legal giriş bekleniyor

    char *strt1Null = malloc(1 * sizeof(char));
    for (i = 0; i < 8; i++) {
        strt1[i].dens = inputArray[i]; //DOSYADAN GIRIS
        if (strt1[i].dens == -1) {
            strt1Null = realloc(strt1Null , sizeof(char));
            strt1Null[k] = strt1[i].name;
            nullCount++;
            k++;
        }
        printf(">>> strt1[%d].name >>> %c, strt1.route %c -> %c  strt1.dens -> %d\n",i,strt1[i].name,strt1[i].route[0],strt1[i].route[1],strt1[i].dens );
    }

    for (i = 0; i < nullCount; i++) {
        printf(">>>strt1Null %c\n",strt1Null[i]);
    }

    // BUNU FONSK YAPMAYA GREK VARMI ?
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 9; j++) {
            s1MasterMatris[i][j] = 0;
        }
    }

    int constantSum = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            if (strt1[j].route[1] == JUNCTION[i] && strt1[j].dens == -1) {
                s1MasterMatris[i][j] = 1;
            }else if (strt1[j].route[0] == JUNCTION[i] && strt1[j].dens == -1){
                s1MasterMatris[i][j] = -1;
            }
            if (strt1[j].dens != -1) {
                if (strt1[j].route[0] == JUNCTION[i]) {
                    constantSum += strt1[j].dens;
                }else if (strt1[j].route[1] == JUNCTION[i]) {
                    constantSum -= strt1[j].dens;
                }
            }
        }
        s1MasterMatris[i][8] = constantSum;
        constantSum = 0;
    }

    int *strt1emptyCol =malloc(nullCount * sizeof(int));
    strt1emptyCol = findEmptyColstrt1(s1MasterMatris,nullCount);
    printstrt1MasterMatris(strt1,s1MasterMatris);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int * findEmptyColstrt1(int s1MasterMatris[4][9],int nullCount){
    int tmp = 0,k = 0,i,j;
    int *strt1emptyCol = malloc(nullCount * sizeof(int));
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 4; i++) {
            if (s1MasterMatris[i][j] == 0) {
                tmp++;
                if (tmp == 4) {
                    strt1emptyCol[k] = j;
                    k++;
                }
            }
        }
        tmp = 0;
    }
    for (i = 0; i < nullCount; i++) {
        printf(">>>bos sutun > %d\n",strt1emptyCol[i] );
    }
    return strt1emptyCol;
}

void printstrt1MasterMatris(struct streetMap1 strt1f[], int s1MasterMatris[4][9]){
    int i,j;
    for (i = 0; i < 8; i++) { //-> PRINT MASTER MATRIS FONK
        printf(" %4c ",strt1f[i].name);
    }
    printf(" cons \n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j <  9; j++) {
            printf("[%4d]",s1MasterMatris[i][j]);
        }
        printf("\n" );
    }
}

void getstrt1Direction(struct streetMap1 strt1f[],int strt1Size){
    //GIRDI VE MODEL TEST EDILDI I/O DENKLEMI KALDI
    createInputFile(9);  //girdi adedi SIMDILIK hardcoded
    int *inputArray;
    inputArray = initInputArray();
    int i,j,nullCount = 0;
    const char JUNCTION[4] = {'A','B','C','D'};
    const char allstrt1[8] = {'x','y','z','t','a','b','c','d'};
    const char outerstrt1[4] = {'x','y','z','t'};
    const char innerstrt1[4] = {'a','b','c','d'};
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

    strt1[0].name = inpStr[0];
    strt1[1].name = inpStr[1];
    strt1[2].name = outStr[0];
    strt1[3].name = outStr[1];
    strt1[0].route[0] = 'I';
    strt1[1].route[0] = 'I';
    strt1[2].route[1] = 'O';
    strt1[3].route[1] = 'O';
    //ALLAHIN INAYETI START
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (strt1[i].name == outerstrt1[j]) {
                strt1[i].route[1] = JUNCTION[j];
            }
        }
    }
    for (i = 2; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (strt1[i].name == outerstrt1[j]) {
                strt1[i].route[0] = JUNCTION[j];
            }
        }
    }

    while(1){
        char tmpc;
        printf("\n-> caddlerin yönlerini seçin \n" );
        printf("-> a caddesinin yönünü seçin (x,t): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'x' || tmpc =='z') {
            strt1[4].name = 'a';
            if (tmpc == 'x') {
                strt1[4].route[0] = 'D';
                strt1[4].route[1] = 'A';
            }else{
                strt1[4].route[0] = 'A';
                strt1[4].route[1] = 'D';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> b caddesinin yönünü seçin (y,x): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'x' || tmpc =='y') {
            strt1[5].name = 'b';
            if (tmpc == 'x') {
                strt1[5].route[0] = 'B';
                strt1[5].route[1] = 'A';
            }
            else{
                strt1[5].route[0] = 'A';
                strt1[5].route[1] = 'B';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> c caddesinin yönünü seçin (y,z): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'z' || tmpc =='y') {
            strt1[6].name = 'c';
            if (tmpc == 'z') {
                strt1[6].route[0] = 'B';
                strt1[6].route[1] = 'C';
            }
            else{
                strt1[6].route[0] = 'C';
                strt1[6].route[1] = 'B';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> d caddesinin yönünü seçin (z,t): " );
        scanf(" %c",&tmpc );
        if (tmpc == 't' || tmpc =='z') {
            strt1[7].name = 'd';
            if (tmpc == 't') {
                strt1[7].route[0] = 'C';
                strt1[7].route[1] = 'D';
            }
            else{
                strt1[7].route[0] = 'D';// COMMIT NOTU HATA DUZELTILDI
                strt1[7].route[1] = 'C';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        break;
    }
}

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
