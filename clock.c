#define NUM_DIGITS 6
unsigned char enable_pins[NUM_DIGITS] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20};
unsigned char hours = 12, minutes = 0, seconds = 0;
unsigned char digits[6];

void extractDigits() {
    digits[0] = hours / 10;
    digits[1] = hours % 10;
    digits[2] = minutes / 10;
    digits[3] = minutes % 10;
    digits[4] = seconds / 10;
    digits[5] = seconds % 10;
}

void displayDigit(unsigned char digit, unsigned char enable_pin) {
    PORTA = enable_pin;
    PORTB = digit;
    Delay_ms(5);
    PORTA = 0x00;
}

void main() {
unsigned char i;
    TRISB = 0x00;
    TRISA = 0x00;
    PORTB = 0x00;
    PORTA = 0x00;

    while (1) {
        extractDigits();

        for (i = 0; i < NUM_DIGITS; i++) {
            displayDigit(digits[i], enable_pins[i]);
        }

        Delay_ms(100);
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
            if (minutes == 60) {
                minutes = 0;
                hours++;
                if (hours == 24) {
                    hours = 0;
                }
            }
        }
    }
}