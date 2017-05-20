

#include <stdio.h>
#include <stdlib.h>





#include <dlfcn.h>

int main (int argc, char* argv[])
{
    int array[] = {6,2,3,1,9};
    void *ext_library;
    int numberOfElements;
    int i;
    numberOfElements = sizeof(array)/sizeof(array[0]);
    double (*powerfunc)(int *A,int n);
    
    ext_library = dlopen("/usr/lib64/libfsdyn.so",RTLD_LAZY);
    if(!ext_library)
    {
	fprintf(stderr,"dlopen() error : %s\n", dlerror());
	return 1;
    };
    printf("yo");
    powerfunc = dlsym(ext_library, argv[1]);
    printf("//Sort this\n");
    for (i = 0 ; i < numberOfElements ; i++)
    {
	printf("%d",array[i]);
    }
    printf("\n");
    
    (*powerfunc)(array,numberOfElements);
    for (i = 0 ; i < numberOfElements ; i++)
    {
	printf("%d",array[i]);
    }
    dlclose(ext_library);
    
    
}