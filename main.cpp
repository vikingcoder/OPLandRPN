#include "convertopl.h"

main(int argc, char *argv[])
{
        ConvertOPL s;
      //  s.fromOPL("(8+2*5)/(1+3*2-4)");
        s.fromRPN("8 2 5 * + 1 3 2 * + 4 - /");

    system("pause");

}
