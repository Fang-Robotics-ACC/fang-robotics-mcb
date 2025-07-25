#ifndef FANG_ROBOTICS_MCB_WRAP_TRAP_SYSTEM_FANG_ASSERT_HPP
#define FANG_ROBOTICS_MCB_WRAP_TRAP_SYSTEM_FANG_ASSERT_HPP
#include "modm/architecture/interface/assert.hpp"
#include <string>

#ifndef NDEBUG
    /**
     * Pass should be a boolean variable
     * if it's false, then an assert will be triggered
     *  
     * The file
     * NAME and DESC should be 
     * 
     */
    #ifndef PLATFORM_HOSTED
        /**
         * Pass should be a boolean variable
         * if it's false, then an assert will be triggered
         *  
         * The file
         * NAME and DESC should be c style strings
         */
        #define FANG_ASSERT(PASS, NAME, DESC)                                               \
            {                                                                               \
                const std::string FANG_ASSERT_FILE{__FILE__};                               \
                const std::string FANG_ASSERT_LINE{"Line " + std::to_string(__LINE__)};     \
                const std::string DESCRIPTION                                               \
                {                                                                           \
                    FANG_ASSERT_FILE +                                                      \
                    " : " + FANG_ASSERT_LINE +                                              \
                    " : " + DESC                                                            \
                };                                                                          \
                modm_assert(PASS, NAME, DESCRIPTION.c_str());                               \
            }
        #else
            /**
             * Pass should be a boolean variable
             * if it's false, then an assert will be triggered
             *  
             * The file
             * NAME and DESC should be c style strings
             */
            #define FANG_ASSERT(PASS, NAME, DESC)                   \
            {                                                       \
                std::string name{NAME};                             \
                assert(PASS && DESC);                               \
            }
        #endif
    #endif
#endif