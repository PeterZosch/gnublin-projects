<title>irCube by Theile and Koch Productions</title>
<meta name="viewport" content="width=device-width; initial-scale=1.0; maximum-scale=1.0;"/>
<select name="remotes" id="remotes">
  <option value="sat">SAT</option>
  <option value="alx">ALX</option>
</select>
<form action="" method="post">
<input type="submit" name="button1" value="MUTE">
<input type="submit" name="button2" value="VOL UP">
<input type="submit" name="button3" value="VOL DOWN">
<br></br>
<input type="submit" name="button4" value="Button 4">
<input type="submit" name="button5" value="Button 5">
<input type="submit" name="button6" value="Button 6">
<br></br>
<input type="submit" name="button7" value="Button 7">
<input type="submit" name="button8" value="Button 8">
<input type="submit" name="button9" value="Button 9">
</form>

<?php

$remote = $_POST['remotes'];
echo $remote;
 
if($_POST['button1'] != '') {
	$output = "<pre>".shell_exec("irsend alx MUTE")."</pre>";
	echo $output;
}

if($_POST['button2'] != '') {
	$output = "<pre>".shell_exec("irsend alx VOLUP")."</pre>";
	echo $output;
}

if($_POST['button3'] != '') {
	$output = "<pre>".shell_exec("irsend alx VOLDOWN")."</pre>";
	echo $output;
}
?>