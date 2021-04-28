#!/usr/bin/perl -w

# Generate performance report table from the measurements listed in the codes

sub report
{
	my($src) = shift @_;
	my($type) = shift @_;

	my($ext) = $src;
	$ext =~ s/^.*\.//g;
	my($label) = "// BENCH";
	if ($ext eq "py")
	{
		$label = "# BENCH";
	}

	my(@lines) = split("\n", `cat $src | grep "$label"`);
	foreach $line (@lines)
	{
		$line =~ s/$label //g;

		if ($line =~ m/$type\s(?<VALUE>(.*))/)
		{
			return $+{VALUE};
		}
	}

	return "$src UNDEFINED";
}

my(@srcs) = split("\n", `find src/tests -name "arrsin*"`);

print "Name | Time | Check | Executable\n";

foreach $src (@srcs)
{
	my($name) = report($src, "NAME");
	my($time) = report($src, "SCORE");
	my($check) = report($src, "CHECK");
	my($executable) = report($src, "EXEC");

	print "$name | $time | $check | $executable\n";
}

