#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include "Headers/LCD_16x2_H_file.h"
#include<avr/interrupt.h>
#include<string.h>

#define Trigger_pin 0  /* Trigger pin */
#define Echo_pin 7     /* Echo pin */
#define IR_SENS1_PIN 2
#define IR_SENS2_PIN 3
#define car_width 17 
#define IDLE 0
#define PARKING 1
#define PARKED 2
#define FIND_SPACE 3
#define ANGLE 4

volatile uint16_t counta=0;
volatile uint16_t rearObstacleDetected=0;
volatile uint16_t frontObstacleDetected=0;

void IRSensInit() {
    DDRA &=~(1<<IR_SENS1_PIN);
    PORTA|= (1<<IR_SENS1_PIN);

    DDRA &=~(1<<IR_SENS2_PIN);
    PORTA|= (1<<IR_SENS2_PIN);
}

uint8_t IRRead1() {
    if (PINA & (1<<IR_SENS1_PIN))
        return 1;
    else
        return 0;
}

uint8_t IRRead2() {
    if (PINA & (1<<IR_SENS2_PIN))
        return 1;
    else
        return 0;
}

void forward() { //car moves forward
    PORTD=(1<<0)|(1<<6);
}

void reverseright(void) { //car reverserights
    PORTD=(1<<5);
}

void froright() { //car goes forward and right
    PORTD=(1<<6);
}

void stop() {
    PORTD &= ~((1<<1) | (1<<0)|(1<<5)|(1<<6));
}

void reverse() { //car reverses
    PORTD=((1<<1)|(1<<5));
}

void mILLIhundotimerinit() { //100ms timer interrupt initialization function
    TCNT1 = 0;
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
    OCR1A = 1562.5;
    TIMSK |= (1 << OCIE1A);
}

void get_distance() {
    char string[16];
    uint16_t pulse=0;
    /* Give 15us trigger pulse on trig. pin to HC-SR04 */
    PORTA |= (1 << Trigger_pin);
    _delay_us(15);
    PORTA &= (~(1 << Trigger_pin));

    while((PIND & (1 << Echo_pin))== 0); //spin until PD7 is 0
    TCNT0=0; //initialize timer counter
    TCCR0=(1<<CS00)|(1<<CS01); //configure for operation of clock with prescalar /64

    while ((PIND & (1 << Echo_pin)) != 0); //spin until PD7 is 1
    pulse=TCNT0;
    TCCR0=0x00;
    counta=(pulse*64)/58;

    dtostrf(counta, 2, 2, string); /* distance to string */
    strcat(string, " cm   ");    /* Concatenate unit i.e.cm */
    LCD_String_xy(2, 0, "Dist = ");
    LCD_String_xy(2, 7, string);    /* Print distance */
}

void motor_init() {
    DDRD |= (1<<0)|(1<<1)|(1<<5)|(1<<6);    //motor pins initialization
}

void Ultra_init() {
    DDRD &= ~(1 << Echo_pin); //configure PA7 as input
    DDRA |= (1<<Trigger_pin); /* Make trigger pin as output */
}

int main(void) {
    LCD_Init();
    IRSensInit();
    Ultra_init();
    motor_init();

    int state = IDLE;  // start in idle state

    mILLIhundotimerinit();
    sei();
    LCD_String_xy(0,0,"Auto-ParkMode on");
    _delay_ms(1000);
    LCD_Clear();	

    while(1) {
        if (state == IDLE) {
            _delay_ms(1000);
            state = FIND_SPACE;  // start moving forward
        }

        else if (state == FIND_SPACE) {
            if (counta > car_width) { 
                forward(); //keep moving until parking gap detected
            } else {
                stop(); //stop after gap detected
                _delay_ms(1000);
                state = ANGLE;
                LCD_String_xy(0,0,"Space detected");
                _delay_ms(1000);
            }
        }

        else if (state == ANGLE) {	
            reverseright();
            _delay_ms(1500);
            stop();
            state=PARKING;
        }

        else if(state==PARKING) {
            if (rearObstacleDetected == 1) {
                forward();
                _delay_ms(500);
            }
            else if(frontObstacleDetected==1) {
                reverse();
                _delay_ms(500);
            }
            else {
                reverse();
                _delay_ms(500);
                froright();
                _delay_ms(500);
                state=PARKED;
                LCD_Clear();
                LCD_String_xy(0,0,"Parked");
            }
        }

        else if(state==PARKED) {
            stop();
        }
    }
}

ISR(TIMER1_COMPA_vect) {
    get_distance();
    frontObstacleDetected=IRRead1();
    rearObstacleDetected=IRRead2();
}
