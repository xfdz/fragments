// fileName: node1.cpp

#include <iostream>
#include <cstdlib>
#include "node1.h"

namespace main_savitch_s {


   // Precondition: previous_ptr points to a node in a linked list.
   //
   // Postcondition: A new node containing the given entry has been added
   // after the node that previous_ptr points to.
   //
   // NOTE: If there is insufficient memory for a new node, then bad_alloc 
   // is thrown before changing the list. 

   void 
   list_insert( node* previous_ptr, const node::value_type& entry ) {

      node *insert_ptr;

      insert_ptr = new node;

      insert_ptr->set_data( entry );

      previous_ptr->set_link( insert_ptr );
   }


   // Precondition: head_ptr is the head pointer of a linked list.
   //
   // Postcondition: The return value is a pointer to the first node 
   // containng the specified target in its data field. If ther is no
   // such node, the null pointer is returned.

   node *
   list_search( node* head_ptr, const node::value_type& target ) {

      node *cursor;

      for( cursor = head_ptr; cursor != NULL; cursor = cursor->link() ){
 
         if ( target == cursor->datat() ){ 
            return cursor; 
         }
      }

      return NULL;
   }

   // Precondition: head_ptr is the head pointer of a linked list.
   //
   // Postcondition: The return value is a pointer to the first node 
   // containing the specified target in its data field. If there is no
   // such node, the null pointer is returned.
   //
   // Library facilities used: cstdlib

   const node* 
   list_search( const node* head_ptr, const node::value_type& target ) {

      const node *cursor;

      for ( cursor = head_ptr; cursor != NULL; cursor = cursor->link() ){
   
         if( target == cursor->data() ){
            return cursor; 
         }

	 return NULL;
      }
   }

   // Preconditions: source_ptr is the head points of a linked list to copy
   //
   // Postconditions: head_ptr, and tail_ptr now point to a copy of linked list
   //
   //
   void
   list_copy( const node* source_ptr, node*& head_ptr, node*& tail_ptr){

      head_ptr = NULL;
      tail_ptr = NULL;

      if( source_ptr == NULL ){ 
         return; 
      }

      // Missing here something?
      list_head_insert( head_ptr, source_ptr->data() ); 

      source_ptr = source_ptr->link();

      while( source_ptr != NULL ) {
	  
         list_insert( tail_ptr, source_ptr->data() );

         tail_ptr = tail_ptr->link();

	 source_ptr = source_ptr->link();
      }
	   
   }

   //Precondition : head_ptr is the head pointer of a linked list, 
   //with at least one node
   //
   //Postcondition: The head node has been removed and returned to the
   //heap; head_ptr is now the head pointer of the new, shorter linked list.
   //
   void 
   list_head_remove( node*& head_ptr) {

      node *remove_ptr = head_ptr;

      head_ptr = head_ptr->link();

      delete remove_ptr;

   }

   //Precondition : previous_ptr pointes to anode in a linked list, and 
   //this is not the the tail node of the list.
   //
   //Postcondition: The node after previous_ptr has been removed from
   //from the linked list.
   //
   void
   list_remove( node* previous_ptr ) {

      node *remove_ptr = previous_ptr->link();

      previous_ptr->link( remove_ptr->link() );

      delete remove_ptr; 
   }


   //Precondition : head_ptr is the head pointer of a linked list.
   //
   //Postcondition: All nodes of the list have been deleted, and 
   //head_ptr is now NULL
   //
   //Library facilities used: cstdlib
   void 
   list_clear( node*& head_ptr ){

      while( head_ptr != NULL ) 
         list_head_remove( head_ptr );

   }

   //Precondition: head_ptr is the head pointer of a linked list
   //
   //PostCondition: The value returned is the number of nodes in 
   // the linked list
   std::size_t
   list_length( const node* head_ptr ){

      const node * cursor;
      int answer = 0; 
    
      for( cursor = head_ptr; cursor != NULL;  cursor = curser->link() ){
         ++answer;
      }

      return answer;
  
   }

   //Precondition:
   //
   //Postcondition:
   void
   list_head_insert( node*& head_ptr, const node::value_type& entry ){ 

      head_ptr = new node( entry, head_ptr );
   } 

   //Precondition: head_ptr is the head pointer of a linked list
   //
   //Postcondition: The node that's being looked up will be returned.
   //
   node*
   list_locate( node* head_ptr, std::size_t position ) {  
   
      node * cursor = head_ptr;
      int i; 

      for(i = 0; ( cursor != NULL; ) && ( i < position; )  ++i ) {
           cursor = cursor->link(); 
      }

      return cursor;
   }
}
