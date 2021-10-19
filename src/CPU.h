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
//																		 //
///////////////////////////////////////////////////////////////////////////

#include <stdint.h>

class SharpCPU {
	public:
		SharpCPU();
		~SharpCPU();

		bool loadApplication(const char* filename);
		void emulateCycle();


	private:

		unsigned short pc;
		unsigned short opcode;

		uint8_t workRam[8192]; //(size == 8K)
		uint8_t videoRam[8192]; 

		int init();
};
