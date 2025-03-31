#include <dos.h>
#include <stdio.h>

// gotoxy(): coloca el cursor en una posición determinada
void gotoxy(int x, int y) {
    union REGS inregs, outregs;

    inregs.h.dh = y;          
    inregs.h.dl = x;          
    inregs.h.bh = 0;          
    inregs.h.ah = 0x02;       

    int86(0x10, &inregs, &outregs);
}


// setcursortype(): fijar el aspecto del cursor
void setcursortype(int type) {
    union REGS inregs, outregs;

    inregs.h.ah = 0x01;       

    switch (type) {
        case 0:  // INVISIBLE
            inregs.h.ch = 0x20; 
            inregs.h.cl = 0x00;
            break;
        case 1:  // NORMAL
            inregs.h.ch = 0x0C; 
            inregs.h.cl = 0x0D;
            break;
        case 2:  // THICK
            inregs.h.ch = 0x00; 
            inregs.h.cl = 0x07;
            break;
        default:
            return; 
    }

    int86(0x10, &inregs, &outregs);
}

// setvideomode(): fija el modo de video deseado
void setvideomode(int mode) {
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;      
    inregs.h.al = mode;      

    int86(0x10, &inregs, &outregs);
}

// getvideomode(): obtiene el modo de video actual
int getvideomode() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x0F;     

    int86(0x10, &inregs, &outregs);

    return outregs.h.al;    
}

unsigned char currentTextColor = 7; // Color del primer plano por defecto (blanco)
// textcolor(): modifica el color de primer plano
void textcolor(int color) {
    if (color >= 0 && color <= 15) { 
        currentTextColor = color; 
    }
}

unsigned char currentBackgroundColor = 0; // Color de fondo por defecto (negro)
// textbackground(): modifica el color de fondo
void textbackground(int color) {
    if (color >= 0 && color <= 15) {
        currentBackgroundColor = color; 
    }
}

// clrscr(): borra toda la pantalla
void clrscr() {
    
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    gotoxy(0, 0);
}

// cputchar(): escribe un carácter en pantalla con el color indicado actualmente
void cputchar(char c) {
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = (currentTextColor << 4) | currentBackgroundColor;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;

	int86(0x10, &inregs, &outregs);
}

// getche(): obtiene un carácter de teclado y lo muestra en pantalla
int getche() {
    union REGS inregs, outregs;
    int character;
    inregs.h.ah = 0x01;      

    int86(0x21, &inregs, &outregs);
    character = outregs.h.al;

    return character;    
}

// pixel(): dibujar un pixel en modo gráfico
void pixel(int x, int y, unsigned char color) {
    union REGS inregs, outregs;

    inregs.h.ah = 0x0C;     
    inregs.h.al = color;      
    inregs.x.cx = x;          
    inregs.x.dx = y;        
    inregs.h.bh = 0;          

    int86(0x10, &inregs, &outregs);
}

// stop(): función para pausas en el main
void stop() {
 union REGS inregs, outregs;
 inregs.h.ah = 0x00;
 int86(0x16, &inregs, &outregs);
}

// drawBox(): dibuja un cuadrado en la pantalla
void drawBox(int x1, int y1, int x2, int y2) {
    int i;

    for (i = x1; i <= x2; ++i) {
        gotoxy(i, y1);
        cputchar(' ');
        gotoxy(i, y2);
        cputchar(' ');
    }
    
    for (i = y1; i <= y2; ++i) {
        gotoxy(x1, i);
        cputchar(' ');
        gotoxy(x2, i);
        cputchar(' ');
    }
}

// drawLine(): dibuja una línea en la pantalla
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    int x, y, i;
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    
    x = x1;
    y = y1;
    for (i = 0; i <= steps; i++) {
        gotoxy(x, y);
        cputchar('x'); 
        x += (int)xIncrement;
        y += (int)yIncrement;
    }
}

