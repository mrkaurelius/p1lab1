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

void initMapS1();
void get_strt1_Direction(struct streetMap1 strt1[],int strt1Size);
void print_strt1_MasterMatris(struct streetMap1 strt1[], int s1MasterMatris[5][9]);
void print_strt1Struct(struct streetMap1 strt1[]);
int get_NullCount_strt1(struct streetMap1 strt1[]);
void inp_S1MasterMatris(struct streetMap1 strt1[],int s1MasterMatris[5][9]);
char * init_strt1_NullArray(struct streetMap1 strt1[],int nullCount,int *strt1emptyCol);
void removeColumnS1(int **matrix, int col);
//NEDEN 2 KERE SWAP OLUYOR -CALISMAYA ETKISI YOK-
void checkandSwapS1(int **matrix);
void printAugMarisS1(int **matrix,int nullCount,char strt1Null[]);
void solveMatrisS1(int **matrix);

void initMapS2();
void get_strt2_Direction(struct streetMap2 strt2[],int strt2Size);
void print_strt2_MasterMatris(struct streetMap2 strt2[], int s2MasterMatris[5][10]);
void print_strt2Struct(struct streetMap2 strt2[]);
int get_NullCount_strt2(struct streetMap2 strt2[]);
void inp_S2MasterMatris(struct streetMap2 strt2[],int s2MasterMatris[5][10]);
char * init_strt2_NullArray(struct streetMap2 strt2[],int nullCount,int *strt2emptyCol);
void removeColumnS2(int **matrix, int col);
//NEDEN 2 KERE SWAP OLUYOR -CALISMAYA ETKISI YOK-
void checkandSwapS2(int **matrix);
void printAugMarisS2(int **matrix,int nullCount,char strt2Null[]);
void solveMatrisS2(int **matrix);



int main() {
    //YOGUNLUKLARI ALDIRAN FONKSYON YAP
    //0 BASLANGICLI SATIRLARI SWAP ET ??
    //TUM GIRIS CIKISA IHTIYAC VARMI ?
    printf("harita1 v harita2\n" );
    int chc;
    scanf("%d",&chc );
    if (chc == 1) {
            int strt1Size = 8;
            //int densValue[] = {20,10,20,10,10,30,40,20};
            // 4 BILINMEYENDE VE  SONRASINDA PATLIYOR
            int densValue[] = {-1,10,-1,-1,10,30,40,20};
            int i,j,k = 0,nullCount = 0;
            int s1MasterMatris[5][9];
            for (i = 0; i < S1ROW; i++) {
                for (j = 0; j < S1COL; j++) {
                    s1MasterMatris[i][j] = 0;
                }
            }
            initMapS1();
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
            //void printAugMarisS1(int **matrix,int nullCount,char strt1Null[]) {
            printAugMarisS1(augMatrixS1,nullCount,strt1Null);
            checkandSwapS1(augMatrixS1);
            solveMatrisS1(augMatrixS1);
            printAugMarisS1(augMatrixS1,nullCount,strt1Null);
            // BACKWARD SUBSITUTE
    }
    if (chc == 2) {
        int strt2Size = 9;
        //MAP 2 densValue[] = {10,10,10,10||,10,20,40,30,10};
        // 4 BILINMEYENDE VE  SONRASINDA PATLIYOR
        int densValue[] = {-1,10,-1,10,-1,20,40,30,10};
        int i,j,k = 0,nullCount = 0;
        int s2MasterMatris[5][10];
        for (i = 0; i < S2ROW; i++) {
            for (j = 0; j < S2COL; j++) {
                s2MasterMatris[i][j] = 0;
            }
        }
        initMapS2();
        get_strt2_Direction(strt2,strt2Size);    // Legal giriş bekleniyor
        //
        for (i = 0; i < 9; i++) {
            strt2[i].dens = densValue[i];
        }
        nullCount = get_NullCount_strt2(strt2);
        char *strt2Null = malloc(nullCount * sizeof(char));
        int *strt2emptyCol =malloc((8 - nullCount) * sizeof(int));
        strt2Null =  init_strt2_NullArray(strt2,nullCount,strt2emptyCol);
        print_strt2Struct(strt2);
        printf("DEBUG\n" );
        for (i = 0; i < nullCount; i++) {
            printf(">sNull -> %c,",strt2Null[i]); //DEBUGP
        }
        printf("\n" );

        for (i = 0; i < (9 - nullCount); i++) {
            printf(">eCol -> %d,",strt2emptyCol[i]); //DEBUGP
        }
        printf("\n" );
        inp_S2MasterMatris(strt2,s2MasterMatris);
        print_strt2_MasterMatris(strt2,s2MasterMatris);

        int **augMatrixS2= (int **)malloc(S2ROW * sizeof(int*));
        for (i = 0; i < S2ROW; i++) augMatrixS2[i] =(int *)malloc(S2COL * sizeof(int)); //AH ANAM VAY ANAM VAYY
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                augMatrixS2[i][j] = (int)s2MasterMatris[i][j];
            }
        }

        s2Msize.row_size = S2ROW;
        s2Msize.col_size = S2COL;
        for (i = 0; i < (9 - nullCount); i++) {
            removeColumnS2(augMatrixS2,strt2emptyCol[9 - nullCount - i - 1]); //MATRIS TERSETEN SAPLAR
        }
        //swap zero leading row with another row until leading is 1

        printf("matris boyutu -> %d, %d \n",s2Msize.row_size,s2Msize.col_size );
        //void printAugMarisS2(int **matrix,int nullCount,char strt2Null[]) {
        printAugMarisS2(augMatrixS2,nullCount,strt2Null);
        checkandSwapS2(augMatrixS2);
        printAugMarisS2(augMatrixS2,nullCount,strt2Null);
        solveMatrisS2(augMatrixS2);
        printAugMarisS2(augMatrixS2,nullCount,strt2Null);
        // BACKWARD SUBSITUTE
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    printf(" cons \n");
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

