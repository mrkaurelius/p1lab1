#include <stdio.h>
#include <stdlib.h>
#define S1ROW 5
#define S1COL 9
#define S2ROW 5
#define S2COL 10

struct s1MatrisSize{
    int row_size;
    int col_size;
}s1Msize;

struct s2MatrisSize{
    int row_size;
    int col_size;
}s2Msize;

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
//YOGUNLUKLARI ALDIRAN FONKSYON YAP
void get_strt1_Direction(struct streetMap1 strt1[],int strt1Size);
void print_strt1_MasterMatris(struct streetMap1 strt1[], int s1MasterMatris[5][9]);
void print_strt1Struct(struct streetMap1 strt1[]);
int get_NullCount_strt1(struct streetMap1 strt1[]);
void inp_S1MasterMatris(struct streetMap1 strt1[],int s1MasterMatris[5][9]);
char * init_strt1_NullArray(struct streetMap1 strt1[],int nullCount,int *strt1emptyCol);
void removeColumnS1(int **matrix, int col);
//NEDEN 2 KERE SWAP OLUYOR -CALISMAYA ETKISI YOK-
void checkandSwapS1(int **matrix);
void solveMatrisS1(int **matrix) {
	int i;
	int rix,iix;
	int lead = 0;
    //s1Msize.row_size = S1ROW;
    //s1Msize.col_size = S1COL;

	for (rix = 0; rix < s1Msize.row_size; rix++) {
		printf("lead -> %d\n",lead );
		if (lead >= s1Msize.col_size) {
			printf("> rref bitti\n" );
			break;
		}
		iix = rix;
		while (matrix[iix,lead] == 0) { // pivotun altı sıfırmı onu kontrol ediyor
			iix++;
			if (iix == s1Msize.row_size) { // pivottan emin olduktan sonra aynı satıra dön
				iix = rix;
				lead++;
				if (lead >= s1Msize.row_size) {
					printf("> rref bitti\n" );
					break;
					}
				}
			}

			if(matrix[iix] != matrix[rix]){
				printf("%d ve %d satır değiştiriliyor\n" );
				// neden satırları değiştiriyoruz
				//lead sıfır ise o sunta baska lead adayı varmı ona bakıyoruz
				//sonra onu swap ediyoruz
				int *temp;
				temp = matrix[iix];
				matrix[iix] = matrix[rix];
				matrix[rix] = temp;
			}

			//normalize row start
			printf("rix->%d\n",rix );
			int a = matrix[rix][lead];
			if (matrix[rix][lead] != 0) {
				for (i = 0; i < s1Msize.col_size ; i++) {
					matrix[rix][i] = matrix[rix][i] / a;
				}
				printf("normalize den sonra\n" );
			}
			//normalize row end

			for (iix = 0; iix < s1Msize.row_size; iix++) {
				if ( iix != rix ) {
					//MulandAd START
					int ix;
					int lv;
					lv = matrix[iix][lead];
					for (ix = 0; ix < s1Msize.col_size; ix++) {
						//lv multiplier
						//iix dest rix source
						matrix[iix][ix] = matrix[iix][ix]  + (-lv * matrix[rix][ix]);
					}
					//printf("Mul row %d by %d and add to row %d\n", , , );
					//MulandAd END
				}
			}
			lead++;

		}
		printf("Reduced R-E form\n");
}


