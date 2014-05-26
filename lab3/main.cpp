#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#define LOG(msg) cerr << msg << endl
#include "CryptoSystem.h"

using namespace std;
using namespace NTL;

int main (int argsLength, char* args[])
{
    GF2X::HexOutput = false;
    /* INPUT */
    /* Generator as a long number */
    const unsigned long pNumber = (1<<15) + (1<<1) + 1;
    /* N (from lab document) */
    const long N = (1 << 15) - 2;
    /* M (from lab document) */
    const long M = (1 << 14) - 1;
    /* END INPUT */

    /* Initialize cryptosystem */
    CryptoSystem *cs = new CryptoSystem(pNumber, N, M);
    /* Check data */
    LOG(cs->p);
    LOG(cs->N);
    LOG(cs->M);
    /* End data checking */
    /* End initialization */

    cs->generateIterationPolynomial();
    cs->calculateF();
    cs->calculateG();
    cs->generateCoordinateFunctions();
    cs->calculateWeights();
    cs->calculateErrorsCoefficients();

    //LOG(cs->weights[0]);
    return 0;
}
