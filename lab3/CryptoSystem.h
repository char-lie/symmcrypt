#include <NTL/GF2X.h>
#include <NTL/matrix.h>
using namespace std;
using namespace NTL;

struct CryptoSystem {
    GF2X p;
    long N;
    long M;
    GF2XModulus P;
    long generatorDegree;
    long maxPolynomial;
    Mat<GF2X> polynomials;
    Mat<long> weights;
    Mat<double> K;

    GF2X f(GF2X x) {
        return PowerMod(x, this->N, this->P);
    }

    GF2X g(GF2X x) {
        return PowerMod(x, this->M, this->P);
    }

    void generateIterationPolynomial () {
        polynomials.kill();
        polynomials.SetDims(this->maxPolynomial, 3);
        for (long i=0; i<this->maxPolynomial; i++) {
            polynomials[i][0] = CryptoSystem::getPolynomial(i);
        }
    }

    void calculateF () {
        for (long i=0; i<this->maxPolynomial; i++) {
            polynomials[i][1] = this->f(polynomials[i][0]);
        }
    }

    void calculateG () {
        for (long i=0; i<this->maxPolynomial; i++) {
            polynomials[i][2] = this->g(polynomials[i][0]);
        }
    }

    void calculateWeights () {
        this->weights.kill();
        this->weights.SetDims(this->maxPolynomial, 2);
        for (long i=0; i<this->maxPolynomial; i++) {
            this->weights[i][0] = weight(this->polynomials[i][1]);
            this->weights[i][1] = weight(this->polynomials[i][2]);
        }
    }

    void calculateErrorsCoefficients () {
        this->K.kill();
        this->K.SetDims(this->generatorDegree, 2);
        GF2X currentPolynomial;
        long summ;
        long tmp;
        for (long functionNumber=0; functionNumber<2; functionNumber++) {
            for (long i=0; i<this->generatorDegree; i++) {
                summ = 0;
                for (long j=0; j<this->maxPolynomial; j++) {
                    tmp = this->weights[functionNumber+1][j];
                    if (((j>>i)^1)&1 == 1) {
                        tmp ^= this->weights[functionNumber+1][1<<i];
                    }
                    summ += tmp&1;
                }
                K[i][functionNumber] = ((double)summ);///this->maxPolynomial;
            }
        }
    }

    void init () {
        this->P = GF2XModulus(this->p);
        this->generatorDegree = deg(this->p);
        this->maxPolynomial = 1<<this->generatorDegree;
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
