<?php
// declare header
header("Content-Type: application/json");

// include config
include("config.php");


//read data from database
//$sql	= "select * from medical_inf order by id desc limit 1";
$sql = "select * from medical_inf where id = (select max(id) from medical_inf)";
$result = mysqli_query($conn, $sql);
//$row	= mysqli_fetch_row($result);

$data = array();
foreach( $result as $row){
	$data[] = $row;
}

mysqli_close($conn);
echo json_encode($data);


?>