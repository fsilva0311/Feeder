/*En este programa de testeo aparece  reiterada veces las siguientes líneas: inOldA=inNowA;
                                                                             inOldB=inNowB;
                                                                             return;
  Esto hace la función de filtro debido a que al encender el led, la función delay() para que el encendido sea visible genera una pérdida de lectura de pulsos.
  En la futura implementación al firmware del feeder esto deberá optimizarse en el soft, eliminando la repetición de dichas líneas, ya que no hay necesidad de generar una delay en el micro.
 * 
 */

// Cada vuelta realiza 26,3mm aprox 

#define CHA 9// Implmentación de apodos para los pines
#define CHB 10
#define ledR A3
#define ledV A4
#define led  13

int contador =0;
int vueltas = 0;

int inOldA;// variable estado anterior de CHA
int inOldB;// variable estado anterior de CHB
int inNowA;// variable estado actual de CHA
int inNowB;// variable estado actual de CHB

void avance();// definición de función para devolución de avance
void retroceso();// definición de función para devolución de retroceso




void setup() 
{
  
  Serial.begin(9600);
  pinMode(ledR,OUTPUT);// definiciones de pines de salida
  pinMode(ledV,OUTPUT);
  pinMode(led,OUTPUT);
  inOldA=digitalRead(CHA);// se setea previamente el estado inicial de los dos CH
  inOldB=digitalRead(CHB);
    
}



void loop() 
{
  inNowA=digitalRead(CHA);//Se realiza lectura de ambos CH para saber su estado actual
  inNowB=digitalRead(CHB);
  
  if( inNowA !=inOldA || inNowB !=inOldB)// se lea si hubo algún cambio en alguno de los CH
  {
    // de acá al fin del if de la línea de arriba se testeara el estado anterior y el cambio hacia un sentido o hacia el otro según el estado actual de los ch 
    if( (inOldA==0 && inOldB==0 ) && (inNowA==1 && inNowB==0 ) )
    {
      avance();
      inOldA=inNowA;
      inOldB=inNowB;
      return;
    }
    else
    {
      if( (inOldA==0 && inOldB==0 ) && (inNowA==0 && inNowB==1 ) )  // se observará dentro de los else esta doble comprobación como filtro y para eviar lecturas erroneas por estado de transición de los estados, esto aplica a todas las estructuras que se repiten
          retroceso();
          inOldA=inNowA;
          inOldB=inNowB;
          return;
    }
  
    if( (inOldA==1 && inOldB==0 ) && (inNowA==1 && inNowB==1 ) )
    {
      avance();
      inOldA=inNowA;
      inOldB=inNowB; 
      return;
    }
    else
    {
      if( (inOldA==1 && inOldB==0 ) && (inNowA==0 && inNowB==0 ) )
      {
        retroceso();
        inOldA=inNowA;
        inOldB=inNowB;
        return;
      }
    }  

  
    if( (inOldA==1 && inOldB==1 ) && (inNowA==0 && inNowB==1 ) )
    {
      avance();
      inOldA=inNowA;
      inOldB=inNowB;
      return;
    }
    else
    {
      if((inOldA==1 && inOldB==1 ) && (inNowA==1 && inNowB==0 ))
      {
        retroceso();
        inOldA=inNowA;
        inOldB=inNowB;
        return;
      }
    }
    
    if( (inOldA==0 && inOldB==1 ) && (inNowA==0 && inNowB==0 ) )
    {
      avance();
      inOldA=inNowA;
      inOldA=inNowB;
      return;
    }
    else
    {
      if( (inOldA==0 && inOldB==1 ) && (inNowA==1 && inNowB==1 ) )
      {
        retroceso();
        inOldA=inNowA;
        inOldB=inNowB;
        return;
      }
    }

  }
  
    
      
}

void avance()// la función de avance y retroceso serán reemplazadas por return de un valor que refleje el cambio de estado del encoder especificando el sentido
{
  //digitalWrite(ledR,HIGH);
  //delay(15);
  //digitalWrite(ledR,LOW);
  contador++;
  if(contador>=100)
  {
    contador=0;
    vueltas++;
    //digitalWrite(ledV,HIGH);
    //Serial.print("Vueltas: ");
    //Serial.println(vueltas);
  }
    Serial.print("longitud: ");
    Serial.print(contador*0.488);
    Serial.println("mm");  
    Serial.println(contador);
}

void retroceso()
{
  //digitalWrite(ledV,HIGH);
  //delay(15);
  //digitalWrite(ledV,LOW);
  contador--;
  //if(contador>0)contador--;
    Serial.print("longitud: ");
    Serial.print(contador*0.488);
    Serial.println("mm");  
    Serial.println(contador);  
  
  //Serial.println(contador); 
}
