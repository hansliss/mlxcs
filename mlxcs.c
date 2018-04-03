#include<stdio.h>
#include<string.h>

int adjustck(int ck) {
  return ck + 255 * ((ck > 255)?-1:0);
}

int initck(int ad) {
  int ck = (int)ad/256;
  return adjustck(ad - 254 * ck + 255*((ck > 127)?-1:0));
}

int addtock(int a, int ck) {
  return adjustck(2 * ck + 255 * ((ck > 127)?-1:0) + a);
}

int main(int argc, char *argv[]) {
  char inbuf[1024];
  int ad, a[9], i;
  while (fgets(inbuf, sizeof(inbuf), stdin) != NULL) {
    while (strlen(inbuf) && inbuf[strlen(inbuf)-1] == '\n') {
      inbuf[strlen(inbuf)-1] = '\0';
    }
    if (strlen(inbuf)) {
      if (sscanf(inbuf, "%04X:%02X %02X %02X %02X %02X %02X %02X %02X %02X",
		 &ad,
		 &(a[0]),
		 &(a[1]),
		 &(a[2]),
		 &(a[3]),
		 &(a[4]),
		 &(a[5]),
		 &(a[6]),
		 &(a[7]),
		 &(a[8])) != 10) {
	printf("Syntax error: \"%s\"\n", inbuf);
	return -1;
      }
      fprintf(stderr, "Checking \"%s\"\n", inbuf);
      int ck = initck(ad);
      for (i=0; i<8; i++) {
	ck = addtock(a[i], ck);
      }
      if (ck != a[8]) {
	printf("Checksum error: \"%s\"\n", inbuf);
	return -1;
      }
    }
  }
  printf("OK\n");
  return 0;
}
