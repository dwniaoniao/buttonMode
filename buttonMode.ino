#define led1 4
#define led2 5
#define led3 6
#define key 2
#define T 300

void setup(){
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(key, INPUT_PULLUP);
}

unsigned char keyStatus = 0;
unsigned char p, mode;
unsigned char keyBak;
unsigned long keyPressStart, keyReleaseStart = 0;
unsigned long keyPressDuration, keyReleaseDuration;

void loop(){
    if(!digitalRead(key)){
        delay(20);
        if(!digitalRead(key)){
            keyStatus = 0;
        }
    } else{
        delay(20);
        if(digitalRead(key)){
            keyStatus = 1;
        }
    }

    keyPressDuration = millis() - keyPressStart;
    keyReleaseDuration = millis() - keyReleaseStart;

    if(!keyStatus){
        if(keyBak){
            if(keyReleaseDuration < T){
                if(p == 2){
                    p = 3;
                }
            }
            if(!p){
                p = 1;
            }
        } else if(keyPressDuration > T){
            mode = 3;
            p = 0;
        }
        keyReleaseStart = millis();
    } else{
        if(!keyBak){
            if(keyPressDuration < T){
                if(p == 1){
                    p = 2;
                } else if(p == 3){
                    p = 4;
                }
            }
        } else if(keyReleaseDuration > T){
            if(p == 2){
                mode = 1;
            } else if(p == 4){
                mode = 2;
            }
            p = 0;
        }
        keyPressStart = millis();
    }

    keyBak = keyStatus;
    
    switch(mode){
        case 1:
            digitalWrite(led1, HIGH);
            digitalWrite(led2, LOW);
            digitalWrite(led3, LOW);
            break;
        case 2:
            digitalWrite(led1, LOW);
            digitalWrite(led2, HIGH);
            digitalWrite(led3, LOW);
            break;
        case 3:
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            digitalWrite(led3, HIGH);
            break;
        default:
            break;
    }
}
