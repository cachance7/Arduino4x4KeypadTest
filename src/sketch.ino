/**
 * Allow for customization of any pins, resistors, or tolerance.
 * FYI - These are the count ranges given all defaults below:
 *  926 < col1 < 933
 *  835 < col2 < 842
 *  693 < col3 < 698
 *  606 < col4 < 611
 */

#ifndef ROW1PIN
#define ROW1PIN 1
#endif

#ifndef ROW2PIN
#define ROW2PIN 2
#endif

#ifndef ROW3PIN
#define ROW3PIN 3
#endif

#ifndef ROW4PIN
#define ROW4PIN 4
#endif

#ifndef R1
#define R1 10000
#endif

#ifndef R2
#define R2 22000
#endif

#ifndef R3
#define R3 47000
#endif

#ifndef R4
#define R4 68000
#endif

#ifndef RCOMM
#define RCOMM 100000
#endif

/* For the default resistor values, this is a pretty good default. */
#ifndef TOLERANCE
#define TOLERANCE 0.004
#endif

#define ANALOG_COUNTS(r) (1024 * RCOMM / (RCOMM + r))
#define PRINT_RANGE(col)({Serial.print(col - (col * TOLERANCE)); Serial.print(" < " #col " < "); Serial.print(col + (col * TOLERANCE)); Serial.println();})
#define GET_RANGE(col,reading) ((col - (col * TOLERANCE)) < reading && reading < (col + (col * TOLERANCE)))

const float col1 = ANALOG_COUNTS(R1);
const float col2 = ANALOG_COUNTS(R2);
const float col3 = ANALOG_COUNTS(R3);
const float col4 = ANALOG_COUNTS(R4);
int rows[4];
int col;

char buttons[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void setup()
{
    pinMode(ROW1PIN, INPUT);
    pinMode(ROW2PIN, INPUT);
    pinMode(ROW3PIN, INPUT);
    pinMode(ROW4PIN, INPUT);

    Serial.begin(9600);

    PRINT_RANGE(col1);
    PRINT_RANGE(col2);
    PRINT_RANGE(col3);
    PRINT_RANGE(col4);
}

void loop()
{
    rows[0] = analogRead(ROW1PIN);
    rows[1] = analogRead(ROW2PIN);
    rows[2] = analogRead(ROW3PIN);
    rows[3] = analogRead(ROW4PIN);

    for (int i = 0; i<4; i++) {
        col = getCol(rows[i]);
        if (col >= 0) {
            Serial.print(buttons[i][col]);
            Serial.println(" pressed");
        }
    }
    delay(100);
}

int getCol(int reading) {
    if (GET_RANGE(col1, reading)) {
        return 0;
    }
    if (GET_RANGE(col2, reading)) {
        return 1;
    }
    if (GET_RANGE(col3, reading)) {
        return 2;
    }
    if (GET_RANGE(col4, reading)) {
        return 3;
    }
    return -1;
}
