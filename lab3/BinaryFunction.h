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
    Vec<long> disbalances;
    Vec<long> errorsCoefficients;
    Vec<long> walshCoefficients;

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

    Mat<GF2>* generateVectorValuedFunctions () {
        this->vectorValuedFunctions.kill();
        this->vectorValuedFunctions.SetDims(this->generatorDegree,
                this->polynomialsNumber);
        for (int i=0; i<this->generatorDegree; i++) {
            for (int x=0; x<this->polynomialsNumber; x++) {
                this->vectorValuedFunctions[i][x] =
                    coeff(this->polynomials[x], i);
                // Using safe function coeff, because degree
                // of the polynomial can be less than i and
                // operator[](i) will cause Index Out Of Bounds error
            }
        }
        return &(this->vectorValuedFunctions);
    }

    Vec<long>* calculateDisbalances () {
        this->disbalances.kill();
        this->disbalances.SetLength(this->generatorDegree);
        for (long i=0; i<this->generatorDegree; i++) {
            this->disbalances[i] = polynomialsNumber/2;
            for (long j=0; j<polynomialsNumber; j++) {
                this->disbalances[i] -= rep(this->
                        vectorValuedFunctions[i][j]);
            }
        }
        return &(this->disbalances);
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

    long scalarMultiplication (long a, long b) {
        long result = a&b;
        const long parity = 0x6996;
        /*
        while (result>1) {
            result ^= (result & 1);
            result >>= 1;
        }
        */
        return (((parity >> (result & 0x0f)) ^ (parity >> (result >> 4))) ^
            ((parity >> ((result>>8) & 0x0f)) ^ (parity >> ((result>>8) >> 4))) ^
            ((parity >> ((result>>16) & 0x0f)) ^ (parity >> ((result>>32) >> 4))) ^
            ((parity >> ((result>>24) & 0x0f)) ^ (parity >> ((result>>24) >> 4))))
                & 0x01;
    }

    long calculateWalshIteration (long functionNumber, long a) {
        long result = 0;
        for (long x=0; x<polynomialsNumber; x++) {
            result += 1 - 2 * (scalarMultiplication(a,x) ^
                rep(this->vectorValuedFunctions[functionNumber][x]));
        }
        return result;
    }

    Vec<long>* calculateWalsh () {
        this->walshCoefficients.kill();
        this->walshCoefficients.SetLength(generatorDegree);
        for (long functionNumber=0; functionNumber<generatorDegree;
                functionNumber++) {
            LOG("f: "<<functionNumber);
            this->walshCoefficients[functionNumber] = 0;
            for (long a=0; a<polynomialsNumber; a++) {
                this->walshCoefficients[functionNumber] +=
                    calculateWalshIteration(functionNumber, a);
                if (a%1000 == 0) {
                    LOG("a: "<<a);
                }
            }
        }
        return &(this->walshCoefficients);
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
