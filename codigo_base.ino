
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

byte encoder();

int distancia=0;
int contador=0;
void setup() 
{
  Serial.begin(9600);
  inOldA=digitalRead(CHA);// se setea previamente el estado inicial de los dos CH
  inOldB=digitalRead(CHB); 
}

void loop()
{
  int lectura=encoder();
  if(lectura != 0 )
  {
    if(lectura==avance)contador++;
    else contador--;
    Serial.println(contador);
  } 
}  

byte encoder()
{
  inNowA=digitalRead(CHA);
  inNowB=digitalRead(CHB);
 
  if(inNowA !=inOldA || inNowB !=inOldB )
  {
    inAuxA=inOldA;
    inAuxB=inOldB;
    inOldA=inNowA;
    inOldB=inNowB;
    
//-------condicion anterior---**---condicion actual--------
    if(inAuxA==0 && inAuxB==1 && inNowA==0 && inNowB==0) return 2; // avance
    if(inAuxA==0 && inAuxB==1 && inNowA==1 && inNowB==1) return 1; // retroceso

    if(inAuxA==0 && inAuxB==0 && inNowA==1 && inNowB==0) return 2; // avance
    if(inAuxA==0 && inAuxB==0 && inNowA==0 && inNowB==1) return 1; // retroceso
       
    if(inAuxA==1 && inAuxB==0 && inNowA==1 && inNowB==1) return 2; // avance
    if(inAuxA==1 && inAuxB==0 && inNowA==0 && inNowB==0) return 1; // retroceso

    if(inAuxA==1 && inAuxB==1 && inNowA==0 && inNowB==1) return 2; // avance
    if(inAuxA==1 && inAuxB==1 && inNowA==1 && inNowB==0) return 1; // retroceso       
  }   
  else return 0;//quieto
}
