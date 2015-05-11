--TEST--
unserialize test, native unserialize
--SKIPIF--
<?php if (!extension_loaded("unserialize2")) print "skip"; ?>
--FILE--
<?php 

$s = 'O:8:"stdClass":1:{s:1:"0";i:123;}';

$obj = unserialize($s);

echo serialize($obj);

?>
--EXPECT--
O:8:"stdClass":1:{s:1:"0";i:123;}
