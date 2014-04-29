#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#include "CryptoSystem.h"

#define LOG(msg) cerr << msg << endl

using namespace std;
using namespace NTL;

const unsigned int parametersLength = 3;
string parameters[] = {"F", "G", "K"};

void showUsage () {
    for (unsigned int i=0; i<parametersLength; i++) {
        cout << parameters[i] << endl;
    }
}

int main (int argsLength, char* args[])
{
    if (argsLength == 1) {
        showUsage();
        return 1;
    }
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
    cs->calculateWeights();
    cs->calculateErrorsCoefficients();
    return 0;
}
