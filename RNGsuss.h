#if !defined(RNGSUSS_H)
#define RNGSUSS_H

//XORShift courtesy of Sebastiano Vigna
//     http://vigna.di.unimi.it/
//Assert implementation courtesy of Casey Muratori
//     http://mollyrocket.com/
//     https://handmadehero.org/

//requres stdint.h
#define Assert(X) if(!(X)){*(int *)0 = 0;}

//RNGsuss starts with default seed but it is strongly recommended that any
//user at the very least reseed before beginning any use.
class RandomState
{
  // should be changed 
	uint64_t CurrentSeed = 1489462064285902538LL;

	uint32_t Const_a = 12;
	uint32_t Const_b = 25;
	uint32_t Const_c = 27;
	
	//could be (but should be) changed
	uint64_t ScrambleValue = 2685821657736338717LL;
	
	uint64_t TempSeed = 0;
	
	void Reseed(uint64_t);
	void ChangeScramble(uint64_t);
	void ChangeConsts(uint32_t,
                  	uint32_t,
                  	uint32_t);
  uint64_t NextNum();
  uint64_t NewSeededNum(uint64_t);
  uint64_t NextSeededNum();
}

//ChangeScramble, ChangeConsts should all be done only once at the
//beginning of execution, if at all. Once ChangeScramble or 
//ChangeConsts is called all seeds from the prior state will no longer be 
//valid

inline void
RandomState::Reseed(uint64_t NewSeed)
{
	State->CurrentSeed = NewSeed;
}

inline void
RandomState::ChangeScramble(uint64_t NewScramble)
{
	//NOTE: THIS WILL CHANGE ALL PREVIOUS SEEDED OUTPUTS
	State->ScrambleValue = NewScramble;
}

inline void
RandomState::ChangeConsts(uint32_t New_a,
                					uint32_t New_b,
                					uint32_t New_c)
{
	//Note: As with the changed scramble, changing the bitshift constants will alter all seeded outputs
	//		some constants work better than others
	//		all constants detail the bitshift, so must be less than 64
	
	Assert(New_a < 64 && New_a != 0);
	Assert(New_b < 64 && New_b != 0);
	Assert(New_c < 64 && New_c != 0);
	Assert(New_a != New_b != New_c);

	Const_a = New_a;
	Const_b = New_b;
	Const_c = New_c;
}

//next pseudorandom value in the series
inline uint64_t
RandomState::NextNum()
{
	uint64_t Number;
	Number ^= CurrentSeed >> Const_a;
	Number ^= Number << Const_b; 
	Number ^= Number >> Const_c;
	Number *= ScrambleValue;

	CurrentSeed = Number;

	return Number;
}

//first pseudorandom value in an alternate series
inline uint64_t
RandomState::NewSeededNum(uint64_t Seed)
{
	uint64_t Number;
	TempSeed = Seed;
	
	Number ^= TempSeed >> Const_a;
	Number ^= Number << Const_b;
	Number ^= Number >> Const_c; 
	Number *= ScrambleValue;

	TempSeed = Number;

	return Number;
}

//next pseudorandom value in an alternate series
inline uint64_t
RandomState::NextSeededNum()
{
	Assert(TempSeed != 0);
	uint64_t Number;
	
	Number ^= TempSeed >> Const_a;
	Number ^= Number << Const_b; 
	Number ^= Number >> Const_c; 
	Number *= ScrambleValue;

	TempSeed = Number;
	return Number;
}

//zero alternate series to avoid confusion
inline uint64_t
RandomState::EndSeededNum()
{
  TempSeed = 0
}
#endif