int main() {
    //0 BASLANGICLI SATIRLARI SWAP ET
    //TUM GIRIS CIKISA IHTIYAC VARMI ?
    // girdi alma mantıgından oturu isiml
    //createInputFiles();
    //int *inputArray;
    //inputArray = init_S1_InputArray();
    int strt1Size = 8;
    //int densValue[] = {20,10,20,10,10,30,40,20};
    int densValue[] = {20,-1,20,-1,10,30,40,-1};
    int i,j,k = 0,nullCount = 0;
    int s1MasterMatris[5][9];
    for (i = 0; i < S1ROW; i++) {
        for (j = 0; j < S1COL; j++) {
            s1MasterMatris[i][j] = 0;
        }
    }
    initMap();
    get_strt1_Direction(strt1,strt1Size);    // Legal giriş bekleniyor
    //
    for (i = 0; i < 8; i++) {
        strt1[i].dens = densValue[i];
    }
    nullCount = get_NullCount_strt1(strt1);
    char *strt1Null = malloc(nullCount * sizeof(char));
    int *strt1emptyCol =malloc((8 - nullCount) * sizeof(int));
    strt1Null =  init_strt1_NullArray(strt1,nullCount,strt1emptyCol);
    print_strt1Struct(strt1);
    printf("DEBUG\n" );
    for (i = 0; i < nullCount; i++) {
        printf(">sNull -> %c,",strt1Null[i]); //DEBUGP
    }
    printf("\n" );

    for (i = 0; i < (8 - nullCount); i++) {
        printf(">eCol -> %d,",strt1emptyCol[i]); //DEBUGP
    }
    printf("\n" );
    inp_S1MasterMatris(strt1,s1MasterMatris);
    print_strt1_MasterMatris(strt1,s1MasterMatris);

    int **augMatrixS1= (int **)malloc(S1ROW * sizeof(int*));
    for (i = 0; i < S1ROW; i++) augMatrixS1[i] =(int *)malloc(S1COL * sizeof(int)); //AH ANAM VAY ANAM VAYY
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 9; j++) {
            augMatrixS1[i][j] = (int)s1MasterMatris[i][j];
        }
    }

    s1Msize.row_size = S1ROW;
    s1Msize.col_size = S1COL;
    for (i = 0; i < (8 - nullCount); i++) {
        removeColumnS1(augMatrixS1,strt1emptyCol[8 - nullCount - i - 1]); //MATRIS TERSETEN SAPLAR
    }
    //swap zero leading row with another row until leading is 1

    printf("matris boyutu -> %d, %d \n",s1Msize.row_size,s1Msize.col_size );
    for (i = 0; i < nullCount; i++) { //-> PRINT MASTER MATRIS FONK
        printf(" %4c ",strt1Null[i]);
    }
    printf("\n" );

    for (i = 0; i < s1Msize.row_size; i++) {
        for (j = 0; j < s1Msize.col_size; j++) {
            printf("[%3d]", augMatrixS1[i][j]);
        }
        printf("\n" );
    }
    checkandSwapS1(augMatrixS1);
    solveMatrisS1(augMatrixS1);
    for (i = 0; i < s1Msize.row_size; i++) {
        for (j = 0; j < s1Msize.col_size; j++) {
            printf("[%3d]", augMatrixS1[i][j]);
        }
        printf("\n" );
    }
    // BACKWARD SUBSITUTE
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkandSwapS1(int **matrix){
	int i,j,k = 0;
	int chg = s1Msize.row_size -1;
	int *temp;
	if(matrix[0][0] == 0){
		for (i = 0; i < s1Msize.row_size; i++) {
			if (matrix[i][0] != 0) {
				temp = matrix[0];
				matrix[0] = matrix[i];
				matrix[i] = temp;
                printf("ILK ELEMAN DEGISTI\n" );
				break;
			}
		}
	}
	for (i = 0; i < s1Msize.row_size; i++) {
		for (j = 0; j < s1Msize.col_size; j++) {
			if (matrix[i][j] == 0) {
				k++;
			}
			if ( k == s1Msize.row_size - 1) {
				temp = matrix[i];
				matrix[i] = matrix[chg];
				matrix[chg] = temp;
				printf("chg -> %d\n",chg );
                printf("SWAP OLDU\n" );

			}
		}
		k = 0;
	}
	//free(matrix[s1Msize.row_size])
}

void inp_S1MasterMatris(struct streetMap1 strt1[],int s1MasterMatris[5][9]){
    int i,j;
    int constantSum = 0;
    const char JUNCTION[4] = {'A','B','C','D'};
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
    for (i = 0; i < 4; i++) { //-1 +1 NEDEN TERS OLDU ?
        for (j = 0; j < 4; j++) {
            if (strt1[i].route[0] == 'I' && strt1[i].dens == -1 && strt1[i].name == strt1[j].name) {
                s1MasterMatris[4][j] = -1;
            }else if(strt1[i].route[1] == 'O' && strt1[i].dens == -1 && strt1[i].name == strt1[j].name) {
                s1MasterMatris[4][j] = 1;
            }
            if (strt1[i].route[1] == 'O' && strt1[i].dens != -1 && strt1[i].name == strt1[j].name) {
                constantSum -= strt1[i].dens;
            }else if (strt1[i].route[0] == 'I' && strt1[i].dens != -1 && strt1[i].name == strt1[j].name) {
                constantSum += strt1[i].dens;
            }
        }
    }
        s1MasterMatris[4][8] = constantSum;
}

