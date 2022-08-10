/*
 * ValueInterface.h
 *
 */

#ifndef MATH_VALUEINTERFACE_H_
#define MATH_VALUEINTERFACE_H_

#include "Tools/Exceptions.h"

class OnlineOptions;
class bigint;
class PRNG;

#define BEGIN_INIT_FIELD()  if (1 == init_flag) { return ;} \
                            static std::mutex init_mutex; std::lock_guard<std::mutex> guard(init_mutex); \
                            if (1 == init_flag) { return ;}

#define END_INIT_FIELD()    init_flag = 1;


class ValueInterface
{
public:
    static const int MAX_EDABITS = 0;

    static const false_type characteristic_two;
    static const false_type prime_field;
    static const false_type invertible;
    static const false_type binary;

    template<class T>
    static void init(bool mont = true) { (void) mont; }
    static void init_default(int, bool = true) {}
    static void init_field(const bigint& = {}, bool = true) {}

    static void read_or_generate_setup(const string&, const OnlineOptions&) {}
    template<class T>
    static void generate_setup(string, int, int) {}
    template<class T>
    static void write_setup(int) {}
    static void write_setup(string) {}
    static void check_setup(string) {}

    static bigint pr() { throw runtime_error("no prime modulus"); }

    void normalize() {}

    void randomize_part(PRNG&, int) { throw not_implemented(); }
};

#endif /* MATH_VALUEINTERFACE_H_ */