//drawAssciiArt(): dibuja un arte ASCII en la pantalla
void drawAssciiArt() {
    int option;
    printf("1. Perro\n");
    printf("2. Gato\n");
    printf("3. Pato\n");
    printf("Ingrese un numero del 1 al 3: ");
    scanf("%d", &option);
    getchar(); 

    switch(option) {
        case 1:
            printf("Rombo: \n");
            printf("  / \\ \n");
            printf(" / _ \\ \n");
            printf("| / \\ | \n");
            printf("| \\_/ | \n");
            printf(" \\   / \n");
            printf("  \\_/ \n");
            break;

        case 2:
            printf("Gato: \n");
            printf(" /\\_/\\ \n");
            printf("( o.o ) \n");
            printf(" > ^ < \n");
            break;

        case 3:
            printf("Pato: \n");
            printf("  __ \n");
            printf("<(o ) \n");
            printf("  || \n");
            break;

        default:
            printf("Opción no válida. Por favor, ingrese un número del 1 al 3.\n");
            break;
    }

}

int main() {
    int option;
    int aux;
    printf("Ejercicios de la practica 1 Jorge y Carlos: \n");
    printf("1. gotoxy(10,10)\n");
    printf("2. setcursortype()\n");
    printf("3. setvideomode() y getvideomode()\n");
    printf("4. textcolor(), textbackground(), cputchar() y getche()\n");
    printf("5. pixel()\n");
    printf("6. drawBox()\n");
    printf("7. drawLine()\n");
    printf("8. drawAssciiArt()\n");
    printf("Ingrese un numero del 1 al 8: ");
    scanf("%d", &option);
    getchar(); // Limpiar el buffer de entrada

    switch(option) {
        case 1:
            printf("Ejercicio 1: gotoxy(10,10): \n");
            gotoxy(10, 10);
            stop();
            break;

        case 2:
            printf("Ejercicio 2: setcursortype(): \n");
            printf("Cursor invisible: \n");
            setcursortype(0);
            stop();
            printf("Cursor grueso: \n");
            setcursortype(2);
            stop();
            printf("Cursor normal: \n");
            setcursortype(1);
            stop();
            break;

        case 3:
            printf("Ejercicios 3 y 4: setvideomode() y getvideomode(): \n");
            printf("Modo de video actual: %d\n", getvideomode());
            setvideomode(0x04);
            printf("Modo de video actual: %d\n", getvideomode());
            stop();
            break;

        case 4:
            printf("Ejercicios 5, 6, 7, 8 y 9: textcolor(), textbackground(), clrscr(), cputchar() y getche(): \n");
            printf("Introduce el caracter:");
            
            aux = getche();
            printf("\n");
            
            stop();
            printf("Color de texto: 1 (azul oscuro) y color de fondo: 10 (verde claro)\n");
            textcolor(10); 
            textbackground(1); 

            printf("Caracter introducido, con cambios: ");
            cputchar((char)aux);
            stop();
               
            clrscr();
            stop();
            break;

        case 5:
            printf("Ejercicio 10: pixel(): \n");
            setvideomode(0x04);
            printf("Dibujando pixeles...\n");
            pixel(10, 10, 1);
            stop();
            break;
        
        case 6:
            clrscr();
            printf("Ejercicio 11: drawBox(): \n");
            textcolor(10); 
            textbackground(1);
            drawBox(5, 5, 15, 15);
            stop();
            stop();
            stop();
            break;
        
        case 7:
            clrscr();
            printf("Ejercicio 12: drawLine(): \n");
            textcolor(10); 
            textbackground(1);
            setvideomode(0x04);
            printf("Dibujando lineas...\n");
            drawLine(5, 5, 15, 15);
            stop();
            stop();
            stop();
            stop();
            stop();
            break;
        
        case 8:
            clrscr();        
            printf("Ejercicio 13: drawAssciiArt(): \n");
            textcolor(10); 
            textbackground(1);
            drawAssciiArt();
            stop();
            stop();
            stop();
            break;

        default:
            printf("Opción no válida. Por favor, ingrese un número del 1 al 5.\n");
            break;
    }
    return 0;
}