void removeColumnS1(int **matrix, int col){
    int i,k;
    int tmp = col;
    s1Msize.col_size--;
    printf("silinecek sutun -> %d\n",col );
    for(i=0;i < s1Msize.row_size; i++){
        //move data to the left
        while(col < s1Msize.col_size){
            matrix[i][col]=matrix[i][col+1];
            col++;
        }
        col = tmp;
        matrix[i] = realloc(matrix[i], sizeof(int)*s1Msize.col_size);
    }
}

void print_strt1_MasterMatris(struct streetMap1 strt1[], int s1MasterMatris[5][9]){
    int i,j;
    for (i = 0; i < 8; i++) { //-> PRINT MASTER MATRIS FONK
        printf(" %4c ",strt1[i].name);
    }
    printf(" cons (PFONK)\n");
    for (i = 0; i < S1ROW; i++) {
        for (j = 0; j <  S1COL; j++) {
            printf("[%4d]",s1MasterMatris[i][j]);
        }
        printf("\n" );
    }
}

void get_strt1_Direction(struct streetMap1 strt1[],int strt1Size){
    //int *inputArray;
    //inputArray = init_S1_InputArray();
    int densValue[] = {20,10,20,10,10,30,40,20};
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
    //BU MANTIKTAN OTURU -XYZT- SIRALI DEGİ
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
        if (tmpc == 'x' || tmpc =='t') {
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

char * init_strt1_NullArray(struct streetMap1 strt1[],int nullCount,int *strt1emptyCol){
    int k = 0,i,j = 0;
    char *strt1Null = malloc(nullCount * sizeof(char));
    for (i = 0; i < 8; i++) {
        if (strt1[i].dens == -1) {
            strt1Null[k] = strt1[i].name;
            k++;
        }else{
            strt1emptyCol[j] = i;
            j++;
        }
    }
    return strt1Null;
}

void print_strt1Struct(struct streetMap1 strt1[]){
int i;
for (i = 0; i < 8; i++) {
    printf(">>> strt1[%d].name >>> %c, strt1.route %c -> %c  strt1.dens -> %d\n",i,strt1[i].name,strt1[i].route[0],strt1[i].route[1],strt1[i].dens );
    }
}
int get_NullCount_strt1(struct streetMap1 strt1[]){
    int i,nullCount = 0;
    for (i = 0; i < 8; i++) {
        if (strt1[i].dens == -1) {
            nullCount++;
        }
    }
    return nullCount;
}

void initMap() {
    printf("        x       \n" );
    printf("      /a b\\         \n" );
    printf("    t-     -y    \n" );
    printf("      \\d c/         \n" );
    printf("        z       \n" );
}
/*
void createInputFiles(){
FILE *inputFileS1;
FILE *inputFileS2;  //!! COK HATALI ILERIDE KULLANMA
if ((inputFileS1 = fopen(FILE_PATH_S1,"r") == NULL ) && ( (inputFileS2 = fopen(FILE_PATH_S2,"r")) == NULL)) {
printf("-> dosya bulunamadı yeniden oluşturulutor\n" );
inputFileS1 = fopen(FILE_PATH_S1,"w");
inputFileS2 = fopen(FILE_PATH_S1,"w");
int i;
srand(time(0));//rasgele sayi üretimi icin
int s1[8];
int s2[9];
for (i = 0; i < 8; i++) {
s1[i] = rand() % 100;
fprintf(inputFileS1, "%d ",s1[i] );
}
for (i = 0; i < 9; i++) {
s1[i] = rand() % 100;
fprintf(inputFileS2, "%d ",s2[i] );
}
fclose(inputFileS1);
fclose(inputFileS2);

}
//flclose seg fault veriyor , dosya kapanmış
//gözüküyor ama nasıl ? hocaya sor
printf("-> inputFileS1 v inputFileS1 oluştu veya zaten vardı :)\n");
}
*/
/*
int *init_S1_InputArray(){
FILE * inputFile = fopen(FILE_PATH_S1,"r");
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

*/
