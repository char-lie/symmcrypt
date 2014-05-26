#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#include <NTL/vector.h>
using namespace std;
using namespace NTL;

struct CryptoSystem {
    GF2X p;
    long N;
    long M;
    GF2XModulus P;
    long generatorDegree;
    long maxPolynomial;
    Vec<GF2X> iterationPolynomial;

    static const long FunctionsCount = 2;
    Vec<GF2X> polynomials[FunctionsCount];
    Mat<GF2X> coordinateFunctions[FunctionsCount];
    Vec<long> weights[FunctionsCount];

    Vec<long> K[FunctionsCount];

    GF2X f(GF2X x) {
        return PowerMod(x, this->N, this->P);
    }

    GF2X g(GF2X x) {
        return PowerMod(x, this->M, this->P);
    }

    void generateIterationPolynomial () {
        iterationPolynomial.kill();
        iterationPolynomial.SetLength(this->maxPolynomial);
        for (long i=0; i<this->maxPolynomial; i++) {
            iterationPolynomial[i] = CryptoSystem::getPolynomial(i);
        }
    }

    void calculateF () {
        polynomials[0].SetLength(this->maxPolynomial);
        for (long i=0; i<this->maxPolynomial; i++) {
            polynomials[0][i] = this->f(iterationPolynomial[i]);
        }
    }

    void calculateG () {
        polynomials[1].SetLength(this->maxPolynomial);
        for (long i=0; i<this->maxPolynomial; i++) {
            polynomials[1][i] = this->g(iterationPolynomial[i]);
        }
    }

    void calculateWeights () {
        for (long i=0; i<this->FunctionsCount; i++) {
            this->weights[i].kill();
            this->weights[i].SetLength(this->maxPolynomial);
            for (long j=0; j<this->maxPolynomial; j++) {
                this->weights[i][j] = weight(this->polynomials[i][j]);
            }
        }
    }

    void calculateErrorsCoefficients () {
        long tmp;
        Vec<GF2X> currentPolynomial;
        for (long functionNumber=0; functionNumber<FunctionsCount;
                functionNumber++) {
            this->K[functionNumber].kill();
            this->K[functionNumber].SetLength(this->generatorDegree);
            for (long i=0; i<this->generatorDegree; i++) {
                K[functionNumber][i] = 0;
                for (long x=0; x<this->maxPolynomial; x++) {
                    currentPolynomial =
                        this->coordinateFunctions[functionNumber][i];
                    if(currentPolynomial[x] + // plus is xor: F2(+,*)
                            currentPolynomial[x ^ (1<<i)] == 1) {
                        K[functionNumber][i]++;
                    }
                }
            }
        }
    }

    void generateCoordinateFunctions () {
        for (int i=0; i<FunctionsCount; i++) {
            this->coordinateFunctions[i].kill();
            this->coordinateFunctions[i].SetDims(
                    this->generatorDegree, this->maxPolynomial);
            for (int j=0; j<this->generatorDegree; j++) {
                for (int x=0; x<this->maxPolynomial; x++) {
                    this->coordinateFunctions[i][j][x] = // multiplication is
                        (this->polynomials[i][x] >> j) * 1; // and: F2(+,*)
                }
            }
        }
    }

    void init () {
        this->P = GF2XModulus(this->p);
        this->generatorDegree = deg(this->p);
        this->maxPolynomial = 1<<this->generatorDegree;
        //this->generateCoordinateFunctions();
    }

    CryptoSystem () {
    }

    CryptoSystem (const CryptoSystem& cs) {
        this->p = GF2X(cs.p);
        this->N = cs.N;
        this->M = cs.M;
        this->init();
    }

    CryptoSystem (GF2X generator, long N, long M) : p(generator), N(N), M(M) {
        this->init();
    }

    CryptoSystem (unsigned long generator, long N, long M) : N(N), M(M) {
        p = getPolynomial(generator);
        this->init();
    }

    static GF2X getPolynomial (ZZ number) {
        GF2X result(0, 0);
        for (long i=0; i<NumBits(number); i++) {
            if (bit(number,i) == 1) {
                SetCoeff(result,i);
            }
        }
        return result;
    }

    static GF2X getPolynomial (unsigned long number) {
        GF2X result(0, 0);
        for (long i=0; number!=0; i++, number>>=1) {
            if (number&1 == 1) {
                SetCoeff(result,i);
            }
        }
        return result;
    }

};
