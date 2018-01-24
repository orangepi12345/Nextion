////////////////////////////////////////////////////////////////////
//Archivo de cabecera para el uso del m�dulo USART PIC con  XC8  ///
////////////////////////////////////////////////////////////////////

#ifndef USART_H
#define	USART_H
 
void UART_Init(unsigned int  spbrg);                                                   
char getch(void);
void UART_Read_Text(char *Output, unsigned int length);
void putch(char data);
void UART_Write_Text(char *text);
char UART_TX_Empty(void);
char UART_Data_Ready();
 
////////////////////////////////////////////////////////////////////
//inicializaci�n del m�dulo USART PIC modo as�ncrono, a 8bits    ///
////////////////////////////////////////////////////////////////////
void  UART_Init(unsigned int spbrg){
    BRG16 =1;
    BRGH = 1; 
    SPBRG = spbrg;                                                              // Writing SPBRG Register
    SPBRGH= spbrg>>8;
    SYNC = 0;                                                                   // Setting Asynchronous Mode, ie UART
    SPEN = 1;                                                                   // Enables Serial Port
    TRISC7 = 1;                                                                 // As Prescribed in Datasheet
    TRISC6 = 1;                                                                 // As Prescribed in Datasheet
    CREN = 1;                                                                   // Enables Continuous Reception
    TXEN = 1;                                                                   // Enables Transmission
}
 
/////////////////////////////////////////////////////////////////////
//recepci�n de un car�cter del m�dulo USART PIC modo as�ncrono    ///
/////////////////////////////////////////////////////////////////////
char getch(void){
    while(!RCIF);
    return RCREG;
}
/////////////////////////////////////////////////////////////////////
//leer cadena de caracteres con el m�dulo USART PIC modo as�ncrono///
/////////////////////////////////////////////////////////////////////
void UART_Read_Text(char *Output, unsigned int length){
    unsigned int x;
    for(x =0 ; x <length; x++){
        Output[x] = getch();
    }
}
/////////////////////////////////////////////////////////////////////
//transmisi�n de un car�cter del m�dulo USART PIC modo as�ncrono  ///
/////////////////////////////////////////////////////////////////////
void putch(char data){
    while(!TRMT);                                                               // mientras el registro TSR est� lleno espera
    TXREG = data;                                                               // cuando el el registro TSR est� vaci� se envi� el car�cter
}

/////////////////////////////////////////////////////////////////////
//transmisi�n de un cadena de caracteres del m�dulo USART PIC modo as�ncrono
///////////////////////////////////////////////////////////////////// 
void UART_Write_Text(char *text){
    while(*text){
        putch(*text++);
    }
}

/////////////////////////////////////////////////////////////////////
// Comprobaci�n del registro de transmisi�n                       ///
/////////////////////////////////////////////////////////////////////
char UART_TX_Empty(void){
    return TRMT;
}

/////////////////////////////////////////////////////////////////////
// Comprobamos si podemos leer                                    ///
/////////////////////////////////////////////////////////////////////
char UART_Data_Ready(){
  return RCIF;
}

void UART_Num_Ascii(unsigned int num){
unsigned int  valor = num;
        if (valor >9999){
            putch((num/10000)+0x30);                                            // cinco d�gitos
            num=num%10000;
        }
        if (valor >999){  
            putch((num/1000)+0x30);                                             // cuatro d�gitos
            num=num%1000;
        }
        if (valor >99){
            putch((num/100)+0x30);                                              // tres d�gitos
            num=num%100;
        }
    if (valor >9)putch((num/10)+0x30);                                          // dos d�gitos
    putch((num%10)+0x30);                                                       // un d�gito
}
#endif	/* USART_H */


