
#define CHA 2// Implmentación de apodos para los pines
#define CHB 3


#define avance 2
#define retroceso 1
#define quieto 0

int inOldA;// variable estado anterior de CHA
int inOldB;// variable estado anterior de CHB
int inNowA;// variable estado actual de CHA
int inNowB;// variable estado actual de CHB
int inAuxA;
int inAuxB;

void encoder();

int distancia=0;
volatile int contador=0;
bool flag=false;


void setup() 
{
  Serial.begin(9600);
  inOldA=digitalRead(CHA);// se setea previamente el estado inicial de los dos CH
  inOldB=digitalRead(CHB); 

  attachInterrupt(digitalPinToInterrupt(2), encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), encoder, CHANGE);
}

void loop()
{
  if(flag)
  {
    flag = false;
    Serial.println(contador);
  } 
}  

void encoder()
{
  inNowA=digitalRead(CHA);
  inNowB=digitalRead(CHB);
 
  if(inNowA !=inOldA || inNowB !=inOldB )
  {
    inAuxA=inOldA;
    inAuxB=inOldB;
    inOldA=inNowA;
    inOldB=inNowB;

    flag = true;
//-------condicion anterior---**---condicion actual--------
    if(inAuxA==0 && inAuxB==1 && inNowA==0 && inNowB==0) contador++; // avance
    if(inAuxA==0 && inAuxB==1 && inNowA==1 && inNowB==1) contador--; // retroceso

    if(inAuxA==0 && inAuxB==0 && inNowA==1 && inNowB==0) contador++; // avance
    if(inAuxA==0 && inAuxB==0 && inNowA==0 && inNowB==1) contador--; // retroceso
       
    if(inAuxA==1 && inAuxB==0 && inNowA==1 && inNowB==1) contador++; // avance
    if(inAuxA==1 && inAuxB==0 && inNowA==0 && inNowB==0) contador--; // retroceso

    if(inAuxA==1 && inAuxB==1 && inNowA==0 && inNowB==1) contador++; // avance
    if(inAuxA==1 && inAuxB==1 && inNowA==1 && inNowB==0) contador--; // retroceso       
  }   
  
}
