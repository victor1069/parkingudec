<?php
//get the post variables
$value = $_POST['value'];
$unit = $_POST['unit'];
$column = $_POST['column'];
//connect to the database
$con=mysqli_connect("mysql.hostinger.es","u205928359_manti","zT9U1bUHnB","u205928359_parki");// server, user, pass, database

// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
//update the value
mysqli_query($con,"UPDATE ESPtable SET $column = '{$value}'
WHERE id=$unit");
//echo "changed";




//go back to the interface
header("location: interface.php");



    ?>