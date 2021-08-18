#include <stdlib.h>
#include "snowflake.h"

void usage(FILE *fp, int rc)
{
    fprintf(fp, "Use the snowflake algorithm to generate distributed id.\n");
    fprintf(fp, "Example: ./snowflake nums");
    exit(rc);
}


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        usage(stdout, 0);
    }

    int nloop = atoi(argv[1]);
    if(nloop < 1)
    {
        fprintf(stderr, "ERROR: the value of nums must bigger than 1.\n");
        exit(1);
    }

    CSnowFlakeGenerator *pSnowFlakeGenerator = new CSnowFlakeGenerator(5,5,1,1);
    if(NULL == pSnowFlakeGenerator)
    {    
        fprintf(stderr, "ERROR: new object fail.\n");
        exit(1);
    }


    while(nloop--)
    {
        fprintf(stdout, "Display: the id is %lu.\n", pSnowFlakeGenerator->GetNextId());
    }

    delete pSnowFlakeGenerator;
    pSnowFlakeGenerator = NULL;

    return 0;
}
