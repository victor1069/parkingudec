<?php

//http://parkingudec.ml/from_micro.php?unit=1&sensor=123

//loop through and grab variables off the URL
foreach($_REQUEST as $key => $value)
{
if($key =="unit"){
$unit = $value;
}

if($key =="sensor"){
$sensor = $value;
}
}//for each


// Create connection to SQL database
$con=mysqli_connect("mysql.hostinger.es","u205928359_manti","zT9U1bUHnB","u205928359_parki");// server, user, pass, database
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
//update sensor value in database
mysqli_query($con,"UPDATE ESPtable SET SENSOR = $sensor
WHERE id=$unit");


//if we need to get the time from the internet, use this.  This sets teh timezone
date_default_timezone_set('America/Bogota');
$t1 = date("gi");//many different possible formats, but this gives 12 hr format, and returns 1:23 as 123

//pull out the table
$result = mysqli_query($con,"SELECT * FROM ESPtable");//table select

//loop through the table and filter out data for this unit id
while($row = mysqli_fetch_array($result)) {
if($row['id'] == $unit){
$d1 = $row['LED'];
$d2 = $row['SENSOR'];
echo "_t1$t1##_d1$d1##_d2$d2##";
}

}//while

if($sensor >200){//send alarm as text message using email function
mail("0001112222@vtext.com", "ALARM", "Sensor=$sensor", "Unit=$unit");
}

?>