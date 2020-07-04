
/*
 Управление за 2 стъпкови мотора на 5 волта. 
 За монтаж на стойка и таблет на кола VW PASSAT B5.5
Дата проект 4.7.2020г

Бележки: Използване на 1 реле за подаване на +5V или GND към PULL UP пин за смяна на състоянието на таблета - Изправен или Прибран. 
При включване и започване на програмата: таблета се прибира или се прави проверка за прибрано състояние. Използва се PUSH switch на гърба.
Има опция за 2 бутона. Които са активни само в изправен режим за ръчно регулиране на Наклона.


 */

#include <Stepper.h>

const int stepsPerRevolution = 600;                  // стъпки за пълен оборот
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // инициализация на стъпков мотор


void setup() {
Serial.begin(9600);
myStepper.setSpeed(50);
pinMode(12, INPUT_PULLUP);              // Минава през реле за превключване на ниско ниво за включване на таблета
pinMode(7, INPUT_PULLUP);               // КЛЮч на гърба на таблета за легнала (0 позиция)
pinMode(6, INPUT_PULLUP);              // бутон за ръчно прибиране или изправяне. Активно ниско ниво
pinMode(5, INPUT_PULLUP);              // бутон за ръчно прибиране или изправяне. Активно ниско ниво

}

void loop() {
int voltageDetector = digitalRead(12); //променлива за промяна на състоянието активно високо - ВКЛ. ; акт. ниско - ИЗКЛ.
int startPosition = digitalRead(7);    //променлива за нулиране на положението в случай на непредвидени обстояттелства връща на 0та и започва отначало.
bool startPoint = false;
bool TabletIsUp = false;
//int buttonCounter = 1;                 // брояч за състояние на таблета (при нечетно - изправен; при четно прибран);

if(digitalRead(7) == HIGH){                      // направи проверка за изправен таблет;
   myStepper.step(-stepsPerRevolution /4);       //   Ако е изправен го прибери.
} else {
      while(digitalRead(7) == LOW){
     startPoint = true;
      digitalRead(12);
      if((digitalRead(12) == LOW)&&(startPoint == true)){               // ако си на стартова позиция и таблета е включен
          myStepper.step(stepsPerRevolution);                              // изправи таблета
          while((startPoint == true) &&(digitalRead(12) == LOW)){     // докато състоянието на таблета е включено следи за изключване или натискане на бутона и принудително прибиране
          digitalRead(12);                  // проверявай за изкл състояние
          digitalRead(5);
          digitalRead(6);
          while(digitalRead(6) == LOW) {       // бутон за допълнително изправяне на таблета
            myStepper.step(stepsPerRevolution/6); 
          }
            while(digitalRead(5) == LOW) {       // бутон за допълнително изправяне на таблета
            myStepper.step(-stepsPerRevolution/6); 
          }
         }
        }
      }
    }
  }



        /*
         * 
  buttonCounter++;
            if(buttonCounter % 2 == 0){
              while(digitalRead(7) == HIGH){          
              myStepper.step(-stepsPerRevolution /4);
              if(buttonCounter %2 !=0){                 //ако се натисне бутон инкрементирай с 1 и ако не е четно изправи таблета
         
 if(voltageDetector == LOW){              // ако е включено захранване към таблета
 switch (voltageDetector) {
 case LOW: {
  myStepper.step(stepsPerRevolution);         // Изправи таблета
 while (voltageDetector == LOW){              // Докато таблета е изправен следи за изключено състояние
 delay(100);
 digitalRead(voltageDetector);
if(voltageDetector == HIGH){                  // ако е изклчено захранване към таблета.
 myStepper.step(-stepsPerRevolution);          // прибери таблета
  }
}
 break;                                        
}
 case HIGH: {                                                         //изключено състояние
while(startPosition == HIGH){                                        //докато е изключено следи за включване и излез.
  delay(200);
digitalRead(voltageDetector);
digitalRead(startPosition);

  }
      }
 break;
         }
       }
    }
 
*/
         
        

   
