<?php
// connect to databases
include("config.php");

//
$red = $green = $blue = 0;
$sql = "select * from rgbValue";
$result = mysqli_query($conn, $sql);
$rgb = mysqli_fetch_row($result); // rgb[0]->red, rgb[1]->blue vv.
$color = ($rgb[0]<<16)|($rgb[1]<<8) |$rgb[2];  // 24bits

if($_SERVER["REQUEST_METHOD"]== "POST"){
	$red= $_POST["red"];
	$green = $_POST["green"];
	$blue = $_POST["blue"];
	
	$sql = "update rgbValue set red=$red, blue=$blue, green=$green, isUpdated=1";
	mysqli_query($conn, $sql);
	
	$sql = "select * from rgbValue";
	$result = mysqli_query($conn, $sql);
	$rgb = mysqli_fetch_row($result); // rgb[0]->red, rgb[1]->blue vv.
	$color = ($rgb[0]<<16)|($rgb[1]<<8) |$rgb[2];  // 24bits
	
}

mysqli_close($conn);
?>


<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Control Led</title>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">

        <style>
            body{
                font-size: 20px;
                color: black;
                background-color: #BDC3C7  ;
                font-style: inherit;
            }

            .wrapper{
                float: left;
                width: 30%;
                height: 500px;
                margin: 20px;
                padding: 10px;
            }

            .box{
                width: 50%;
                height: 50%;
                margin: auto;
            }

            .table_size{
                margin: auto;
                width: 70%;
            }
        </style>
    </head>
    
    <body>
        <div class="wrapper border border-3 rounded rounded-2 border-primary">
            <h3>LED RGB</h2><br>
            <form acticon="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>"   method="POST">
                <div class="mb-3">
                    <label class="form-label">Brightness</label><br>
                    <input type="range" name="redBright" class="form-range" min="0" max="10" id="brightness">
                </div>

                <div class="form-text">Scroll the slider to select the LED brightness</div>
                <div class="mb-3">
                    <label class="form-label">Color Adjustment</label><br>
                    <label>R:</label><input type="range" name="red" class="form-range" min="0" max="255" id="red"><br>
                    <label>G:</label><input type="range" name="green" class="form-range" min="0" max="255" id="green"><br>
                    <label>B:</label><input type="range" name="blue" class="form-range" min="0" max="255" id="blue"><br>
                </div>

                <input type="submit" class="btn btn-primary" value="Apply"><br>
            </form>
        </div>


        <div class="wrapper border border-3 rounded border-primary">
            <h3>CURRENT COLOR</h3><br>
            <div class="box border border-info" style="background-color:#<?php echo dechex($color); ?>;"></div><br>
            
            <div>
                <h5>Current color</h5><br>
                <table class="table table_size">
                    <thead>
                        <tr>
                            <th scope="col">Red</th>
                    <th scope="col">Green</th>
                    <th scope="col">Blue</th>
                        </tr>
                    </thead>
                    
                    <tbody>
                        <tr>
                            <td><?php echo $rgb[0] ?></td>
                            <td><?php echo $rgb[1] ?></td>
                            <td><?php echo $rgb[2] ?></td>
                        </tr>
                    </tbody>

                </table>
            </div>
        </div>
    </body>
</html>