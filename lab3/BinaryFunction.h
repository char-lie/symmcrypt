#pragma once

#include <NTL/GF2X.h>
#include <NTL/matrix.h>
#include <NTL/vector.h>
#include "sizes.h"
using namespace std;
using namespace NTL;

struct BinaryFunction {
    Vec<GF2X> polynomials;

    GF2X generator;
    long power;
    GF2XModulus modulus;

    Mat<GF2> vectorValuedFunctions;
    Mat<long> longVectorValuedFunctions;
    Vec<long> disbalances;
    Vec<long> errorsCoefficients;
    Mat<long> fourierCoefficients;
    Mat<long> walshCoefficients;

    long generatorDegree;
    long polynomialsNumber;
    
    long c2n; // 2^n
    long c2n1; // 2^(n+1)

    GF2X getValue (const GF2X& x) {
        return PowerMod(x, this->power, this->modulus);
    }

    Vec<GF2X>* initPolynomials (const Vec<GF2X>& iterator) {
        polynomials.SetLength(this->polynomialsNumber);
        for (long i = 0; i < this->polynomialsNumber; i++) {
            polynomials[i] = this->getValue(iterator[i]);
        }
        return &(this->polynomials);
    }

    Mat<GF2>* generateVectorValuedFunctions () {
        this->vectorValuedFunctions.kill();
        this->vectorValuedFunctions.SetDims(this->generatorDegree,
                this->polynomialsNumber);
        for (int i = 0; i < this->generatorDegree; i++) {
            for (int x = 0; x<this->polynomialsNumber; x++) {
                this->vectorValuedFunctions[i][x] = 
                    coeff(this->polynomials[x], i);
                // Using safe function coeff, because degree
                // of the polynomial can be less than i and
                // operator[](i) will cause Index Out Of Bounds error
            }
        }
        return &(this->vectorValuedFunctions);
    }

    Mat<long>* generateLongVectorValuedFunctions () {
        this->longVectorValuedFunctions.kill();
        this->longVectorValuedFunctions.SetDims(this->generatorDegree,
                this->polynomialsNumber);
        for (int i = 0; i < this->generatorDegree; i++) {
            for (int x = 0; x<this->polynomialsNumber; x++) {
                this->longVectorValuedFunctions[i][x] = 
                    rep(this->vectorValuedFunctions[i][x]);
            }
        }
        return &(this->longVectorValuedFunctions);
    }

    Vec<long>* calculateDisbalances () {
        this->disbalances.kill();
        this->disbalances.SetLength(this->generatorDegree);
        for (long i = 0; i < this->generatorDegree; i++) {
            this->disbalances[i] = polynomialsNumber/2;
            for (long j = 0; j<polynomialsNumber; j++) {
                this->disbalances[i] -= this->longVectorValuedFunctions[i][j];
            }
        }
        return &(this->disbalances);
    }

    Vec<long>* calculateErrorsCoefficients () {
        this->errorsCoefficients.kill();
        this->errorsCoefficients.SetLength(this->generatorDegree);
        for (long i = 0; i < this->generatorDegree; i++) {
            errorsCoefficients[i] = 0;
            for (long x = 0; x<this->polynomialsNumber; x++) {
                errorsCoefficients[i] += this->longVectorValuedFunctions[i][x] +
                        this->longVectorValuedFunctions[i][x ^ (1 << i)];
            }
        }
        return &(this->errorsCoefficients);
    }

    long calculateWalshIteration (const long functionNumber, const long a) {
        long result = 0;
        for (long x = 0; x < polynomialsNumber; x++) {
            result += SIZES[a&x] ^
                this->longVectorValuedFunctions[functionNumber][x];
        }
        result = polynomialsNumber - 2 * result;
        return result;
    }

    // Should be lambda in calculateFourierCoefficients :(
    void calculateFourierCoefficientsRecursive (long *previousStep, long size) {
        if (size == 1) {
            return;
        }
        else {
            long i, j, tmp;
            size >>= 1;
            for (i = 0, j = size; i < size; i++, j++) {
                tmp = previousStep[i];
                previousStep[i] += previousStep[j];
                previousStep[j] = tmp - previousStep[j];
            }
            calculateFourierCoefficientsRecursive(&previousStep[0], size);
            calculateFourierCoefficientsRecursive(&previousStep[size], size);
            return;
        }
    }

    void calculateFourierCoefficients (const long functionNumber,
            const long a, long *longFourierCoefficients) {
        long x;
        for (x = 0; x < this->polynomialsNumber; x++) {
            longFourierCoefficients[x] =
                this->longVectorValuedFunctions[functionNumber][x];
        }
        calculateFourierCoefficientsRecursive(longFourierCoefficients,
                this->polynomialsNumber);
        for (x = 0; x < this->polynomialsNumber; x++) {
            this->fourierCoefficients[functionNumber][x] =
                longFourierCoefficients[x];
        }
    }

    long calculateWalshFromFourie (const long fourierCoefficient,
            const long a) {
        long result = - this->c2n1 * fourierCoefficient;
        if (a == 0) {
            result += this->c2n;
        }
        return result;
    }

    Mat<long>* calculateWalsh () {
        this->walshCoefficients.kill();
        this->walshCoefficients.SetDims(generatorDegree, polynomialsNumber);
        this->fourierCoefficients.kill();
        this->fourierCoefficients.SetDims(generatorDegree, polynomialsNumber);
        long tmp, a, x;
        long *longFourierCoefficients = new long[this->polynomialsNumber];
        for (long functionNumber = 0; functionNumber<generatorDegree;
                functionNumber++) {
            LOG("functionNumber: " << functionNumber);
            for (a = 0; a<polynomialsNumber; a++) {
                /*
                // VERY SLOW
                calculateFourierCoefficients(functionNumber, a,
                        longFourierCoefficients);
                    */
                this->walshCoefficients[functionNumber][a] = 
                    calculateWalshIteration(functionNumber, a);
            }
        }
        return &(this->walshCoefficients);
    }

    void init () {
        this->modulus = GF2XModulus(this->generator);
        this->generatorDegree = deg(this->generator);
        this->polynomialsNumber = 1 << this->generatorDegree;
        this->c2n = 1 << this->generatorDegree;
        this->c2n1 = this->c2n << 1;
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
