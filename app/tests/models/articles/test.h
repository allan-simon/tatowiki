#ifndef TATOWIKI_TESTS_MODELS_ARTICLES_H
#define TATOWIKI_TESTS_MODELS_ARTICLES_H


#define TEST_RESULT_SHOULD_WORK(MESSAGE,FUNCTION_CALL,NO_FAILED)  \
    {\
        std::cout << MESSAGE;\
        int result = FUNCTION_CALL;\
        if (result == 1) {\
            NO_FAILED = false;\
            std::cout << "[fail]" << std::endl;\
        } else {\
            std::cout << "[ok]" << std::endl;\
        }\
    }

#define TEST_RESULT_SHOULD_NOT_WORK(MESSAGE,FUNCTION_CALL,NO_FAILED)  \
    {\
        std::cout << MESSAGE;\
        int result = FUNCTION_CALL;\
        if (result == 0) {\
            NO_FAILED = false;\
            std::cout << "[fail]" << std::endl;\
        } else {\
            std::cout << "[ok]" << std::endl;\
        }\
    }\



#endif 
