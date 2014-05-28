#pragma once

#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#include <NTL/vector.h>
using namespace std;
using namespace NTL;

struct BinaryFunction {
    Vec<GF2X> polynomials;

    GF2X generator;
    long power;
    GF2XModulus modulus;

    Mat<GF2> vectorValuedFunctions;
    Vec<long> weights;
    Vec<long> errorsCoefficients;

    long generatorDegree;
    long polynomialsNumber;

    GF2X getValue (const GF2X& x) {
        return PowerMod(x, this->power, this->modulus);
    }

    Vec<GF2X>* initPolynomials (const Vec<GF2X>& iterator) {
        polynomials.SetLength(this->polynomialsNumber);
        for (long i=0; i<this->polynomialsNumber; i++) {
            polynomials[i] = this->getValue(iterator[i]);
        }
        return &(this->polynomials);
    }

    Vec<long>* calculateWeights () {
        this->weights.kill();
        this->weights.SetLength(this->polynomialsNumber);
        for (long j=0; j<this->polynomialsNumber; j++) {
            this->weights[j] = weight(this->polynomials[j]);
        }
        return &(this->weights);
    }

    Vec<long>* calculateErrorsCoefficients () {
        this->errorsCoefficients.kill();
        this->errorsCoefficients.SetLength(this->generatorDegree);
        for (long i=0; i<this->generatorDegree; i++) {
            errorsCoefficients[i] = 0;
            for (long x=0; x<this->polynomialsNumber; x++) {
                errorsCoefficients[i] += rep(this->vectorValuedFunctions[i][x] +
                        this->vectorValuedFunctions[i][x ^ (1<<i)]);
            }
        }
        return &(this->errorsCoefficients);
    }

    Mat<GF2>* generateVectorValuedFunctions () {
        this->vectorValuedFunctions.kill();
        this->vectorValuedFunctions.SetDims(this->generatorDegree,
                this->polynomialsNumber);
        for (int j=0; j<this->generatorDegree; j++) {
            for (int x=0; x<this->polynomialsNumber; x++) {
                this->vectorValuedFunctions[j][x] =
                    coeff(this->polynomials[x], j);
                // Using safe function coeff, because degree
                // of the polynomial can be less than j and
                // operator[](j) will cause Index Out Of Bounds error
            }
        }
        return &(this->vectorValuedFunctions);
    }

    void init () {
        this->modulus = GF2XModulus(this->generator);
        this->generatorDegree = deg(this->generator);
        this->polynomialsNumber = 1<<this->generatorDegree;
    }

    void init (const GF2X& generator, long power) {
        this->generator = generator;
        this->power = power;
        this->init();
    }

    BinaryFunction () {
    }

    BinaryFunction (const GF2X& generator, long power)
        : generator(generator), power(power) {
        this->init();
    }

};
