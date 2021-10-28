///////////////////////////////////////////////////////////////////////////
//This is an implementation of a Sharp LR35902 Processor				 //
/////////////////////////////////////////////////////////////////////////// 
// Specs:																 //
// CPU freq  : 4.194304 MHz												 //
// Work Ram  : 8 KB														 //
// Video Ram : 8 KB														 //
// Resolution: 8 KB														 //
// OBJ ("Sprites"): 8 x 8 or 8 x 16; max 40 per screen, 10 per line		 //
// Palettes: BG: 1x4, OBJ: 2 x 3										 //
// Colors: 4 shades of green											 //
// Horizontal sync: 9.198 KHz											 //
// Vertical sync:   59.73 Hz											 //
///////////////////////////////////////////////////////////////////////////								
// This processor uses a technique called fetch/execute overlap.  What   //
// this means is that an opcode is fetched in parallel with the          //
// instruction execution.  The CPU cannot use the opcode in the same     //
// cycle i.e. the CPU cannot use the data during the same M-cycle so we  //
// can say that the true minimum effective duration of instructions is   //
// 2 machine cycles.													 //
//																		 //
// 																		 //
///////////////////////////////////////////////////////////////////////////

#include "SharpSM83.h"

SharpSM83::SharpSM83(){

}

SharpSM83::~SharpSM83() {

}

int SharpSM83::init() {
	//set starting program counter address (which is $100)
	//set position for starting opcode
	//set beginning index register
	//set current stack pointer
	//Write scrolling nintendo text into memory address

}

bool SharpSM83::initialRead(const char* filename) {

}

void SharpSM83::emulateCycle() {

}

