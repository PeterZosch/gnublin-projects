<title>irCube by Theile and Koch Productions</title>
<meta name="viewport" content="width=device-width; initial-scale=1.0; maximum-scale=1.0;"/>
<body background="gif/wallpaper.gif">
</body>
<form action="" method="post">
<select name="remotes"> 
  <option value="sat"<?php echo($_POST['remotes']=='sat'?' selected="selected"':'');?>>SAT</option>
  <option value="alx"<?php echo($_POST['remotes']=='alx'?' selected="selected"':'');?>>ALX</option>
</select>
<br></br>
<br></br>
<input type="image" src="gif/minus_96.gif" name="minus">
<input type="image" src="gif/mute_96.gif" name="mute">
<input type="image" src="gif/plus_96.gif" name="plus">
</form>

<?php

$remote = $_POST['remotes'];
 
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
