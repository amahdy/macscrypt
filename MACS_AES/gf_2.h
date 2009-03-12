/* 
 * File:   gf_2.h
 * Author: Paula
 *
 * Created on March 12, 2009, 4:12 PM
 */

#ifndef _GF_2_H
#define	_GF_2_H

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//			Finite Fields Of the Form GF(2n)
//	Done by : Paula Mansour Fouad
//	Date	: 21-01-2008
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
class GF_2_
{
private:
	unsigned char oneb ;
public:
	unsigned char MultiplyBy2GF2(unsigned char byte);
	unsigned char MultiplyBy3GF2(unsigned char byte);
	unsigned char MultiplyGF2(unsigned char byte,unsigned char b);
};

#endif	/* _GF_2_H */

