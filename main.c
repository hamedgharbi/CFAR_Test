#include <stdio.h>
#include <stdlib.h>

typedef signed char    sint8;               /*        -128 .. +127            */
typedef unsigned char  uint8;               /*           0 .. 255             */
typedef signed short   sint16;              /*      -32768 .. +32767          */
typedef unsigned short uint16;              /*           0 .. 65535           */
typedef signed long    sint32;              /* -2147483648 .. +2147483647     */
typedef long unsigned int  uint32;              /*           0 .. 4294967295      */
typedef float          float32;
typedef double         float64;
#define	FFT_NUM_CHIRPS	128
#define	FFT_NUM_SAMPLES	128
#define	bTrue			1
#define	bFalse			0
#define	bool_t			int
#define	uint8_t			uint8
#define	uint16_t		uint16
#define	int32_t			int
#define	int16_t			int
#define	magnitude_t		uint32
#define	fft_value_t		short
magnitude_t os_cfar (magnitude_t* inAddr,uint32 N_Cell,uint16_t inc,uint16_t num,uint16_t i,uint32 sFactor, magnitude_t* BAddr);
void shell_sort (magnitude_t *window, int len);

uint32 sFactor=1;
uint32 N_Cell=4;

int main()
{
    uint16_t num=64;
    int i;
    uint16_t inc=8;
    magnitude_t inAddr[num];
    for(i=0;i<num;i++){
        *(inAddr+i)=i;
    }
    for(i=0;i<num;i++){printf("%lu ",*(inAddr+i)); }

    magnitude_t S;
    S = os_cfar(inAddr+8*5,N_Cell,inc,num/8,4,sFactor,inAddr);
    printf("\n S = %lu \n",S);
    printf("%lu \n", *inAddr);
    for(i=0;i<num;i++){printf("%lu ",*(inAddr+i)); }
    return 0;
}
magnitude_t os_cfar (magnitude_t* inAddr,uint32 N_Cell,uint16_t inc,uint16_t num,uint16_t i,uint32 sFactor, magnitude_t* BAddr){
	magnitude_t z;
	magnitude_t window[N_Cell];
	uint16_t j;
	printf(" \n Cell test = %lu \n ",*(inAddr+i));
	uint32 K=(int)((N_Cell*3)/4);
    printf(" \n K = %lu \n ",K);
	// fill cells window
	if (inAddr+i-N_Cell/2*inc<BAddr){
		for(j=0;j<N_Cell;j++){
                window[j] = *(inAddr + i +(j+1)*inc);
               printf(" \n windodw [%d] = %lu \n ",j,*(inAddr + i +(j+1)*inc));

		}
	}
	else if (inAddr+i+N_Cell/2*inc>=BAddr+num*num*inc){
		for(j=0;j<N_Cell;j++){
			window[j]= *(inAddr +i-((j+1)*inc));
            printf(" \n windodw [%d] = %lu \n ",j,*(inAddr + i -(j+1)*inc));
		}

	}
	else{
		for(j=0;j<N_Cell/2;j++){
			window[j]= *(inAddr +i-(j+1)*inc);
		}
		for(j=N_Cell/2;j<N_Cell;j++){
			window[j]= *(inAddr +i+ (j-N_Cell/2+1)*inc);
		}
	}
	// sort window
	//qsort(window, sizeof(window)/sizeof(*window), sizeof(*window), comp);
	int k;
    printf("\n sorted window : ");
	for(k=0;k<N_Cell;k++){printf(" %lu ",window[k]);}
	shell_sort(window,N_Cell);

        printf("\n sorted window : ");
	for(k=0;k<N_Cell;k++){printf(" %lu ",window[k]);}
	// threshold
	z=window[K-1]*sFactor;
return z;

}
void shell_sort (magnitude_t *window, int len) {
    int h, i, j;
    magnitude_t t;
    for (h = len; h /= 2;) {
        for (i = h; i < len; i++) {
            t = window[i];
            for (j = i; j >= h && t < window[j - h]; j -= h) {
                window[j] = window[j - h];
            }
            window[j] = t;
        }
    }
}
