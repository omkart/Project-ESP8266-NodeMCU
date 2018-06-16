<?php   
    include 'dbconnect.php';
    if ($conn->connect_error)
	{
		die("Connection failed: " . $conn->connect_error);
	}
	else
	{
        $value = $_GET["name"];
        echo $value;
        $insert="INSERT INTO `temperature`(`temperature`) VALUES (".$value.");";
        mysqli_query($conn, $insert);
	}
	$conn->close();
?>