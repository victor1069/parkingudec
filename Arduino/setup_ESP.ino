boolean setup_ESP(){//returns a '1' if successful
  delay(5000);
  Serial2.println("AT\r\n");// Send just 'AT' to make sure the ESP is responding
  delay(2000);
  //this read_until_... function is used to find a keyword in the ESP response - more on this later and in the function itself
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//go look for keyword "OK" with a 5sec timeout
    Serial2.println("ESP CHECK OK");
   
  else
    Serial2.println("ESP CHECK FAILED");
    
  serial_dump_ESP();//this just reads everything in the buffer and what's still coming from the ESP

  Serial2.print("AT+RST\r\n");// Give it a reset - who knows what condition it was in, better to start fresh
  delay(2000);
  if(read_until_ESP(keyword_Ready,sizeof(keyword_Ready),5000,0))//go look for keyword "Ready" - takes a few seconds longer to complete
    Serial2.println("ESP RESET OK");//depneding on the FW version on the ESP, sometimes the Ready is with a lowercase r - ready
  else
    Serial2.println("ESP RESET FAILED"); 
  serial_dump_ESP();
  
   Serial2.print("AT+CWMODE=");// set the CWMODE
   Serial2.print(CWMODE);//just send what is set in the constant
   Serial2.print("\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),1000,0))//go look for keyword "OK"
    Serial2.println("ESP CWMODE SET");
  else
    Serial2.println("ESP CWMODE SET FAILED"); //probably going to fail, since a 'no change' is returned if already set - would be nice to check for two words
  serial_dump_ESP();  
   
   //Here's where the SSID and PW are set
  Serial2.print("AT+CWJAP=\"");// set the SSID AT+CWJAP="SSID","PW"
   Serial2.print(SSID_ESP);//from constant 
   Serial2.print("\",\"");
   Serial2.print(SSID_KEY);//form constant
   Serial2.print("\"\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),10000,0))//go look for keyword "OK"
    Serial2.println("ESP SSID SET OK");
  else
    Serial2.println("ESP SSID SET FAILED");   
  serial_dump_ESP();
  
  //This checks for and stores the IP address
  Serial2.println("CHECKING FOR AN IP ADDRESS");
  Serial2.print("AT+CIFSR\r\n");//command to retrieve IP address from ESP
  if(read_until_ESP(keyword_rn,sizeof(keyword_rn),10000,0)){//look for first \r\n after AT+CIFSR echo - note mode is '0', the ip address is right after this
  if(read_until_ESP(keyword_rn,sizeof(keyword_rn),1000,1)){//look for second \r\n, and store everything it receives, mode='1'
    //store the ip adress in its variable, ip_address[]
    for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_rn)+1); i++)//that i<=... is going to take some explaining, see next lines
       ip_address[i] = scratch_data_from_ESP[i];//fill up ip_address with the scratch data received
//i=1 because i=0 is the length of the data found between the two keywords, BUT this includes the length of the second keyword, so i<= to the length minus
//size of teh keyword, but remember, sizeof() will return one extra, which is going to be subtracted, so I just added it back in +1
    ip_address[0] = (scratch_data_from_ESP[0]-sizeof(keyword_rn)+1);//store the length of ip_address in [0], same thing as before
    Serial2.print("IP ADDRESS = ");//print it off to verify
    for(int i=1; i<=ip_address[0]; i++)//send out the ip address
    Serial2.print(ip_address[i]);
    Serial2.println("");
  }}//if first \r\n
  else
  Serial2.print("IP ADDRESS FAIL");
  serial_dump_ESP();
  
   Serial2.print("AT+CIPMUX=");// set the CIPMUX
   Serial2.print(CIPMUX);//from constant
   Serial2.print("\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//go look for keyword "OK" or "no change
    Serial2.println("ESP CIPMUX SET");
  else
    Serial2.println("ESP CIPMUX SET FAILED"); 
  serial_dump_ESP();
 

 //that's it!  Could be done by nesting everything together, so if one thing fails, it returns '0', and if it gets all the way through it returns '1'...oh well
  
  
}//setup ESP
