# RNGsuss
Random Number generation library

Currently implements XORshift, will expand to other methods in the future.

To use, place RNGsuss.h in your project directory and #include "RNGsuss.h".
From there, instantiate the RandomState class and use the functions:
Reseed()
ChangeScramble()
ChangeConsts()
to personalize your own pRNG implementation or simply use the default values
included (courtesy of Sebastian Vigna). 

For default number generation, use the function:
NextNum()
Please be aware that if you do not reseed at runtime, this is effectively
identical to the seeded generation below, and you will _not_ get the
appearance of randomness.

To use seeded generation, use the
functions:
NewSeededNum()
NextSeededNum()
EndSeededNum()
The NewSeededNum function is passed the seed which _only_ sets the tempSeed.
By default the temporary seed will be set to 0. NextSeededNum is used to
retrieve all subsequent values in the seeded series. Use EndSeededNum to
reset the temporary seed property to 0 for error-catching.

*Note: Please ensure that when using seeded generation you are not using
the seed value as your first random number.

A general assert statement is included so for more detailed error messages
please consider implementing your own preferred method of error catching.

I think that is everything, please feel free to suggest features or tell me
what you didn't like about RNGsuss, and most of all enjoy!
