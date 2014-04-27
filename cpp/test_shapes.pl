package Tetris::Shape;

use strict;
use Data::Dumper;
use Class::Accessor;

use fields qw(ths);
use base qw( Class::Accessor );
my @accessors = keys %Tetris::Shape::FIELDS;

__PACKAGE__->mk_accessors( @accessors );

sub new {

   my $class = shift;

   my $data = shift;

   my $self = fields::new($class);

   return $self; 

}
