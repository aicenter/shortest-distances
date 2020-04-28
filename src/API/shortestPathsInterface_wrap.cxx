/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */


#ifndef SWIGJAVA
#define SWIGJAVA
#endif



#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
    struct SwigMovePointer {
        T *ptr;
        SwigMovePointer(T *p) : ptr(p) { }
        ~SwigMovePointer() { delete ptr; }
        SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
    } pointer;
    SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
    SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
    SwigValueWrapper() : pointer(0) { }
    SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
    operator T&() const { return *pointer.ptr; }
    T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
    return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif


/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
    SWIG_JavaOutOfMemoryError = 1,
    SWIG_JavaIOException,
    SWIG_JavaRuntimeException,
    SWIG_JavaIndexOutOfBoundsException,
    SWIG_JavaArithmeticException,
    SWIG_JavaIllegalArgumentException,
    SWIG_JavaNullPointerException,
    SWIG_JavaDirectorPureVirtual,
    SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
    SWIG_JavaExceptionCodes code;
    const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
    jclass excep;
    static const SWIG_JavaExceptions_t java_exceptions[] = {
            { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
            { SWIG_JavaIOException, "java/io/IOException" },
            { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
            { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
            { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
            { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
            { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
            { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
            { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
            { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" }
    };
    const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

    while (except_ptr->code != code && except_ptr->code)
        except_ptr++;

    jenv->ExceptionClear();
    excep = jenv->FindClass(except_ptr->java_exception);
    if (excep)
        jenv->ThrowNew(excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else


#include <string>


/* Includes the header in the wrapper code */
#include "CHDistanceQueryManagerAPI.h"



/* Includes the header in the wrapper code */
#include "TNRDistanceQueryManagerAPI.h"



/* Includes the header in the wrapper code */
#include "TNRAFDistanceQueryManagerAPI.h"



#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_CHDistanceQueryManagerAPI_1initializeCH(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jstring jarg3) {
    CHDistanceQueryManagerAPI *arg1 = (CHDistanceQueryManagerAPI *) 0 ;
    std::string arg2 ;
    std::string arg3 ;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(CHDistanceQueryManagerAPI **)&jarg1;
    if(!jarg2) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
        return ;
    }
    const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2_pstr) return ;
    (&arg2)->assign(arg2_pstr);
    jenv->ReleaseStringUTFChars(jarg2, arg2_pstr);
    if(!jarg3) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
        return ;
    }
    const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3_pstr) return ;
    (&arg3)->assign(arg3_pstr);
    jenv->ReleaseStringUTFChars(jarg3, arg3_pstr);
    (arg1)->initializeCH(arg2,arg3);
}


SWIGEXPORT jlong JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_CHDistanceQueryManagerAPI_1distanceQuery(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobject jarg2, jobject jarg3) {
    jlong jresult = 0 ;
    CHDistanceQueryManagerAPI *arg1 = (CHDistanceQueryManagerAPI *) 0 ;
    unsigned long long arg2 ;
    unsigned long long arg3 ;
    unsigned int result;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(CHDistanceQueryManagerAPI **)&jarg1;
    {
        jclass clazz;
        jmethodID mid;
        jbyteArray ba;
        jbyte* bae;
        jsize sz;
        int i;

        if (!jarg2) {
            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "BigInteger null");
            return 0;
        }
        clazz = jenv->GetObjectClass(jarg2);
        mid = jenv->GetMethodID(clazz, "toByteArray", "()[B");
        ba = (jbyteArray)jenv->CallObjectMethod(jarg2, mid);
        bae = jenv->GetByteArrayElements(ba, 0);
        sz = jenv->GetArrayLength(ba);
        arg2 = 0;
        for(i=0; i<sz; i++) {
            arg2 = (arg2 << 8) | (unsigned long long)(unsigned char)bae[i];
        }
        jenv->ReleaseByteArrayElements(ba, bae, 0);
    }
    {
        jclass clazz;
        jmethodID mid;
        jbyteArray ba;
        jbyte* bae;
        jsize sz;
        int i;

        if (!jarg3) {
            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "BigInteger null");
            return 0;
        }
        clazz = jenv->GetObjectClass(jarg3);
        mid = jenv->GetMethodID(clazz, "toByteArray", "()[B");
        ba = (jbyteArray)jenv->CallObjectMethod(jarg3, mid);
        bae = jenv->GetByteArrayElements(ba, 0);
        sz = jenv->GetArrayLength(ba);
        arg3 = 0;
        for(i=0; i<sz; i++) {
            arg3 = (arg3 << 8) | (unsigned long long)(unsigned char)bae[i];
        }
        jenv->ReleaseByteArrayElements(ba, bae, 0);
    }
    result = (unsigned int)(arg1)->distanceQuery(arg2,arg3);
    jresult = (jlong)result;
    return jresult;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_CHDistanceQueryManagerAPI_1clearStructures(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
    CHDistanceQueryManagerAPI *arg1 = (CHDistanceQueryManagerAPI *) 0 ;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(CHDistanceQueryManagerAPI **)&jarg1;
    (arg1)->clearStructures();
}


SWIGEXPORT jlong JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_new_1CHDistanceQueryManagerAPI(JNIEnv *jenv, jclass jcls) {
    jlong jresult = 0 ;
    CHDistanceQueryManagerAPI *result = 0 ;

    (void)jenv;
    (void)jcls;
    result = (CHDistanceQueryManagerAPI *)new CHDistanceQueryManagerAPI();
    *(CHDistanceQueryManagerAPI **)&jresult = result;
    return jresult;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_delete_1CHDistanceQueryManagerAPI(JNIEnv *jenv, jclass jcls, jlong jarg1) {
    CHDistanceQueryManagerAPI *arg1 = (CHDistanceQueryManagerAPI *) 0 ;

    (void)jenv;
    (void)jcls;
    arg1 = *(CHDistanceQueryManagerAPI **)&jarg1;
    delete arg1;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_TNRDistanceQueryManagerAPI_1initializeTNR(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jstring jarg3) {
    TNRDistanceQueryManagerAPI *arg1 = (TNRDistanceQueryManagerAPI *) 0 ;
    std::string arg2 ;
    std::string arg3 ;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(TNRDistanceQueryManagerAPI **)&jarg1;
    if(!jarg2) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
        return ;
    }
    const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2_pstr) return ;
    (&arg2)->assign(arg2_pstr);
    jenv->ReleaseStringUTFChars(jarg2, arg2_pstr);
    if(!jarg3) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
        return ;
    }
    const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3_pstr) return ;
    (&arg3)->assign(arg3_pstr);
    jenv->ReleaseStringUTFChars(jarg3, arg3_pstr);
    (arg1)->initializeTNR(arg2,arg3);
}


SWIGEXPORT jlong JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_TNRDistanceQueryManagerAPI_1distanceQuery(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobject jarg2, jobject jarg3) {
    jlong jresult = 0 ;
    TNRDistanceQueryManagerAPI *arg1 = (TNRDistanceQueryManagerAPI *) 0 ;
    unsigned long long arg2 ;
    unsigned long long arg3 ;
    unsigned int result;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(TNRDistanceQueryManagerAPI **)&jarg1;
    {
        jclass clazz;
        jmethodID mid;
        jbyteArray ba;
        jbyte* bae;
        jsize sz;
        int i;

        if (!jarg2) {
            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "BigInteger null");
            return 0;
        }
        clazz = jenv->GetObjectClass(jarg2);
        mid = jenv->GetMethodID(clazz, "toByteArray", "()[B");
        ba = (jbyteArray)jenv->CallObjectMethod(jarg2, mid);
        bae = jenv->GetByteArrayElements(ba, 0);
        sz = jenv->GetArrayLength(ba);
        arg2 = 0;
        for(i=0; i<sz; i++) {
            arg2 = (arg2 << 8) | (unsigned long long)(unsigned char)bae[i];
        }
        jenv->ReleaseByteArrayElements(ba, bae, 0);
    }
    {
        jclass clazz;
        jmethodID mid;
        jbyteArray ba;
        jbyte* bae;
        jsize sz;
        int i;

        if (!jarg3) {
            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "BigInteger null");
            return 0;
        }
        clazz = jenv->GetObjectClass(jarg3);
        mid = jenv->GetMethodID(clazz, "toByteArray", "()[B");
        ba = (jbyteArray)jenv->CallObjectMethod(jarg3, mid);
        bae = jenv->GetByteArrayElements(ba, 0);
        sz = jenv->GetArrayLength(ba);
        arg3 = 0;
        for(i=0; i<sz; i++) {
            arg3 = (arg3 << 8) | (unsigned long long)(unsigned char)bae[i];
        }
        jenv->ReleaseByteArrayElements(ba, bae, 0);
    }
    result = (unsigned int)(arg1)->distanceQuery(arg2,arg3);
    jresult = (jlong)result;
    return jresult;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_TNRDistanceQueryManagerAPI_1clearStructures(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
    TNRDistanceQueryManagerAPI *arg1 = (TNRDistanceQueryManagerAPI *) 0 ;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(TNRDistanceQueryManagerAPI **)&jarg1;
    (arg1)->clearStructures();
}


SWIGEXPORT jlong JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_new_1TNRDistanceQueryManagerAPI(JNIEnv *jenv, jclass jcls) {
    jlong jresult = 0 ;
    TNRDistanceQueryManagerAPI *result = 0 ;

    (void)jenv;
    (void)jcls;
    result = (TNRDistanceQueryManagerAPI *)new TNRDistanceQueryManagerAPI();
    *(TNRDistanceQueryManagerAPI **)&jresult = result;
    return jresult;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_delete_1TNRDistanceQueryManagerAPI(JNIEnv *jenv, jclass jcls, jlong jarg1) {
    TNRDistanceQueryManagerAPI *arg1 = (TNRDistanceQueryManagerAPI *) 0 ;

    (void)jenv;
    (void)jcls;
    arg1 = *(TNRDistanceQueryManagerAPI **)&jarg1;
    delete arg1;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_TNRAFDistanceQueryManagerAPI_1initializeTNRAF(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jstring jarg3) {
    TNRAFDistanceQueryManagerAPI *arg1 = (TNRAFDistanceQueryManagerAPI *) 0 ;
    std::string arg2 ;
    std::string arg3 ;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(TNRAFDistanceQueryManagerAPI **)&jarg1;
    if(!jarg2) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
        return ;
    }
    const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2_pstr) return ;
    (&arg2)->assign(arg2_pstr);
    jenv->ReleaseStringUTFChars(jarg2, arg2_pstr);
    if(!jarg3) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
        return ;
    }
    const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3_pstr) return ;
    (&arg3)->assign(arg3_pstr);
    jenv->ReleaseStringUTFChars(jarg3, arg3_pstr);
    (arg1)->initializeTNRAF(arg2,arg3);
}


