<?php

// insert header for json
header("Content-Type: application/json");


// Include config file
include("config.php");


// Get data from database
$sql = "select * from setup";
$result = mysqli_query( $conn, $sql );

$dataS = array();
foreach( $result as $row){
	$dataS[] = $row;
}
/*
$sql= "select * from tempAndHumid";
$result = mysqli_query($conn, $sql);
$dataT = array();
foreach( $result as $row){
	$dataT[]  = $row;
}	*/

mysqli_close($conn);

echo json_encode($dataS);
//echo json_encode($dataT);


?>