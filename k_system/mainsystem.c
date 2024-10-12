void delay(int s);
unsigned char inb(unsigned short port);
void panic(char *msg);

void delay(int s){
    s *= 1000;
    for (s; s != 0; s--){
    }
}

unsigned char inb(unsigned short port){
    unsigned char ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

void panic(char *msg){
    while (1);
}
