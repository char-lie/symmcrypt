#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#define LOG(msg) cerr << msg << endl
#include "CryptoSystem.h"

using namespace std;
using namespace NTL;

int main (int argsLength, char* args[])
{
    LOG("");
    LOG("Hi! Let's rock the cryptography!");
    LOG("");

    GF2X::HexOutput = false;
    /* INPUT */
    LOG("INITIAL DATA");
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
    LOG("Generator: " << cs->p << ", degree: " << deg(cs->p));
    LOG("N: " << cs->N);
    LOG("M: " << cs->M);
    LOG("");
    /* End data checking */
    /* End initialization */

    LOG("GENERATION");
    cs->generateIterationPolynomial();
    LOG("Iteration polynomial generated");
    cs->calculateF();
    LOG("F calculated");
    cs->calculateG();
    LOG("G calculated");
    cs->generateVectorValuedFunctions();
    LOG("Vector-valued functions generated");
    cs->generateLongVectorValuedFunctions();
    LOG("Vector-valued functions transformed from GL2 to LONG");
    LOG("");

    LOG("CALCULATIONS");
    cs->calculateDisbalances();
    LOG("Disbalances calculated");
    cs->calculateErrorsCoefficients();
    LOG("Errors coefficients calculated");
    cs->calculateWalsh();
    LOG("Walsh coefficients calculated");
    LOG("");

    /*
    cout << "WALSH1" << endl << cs->walshCoefficients[0] << endl;
    cout << "WALSH2" << endl << cs->walshCoefficients[1] << endl;
    */

    return 0;
}
