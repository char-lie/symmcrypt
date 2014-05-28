#pragma once

#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#include <NTL/vector.h>
#include "BinaryFunction.h"
using namespace std;
using namespace NTL;

struct CryptoSystem {
    static const long FUNCTIONS_COUNT = 2;
    BinaryFunction binaryFunctions[FUNCTIONS_COUNT];
    GF2X p;
    long N;
    long M;
    GF2XModulus P;
    long generatorDegree;
    long maxPolynomial;
    Vec<GF2X> iterationPolynomial;

    Vec<GF2X> polynomials[FUNCTIONS_COUNT];
    Mat<GF2> vectorValuedFunctions[FUNCTIONS_COUNT];
    Vec<long> weights[FUNCTIONS_COUNT];

    Vec<long> K[FUNCTIONS_COUNT];

    GF2X f(const GF2X& x) {
        return PowerMod(x, this->N, this->P);
    }

    GF2X g(const GF2X& x) {
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
        this->polynomials[0] = *(this->binaryFunctions[0].initPolynomials(
                this->iterationPolynomial));
    }

    void calculateG () {
        this->polynomials[1] = *(this->binaryFunctions[1].initPolynomials(
                this->iterationPolynomial));
    }

    void calculateWeights () {
        for (long functionNumber=0; functionNumber<this->FUNCTIONS_COUNT;
                functionNumber++) {
            this->weights[functionNumber] = *(this->
                    binaryFunctions[functionNumber].calculateWeights());
        }
    }

    void calculateErrorsCoefficients () {
        for (long functionNumber=0; functionNumber<FUNCTIONS_COUNT;
                functionNumber++) {
            this->K[functionNumber] = *(this->
                binaryFunctions[functionNumber].calculateErrorsCoefficients());
        }
    }

    void generateVectorValuedFunctions () {
        for (int functionNumber=0; functionNumber<FUNCTIONS_COUNT;
                functionNumber++) {
            this->vectorValuedFunctions[functionNumber] = *(this->
                    binaryFunctions[functionNumber].
                    generateVectorValuedFunctions());
        }
    }

    void init () {
        this->P = GF2XModulus(this->p);
        this->generatorDegree = deg(this->p);
        this->maxPolynomial = 1<<this->generatorDegree;
        this->binaryFunctions[0].init(p, this->N);
        this->binaryFunctions[1].init(p, this->M);
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

    CryptoSystem (const GF2X& generator, long N, long M)
            : p(generator), N(N), M(M) {
        this->init();
    }

    CryptoSystem (unsigned long generator, long N, long M) : N(N), M(M) {
        p = getPolynomial(generator);
        this->init();
    }

    static GF2X getPolynomial (const ZZ& number) {
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
            if ((number&1) == 1) {
                SetCoeff(result,i);
            }
        }
        return result;
    }

};
