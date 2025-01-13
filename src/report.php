<?php
/*
*/

/*** UTIL***/

	function writeText($some_text){
		$filename="temp.txt";
		$myfile = fopen($filename, "a") or die("Unable to open file!");
		fwrite($myfile,"$some_text \n");
		fclose($myfile);	
	}

    function sanitiseInput($s){
        if (preg_match("/[<>'".'"'."]/",$s)) {
			return false; 
		}
        return true;
    }

/****RECIEVE REPORT****/
	if(isset($_POST['r'])){
		$report=$_POST['r'];
        if(!sanitiseInput($report)) die("E1");
	} 
	else{
		die("E2");
	}
	
	$client_ip = $_SERVER['REMOTE_ADDR'];
echo "Your IP address is: " . $client_ip;



    writeText($report." IP:".$client_ip);

exit("okay");

?>