SWIGEXPORT jlong JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_TNRAFDistanceQueryManagerAPI_1distanceQuery(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobject jarg2, jobject jarg3) {
    jlong jresult = 0 ;
    TNRAFDistanceQueryManagerAPI *arg1 = (TNRAFDistanceQueryManagerAPI *) 0 ;
    unsigned long long arg2 ;
    unsigned long long arg3 ;
    unsigned int result;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(TNRAFDistanceQueryManagerAPI **)&jarg1;
    {
        jclass clazz;
        jmethodID mid;
        jbyteArray ba;
        jbyte* bae;
        jsize sz;
        int i;

        if (!jarg2) {
            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "BigInteger null");
            return 0;
        }
        clazz = jenv->GetObjectClass(jarg2);
        mid = jenv->GetMethodID(clazz, "toByteArray", "()[B");
        ba = (jbyteArray)jenv->CallObjectMethod(jarg2, mid);
        bae = jenv->GetByteArrayElements(ba, 0);
        sz = jenv->GetArrayLength(ba);
        arg2 = 0;
        for(i=0; i<sz; i++) {
            arg2 = (arg2 << 8) | (unsigned long long)(unsigned char)bae[i];
        }
        jenv->ReleaseByteArrayElements(ba, bae, 0);
    }
    {
        jclass clazz;
        jmethodID mid;
        jbyteArray ba;
        jbyte* bae;
        jsize sz;
        int i;

        if (!jarg3) {
            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "BigInteger null");
            return 0;
        }
        clazz = jenv->GetObjectClass(jarg3);
        mid = jenv->GetMethodID(clazz, "toByteArray", "()[B");
        ba = (jbyteArray)jenv->CallObjectMethod(jarg3, mid);
        bae = jenv->GetByteArrayElements(ba, 0);
        sz = jenv->GetArrayLength(ba);
        arg3 = 0;
        for(i=0; i<sz; i++) {
            arg3 = (arg3 << 8) | (unsigned long long)(unsigned char)bae[i];
        }
        jenv->ReleaseByteArrayElements(ba, bae, 0);
    }
    result = (unsigned int)(arg1)->distanceQuery(arg2,arg3);
    jresult = (jlong)result;
    return jresult;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_TNRAFDistanceQueryManagerAPI_1clearStructures(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
    TNRAFDistanceQueryManagerAPI *arg1 = (TNRAFDistanceQueryManagerAPI *) 0 ;

    (void)jenv;
    (void)jcls;
    (void)jarg1_;
    arg1 = *(TNRAFDistanceQueryManagerAPI **)&jarg1;
    (arg1)->clearStructures();
}


SWIGEXPORT jlong JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_new_1TNRAFDistanceQueryManagerAPI(JNIEnv *jenv, jclass jcls) {
    jlong jresult = 0 ;
    TNRAFDistanceQueryManagerAPI *result = 0 ;

    (void)jenv;
    (void)jcls;
    result = (TNRAFDistanceQueryManagerAPI *)new TNRAFDistanceQueryManagerAPI();
    *(TNRAFDistanceQueryManagerAPI **)&jresult = result;
    return jresult;
}


SWIGEXPORT void JNICALL Java_cz_cvut_fel_aic_shortestpaths_shortestPathsJNI_delete_1TNRAFDistanceQueryManagerAPI(JNIEnv *jenv, jclass jcls, jlong jarg1) {
    TNRAFDistanceQueryManagerAPI *arg1 = (TNRAFDistanceQueryManagerAPI *) 0 ;

    (void)jenv;
    (void)jcls;
    arg1 = *(TNRAFDistanceQueryManagerAPI **)&jarg1;
    delete arg1;
}


#ifdef __cplusplus
}
#endif

