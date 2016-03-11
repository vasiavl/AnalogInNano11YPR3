//комитим из локалки ух ты стра
// еще клмитим из локалки кое как добавляем из локалки в 1 вктвь
// теперь сохраним в перца
//  я же умный очень
// правим в ГИТ и смотрим как уйдет на локалку
#define Button_1      2//8
 #define Button_2      12//13
 #define Button_3      13//12
const int analogInYawPin = A0;  // резистор джоя по Yaw
const int analogInRollPin = A2; // резистор джоя по Roll
const int analogInPitch
Pin = A4; // пин для резистора по Pitch

 #define LRPin               4//5// управляет реверсом мотора руля
 #define forward_agoPinL      7//6// управляет реверсом левого двигателя
  #define forward_agoPinR      8//7// управляет реверсом правого двигателя
  
  #define analogWriteRPin        9  // ШИМ на рулевой мотор
 #define analogWritePRYPinL     10 // ШИМ на левый  ходовой мотор
 #define analogWritePRYPinR      11// ШИМ на правый ходовой мотор

 

      
int Yaw,outputYawL,outputYawR, flagY,flagYF = 0; 
int Roll,tvist,tvistFlag, timeY = 0;        
int outputRoll = 0;
int outputRollR = 0;
int Pitch = 0;        
int outputPitch = 0;
int outputPitchD = 0;
int L,Ldriv = 0; // шим левого двигателя
int R,Rdriv = 0;// шим правого двигателя

int But1=0;
int But2=0;   //20
int But3=0;
int forwardR,forwardL,flag,flagP, flagForwardL, flagForwardR =0;//состояние реверса двигателей и флаги  переключения состояний