void initMapS1() {
    printf("        x       \n" );
    printf("      /a b\\         \n" );
    printf("    t-     -y    \n" );
    printf("      \\d c/         \n" );
    printf("        z       \n" );
}

void printAugMarisS1(int **matrix,int nullCount,char strt1Null[]){
    int i,j;
    for (i = 0; i < nullCount; i++) { //-> PRINT MASTER MATRIS FONK
        printf(" %4c ",strt1Null[i]);
    }
    printf(" cons \n");
    for (i = 0; i < s1Msize.row_size; i++) {
        for (j = 0; j < s1Msize.col_size; j++) {
            printf(" %4d ", matrix[i][j]);
        }
        printf("\n" );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void solveMatrisS2(int **matrix) {
	int i;
	int rix,iix;
	int lead = 0;
    //s2Msize.row_size = S2ROW;
    //s2Msize.col_size = S2COL;

	for (rix = 0; rix < s2Msize.row_size; rix++) {
		printf("lead -> %d\n",lead );
		if (lead >= s2Msize.col_size) {
			printf("> rref bitti\n" );
			break;
		}
		iix = rix;
		while (matrix[iix,lead] == 0) { // pivotun altı sıfırmı onu kontrol ediyor
			iix++;
			if (iix == s2Msize.row_size) { // pivottan emin olduktan sonra aynı satıra dön
				iix = rix;
				lead++;
				if (lead >= s2Msize.row_size) {
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
				for (i = 0; i < s2Msize.col_size ; i++) {
					matrix[rix][i] = matrix[rix][i] / a;
				}
				printf("normalize den sonra\n" );
			}
			//normalize row end

			for (iix = 0; iix < s2Msize.row_size; iix++) {
				if ( iix != rix ) {
					//MulandAd START
					int ix;
					int lv;
					lv = matrix[iix][lead];
					for (ix = 0; ix < s2Msize.col_size; ix++) {
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

void checkandSwapS2(int **matrix){
	int i,j,k = 0;
	int chg = s2Msize.row_size -1;
	int *temp;
	if(matrix[0][0] == 0){
		for (i = 0; i < s2Msize.row_size; i++) {
			if (matrix[i][0] != 0) {
				temp = matrix[0];
				matrix[0] = matrix[i];
				matrix[i] = temp;
                printf("ILK ELEMAN DEGISTI\n" );
				break;
			}
		}
	}
	for (i = 0; i < s2Msize.row_size; i++) {
		for (j = 0; j < s2Msize.col_size; j++) {
			if (matrix[i][j] == 0) {
				k++;
			}
			if ( k == s2Msize.row_size - 1) {
				temp = matrix[i];
				matrix[i] = matrix[chg];
				matrix[chg] = temp;
				printf("chg -> %d\n",chg );
                printf("SWAP OLDU\n" );

			}
		}
		k = 0;
	}
	//free(matrix[s2Msize.row_size])
}

void inp_S2MasterMatris(struct streetMap2 strt2[],int s2MasterMatris[5][10]){
    int i,j;
    int constantSum = 0;
    const char JUNCTION[4] = {'A','B','C','D'};
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 9; j++) {
            if (strt2[j].route[1] == JUNCTION[i] && strt2[j].dens == -1) {
                s2MasterMatris[i][j] = 1;
            }else if (strt2[j].route[0] == JUNCTION[i] && strt2[j].dens == -1){
                s2MasterMatris[i][j] = -1;
            }
            if (strt2[j].dens != -1) {
                if (strt2[j].route[0] == JUNCTION[i]) {
                    constantSum += strt2[j].dens;
                }else if (strt2[j].route[1] == JUNCTION[i]) {
                    constantSum -= strt2[j].dens;
                }
            }
        }
        s2MasterMatris[i][9] = constantSum;
        constantSum = 0;
        }
    for (i = 0; i < 4; i++) { //-1 +1 NEDEN TERS OLDU ?
        for (j = 0; j < 4; j++) {
            if (strt2[i].route[0] == 'I' && strt2[i].dens == -1 && strt2[i].name == strt2[j].name) {
                s2MasterMatris[4][j] = -1;
            }else if(strt2[i].route[1] == 'O' && strt2[i].dens == -1 && strt2[i].name == strt2[j].name) {
                s2MasterMatris[4][j] = 1;
            }
            if (strt2[i].route[1] == 'O' && strt2[i].dens != -1 && strt2[i].name == strt2[j].name) {
                constantSum -= strt2[i].dens;
            }else if (strt2[i].route[0] == 'I' && strt2[i].dens != -1 && strt2[i].name == strt2[j].name) {
                constantSum += strt2[i].dens;
            }
        }
    }
        s2MasterMatris[4][9] = constantSum;
}

void removeColumnS2(int **matrix, int col){
    int i,k;
    int tmp = col;
    s2Msize.col_size--;
    printf("silinecek sutun -> %d\n",col );
    for(i=0;i < s2Msize.row_size; i++){
        //move data to the left
        while(col < s2Msize.col_size){
            matrix[i][col]=matrix[i][col+1];
            col++;
        }
        col = tmp;
        matrix[i] = realloc(matrix[i], sizeof(int)*s2Msize.col_size);
    }
}

void print_strt2_MasterMatris(struct streetMap2 strt2[], int s2MasterMatris[5][10]){
    int i,j;
    for (i = 0; i < 8; i++) { //-> PRINT MASTER MATRIS FONK
        printf(" %4c ",strt2[i].name);
    }
    printf(" cons \n");
    for (i = 0; i < S2ROW; i++) {
        for (j = 0; j <  S2COL; j++) {
            printf("[%4d]",s2MasterMatris[i][j]);
        }
        printf("\n" );
    }
}

void get_strt2_Direction(struct streetMap2 strt2[],int strt2Size){
    //int *inputArray;
    //inputArray = init_S2_InputArray();
    int densValue[] = {20,10,20,10,10,30,40,20};
    int i,j,nullCount = 0;
    const char JUNCTION[4] = {'A','B','C','D'};
    const char allstrt2[8] = {'x','y','z','t','a','b','c','d'};
    const char outerstrt2[4] = {'x','y','z','t'};
    const char innerstrt2[4] = {'a','b','c','d'};
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
    strt2[0].name = inpStr[0];
    strt2[1].name = inpStr[1];
    strt2[2].name = outStr[0];
    strt2[3].name = outStr[1];
    strt2[0].route[0] = 'I';
    strt2[1].route[0] = 'I';
    strt2[2].route[1] = 'O';
    strt2[3].route[1] = 'O';
    //ALLAHIN INAYETI START
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (strt2[i].name == outerstrt2[j]) {
                strt2[i].route[1] = JUNCTION[j];
            }
        }
    }
    for (i = 2; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (strt2[i].name == outerstrt2[j]) {
                strt2[i].route[0] = JUNCTION[j];
            }
        }
    }

    while(1){
        char tmpc;
        printf("\n-> caddlerin yönlerini seçin \n" );
        printf("-> a caddesinin yönünü seçin (x,t): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'x' || tmpc =='t') {
            strt2[4].name = 'a';
            if (tmpc == 'x') {
                strt2[4].route[0] = 'D';
                strt2[4].route[1] = 'A';
            }else{
                strt2[4].route[0] = 'A';
                strt2[4].route[1] = 'D';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> b caddesinin yönünü seçin (y,x): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'x' || tmpc =='y') {
            strt2[5].name = 'b';
            if (tmpc == 'x') {
                strt2[5].route[0] = 'B';
                strt2[5].route[1] = 'A';
            }
            else{
                strt2[5].route[0] = 'A';
                strt2[5].route[1] = 'B';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> c caddesinin yönünü seçin (y,z): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'z' || tmpc =='y') {
            strt2[6].name = 'c';
            if (tmpc == 'z') {
                strt2[6].route[0] = 'B';
                strt2[6].route[1] = 'C';
            }
            else{
                strt2[6].route[0] = 'C';
                strt2[6].route[1] = 'B';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> d caddesinin yönünü seçin (z,t): " );
        scanf(" %c",&tmpc );
        if (tmpc == 't' || tmpc =='z') {
            strt2[7].name = 'd';
            if (tmpc == 't') {
                strt2[7].route[0] = 'C';
                strt2[7].route[1] = 'D';
            }
            else{
                strt2[7].route[0] = 'D';// COMMIT NOTU HATA DUZELTILDI
                strt2[7].route[1] = 'C';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        printf("-> e caddesinin yönünü seçin (y,t): " );
        scanf(" %c",&tmpc );
        if (tmpc == 'y' || tmpc =='t') {
            strt2[8].name = 'e';
            if (tmpc == 'y') {
                strt2[8].route[0] = 'D';
                strt2[8].route[1] = 'B';
            }
            else{
                strt2[8].route[0] = 'B';// COMMIT NOTU HATA DUZELTILDI
                strt2[8].route[1] = 'D';
            }
        }else{
            printf("-> hatalı giriş yaptınız\n" );
            continue;
        }
        break;
    }
}

char * init_strt2_NullArray(struct streetMap2 strt2[],int nullCount,int *strt2emptyCol){
    int k = 0,i,j = 0;
    char *strt2Null = malloc(nullCount * sizeof(char));
    for (i = 0; i < 9; i++) {
        if (strt2[i].dens == -1) {
            strt2Null[k] = strt2[i].name;
            k++;
        }else{
            strt2emptyCol[j] = i;
            j++;
        }
    }
    return strt2Null;
}

void print_strt2Struct(struct streetMap2 strt2[]){
int i;
for (i = 0; i < 8; i++) {
    printf(">>> strt2[%d].name >>> %c, strt2.route %c -> %c  strt2.dens -> %d\n",i,strt2[i].name,strt2[i].route[0],strt2[i].route[1],strt2[i].dens );
    }
}
int get_NullCount_strt2(struct streetMap2 strt2[]){
    int i,nullCount = 0;
    for (i = 0; i < 9; i++) {
        if (strt2[i].dens == -1) {
            nullCount++;
        }
    }
    return nullCount;
}

void initMapS2() {
    printf("        x       \n" );
    printf("      /a b\\         \n" );
    printf("    t-  e   -y    \n" );
    printf("      \\d c/         \n" );
    printf("        z       \n" );
}

void printAugMarisS2(int **matrix,int nullCount,char strt2Null[]){
    int i,j;
    for (i = 0; i < nullCount; i++) { //-> PRINT MASTER MATRIS FONK
        printf(" %4c ",strt2Null[i]);
    }
    printf(" cons \n");
    for (i = 0; i < s2Msize.row_size; i++) {
        for (j = 0; j < s2Msize.col_size; j++) {
            printf(" %4d ", matrix[i][j]);
        }
        printf("\n" );
    }
}
