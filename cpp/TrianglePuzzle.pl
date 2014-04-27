#!/usr/bin/perl 

use strict;
use warnings;
use IO::File;
use Carp;
use POSIX;

&main();

sub main {

    my $filename = $ARGV[0];
    if( !defined $filename ){
        usage();
    }
    elsif(! -e $filename ){
        usage("ERROR: file $filename not found"); 
    }

    my $interval = 2;
    my $sum = TrianglePuzzleSum($filename, $interval);
    print "maximum sum for the triangle: " . $sum . "\n";
    exit();
}

sub TrianglePuzzleSum {

    my ( $filename, $interval ) = @_; 
    my $file = IO::File->new($filename,"r") 
               or confess( "ERROR: " . $! ); 

    while( <$file> ){
    # read a line
        chomp($_);
        my @line = split(//,$_);
 

    }
    return $sum;
}


sub _tokenizer{
  
   my $
 
    my $sum     = 0;
    my $number  = 0;
    my $indigit = 0;
    my $begin   = 0;
    my $character_count = 0; 
    my @current_line;
        
    foreach my $char (@line){
            ++$character_count; 
            if( $char =~ m/ \s /x ){
                next if( $indigit == 0 ); # not scanning digit 

                $indigit = 0;
                $number = join('', @integer);
                my $number_ref = {
                    integer => $number, 
                    begin   => $begin,   
                    end     => $character_count, 
                };
 
                push(@integer, $number_ref); 
                next;
            }
            if( $indigit == 0 ){
                $begin = $character_count;
                $indigit = 1;
            }
            push(@integer, $char);
        } 
    }
}

sub usage{
    my $estring = shift;
    print $estring if( defined $estring );
    print "\nUsage: ./TrianglePuzzle <TriangleFile.txt>\n"; 
    exit();
}

=pod

=head1 SYNOPSYS

   TRIANGLE PUZZLE

=cut

=head1 DETAILS

 By starting at the top of the triangle and moving to adjacent 
 numbers on the row below, the maximum total from top to bottom is 27..

      5
     9 6
    4 6 8
   0 7 1 5

I.e. 5 + 9 + 6 + 7 = 27.

=cut

=head1 AUTHOR

 Javier Fernandez <javierfrdz@gmail.com>

=cut

