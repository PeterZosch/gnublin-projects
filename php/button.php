<title>irCube by Theile and Koch Productions</title>
<meta name="viewport" content="width=device-width; initial-scale=1.0; maximum-scale=1.0;"/>
<form action="" method="post">
<select name="remotes"> 
  <option value="sat"<?php echo($_POST['remotes']=='sat'?' selected="selected"':'');?>>SAT</option>
  <option value="alx"<?php echo($_POST['remotes']=='alx'?' selected="selected"':'');?>>ALX</option>
</select>
<br></br>
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
<br></br>
<input type="image" src="minus.gif" name="minus">
<input type="image" src="mute.gif" name="mute">
<input type="image" src="plus.gif" name="plus">
</form>

<?php

$remote = $_POST['remotes'];
 
if($_POST['button1'] != '') {
	$output = "<pre>".shell_exec("irsend $remote MUTE")."</pre>";
	echo $output;
}

if($_POST['button2'] != '') {
	$output = "<pre>".shell_exec("irsend $remote VOLUP")."</pre>";
	echo $output;
}

if($_POST['button3'] != '') {
	$output = "<pre>".shell_exec("irsend $remote VOLDOWN")."</pre>";
	echo $output;
}

if(isset($_POST['minus_x'] )) {
	$output = "<pre>".shell_exec("irsend $remote CHDOWN")."</pre>";
	echo $output;
}

if(isset($_POST['mute_x'] )) {
	$output = "<pre>".shell_exec("irsend $remote MUTE")."</pre>";
	echo $output;
}

if(isset($_POST['plus_x'] )) {
	$output = "<pre>".shell_exec("irsend $remote CHUP")."</pre>";
	echo $output;
}
?>
