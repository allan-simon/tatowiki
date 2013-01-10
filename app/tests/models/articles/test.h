#ifndef TATOWIKI_TESTS_MODELS_ARTICLES_H
#define TATOWIKI_TESTS_MODELS_ARTICLES_H


#define TEST_RESULT_SHOULD_WORK()  \
    if (result == 1) {\
        std::cout << "[fail]" << std::endl;\
    } else {\
        std::cout << "[ok]" << std::endl;\
    }

#define TEST_RESULT_SHOULD_NOT_WORK()  \
    if (result == 1) {\
        std::cout << "[fail]" << std::endl;\
    } else {\
        std::cout << "[ok]" << std::endl;\
    }



#endif 
