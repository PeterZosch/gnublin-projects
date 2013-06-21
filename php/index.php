<html>
<head>
<title>irCube by Theile and Koch Productions</title>
<meta name="viewport" content="width=device-width">
<meta name="viewport" content="initial-scale=1.0, user-scalable=no">
<meta name="apple-mobile-web-app-capable" content="yes">
</head>
<body background="gif/wallpaper.gif">
<form action="" method="post">
<table border=1>
<tr><td>
<select name="remotes"> 
  <option value="sat"<?php echo($_POST['remotes']=='sat'?' selected="selected"':'');?>>SAT</option>
  <option value="alx"<?php echo($_POST['remotes']=='alx'?' selected="selected"':'');?>>ALX</option>
</select>
</td></tr>
<tr align="center" valign="middle">
<td><input type="image" src="gif/minus_96.gif" name="minus"></td>
<td><input type="image" src="gif/mute_96.gif" name="mute"></td>
<td><input type="image" src="gif/plus_96.gif" name="plus"></td>
</tr>
</table>
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
</body>
</html>
