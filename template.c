#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//
void help(void){
	printf("print help!\n");
}
//
int main(int argc, char *argv[])
{
    int ch;
    //opterr = 0;  //使getopt不行stderr输出错误信息
    while( (ch = getopt(argc, argv, "vb:c::")) != -1 )
    {
           switch(ch)
          {
               case 'v':
                   printf("option=v, optopt=%c, optarg=%s\n", optopt, optarg);
                   break;
              case 'b':
                   printf("option=b, optopt=%c, optarg=%s\n", optopt, optarg);
                   break;
              case 'c':
                   printf("option=c, optopt=%c, optarg=%s\n", optopt, optarg);
                   break;
              case '?':
                    //break;
              default:
                   help();
                   break;
           }
        //printf("argv[%d]=%s\n", optind, argv[optind]);
    }
    //printf("ch=-1, optind=%d\n", optind);   //看看最后optind的位置
    for(ch = optind; ch < argc; ch++)
         printf("-----argv[%d]=%s\n", ch, argv[ch]);
	return EXIT_SUCCESS;
}
