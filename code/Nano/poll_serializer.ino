
int poll_serializer(){
  int btn_num = -1;
  //Serial.println("poll buttons..");
  //Serial.println("87654321 87654321 87654321");

  digitalWrite(SERIALIZER_CLK, LOW);
  digitalWrite(SERIALIZER_PS, LOW);
  delay(10); // debounce delay

  digitalWrite(SERIALIZER_PS, HIGH);
  delay(SERIALIZER_FREQ);
  //digitalWrite(SERIALIZER_CLK, HIGH);

  for(int i=0; i<24; i++){
    //if(i==8)  Serial.print(" ");
    //if(i==16) Serial.print(" ");

    digitalWrite(SERIALIZER_CLK, HIGH);
    delayMicroseconds(SERIALIZER_FREQ*1000/2);
    //Serial.print(digitalRead(SERIALIZER_OUT));
    if(digitalRead(SERIALIZER_OUT)) btn_num = i;
    delayMicroseconds(SERIALIZER_FREQ*1000/2);
    digitalWrite(SERIALIZER_CLK, LOW);
    if(i==0) digitalWrite(SERIALIZER_PS, LOW);
    delay(SERIALIZER_FREQ);    
  }
  //Serial.println("");
  btn_num++;
  //Serial.println(btn_num);
  switch(btn_num){
    case 1: return BTN01; break;
    case 2: return BTN02; break;
    case 3: return BTN03; break;
    case 4: return BTN04; break;
    case 5: return BTN05; break;
    case 6: return BTN06; break;
    case 7: return BTN07; break;
    case 8: return BTN08; break;

    case 9: return BTN09; break;
    case 10: return BTN10; break;
    case 11: return BTN11; break;
    case 12: return BTN12; break;
    case 13: return BTN13; break;
    case 14: return BTN14; break;
    case 15: return BTN15; break;
    case 16: return BTN16; break;

    case 17: return BTN17; break;
    case 18: return BTN18; break;
    case 19: return BTN19; break;
    case 20: return BTN20; break;
    case 21: return BTN21; break;
    case 22: return BTN22; break;
    case 23: return BTN23; break;
    case 24: return BTN24; break;
    
    default: return -1; break;
  }
}
