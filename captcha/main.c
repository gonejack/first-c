#include <zconf.h>
#include <fcntl.h>
const int gifsize;
void captcha(unsigned char im[70 * 200], unsigned char l[6]);
void makegif(unsigned char im[70 * 200], unsigned char gif[gifsize]);

int main() {
  unsigned char l[6];
  unsigned char im[70 * 200];
  unsigned char gif[gifsize];

  captcha(im, l);
  makegif(im, gif);

  write(open("./abc.gif", O_WRONLY), gif, gifsize);
  //  write(1, gif, gifsize);
  write(2, l, 5);

  return 0;
}