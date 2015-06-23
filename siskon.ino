#define ECHOPIN 2                   //definisi PIN Echo         
#define TRIGPIN 3                   //definisi PIN trigger     
#define LEDFLASHER 4
#define ALARMSOUNDER 5 

  int i = 0; 
  int state = 0;
  int jarak;
  int distance;
  int val = LOW; 
  int pre_val = LOW; 

void setup(){
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(LEDFLASHER, OUTPUT); 
  pinMode(ALARMSOUNDER, OUTPUT); 
}

void loop(){
  if(state==0){                    //State untuk menunggu benda....
    
    Serial.print("Menginisialisasi Jarak \n");  
    Serial.print("Mohon jangan pindahkan benda \n");  
    digitalWrite(LEDFLASHER, HIGH);  
    delay(3000);
    digitalWrite(LEDFLASHER, LOW); 
  
  state = 1;
  }
  else if(state == 1){            //menghitung jarak benda
    
    digitalWrite(TRIGPIN, LOW);                   
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);                  
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);  
  
    jarak = pulseIn(ECHOPIN, HIGH);        
    jarak = jarak/58;   
    if(jarak > 100){
      Serial.print(jarak);  
      state=5;
    }else{
       state=3; 
    }
  
  }
  else if(state == 3){          //Mendeteksi pergerakan jarak benda
    digitalWrite(TRIGPIN, LOW);                   
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);                  
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);                   
    distance = pulseIn(ECHOPIN, HIGH);        
    distance= distance/58;                        // Menghitung nilainya dan mengubahnya ke cm              
    Serial.print(distance);  
    Serial.print("cm \n");   
      if(distance <= jarak - 5 || distance >= jarak + 5){
          state=4;
      }
     delay(100);  
  }
  else if(state == 4){          
       for(i = 0; i < 50; i = i + 2)
        {
            analogWrite(LEDFLASHER, i);
            analogWrite(ALARMSOUNDER, i);
            delay(10);
        }
        for(i = 400; i > 1; i = i - 2)
        {
            analogWrite(LEDFLASHER, i);
            analogWrite(ALARMSOUNDER, i);
            delay(5);
        }
        for(i = 1; i <= 10; i++)
        {
            analogWrite(LEDFLASHER, 255);
            analogWrite(ALARMSOUNDER, 200);
            delay(100);
            analogWrite(LEDFLASHER, 0);
            analogWrite(ALARMSOUNDER, 25);
            delay(100);
        }
    pre_val = val; 
  
  }
                                   
}
