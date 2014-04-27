
use strict;
use warnings;
use IO::File;
use Error;

my $file;

# grab file name from user
usage() if(!defined( $file = $ARGV[0] ));

my $fh = IO::File->new( $file, "r")
or throw Error::Simple("ERROR: Opening file: $!");

# tranformation happens here
while(my $line = <$fh>){
    chomp($line);
    my @tokens = split(/,/,$line);

    # pad field with empty string if missing
    foreach(0..3){
        $tokens[$_] = "" if(! defined $tokens[$_]);
    }

    print $tokens[3] . "," . $tokens[0] . "," . $tokens[2] . "\n";
}

sub usage {
    throw Error::Simple( 
     "WARNING: usage\n CsvTransform.pl </path/to/file/filename>\n "
    );
}

=pod

=head1 SYNOPSYS

Write a unix filter in perl (program that reads stdin and writes stdout) that
will reformat a multi-record, comma delimited file with 4 fields per line and
select only fields 1,3,4 and output the fields in the order 4,1,3. Assume
that the file is massive and cannot be processed in memory.

for example:

=head1 AUTHOR

Javier Fernandez <javierfernandez108@gmail.com>

=cut

john@chtah.com,Doe,John,M

becomes

M,john@chtah.com,John

