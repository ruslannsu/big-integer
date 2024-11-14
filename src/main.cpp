#include <iostream>

#include "BigInt.h"

int main()
{
    BigInt bg = BigInt("9453989039349045356744646540393912345765475434458397854389");
   // BigInt bg = BigInt("5765");
    BigInt bg2; bg2 = BigInt("1999999999554311151445757974567543215678985974389578378534895789347859348979");

    bg*=bg2;
    bg.TempPrint();



}
