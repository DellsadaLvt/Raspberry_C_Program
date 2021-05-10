<?php
// send a json message to website
header('Content-Type: application/json');

// connect database
include("config.php");

// read data
$sql = "select * from accounts";
$result = mysqli_query($conn, $sql);

// sent to web
$data = array();
foreach($result as $row)
{
    $data[] = $row;
}
// disconnect
mysqli_close($conn);

echo json_encode($data);
?>