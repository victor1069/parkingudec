
//pretty simple function - read everything out of the serial buffer and whats coming and get rid of it
void serial_dump_ESP(){
  char temp;
  while(Serial2.available()){
    temp =Serial2.read();
    delay(1);//could play around with this value if buffer overflows are occuring
  }//while
  
  
}//serial dump
