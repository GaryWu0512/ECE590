#include <gtest/gtest.h>
#include <elma/elma.h>

#include "measurelambda.h"

using namespace elma;

TEST(TEST,TEST){
    Manager m;
    MeasureLambda ml("add", 1, 2);
    m.schedule(ml, 1_s)
    .init()
    .run(20_s);

    std::cout << ml.min() << ", " << ml.max() << ", " << ml.mean() << "\n";
}