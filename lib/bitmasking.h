#ifndef _BIT_MASKING_H_
#define _BIT_MASKING_H_	

#define SET_BIT(BIT, REG) 		(REG) |=  (1 << (BIT))
#define CLR_BIT(BIT, REG) 		(REG) &= ~(1 << (BIT))
#define TOG_BIT(BIT, REG) 		(REG) ^=  (1 << (BIT))
#define GET_BIT(BIT, REG) 	    (((REG) >> (BIT)) & 1)

#endif /* _BIT_MASKING_H_ */
