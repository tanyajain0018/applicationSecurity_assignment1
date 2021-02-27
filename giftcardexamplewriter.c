/*
  * Gift Card Example Writer
  * Original Author: Shoddycorp's Cut-Rate Contracting
  * Maintainer: ???
  * Comments added by Justin Cappos (JAC)
  * Modification Date: 8 July 2020
  */

 #include <stdio.h>
 #include "giftcard.h"
 /* JAC: Why is this included? */
 #include <time.h>

 struct this_gift_card examplegc;
 struct gift_card_data examplegcd;
 struct gift_card_record_data examplegcrd;
 struct gift_card_amount_change examplegcac;
 struct gift_card_program hang; 


 // Break it up so that we don't have long functions!  Good programming style!
 //  (JAC: This is so wrong.  Global variable use / initialization is a 
 //  terrible thing to do.)
 void setupgc() {
 	examplegc.num_bytes = 10;
 	examplegc.gift_card_data = (void *) &examplegcd;
 	examplegcd.merchant_id = "GiftCardz.com                   ";
 	examplegcd.customer_id = "DuaneGreenes Store 1451         ";
 	examplegcd.number_of_gift_card_records = 1;

 	/* JAC: Something seems fishy... */
 	examplegcd.gift_card_record_data = malloc(examplegcd.number_of_gift_card_records);
 	/* JAC: here too! */
	examplegcd.number_of_gift_card_records = -1;
 	examplegcd.gift_card_record_data[0] = (void *) &examplegcrd;
 	examplegcrd.record_size_in_bytes = 44;
 	examplegcrd.type_of_record = 1; // JAC: Should be enum!  amount_change
 	examplegcrd.actual_record = (void *) &examplegcac;
 	examplegcac.amount_added = 2000;
 	examplegcac.actual_signature = "[ insert crypto signature here ]";
 	examplegcrd.actual_record = (void *) &hang;
	hang.message = malloc(32);
	hang.message = "Please work";
	hang.program = malloc(128);
	hang.program[0] = 0x09; // to get it to reach case 9
	hang.program[1] = 253;
	
	//examplegc.gift_card_data = -1;
 }



 // moved into separate files to avoid erroenous style checker error...
 /* JAC: opening and writing a fixed filename using a global is terrible style.
  *     the style checker was right!  This code is terrible   
  */
 void writegc() {
 	FILE *fd1;
 	// JAC: Why don't any of these check for error return codes?!?
 	fd1 = fopen("crash2.gft","w");
 	fwrite(&examplegc.num_bytes,1,1,fd1);
 	fwrite(examplegcd.merchant_id,1,1,fd1);
 	fwrite(examplegcd.customer_id,1,1,fd1);
 	fwrite(&examplegcd.number_of_gift_card_records,1,1,fd1);
 	fwrite(&examplegcrd.record_size_in_bytes,1,1,fd1);
 	fwrite(&examplegcrd.type_of_record,1,1,fd1);
 	fwrite(&examplegcac.amount_added,1,1,fd1);
 	fwrite(examplegcac.actual_signature,1,1,fd1);
    fwrite(hang.message, 1, 1, fd1);
    fwrite(hang.program, 1,1,fd1);
 	fclose(fd1);
 }

 /* JAC: No args and return -1 for no reason!?! */
 int main(void) {
 	setupgc();
 	writegc();
 	return -1;
 }