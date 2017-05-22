
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>




#include <dlfcn.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t,NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max-min) + min;
}


int main (int argc, char* argv[])
{
    int *array;
    void *ext_library;
    int numberOfElements;
    int i,j;
    double t = 0;
    int c;
    
    
    
    numberOfElements = atoi(argv[2]);
    int usl = atoi(argv[3]);
    printf("%d",usl);
    
    if ( numberOfElements > 32768 )
    {
	printf("\nMax 32768(2^18) el\n");
	return 0;
    }
    printf("%d",numberOfElements);
    array = (int*)malloc(numberOfElements*sizeof(int));
    //array = (int*)realloc(NULL, numberOfElements*sizeof(int)); //equvialent malloc
    switch(usl)
    {
	case 1:
	{
	    for( i = 0; i < numberOfElements; i++)
		{
		    array[i] = getrand(0,numberOfElements + 1);
		}
	break;
	}    
	case 2:
	{
	    for(i = 0 ; i < numberOfElements;i++)
		{
		    array[i] = getrand(0,numberOfElements + 1);
		}
	    
	    for ( i = 0; i < numberOfElements-1; i ++ )
		for ( j = numberOfElements-2; j >= i; j--)
		
		if ( array[j] > array[j+1] )
		    {
			c = array[j]; array[j] = array[j+1];
			array[j+1] = c;
		    }
	break;
	}
	case 3:
	{
	    for(i = 0 ; i < numberOfElements;i++)
		{
		    array[i] = getrand(0,numberOfElements + 1 );
		}
	    
	    for (i = 0; i < numberOfElements-1; i++)
		for (j = numberOfElements - 2; j >= i; j--)
		
		    if( array[j] < array[j+1] )
		    {
			c= array[j]; array[j] = array[j+1];
			array[j+1]=c;
		    }
	break;
	}
	default:
	{
	    printf("\n The third element = <1.rand, 2.grow,3.decr>\n");
	    return 0;
	    break;
	}
    }
    
    double (*powerfunc)(int *A,int n);
    
    ext_library = dlopen("/usr/lib64/sortlib.so",RTLD_LAZY);
    if(!ext_library)
    {
	fprintf(stderr,"dlopen() error : %s\n", dlerror());
	return 1;
    };
    
    
    powerfunc = dlsym(ext_library, argv[1]);
    
    
    printf("\n%s\n",argv[1]);
    for (i = 0 ; i < numberOfElements ; i++)
    {
	printf(" %d",array[i]);
    }
    printf("\n");
    
    
    t = wtime ();
    (*powerfunc)(array,numberOfElements);
    t = wtime() - t;
    
    
    for (i = 0 ; i < numberOfElements ; i++)
    {
	printf(" %d",array[i]);
    }
    printf("\n%lf",t);
    
    FILE *timer;
    
    if (argv[1] == "MergeSort")
    {
	 timer = fopen("time.txt","a");
    }
    else
    {
	timer = fopen("time1.txt","a");
    }
    if (!timer)
	{
	    printf("Error: time.txt doesn't exists\n");
	    return 0;
	}
    fprintf(timer,"%d\t%lf\n",numberOfElements,t);
    fclose(timer);
    
    free(array);
    dlclose(ext_library);
    
    
}
