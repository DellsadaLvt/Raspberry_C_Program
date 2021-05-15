<?php

// Add config.php
include("config.php");
	
// get data form web
$stateLed = $_POST["stateLed"];
$timeOnLed = $_POST["timeOnLed"];
$timeOffLed = $_POST["timeOffLed"];

$statePump = $_POST["statePump"];
$timeOnPump = $_POST["timeOnPump"];
$timeOffPump = $_POST["timeOffPump"];

$mode = $_POST["mode"];	


// add data to database
/*$sql = "insert into setup ( mode,  stateLed,   statePump, timeOnLed, timeOffLed , timeOnPump, timeOffPump) 
					values('$mode','$stateLed','$statePump', '$timeOnLed', '$timeOffLed' , '$timeOnPump', '$timeOffPump')";*/

$sql = "update setup set mode='$mode', stateLed='$stateLed', statePump='$statePump',
						timeOnLed='$timeOnLed', timeOffLed='$timeOffLed',
						timeOnPump='$timeOnPump', timeOffPump='$timeOffPump'";
// update data						
mysqli_query($conn, $sql);

// close connect
mysqli_close($conn);


?>



