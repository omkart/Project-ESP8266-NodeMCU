<?php
    include 'dbconnect.php';
    $response=[];
    if ($conn->connect_error)
	{
		die("Connection failed: " . $conn->connect_error);
	}
	else
	{
        $sql="SELECT * FROM `temperature` WHERE 1";
        $result = mysqli_query($conn, $sql);
		if (mysqli_num_rows($result) > 0)
		{
			while($row = mysqli_fetch_assoc($result))
			{
				array_push($response,$row);
			}
		}
		//array_push($superresponse,$response);
		//$superresponse=array_fill_keys($superresponse,'event');
		echo json_encode($response);
	}
	$conn->close();
?>