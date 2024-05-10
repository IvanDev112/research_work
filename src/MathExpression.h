#ifndef MATH_EXPRESSION_H_
#define MATH_EXPRESSION_H_

#include <string>
#include <ctime>
#include <cstdlib>

class MathExpression {
public:
    MathExpression() {}
    void Generate() {
        // Set random seed for generating random numbers
        srand(time(nullptr));

        // Generate random numbers between 0 and 100 (for addition and subtraction)
        mA = rand() % 100;
        mB = rand() % 100;

        int option = rand() % 4;
        switch (option) {
        case 0:
            mOp = '+';
            mAnswer = mA + mB;
            break;
        case 1:
            mOp = '-';
            mAnswer = mA - mB;
            break;
        case 2:
            // Generate random numbers between 0 and 10 to not make the expression too difficult to calculate
            mOp = '*';
            mA = rand() % 10;
            mB = rand() % 10;
            mAnswer = mA * mB;
            break;
        case 3:
            mOp = '/';
            do {
                mA = rand() % 10;
                mB = rand() % 10;
            } while (mB == 0 || mA % mB != 0); // Do while b is not zero and a is divisible by b
            mAnswer = mA / mB;
            break;
        }
    }

    std::string GetExpression() {
        return std::to_string(mA) + " " + mOp + " " + std::to_string(mB) + " = ?";
    }

    bool CheckAnswer(int answer) {
        return answer == mAnswer;
    }
private:
    int mA, mB;
    char mOp;
    int mAnswer;
};

#endif // MATH_EXPRESSION_H_
