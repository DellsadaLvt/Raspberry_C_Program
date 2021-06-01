<?php

header("Content-type: application/json");


include("config.php");


$sql = "select * from control";
$result = mysqli_query($conn, $sql);

$data= array();
foreach ( $result as $row){
	$data[] = $row;
}

mysqli_close($conn);

echo json_encode($data);



?>