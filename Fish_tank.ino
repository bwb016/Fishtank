/* 
 + -- Csp  - NaCl Concentration for the setpoint
 + -- C1   - Initial NaCl Concentration
 + -- C2   - Target NaCl Concentration
 + -- G    - Gain
 + -- OF   - Fraction of Overflow from DI
 + -- m    - Mass of water in tank
 + -- X    - Mass of DI Water being added
 + -- FR   - Flow Rate
 + -- t    - Time to leave valve open (in ms)
 +
 + ==| C2 = C1 + (Csp-C1) * G
 + ==| X = (m(C1-C2))/(C1(1-OF))
 + ==| t = (FR)^-1 * (60*X)
 */
int deadtime = 600;

double C1=0; //Initial NaCl Concentration
double C2=0; //Target NaCl Concentration
double X=0;  //Mass of DI water being added

double LCLsp=0.0005;
double UCLsp=0.0015;
double Csp=0.001;


double FR = 0.65; //Flow Rate - L/min
double G = 0.8; //Gain
double m = 78.252; // grams
double OF = 0.15; //Over Flow

int topen=0;
int tlast=0;
int time;

int analogS;



void setup(){
pinMode(3,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
Serial.begin(9600);

}

void loop( ) { 
  digitalWrite(3,HIGH); 
  delay(100); 

  for (int i=0; i<30;i++) { 
    analogS=analogRead(0);
  }
  digitalWrite(3, LOW);
  
  C1=(2.7589*(pow(10,-24)))*(pow(analogS,9.578544));
  time-millis()-tlast;
  Serial.print(" ");
  Serial.print(" ");
  Serial.print(" ");
  
  if(C1<LCLsp && time>deadtime){
    Add_Salt();
  }
  else if(C1>UCLsp && time>deadtime){
    Add_DI();
  }
  else {Stay_same();}
}

void Add_Salt(){
  C2=(C1+(Csp-C1)*G);
  X=((m*(C2-C1))/((1-OF)*(0.001-C1)));
  topen=(60*(X/FR));
  digitalWrite(7,HIGH);
  delay(topen);
  digitalWrite(7,LOW);
  tlast=millis();
}

void Add_DI(){
  C2=(C1-(C1-Csp)*G);
  X=((m*(C1-C2))/((1-OF)*C1));
  topen=(60*(X/FR));
  digitalWrite(8,HIGH);
  delay(topen);
  digitalWrite(8,LOW);
  tlast=millis();
}

void Stay_same(){
  loop();
}





