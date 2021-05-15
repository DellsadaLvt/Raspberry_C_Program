<?php

// insert header for json
header("Content-Type: application/json");


// Include config file
include("config.php");


// Get data from database, select last five rows
$sql= "select * from tempAndHumid where id> ((select max(id) from tempAndHumid) -5)";
$result = mysqli_query($conn, $sql);
$dataT = array();
foreach( $result as $row){
	$dataT[]  = $row;
}	

mysqli_close($conn);

echo json_encode($dataT);


?>