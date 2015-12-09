const int row1Pin = 1;
const int row2Pin = 2;
const int row3Pin = 3;
const int row4Pin = 4;

const float voltage = 5.0; // 3.3

const float col1 = 186; // 190
const float col2 = 168; // 172
const float col3 = 140;
const float col4 = 122;
const float tolerance = 0.02;

void setup()
{
    pinMode(row1Pin, INPUT);
    pinMode(row2Pin, INPUT);
    pinMode(row3Pin, INPUT);
    pinMode(row4Pin, INPUT);

    Serial.begin(9600);

    /*
    Serial.print(col1 - (col1 * tolerance));
    Serial.print("< col1 <");
    Serial.print(col1 + (col1 * tolerance));
    Serial.println();

    Serial.print(col2 - (col2 * tolerance));
    Serial.print("< col2 <");
    Serial.print(col2 + (col2 * tolerance));
    Serial.println();

    Serial.print(col3 - (col3 * tolerance));
    Serial.print("< col3 <");
    Serial.print(col3 + (col3 * tolerance));
    Serial.println();

    Serial.print(col4 - (col4 * tolerance));
    Serial.print("< col4 <");
    Serial.print(col4 + (col4 * tolerance));
    Serial.println();
    */
}

int rows[4];
int col;

char buttons[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void loop()
{
    rows[0] = analogRead(row1Pin);
    rows[1] = analogRead(row2Pin);
    rows[2] = analogRead(row3Pin);
    rows[3] = analogRead(row4Pin);

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
    float scaled = reading / voltage;
    if ((col1 - (col1 * tolerance)) < scaled && scaled < (col1 + (col1 * tolerance))) {
        return 0;
    }
    if ((col2 - (col2 * tolerance)) < scaled && scaled < (col2 + (col2 * tolerance))) {
        return 1;
    }
    if ((col3 - (col3 * tolerance)) < scaled && scaled < (col3 + (col3 * tolerance))) {
        return 2;
    }
    if ((col4 - (col4 * tolerance)) < scaled && scaled < (col4 + (col4 * tolerance))) {
        return 3;
    }
    return -1;
}
