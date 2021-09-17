int pwmout = 3;
int start = 12;
int analog = A5;
int value = 0;
int grid = 0;
int go = 0;
int rdy = 0;

float anode[15];
float anv = 0;

int garray[] = {119, 126, 133, 141, 148, 156, 163,  
                171, 179, 185, 193, 200, 207};
  //119 = -3.01V; 126 = -2.53V; 133 = -2.06V; 141 = -1.51V
  //148 = -1.03V; 156 = -0.49V; 163 = -0.01V; 171 = 0.53V
  //179 = 1.08V; 185 = 1.48V; 193 = 2.03V; 200 = 2.50V; 207 = 2.98V

  
void setup() {
  Serial.begin(9600); 
  pinMode(pwmout, OUTPUT);
  pinMode(start, INPUT);
}

void loop() {

  if (rdy == 0) {
    Serial.println();
    Serial.println("Press button to begin.");
    Serial.println();
    rdy = 1;
  }

  grid = garray[0];
  analogWrite(pwmout, grid);
  
  if (digitalRead(start) == HIGH && go == 0) {
    go = 1;
    Serial.print("Testing");
  }

  if (go == 1) {

    anv = 0;
        
    for (int i = 0; i < 13; i++) {
      grid = garray[i];
      analogWrite(pwmout, grid);
      
      delay(100);

      value = analogRead(analog);
      anv = value * 0.0049 * 5.376;   //Analog value times V/div times 1.47M/330k divider
      anode[i] = anv;

      Serial.print(".");
    }

    Serial.println();
    Serial.println("Grid voltage from -3.0V to + 3.0V in 0.5V increments.");
    Serial.println("Anode voltage with plate resistor of 33k ohms.");
    for (int i = 0; i < 13; i++) {
      Serial.print(anode[i]);
      Serial.println();
    }

    go = 0;
    rdy = 0;
  }

  delay(250);
}
