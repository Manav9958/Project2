#include <sys/types.h>
#include <unistd.h>
int main( void ) { int x = 0;
   x++;
   if (fork( ) > 0) {
      x++;
      if (fork( ) > 0) {
x++;
         printf( "Hello\n" );
      }
x--; } else {
      if (fork( ) == 0) {
         x--;
}
      printf( "Goodbye\n" );
   }
   printf( "x = %d\n", x );
return 0; }