/*
 * File:   main.c
 * Author: Caio Schultz
 *
 * Created on 2 de Dezembro de 2020, 13:45
 */

#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "keypad.h"
#include "timer.h"



#define L0  0x80
#define L1  0xC0
#define CLR 0x01

void main(void) {
    unsigned int tecla = 8, tempo = 100000000;
    unsigned char coluna = 0, linha = 0, dino = 0xFC;
    unsigned char estado = 0;//mantem o jogo ou finaliza
    unsigned char coluna1 = 7, linha1 = 0, pedra1 = 0xFF;
    unsigned char coluna2 = 8, linha2 = 0, pedra2 = 0xFF;
    unsigned char coluna3 = 16, linha3 = 1, pedra3 = 0xFF;
    unsigned char coluna4 = 17, linha4 = 1, pedra4 = 0xFF;

    lcdInit();
    kpInit();
    timerInit();

    //imprime o dino no começo do lcd
    lcdData(dino);
    //imprime as primeiras pedras
    lcdPosition(linha1, coluna1);
    lcdData(pedra1);
    lcdPosition(linha2, coluna2);
    lcdData(pedra2);
    lcdPosition(linha3, coluna3);
    lcdData(pedra3);
    lcdPosition(linha4, coluna4);
    lcdData(pedra4);
    lcdPosition(0, 1);
    lcdData('|');
    lcdPosition(1, 1);
    lcdData('|');
    


    for (;;) {
        kpDebounce();
        if (estado == 0) {//o jogo não acabou, quando for 1 ele sai do loop do jogo.           
            
            if (timerEnded()!= 0) {
                //movimento das pedras                  
                coluna1--;
                if (coluna1 == 0) {
                    coluna1 = 16;
                    lcdPosition(linha1, 1);
                    lcdData('|');
                    if(linha1==0){
                        linha1 = 1;
                    }else{
                        linha1=0;
                    }
                }

                coluna2--;
                if (coluna2 == 0) {
                    coluna2 = 16;
                    lcdPosition(linha2, 1);
                    lcdData('|');
                    if(linha2==0){
                        linha2 = 1;
                    }else{
                        linha2=0;
                    }
                }

                coluna3--;
                if (coluna3 == 0) {
                    coluna3 = 16;
                    lcdPosition(linha3, 1);
                    lcdData('|');
                    if(linha3==0){
                        linha3 = 1;
                    }else{
                        linha3=0;
                    }
                }

                coluna4--;
                if (coluna4 == 0) {
                    coluna4 = 16;
                    lcdPosition(linha4, 1);
                    lcdData('|');
                    if(linha4==0){
                        linha4 = 1;
                    }else{
                        linha4=0;
                    }
                }

                //imprime as pedras nas novas posiçoes e apaga nas antigas
                lcdPosition(linha1, coluna1 + 1);
                lcdData(' ');
                lcdPosition(linha1, coluna1);
                lcdData(pedra1);

                lcdPosition(linha2, coluna2 + 1);
                lcdData(' ');
                lcdPosition(linha2, coluna2);
                lcdData(pedra2);

                lcdPosition(linha3, coluna3 + 1);
                lcdData(' ');
                lcdPosition(linha3, coluna3);
                lcdData(pedra3);

                lcdPosition(linha4, coluna4 + 1);
                lcdData(' ');
                lcdPosition(linha4, coluna4);
                lcdData(pedra4);
                
                timerReset(tempo); 
            }

            if (kpRead() != tecla) {
                tecla = kpRead();
                if (bitTst(tecla, 3)) {
                    //movimento do dino
                    linha = 0;
                    lcdPosition(1, coluna);
                    lcdData(' ');
                    lcdPosition(linha, coluna);
                    lcdData(dino);


                }
                if (bitTst(tecla, 7)) {
                    //movimento do dino
                    linha = 1;
                    lcdPosition(0, coluna);
                    lcdData(' ');
                    lcdPosition(linha, coluna);
                    lcdData(dino);


                }
                if (bitTst(tecla, 6)) {
                    //movimento dos dinos
                    coluna++;
                    lcdPosition(linha, coluna - 1);
                    lcdData(' ');
                    lcdPosition(linha, coluna);
                    lcdData(dino);


                }
                if (bitTst(tecla, 2)) {
                    //movimento do dino
                    coluna--;
                    lcdPosition(linha, coluna + 1);
                    lcdData(' ');
                    lcdPosition(linha, coluna);
                    lcdData(dino);

                }

            }




            // Resultados do jogo:
            //Perderá se:
            if ((coluna == coluna1)&&(linha == linha1)) {
                lcdCommand(CLR);
                lcdData('V');
                lcdData('o');
                lcdData('c');
                lcdData('e');
                lcdData(' ');
                lcdData('F');
                lcdData('a');
                lcdData('l');
                lcdData('h');
                lcdData('o');
                lcdData('u');
                estado = 1;
            }
            if ((coluna == coluna2)&&(linha == linha2)) {
                lcdCommand(CLR);
                lcdData('V');
                lcdData('o');
                lcdData('c');
                lcdData('e');
                lcdData(' ');
                lcdData('F');
                lcdData('a');
                lcdData('l');
                lcdData('h');
                lcdData('o');
                lcdData('u');
                estado = 1;
            }
            if ((coluna == coluna3)&&(linha == linha3)) {
                lcdCommand(CLR);
                lcdData('V');
                lcdData('o');
                lcdData('c');
                lcdData('e');
                lcdData(' ');
                lcdData('F');
                lcdData('a');
                lcdData('l');
                lcdData('h');
                lcdData('o');
                lcdData('u');
                estado = 1;
            }
            if ((coluna == coluna4)&&(linha == linha4)) {
                lcdCommand(CLR);
                lcdData('V');
                lcdData('o');
                lcdData('c');
                lcdData('e');
                lcdData(' ');
                lcdData('F');
                lcdData('a');
                lcdData('l');
                lcdData('h');
                lcdData('o');
                lcdData('u');
                estado = 1;
            }

            //Vencerá se:
            if (coluna == 16) {
                lcdCommand(CLR);
                lcdData('V');
                lcdData('o');
                lcdData('c');
                lcdData('e');
                lcdData(' ');
                lcdData('V');
                lcdData('e');
                lcdData('n');
                lcdData('c');
                lcdData('e');
                lcdData('u');
                estado = 1;
            }

        }

    }
}