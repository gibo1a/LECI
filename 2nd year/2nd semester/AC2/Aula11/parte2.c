#include <detpic32.h>

typedef struct{
    char mem[100]; // Storage area
    int nchar; // Number of characters to be transmitted
    int posrd; // Position of the next character to be transmitted
} t_buf;

volatile t_buf txbuf;

void putstrInt(char *s){    
    while(txbuf.nchar > 0); // Wait while the buffer is not empty
    // Copy all characters of the string "s" to the buffer, and update
    // "nchar"
    char* str = s;
    while(*str != '\0'){
        txbuf.mem[txbuf.nchar] = *str;
        str++;
        txbuf.nchar++;
    }
    txbuf.posrd = 0;
    // Initialize "posrd" variable with 0
    // Enable UART2 Tx interrupts
    IEC1bits.U2TXIE = 1;
}

void _int_(32) isr_uart2(void){
    if (IFS1bits.U2TXIF == 1){   
        if(txbuf.nchar > 0) { 
            U2TXREG = txbuf.mem[txbuf.posrd];    // At least one character to be transmitted
            txbuf.posrd++;    // U2TXREG = ... // Read 1 character from the buffer and send it
            txbuf.nchar--;                // Update buffer "posrd" and "nchar" variables
        }else{
            IEC1bits.U2TXIE = 0;// Disable UART2 Tx interrupts  
        }
        IFS1bits.U2TXIF = 0;  // Clear UART2 Tx interrupt flag
    }
}

int main(void){
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;            // Configure UART2: 115200, N, 8, 1
        
    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 2;
    U2STAbits.UTXISEL = 0;  
    U2STAbits.URXISEL = 0;                            // Configure UART2 interrupts, with RX and TX interrupts DISABLED disable U2RXIE, disable U2TXIE (register IEC1) set UART2 priority level (register IPC8) define TX interrupt mode (UTXISEL bits)
                                // Enable global Interrupts
                                // Initialize buffer variable "nchar" with 0
    EnableInterrupts();
    txbuf.nchar = 0;
    while(1){
        putstrInt("Test string which can be as long as you like, up to a maximum of 100 characters\n");
    }
    return 0;
}