void setup() {
    pinMode(Button_1, INPUT_PULLUP);
    pinMode(Button_2, INPUT_PULLUP);
    pinMode(Button_3, INPUT_PULLUP);
    pinMode(forward_agoPinR, OUTPUT);
    pinMode(forward_agoPinL, OUTPUT);
    pinMode(LRPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {                               
  Yaw = analogRead(analogInYawPin); 
  Roll = analogRead(analogInRollPin); 
  Pitch = analogRead(analogInPitchPin);
  forwardR=  digitalRead(forward_agoPinR);
  forwardL=  digitalRead(forward_agoPinL); 
  tvistFlag= digitalRead( LRPin);
  
   
  outputPitch = map(Pitch, 540, 1023, 0, 255); 
  outputPitchD = map(Pitch, 480, 0, 0, 255); 
  outputRoll =  map(Roll, 480, 0, 0, 255);
  outputRollR =  map(Roll, 540, 1023, 0, 255);
  outputYawL = map(Yaw, 540, 1023, 0, 255); 
  outputYawR = map(Yaw, 480, 0, 0, 255);
                                                                                        
                                                                                                                                                              
   if (460>Pitch)
   {       outputPitch= 0;
           if (HIGH==forwardR|| HIGH==forwardL)
              { flagForwardL =flagForwardR=flag= LOW;}
           if (480>Roll){ R= outputPitchD;  outputRollR= 0;//left
             if (outputPitchD>outputRoll)   L= (outputPitchD-outputRoll/1.5);
             if (outputPitchD<outputRoll)   L= 0; }
           if ((540>Roll)&& (Roll>480))  {  R=L=outputPitchD;     }                                                  
           if  (Roll>540)   { L= outputPitchD;  outputRoll= 0;
              if (outputPitchD>outputRollR)   R= (outputPitchD-outputRollR/1.5);
              if (outputPitchD<outputRollR)   R= 0;}
   }  
 if (Pitch > 560)
  {             outputPitchD= 0;
          if (LOW==forwardR|| LOW==forwardL)
          { flagForwardR =flagForwardL=flag= HIGH ; }
                                                                      
          if  (480>Roll) { R= outputPitch;  //outputRollR= 0;
             if (outputPitch>outputRoll)   L= (outputPitch-outputRoll/1.5);
             if (outputPitch<outputRoll)   L= 0; }          
           if  ((540>Roll)&& (Roll>480)) {outputRoll= outputRollR =0; R=L= outputPitch;  } 
          if  (Roll>540) {     L= outputPitch;   outputRoll= 0;
             if (outputPitch>outputRollR)   R= (outputPitch-outputRollR/1.5);
             if (outputPitch<outputRollR)   R= 0; }
    }    
    if ((560>Pitch)&& (Pitch >460))
    {       Rdriv=Ldriv=0;
            outputRoll =outputRollR =  0;  //R=L=outputPitchD =outputPitch =0;  
         if (   Yaw>540)//left
         { 
              if (HIGH==forwardL|| LOW==forwardR)
              { flagForwardL= LOW; flagForwardR= HIGH; flagY= LOW; }  
                  L = 0;  R= outputYawL;
               if (Yaw>820) {  R= L= outputYawL; }                                        
         }           
         if (480>Yaw)//rait
          { 
              if (LOW==forwardL|| HIGH==forwardR)
               {  flagForwardL= HIGH ; flagForwardR= LOW; flagY= HIGH;}
                   R= 0;   L= outputYawR;
              if  (200>Yaw){  R=L= outputYawR; }  
          }                                                      
         if ((540>Yaw)&& (Yaw >480)) {  R=L =0;}
    }  
  
  if  (460>Roll)// left  Ydiff
  {    
    if  (HIGH== tvistFlag){tvistFlag= LOW; timeY=0 ; }
    if(timeY>2)tvist=0 ;
    if(timeY<2)tvist=25 ;
      timeY=timeY+1 ;        
   }      
  if  (560>Roll&& Roll>460) {tvist=timeY=0 ; }                                          
  if  (Roll>560)//right
   {   if  (LOW==tvistFlag) {tvistFlag= HIGH; timeY=0 ;}
        if(timeY>2)tvist=0 ;
       if(timeY<2)tvist=25 ;
         timeY=timeY+1 ; 
   }


    
 if (flag !=flagP  ){Rdriv=Ldriv=R=L=0; flagP=flag; }
 if (flagY !=flagYF){Rdriv=Ldriv=0; flagYF=flagY; }
   if  (Rdriv-R >20)  { Rdriv=Rdriv-25;} 
   else {if (R-Rdriv>20)Rdriv=Rdriv+25;
        else Rdriv=R;  }
    if (L-Ldriv>20) { Ldriv=Ldriv+25; }
    else {
      if (Ldriv-L >20) Ldriv=Ldriv-25;
          else Ldriv=L; }
     digitalWrite( LRPin, tvistFlag);
     digitalWrite( forward_agoPinL,flagForwardL );
     digitalWrite( forward_agoPinR,flagForwardR );     
     analogWrite(analogWriteRPin, tvist); 
     analogWrite(analogWritePRYPinR, Rdriv);
     analogWrite(analogWritePRYPinL, Ldriv); 
   But1=    digitalRead(Button_1);
    But2= digitalRead(Button_2);       
    But3=  digitalRead(Button_3);                                                                                                                           
                                                         
 
 
  Serial.print(" Yaw = " );                       
  Serial.print(Yaw);      
  Serial.print("\t outputYawR = ");      
  Serial.print(outputYawR); 
  Serial.print("\t outputYawL = ");      
  Serial.print(outputYawL);  
  Serial.print("\n Roll = " );                       
  Serial.print(Roll);      
  Serial.print("\t outputRoll = ");      
  Serial.print(outputRoll); 
   Serial.print("\t outputRollR = ");      
  Serial.print(outputRollR); 
  Serial.print("\n Pitch = " );                       
  Serial.print(Pitch);      
  Serial.print("\t outputPitch = ");      
  Serial.print(outputPitch); 
  Serial.print("  R = " );                       
  Serial.print(R); 
  Serial.print("\t Rdriv = " );                       
  Serial.print(Rdriv);
  Serial.print("\n                outputPitchD = ");      
  Serial.print(outputPitchD); 
  Serial.print("  L = ");      
  Serial.print(L);
  Serial.print("\t Ldriv = ");      
  Serial.print(Ldriv); 
  Serial.print("\n forwardR = ");            
  Serial.print(  forwardR); 
  Serial.print("\t forwardL = ");            
  Serial.print(  forwardL);  
 Serial.print("\t flag=") ;            
  Serial.print(  flag); 
 Serial.print("\t flagP=") ;            
  Serial.println(  flagP); 
Serial.print("\t flagY=") ;            
  Serial.print(  flagY); 
 Serial.print("\t flagYF=") ;            
  Serial.println(  flagYF); 
Serial.print("\t tvistFlag=") ;            
  Serial.print(  tvistFlag); 
 Serial.print("\t tvist=") ;            
  Serial.print(  tvist); 
 Serial.print("\t timeY=") ;            
  Serial.print(  timeY);  
  
  delay(2550);   

}
