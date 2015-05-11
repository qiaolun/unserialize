--TEST--
ZE2 Serializable
--FILE--
<?php



$test = array();
$item = array('String', NULL, 42, false);

for($i = 0; $i < 10000; $i++) {
    $test[] = $item;
}

$v = serialize($test);
$c = unserialize($v);

$mu = memory_get_usage();
for($i = 0; $i < 100 ; $i++) {
    $c = unserialize($v);
}

$mu2 = memory_get_usage();

if( ($mu2 - $mu) / $mu < 0.1 ) {
    echo 'OK'.PHP_EOL;
}

?>
<?php exit(0); ?>
--EXPECTF--
OK
