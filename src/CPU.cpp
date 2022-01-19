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

#include "CPU.h"
#include <unordered_map>

CPU::CPU(){
	pc = 0x100;
	opcode = 0;
	I = 0;
	sp = 0;

	for (int i = 0; i < 65535; i++)
		memory[i] = 0;
	for (int i = 0; i < 8; i++)
		V[i] = 0;
}

CPU::~CPU() {

}

int CPU::init() {
	//set starting program counter address (which is $100)
	//set position for starting opcode
	//set beginning index register
	//set current stack pointer
	//Write scrolling nintendo text into memory address

}

bool CPU::initialRead(const char* filename) {
	//add all opcode conversions into a private map

}

void CPU::emulateCycle() {

}

void CPU::opcodeDecode() {


}

void CPU::opcodeExecute() {

}

/*						Things to implement after Alpha					*/
/*						Echo Ram										*/				